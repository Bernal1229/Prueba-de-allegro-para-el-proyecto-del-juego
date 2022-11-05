#include "Bala.h"
#include <allegro5/allegro_color.h>

#include "Ajustes.h"
#include <math.h>
#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>

void EncolarBala(std::vector<PtrBala>& Balas, PtrBala& NuevaBala) {
	Balas.push_back(NuevaBala);
	//std::cout << Balas.size();
}
void BorrarPosicion(std::vector<PtrBala>& Balas) {
	for (int i = 0; i < Balas.size(); i++) {
		//std::cout << Balas[i]->activa << std::endl;
		if (Balas[i]->activa == false) {
			std::vector<PtrBala>::iterator IteradorBala = Balas.begin() + i;
			Balas.erase(IteradorBala);
		}
	}
}
void CrearBala(Jugador jugador, std::vector<PtrBala>& Balas) {
	al_install_audio();
	
	ALLEGRO_SAMPLE* Disparos = al_load_sample("Musica/Disparo.wav");
	al_play_sample(Disparos, 0.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	
	PtrBala NuevaBala = new(Bala);
	NuevaBala->activa = true;
	NuevaBala->Angulo = jugador.angulo;
	NuevaBala->Velociad = VELOCIDAD_BALA;
	NuevaBala->X = jugador.X;
	NuevaBala->Y = jugador.Y;
	EncolarBala(Balas, NuevaBala);
}

void CheckBorde(PtrBala& Aux) {
	if ((Aux)->X >= ANCHO_PANTALLA || (Aux)->X <= 0) {
		(Aux)->activa = false;
	}
	if ((Aux)->Y >= ALTO_PANTALLA || (Aux)->Y <= 0) {
		(Aux)->activa = false;
	}
}
void Actualizar(std::vector<PtrBala>& Balas) {
	for (auto&& BalasIter : Balas) {
		(BalasIter)->Y += (BalasIter)->Velociad * -cos((BalasIter)->Angulo);
		(BalasIter)->X += (BalasIter)->Velociad * sin((BalasIter)->Angulo);
		CheckBorde(BalasIter);
	}
}

void DrawBala(std::vector<PtrBala>& Balas, ALLEGRO_BITMAP*& Imagen) {
	for (std::vector<PtrBala>::iterator BalasIter = Balas.begin(); BalasIter != Balas.end(); BalasIter++) {
		al_draw_rotated_bitmap(Imagen, al_get_bitmap_width(Imagen) / 2, al_get_bitmap_height(Imagen) / 2, (*BalasIter)->X, (*BalasIter)->Y, (*BalasIter)->Angulo, 0);
	}

}
