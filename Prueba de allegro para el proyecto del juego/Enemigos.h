#pragma once
#include <vector>
#include <allegro5/allegro_color.h>

typedef struct Enemigo {

	int X, Y, angulo, velocidad, vida;
	float size, angulo2;
	bool Activo;

}*PtrEnemigo;

void EncolarEnemigo(std::vector<PtrEnemigo>& Enemigos, PtrEnemigo& NuevoEnemigo);
void crearenemigo(int tipo, std::vector<PtrEnemigo>& Enemigos);
void dibujarenemigos(std::vector<PtrEnemigo>& Enemigos, ALLEGRO_BITMAP*& Imagen);
void revisarbordes(PtrEnemigo Enemigos);
void Actualizarenemigos(std::vector<PtrEnemigo>& Enemigos);
void EliminarEnemigo(std::vector<PtrEnemigo> & Enemigos);