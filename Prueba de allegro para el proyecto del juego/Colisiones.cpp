#include "Colisiones.h"
#include <iostream>
#include "Ajustes.h"

void colision_balas_meteoritos(std::vector<PtrBala>& Balas, std::vector<PtrEnemigo>& Enemigos, ALLEGRO_BITMAP*& Imagen1, ALLEGRO_BITMAP*& Imagen2, Estadisticas& stats, ALLEGRO_BITMAP* Imagenes[6], std::vector<PtrExplosion>& Explosiones) {

	for (int i = 0; i < Balas.size(); i++) {
		for (int j = 0; j < Enemigos.size(); j++) {
			float sizemeteorito = ((Enemigos[j]->size) * al_get_bitmap_width(Imagen2))/2;
			if (colision1(Balas[i]->X, Balas[i]->Y, Imagen1, Enemigos[j]->X, Enemigos[j]->Y, sizemeteorito)) {
				Enemigos[j]->Activo = false;
				Enemigos[j]->Colision = true;
				stats.meteoritos_destruidos++;
				Balas[i]->activa = false;

			}
		}

	}

};

bool colision1(float x1, float y1, ALLEGRO_BITMAP*& Imagen1, float x2, float y2, float size_meteorito) {

	float disx = x1 - x2;
	float disy = y1 - y2;
	float distancia = sqrt(disx * disx + disy * disy);
	float distancia_min = (size_meteorito + (al_get_bitmap_height(Imagen1)/2));
	
	if (distancia <= distancia_min) {
		return true;
	}
	else {
		return false;
	}
	
};

bool colision2(float x1, float y1, ALLEGRO_BITMAP*& Imagen1, float x2, float y2, float size_meteorito) {

	float disx = x1 - x2;
	float disy = y1 - y2;
	float distancia = sqrt(disx * disx + disy * disy);
	float distancia_min = abs((size_meteorito + 32));
	
	if (distancia <= distancia_min) {
		return true;
	}
	else {
		return false;
	}

};

void colision_jugador_meteoritos(Jugador jugador, std::vector<PtrEnemigo>& Enemigos, ALLEGRO_BITMAP*& Imagen1, ALLEGRO_BITMAP*& Imagen2, Estadisticas& stats) {

	for (int i = 0; i < Enemigos.size(); i++) {
		float sizemeteorito = (Enemigos[i]->size) * (al_get_bitmap_width(Imagen2))/2;
		
		if (colision2(jugador.X, jugador.Y, Imagen1, Enemigos[i]->X, Enemigos[i]->Y, sizemeteorito)) {
			Enemigos[i]->Activo = false;
			stats.vidas_restantes--;
		}
		

	}
}
