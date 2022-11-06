#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
//Importacion de headers propios
#include "Jugador.h"
#include "Ajustes.h"
#include "Bala.h"
#include "Enemigos.h"
#include "Colisiones.h"
#include "Estadisticas.h"
#include "Menu.h"
//********Creacion variables del juego
#define FPS 60.0



//*******Funciones de juego

void RecibirTeclasPresionadas(ALLEGRO_EVENT evento, Jugador& jugador, std::vector<PtrBala>& Balas) {
	switch (evento.keyboard.keycode) {
	case ALLEGRO_KEY_RIGHT:
		jugador.rotacion_derecha = true;
		break;
	case ALLEGRO_KEY_LEFT:
		jugador.rotacion_izquierda = true;
		break;
	case ALLEGRO_KEY_UP:
		jugador.acelerando = true;
		break;
	case ALLEGRO_KEY_SPACE:
		CrearBala(jugador, Balas);

		break;
	}
}

void RecibirTeclasLevantadas(ALLEGRO_EVENT evento, Jugador& jugador) {
	switch (evento.keyboard.keycode) {
	case ALLEGRO_KEY_RIGHT:
		jugador.rotacion_derecha = false;
		break;
	case ALLEGRO_KEY_LEFT:
		jugador.rotacion_izquierda = false;
		break;
	case ALLEGRO_KEY_UP:
		jugador.acelerando = false;
		break;
	}
}



void Guardarestadisticas(Estadisticas &stats) {
	FILE* archivo = NULL;
	fopen_s(&archivo, "MejorPuntaje.txt", "w+");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo.");
		return;
	}
	else {
		fprintf(archivo, "%d\n", stats.meteoritos_destruidos);
		
	}
	fclose(archivo);
}

void CargarMejorPuntaje(Estadisticas &stats) {

	FILE* archivo;
	fopen_s(&archivo, "MejorPuntaje.txt", "r+");
	if (NULL == archivo) {
		stats.mejor_puntaje = 0;
		return;
	}
	else {

		while (!feof(archivo)) {
			
			fscanf_s(archivo, "%i\n", &stats.mejor_puntaje);

		}
	}
	fclose(archivo);

	cout << stats.mejor_puntaje << endl;
}


