#pragma once

#include "Bala.h"
#include "Enemigos.h"
#include"Jugador.h"
#include <allegro5/allegro_color.h>
#include "Estadisticas.h"
#include "Explosion.h"


void colision_balas_meteoritos(std::vector<PtrBala>& Balas, std::vector<PtrEnemigo>& Enemigos, ALLEGRO_BITMAP*& Imagen1, ALLEGRO_BITMAP*& Imagen2, Estadisticas& stats, ALLEGRO_BITMAP* Imagenes[6], std::vector<PtrExplosion>& Explosiones);
bool colision1(float x1, float y1, ALLEGRO_BITMAP*& Imagen1, float x2, float y2, float size_meteorito);
bool colision2(float x1, float y1, ALLEGRO_BITMAP*& Imagen1, float x2, float y2, float size_meteorito);
void colision_jugador_meteoritos(Jugador jugador, std::vector<PtrEnemigo>& Enemigos, ALLEGRO_BITMAP*& Imagen1, ALLEGRO_BITMAP*& Imagen2, Estadisticas& stats);