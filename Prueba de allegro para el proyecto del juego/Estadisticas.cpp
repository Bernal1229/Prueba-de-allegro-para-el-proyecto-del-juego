#include "Estadisticas.h"
#include "string"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void Imprimirestadisticas(ALLEGRO_FONT* fuente, Estadisticas& stats) {

	if (stats.meteoritos_destruidos % 20 == 0 && stats.meteoritos_destruidos != stats.contadornivel) { //Se revisa si los meteoritos destruidos son un multiplo de 20 para subir de nivel

		stats.nivel++;
		stats.contadornivel = stats.meteoritos_destruidos;

	}

	//Se imprimen las estadisticas
	al_draw_textf(fuente, al_map_rgb(255, 255, 255), 2,10 , ALLEGRO_ALIGN_LEFT, "Meteoritos destruidos: %i", stats.meteoritos_destruidos);
	al_draw_textf(fuente, al_map_rgb(255, 255, 255), 2, 50, ALLEGRO_ALIGN_LEFT, "Nivel: %i", stats.nivel);
	al_draw_textf(fuente, al_map_rgb(255, 255, 255), 2, 100, ALLEGRO_ALIGN_LEFT, "Vidas: %i", stats.vidas_restantes);
};


