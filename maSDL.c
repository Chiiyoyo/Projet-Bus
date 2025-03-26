#include <stdbool.h>

#include "SDL.h"
#include "maSDL.h"
#include "listeDouble.h"    //getPtrData
#include "ligneBus.h"       //getPosXStation


void DessineUneLigneBus(TlisteStation l, LTexture mySpriteArretBus, SDL_Renderer* gRenderer){
    TlisteStation maLigneBus = l, prochaineStation, prochainTroncon;
    int idframe=0;
    if (ligneBusVide(maLigneBus)){
        SDL_Log("\n Erreur: ligne de bus sans station (maSDL.c)");
    }
    else{
        while (!ligneBusVide(maLigneBus)){
                Affiche_Sprite(&mySpriteArretBus, gRenderer, getPosXStation(getPtrData(maLigneBus)), getPosYStation(getPtrData(maLigneBus)), idframe);

                //A faire: tracer une ligne entre malignebus et la station suivante
                prochaineStation = getNextStation( maLigneBus );
                prochainTroncon = getNextTroncon( maLigneBus );
                if (!ligneBusVide(prochaineStation)){
                    TraceLigne(gRenderer,getPosXStation(getPtrData(maLigneBus)),getPosYStation(getPtrData(maLigneBus)),getPosXStation(getPtrData(prochaineStation)),getPosYStation(getPtrData(prochaineStation)),getIdLigneTroncon(getPtrData(prochainTroncon)));
                }

                maLigneBus = prochaineStation;
        }
    }
}

void TraceLigne(SDL_Renderer* gRenderer, int xdep, int ydep, int xarr, int yarr, int idLigneBustoColor){
    //la couleur du trait est défini par l'id de la ligne de bus
    SDL_SetRenderDrawColor( gRenderer, 255-(idLigneBustoColor*250)%256, 255-(idLigneBustoColor*150)%256, (idLigneBustoColor*220)%256, 0xFF );
    //printf("\n r: %d   v: %d   b: %d    alpha: %d",(idLigneBustoColor*100)%256, 255-(idLigneBustoColor*100)%256, 255-(idLigneBustoColor*150)%256, 0xFF);

    // epaissi le trait
    int EpaiseurTrait = 5;

    for (int i=0; i<EpaiseurTrait; i++)  SDL_RenderDrawLine(gRenderer, xdep+i, ydep+i, xarr+i, yarr+i);
}
