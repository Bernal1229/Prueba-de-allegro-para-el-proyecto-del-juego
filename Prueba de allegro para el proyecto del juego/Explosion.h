#pragma once

#pragma once
#include<allegro5/allegro.h>
#include <vector>
#include "Enemigos.h"
typedef struct Explosion {
	int X;
	int Y;
	float delay;
	bool activa;
	int index;
	float segundo_indice;
	float size;
} *PtrExplosion;
void GenerarExplosion(std::vector<PtrEnemigo>& Enemigos, std::vector<PtrExplosion>& Explosiones);
void AnimarExplosion(std::vector<PtrExplosion>& Explosiones);
void DrawExplosion(ALLEGRO_BITMAP* Imagenes[6], std::vector<PtrExplosion>& Explosiones);
void BorrarExplosiones(std::vector<PtrExplosion>& Explosiones);