int main() {
	if (!al_init()) {
		return -1;
	}

	srand(time(0));


	//*********Inicializacion de los addons de allegro
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(7);
	al_install_mouse();

	//*********Creacion de estructuras de Allegro
	ALLEGRO_DISPLAY* display = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);
	al_set_window_title(display, "Galaroid");
	ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1 / FPS);

	ALLEGRO_FONT* gameFont = nullptr;
	ALLEGRO_FONT* fuente2 = nullptr;
	ALLEGRO_FONT* fuente3 = nullptr;
	gameFont = al_load_font("pixel.ttf", 40, NULL);
	fuente2 = al_load_font("pixel.ttf", 100, NULL);
	fuente3 = al_load_font("pixel.ttf", 60, NULL);


	//************************************Registro de eventos en la cola de eventos
	al_register_event_source(cola_eventos, al_get_display_event_source(display));
	al_register_event_source(cola_eventos, al_get_timer_event_source(timer));
	al_register_event_source(cola_eventos, al_get_keyboard_event_source());
	al_register_event_source(cola_eventos, al_get_mouse_event_source());


	//*************************************Subida de imagenes para el juego
	ALLEGRO_BITMAP* ImagenJugador = al_load_bitmap("Assets/Nave_Jugador.png");
	ALLEGRO_BITMAP* ImagenBala = al_load_bitmap("Assets/BALAA.png");
	ALLEGRO_BITMAP* ImagenAsteroide = al_load_bitmap("Assets/Asteroide.png");
	ALLEGRO_BITMAP* Fondo = al_load_bitmap("Assets/Fondo.jpg");
	ALLEGRO_BITMAP* Fondomenu = al_load_bitmap("Assets/FondoMenu.png");
	ALLEGRO_BITMAP* Explosion = al_load_bitmap("Assets/Explosionmeteorito.gif");


	//Inicializar Jugador
	Jugador jugador;
	jugador.acelerando = false;
	jugador.rotacion_derecha = false;
	jugador.rotacion_izquierda = false;
	jugador.velocidad = 0.5;
	jugador.X = ANCHO_PANTALLA / 2;
	jugador.Y = ALTO_PANTALLA / 2;
	jugador.vivo = true;
	jugador.angulo = 0;
	jugador.dx = 0;
	jugador.dy = 0;
	//Bala************************************************

	//***********************Creacion de estructuras y declaracion de variables
	std::vector<PtrBala> Balas;
	std::vector<PtrEnemigo> Enemigos;
	Estadisticas stats;
	int mousex = 0;
	int mousey = 0;
	bool menuactivo = true;

	CargarMejorPuntaje(stats);



	//Se inicia el timer
	al_start_timer(timer);

	//While para el menu del juego
	while (menuactivo) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(cola_eventos, &Evento);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(Fondo, 0, 0, 0);
		al_draw_textf(fuente2, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2.0, ALTO_PANTALLA / 5.0, ALLEGRO_ALIGN_CENTER, "Galaroid");
		al_draw_textf(fuente3, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2.0, (ALTO_PANTALLA / 5.0) * 2, ALLEGRO_ALIGN_CENTER, "Jugar");
		al_draw_textf(fuente3, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2.0, (ALTO_PANTALLA / 6.0) * 3, ALLEGRO_ALIGN_CENTER, "Instrucciones");
		al_draw_textf(fuente3, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2.0, (ALTO_PANTALLA / 6.0) * 4, ALLEGRO_ALIGN_CENTER, "Salir");
		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mousex = Evento.mouse.x;
			mousey = Evento.mouse.y;
		}
		if ((mousex >= 697) && (mousex <= 801) && (mousey >= 373) && (mousey <= 409)) {
			al_draw_textf(fuente3, al_map_rgb(255, 255, 20), ANCHO_PANTALLA / 2.0, (ALTO_PANTALLA / 5.0) * 2, ALLEGRO_ALIGN_CENTER, "Jugar");
			if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (Evento.mouse.button & 1) {
					//Si se presiona el click del mouse se inicia el juego y se indican las vidas totales y el nivel, si el juego termina se avanza de nivel hasta que se pierdan las vidas y el modo determina si es maquina vs maquina o jugador vs maquina
					menuactivo = false;
				}
			}
		}
		if ((mousex >= 619) && (mousex <= 875) && (mousey >= 464) && (mousey <= 494)) {
			al_draw_textf(fuente3, al_map_rgb(255, 255, 20), ANCHO_PANTALLA / 2.0, (ALTO_PANTALLA / 6.0) * 3, ALLEGRO_ALIGN_CENTER, "Instrucciones");
			if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (Evento.mouse.button & 1) {
					//Si se presiona el click del mouse se inicia el juego y se indican las vidas totales y el nivel, si el juego termina se avanza de nivel hasta que se pierdan las vidas y el modo determina si es maquina vs maquina o jugador vs maquina
					instrucciones(cola_eventos, gameFont);
				}
			}
		}
		if ((mousex >= 710) && (mousex <= 788) && (mousey >= 610) && (mousey <= 644)) {
			al_draw_textf(fuente3, al_map_rgb(255, 255, 20), ANCHO_PANTALLA / 2.0, (ALTO_PANTALLA / 6.0) * 4, ALLEGRO_ALIGN_CENTER, "Salir");
			if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (Evento.mouse.button & 1) {
					//Si se presiona el click del mouse se inicia el juego y se indican las vidas totales y el nivel, si el juego termina se avanza de nivel hasta que se pierdan las vidas y el modo determina si es maquina vs maquina o jugador vs maquina
					return 0;
				}
			}
		}

		al_flip_display();
	}

	//Se desinstala el mouse
	al_uninstall_mouse();


	//Se crea una variable para la condicion de true del juego y se inicia el while del juego
	bool juego = true;

	while (juego) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(cola_eventos, &Evento);
		al_draw_bitmap(Fondo, 0, 0, 0);
		

		if (Evento.type == ALLEGRO_EVENT_KEY_DOWN) { //Si se presiona una tecla, se obtiene cual es.
			RecibirTeclasPresionadas(Evento, jugador, Balas);
		}
		else if (Evento.type == ALLEGRO_EVENT_KEY_UP) {
			RecibirTeclasLevantadas(Evento, jugador); //Tambien se obtienen las teclas levantadas
		}
		Mover(jugador); //Funcion para mover al jugador
		ContarBorde(jugador); //Funciona para revisar que el jugador no salga de la pantalla.
		DrawJugador(jugador, ImagenJugador); //Funcion para dibujar al jugador
		Actualizar(Balas);//Funcion para actualizar los parametros de las balas.
		DrawBala(Balas, ImagenBala);//Funcion para dibujar las balas en el display.
		BorrarPosicion(Balas);//Funcion para Borrar las balas inactivas
		if (((rand() % 1000) % 99) == 0) { //Condicion para crear enemigos aleatoriamente
			int i = (rand() % 4) + 1;// Numero aleatorio entre 1 y 4
			crearenemigo(i, Enemigos, stats, jugador); // Se crea un enemigo si se cumple la condicion y se crea con el numero creado aleatoriamente entre 1 y 4.
		}
		dibujarenemigos(Enemigos, ImagenAsteroide); //Se dibujan los enemigos.
		Actualizarenemigos(Enemigos, stats);//Se actualizan las caracteristicas de los enemigos.
		EliminarEnemigo(Enemigos); //Se eliminan los enemigos inactivos
		colision_balas_meteoritos(Balas, Enemigos, ImagenBala, ImagenAsteroide, Explosion, stats); // Se revisan las coordenadas de kos enemigos y las balas para detectar colisiones.
		colision_jugador_meteoritos(jugador, Enemigos, ImagenJugador, ImagenAsteroide, stats); // Se revisan las coordenadas de los enemigos y el jugador para detectar colisiones.
		Imprimirestadisticas(gameFont, stats); //Se imprimen las estadisticas a la pantalla del juego.

		if (stats.vidas_restantes == 0) { //Si las vidas son iguales a 0, se declara juego como false para salir del ciclo.


			juego = false;


		}

		al_flip_display(); //Se actualiza el display
		al_clear_to_color(al_map_rgb(0, 0, 0)); //Se pinta la pantalla de negro.
	}
	bool finjuego = true;

	int r = 0;
	int g = 0;
	int b = 0;

	while (finjuego) { //Se imprime el final del juego con todas las estadisticas de la partida.
		cout << stats.mejor_puntaje << endl;
		r += 30;
		g += 1;
		b += 50;
		if (r == 255) r = 0;
		if (g == 255) g = 0;
		if (b == 255) b = 0;
		ALLEGRO_EVENT Evento;
		al_wait_for_event(cola_eventos, &Evento);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(gameFont, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2, ALTO_PANTALLA / 12 * 3, ALLEGRO_ALIGN_CENTER, "Fin del juego");
		al_draw_textf(gameFont, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2, ALTO_PANTALLA / 12 * 4, ALLEGRO_ALIGN_CENTER, "Meteoritos destruidos: %i", stats.meteoritos_destruidos);
		al_draw_textf(gameFont, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2, ALTO_PANTALLA / 12 * 5, ALLEGRO_ALIGN_CENTER, "Nivel alcanzado: %i", stats.nivel);
		if (stats.meteoritos_destruidos <= stats.mejor_puntaje) {
			al_draw_textf(gameFont, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2, ALTO_PANTALLA / 12 * 7, ALLEGRO_ALIGN_CENTER, "Mejor Puntaje: %i", stats.mejor_puntaje);
		}
		if (stats.meteoritos_destruidos > stats.mejor_puntaje) {
			al_draw_textf(gameFont, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2, ALTO_PANTALLA / 12 * 7, ALLEGRO_ALIGN_CENTER, "Anterior Mejor Puntaje: %i", stats.mejor_puntaje);
			al_draw_textf(gameFont, al_map_rgb(r, g, b), ANCHO_PANTALLA / 2, ALTO_PANTALLA / 12 * 8, ALLEGRO_ALIGN_CENTER, "Nuevo Mejor Puntaje: %i", stats.meteoritos_destruidos);
		}

		al_draw_textf(gameFont, al_map_rgb(255, 255, 255), ANCHO_PANTALLA / 2.0, ALTO_PANTALLA / 12 * 10, ALLEGRO_ALIGN_CENTER, "Presione ESC para salir");

		if (Evento.type == ALLEGRO_EVENT_KEY_DOWN) {


			if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {

				finjuego = false;

			}
		}
	}

	if (stats.meteoritos_destruidos > stats.mejor_puntaje) {

		Guardarestadisticas(stats);

	}

	return 0;
}