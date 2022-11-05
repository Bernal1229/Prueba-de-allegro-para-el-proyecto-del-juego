#pragma once
#include <vector>
#include "Jugador.h"
#include <allegro5/allegro_color.h>

typedef struct Bala {
	int X;
	int Y;
	float Velociad;
	float Angulo;
	bool activa;
}*PtrBala;



void EncolarBala(std::vector<PtrBala>& Balas, PtrBala& NuevaBala);
void BorrarPosicion(std::vector<PtrBala>& Balas);

void CrearBala(Jugador jugador, std::vector<PtrBala>& Balas);
void CheckBorde(PtrBala& Aux);
void Actualizar(std::vector<PtrBala>& Balas);
void DrawBala(std::vector<PtrBala>& Balas, ALLEGRO_BITMAP*& Imagen);

