#include <allegro5/allegro_color.h>
#include "Jugador.h"
#include "Ajustes.h"
#include <math.h>
#include <iostream>

void Mover(Jugador& jugador) {
	if (jugador.acelerando) {
		jugador.dy -= 0.1 * jugador.velocidad * cos(jugador.angulo);
		jugador.dx += 0.1 * jugador.velocidad * sin(jugador.angulo);
	}
	if (jugador.rotacion_derecha) {
		jugador.angulo += 0.1;
	}
	if (jugador.rotacion_izquierda) {
		jugador.angulo -= 0.1;
	}
	jugador.X += jugador.dx;
	jugador.Y += jugador.dy;

}

void DrawJugador(Jugador& jugador, ALLEGRO_BITMAP*& Imagen) {
	al_draw_rotated_bitmap(Imagen, al_get_bitmap_width(Imagen) / 2, al_get_bitmap_height(Imagen) / 2, jugador.X, jugador.Y, jugador.angulo, 0);
}
void ContarBorde(Jugador& jugador) {
	if (jugador.X + jugador.dx >= ANCHO_PANTALLA) {
		//jugador.angulo += pi;
		jugador.dx = -jugador.dx;
	}
	if (jugador.X + jugador.dx <= 0) {
		//jugador.angulo += pi;
		jugador.dx = -jugador.dx;
	}
	if (jugador.Y + jugador.dy >= ALTO_PANTALLA) {
		//jugador.angulo += pi;
		jugador.dy = -jugador.dy;
	}
	if (jugador.Y + jugador.dy <= 0) {
		//jugador.angulo += pi;
		jugador.dy = -0.5 * jugador.dy;
	}
}

