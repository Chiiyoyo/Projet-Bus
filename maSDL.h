//"surcouche partielle" de la SDL pour les affichages liés aux données de l'application

#include "types.h"
#include "SDL_VSYNC.h"

#ifndef MASDL_H_INCLUDED
#define MASDL_H_INCLUDED

void DessineUneLigneBus(TlisteStation l, LTexture mySpriteArretBus, SDL_Renderer* gRenderer);
void TraceLigne(SDL_Renderer* gRenderer, int xdep, int ydep, int xarr, int yarr, int idLigneBustoColor);

#endif // MASDL_H_INCLUDED
