#pragma once
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"



//Se define el struct de estadisticas.
struct Estadisticas {

	int meteoritos_destruidos = 0, vidas_restantes = 5, nivel = 1, contadornivel = 0;

};

void Imprimirestadisticas(ALLEGRO_FONT* fuente, Estadisticas& stats);
