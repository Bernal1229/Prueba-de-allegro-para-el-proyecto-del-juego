#include<allegro5/allegro.h>
#include<allegro5/color.h>
#include <vector>
#include "Explosion.h"
#include "Enemigos.h"
#include "Ajustes.h"
void GenerarExplosion(std::vector<PtrEnemigo>& Enemigos, std::vector<PtrExplosion>& Explosiones) {
	for (int i = 0; i < Enemigos.size(); i++) {
		PtrEnemigo enemigo = Enemigos[i];
		if (enemigo->Colision == true) {
			PtrExplosion explosion = new(Explosion);
			explosion->X = enemigo->X;
			explosion->Y = enemigo->Y;
			explosion->index = 0;
			explosion->segundo_indice = 0;
			explosion->delay = duracion;
			explosion->activa = true;
			explosion->size = enemigo->size;
			Explosiones.push_back(explosion);
		}
	}
}
void AnimarExplosion(std::vector<PtrExplosion>& Explosiones) {
	for (int i = 0; i < Explosiones.size(); i++) {
		PtrExplosion explosion = Explosiones[i];
		if (explosion->segundo_indice > 5) {
			explosion->activa = false;
		}
		if (explosion->activa) {
			explosion->segundo_indice += explosion->delay;
			explosion->index = explosion->segundo_indice;
		}


	}
}


void DrawExplosion(ALLEGRO_BITMAP* Imagenes[6], std::vector<PtrExplosion>& Explosiones) {
	for (int i = 0; i < Explosiones.size(); i++) {
		al_draw_scaled_bitmap(
			Imagenes[Explosiones[i]->index],
			0,0,
			al_get_bitmap_width(Imagenes[Explosiones[i]->index]), al_get_bitmap_height(Imagenes[Explosiones[i]->index]),
			Explosiones[i]->X - 100, Explosiones[i]->Y - 100,
			al_get_bitmap_width(Imagenes[Explosiones[i]->index]) * 3, al_get_bitmap_height(Imagenes[Explosiones[i]->index]) * 3,
			NULL
		);
	}
}



void BorrarExplosiones(std::vector<PtrExplosion>& Explosiones) {
	for (int i = 0; i < Explosiones.size(); i++) {
		if (Explosiones[i]->activa == false) {
			std::vector<PtrExplosion>::iterator IteradorExplosion = Explosiones.begin() + i;
			Explosiones.erase(IteradorExplosion);
		}
	}
}