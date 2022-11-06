#include "Enemigos.h"
#include "Ajustes.h"
#include <iostream>
#include <cmath>


void EncolarEnemigo(std::vector<PtrEnemigo>& Enemigos, PtrEnemigo& NuevoEnemigo) { //Se agrega un nuevo enemigo al vector de enemigos

	Enemigos.push_back(NuevoEnemigo);

};

void crearenemigo(int tipo, std::vector<PtrEnemigo>& Enemigos, Estadisticas stats, Jugador jugador) { //Se crea un nuevo enemigo
	PtrEnemigo Enemy = new(Enemigo);
	switch (tipo) {
	//Caracteristicas dependiendo del caso
	case 1:
		Enemy->vida = 1;
		Enemy->velocidad = 1;
	case 2:
		Enemy->vida = 2;
		Enemy->velocidad = 2;
	case 3:
		Enemy->vida = 3;
		Enemy->velocidad = 4;
	case 4:
		Enemy->vida = 4;
		Enemy->velocidad = 5;

	}

	//Se definen otras caracteristicas, todas con igual probabilidad
	//Esto se hace para que salgan en distintas partes de la pantalla con distintos angulos.
	int inicio = rand() % 101;

	if (inicio < 25) {
		Enemy->X = ANCHO_PANTALLA / 2 - inicio;
		Enemy->Y = ALTO_PANTALLA;
		Enemy->angulo = (230 + rand() % 100) * (pi / 180);
	}
	if (inicio > 25 && inicio < 50) {
		Enemy->X = ANCHO_PANTALLA / 2 - inicio;
		Enemy->Y = 0;
		Enemy->angulo = (45 + rand() % 100)* (pi / 180);
	}
	if (inicio > 50 && inicio < 75) {
		Enemy->X = ANCHO_PANTALLA;
		Enemy->Y = ALTO_PANTALLA / 2 - inicio;
		Enemy->angulo = (120 + rand() % 120) * (pi / 180);
	}
	if (inicio > 75) {
		Enemy->X = 0;
		Enemy->Y = ALTO_PANTALLA / 2 - inicio;
		Enemy->angulo = (-90 + rand() % 90)* (pi / 180);
	}
	Enemy->size = (3.0 + (rand() % 7))/100;
	Enemy->Activo = true;
	Enemy->angulo2 = 0;

	

	EncolarEnemigo(Enemigos, Enemy);

};

void revisarbordes(PtrEnemigo Enemigos) { //Se revisa que el meteorito no este en los extremos del display, en caso de hacerlo se desactiva
		
		if (Enemigos->X > ANCHO_PANTALLA || Enemigos->X < 0) {
			Enemigos->Activo = false;
		}
		if (Enemigos->Y > ALTO_PANTALLA || Enemigos->Y < 0) {
			Enemigos->Activo = false;
		}
};

void Actualizarenemigos(std::vector<PtrEnemigo> &Enemigos, Estadisticas stats) { //Se actualizan las caracteristicas de los meteoritos como su posicion
	for (int i = 0; i < Enemigos.size(); i++) {
				Enemigos[i]->X = Enemigos[i]->X + Enemigos[i]->velocidad* cos(Enemigos[i]->angulo);
				Enemigos[i]->Y = Enemigos[i]->Y + Enemigos[i]->velocidad * sin(Enemigos[i]->angulo);
				Enemigos[i]->angulo2 += 3.5 * (3.1415/180);
				revisarbordes(Enemigos[i]);

				if (stats.nivel == 3 && Enemigos[i]->angulo != 0) {


					Enemigos[i]->X += 20*cos(Enemigos[i]->Y*0.069);

				}

	}
	
};



void dibujarenemigos(std::vector<PtrEnemigo>& Enemigos, ALLEGRO_BITMAP*& Imagen) { //Se dibujan todos los meteoritos una vez actualizados
	for (std::vector<PtrEnemigo>::iterator Enemigoiter = Enemigos.begin(); Enemigoiter != Enemigos.end(); Enemigoiter++) {
		al_draw_scaled_rotated_bitmap(Imagen, al_get_bitmap_width(Imagen) / 2, al_get_bitmap_height(Imagen) / 2, (*Enemigoiter)->X, (*Enemigoiter)->Y, (*Enemigoiter)->size, (*Enemigoiter)->size, (*Enemigoiter)->angulo2, 0);
	}
};


void EliminarEnemigo(std::vector<PtrEnemigo>& Enemigos) { //Se eliminana los meteoritos inactivos.

	for (int i = 0; i < Enemigos.size(); i++) {
		//std::cout << Balas[i]->activa << std::endl;
		if (Enemigos[i]->Activo == false) {
			std::vector<PtrEnemigo>::iterator IteradorEnemigo = Enemigos.begin() + i;
			Enemigos.erase(IteradorEnemigo);
		}
	}

};

