#pragma once
#include <allegro5/allegro_color.h>
struct Jugador {
	float X;
	float Y;
	float velocidad;
	float angulo;
	float dx, dy;
	bool vivo;

	bool rotacion_izquierda;
	bool rotacion_derecha;
	bool acelerando;
};

void Mover(Jugador& jugador);
void DrawJugador(Jugador& jugador, ALLEGRO_BITMAP*& Imagen);
void ContarBorde(Jugador& jugador);
