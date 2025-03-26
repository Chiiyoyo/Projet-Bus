//NOM prénom étudiant 1 :
//NOM prénom étudiant 2 :

#include "SDL.h"
#include "maSDL.h"
#include "SDL_VSYNC.h"

//#include "types.h"
#include "ligneBus.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    //SDL
    //fênetre dans windows
    SDL_Window *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    //la texture (chargée dans la ram de la carte graphique) target representant tout le jeu
    SDL_Renderer* gRenderer = NULL;

    //Les textures, le type Ltexture est défini dans SDL_VSYNC.h
    LTexture gSpriteBus;
    LTexture gSpriteArretBus;

    //Start up SDL and create window
	if( !init(&gWindow,&gRenderer) )  //initialise la fenetre SDL et charge UNE texture
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadAnimation(&gSpriteBus, gRenderer, "./data/4bus.png")
            || !loadSprite(&gSpriteArretBus, gRenderer, "./data/arret_bus_50x27.png"))
        {
			fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
		}
		else
		{
        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^
        message("Welcome in BusProject","Ceci est un point de depart de votre future interface de vos lignes de Bus");
        message("et fin","ECHAP->quitter, + vos touches + D/V pour sauvegarer/restaurer un bus et le reseau de lignes");

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
        /*                                                                    */
        /**********************************************************************/


        TlisteStation ligne1 = creeLigneDeBus1();
        TlisteStation ligne2 = creeLigneDeBus2();
        TlisteStation ligne3 = creeLigneDeBus3();

        //création d'un (seul) bus
        Tbus bus1 = creeBus(1,ligne1);

        //affiche sur la console les stations et troncons des lignes de bus
        afficheConsoleLigneBus(ligne1);
        afficheConsoleLigneBus(ligne2);
        afficheConsoleLigneBus(ligne3);

        //Current animation frame
        int frame = 0;

        //affiche et initialise le sprite du bus au départ
        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));


        // boucle principale du jeu
        int cont = 1;
        int  incXDeplSpriteBus1 = 0, incYDeplSpriteBus1 = 0; //déplacement du sprite du bus à chaque passage dans la boucle principale

        while ( cont != 0 ){
                SDL_PumpEvents(); //do events

                /***********************************************************************/
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE "JEU"
                /*                                                                     */
                /***********************************************************************/

                //deplaceBus gère le déplacement du bus sur sa ligne, selon son sens du parcours de la ligne;
                //met à jour les variations en X et Y pour déplacer le sprite du Bus (cf ligne 151)
                deplaceBus(bus1, getSensParcours(bus1), &incXDeplSpriteBus1, &incYDeplSpriteBus1);


                //afficheCoordonneesBus( bus1 );  //utile?

                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                //les touches sont lues en Qwerty
                if ( pKeyStates[SDL_SCANCODE_W] ){

                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur Z */
                        printf("\nTouche Z, sens déplacement depart vers terminus\n");
                        setSensParcours(bus1, depart_vers_arrivee );
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){

                        printf("\nTouche S, sens déplacement terminus vers depart\n");
                        setSensParcours(bus1, arrivee_vers_depart );
                }
                if ( pKeyStates[SDL_SCANCODE_1] ){

                        printf("\nTouche 1, Bus au depart de la ligne 1\n");
                        busSurStation(bus1, ligne1, depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));
                }
                if ( pKeyStates[SDL_SCANCODE_2] ){

                        printf("\nTouche 2, Bus au départ de la ligne 2\n");
                        busSurStation(bus1, ligne2, depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));
                }
                if ( pKeyStates[SDL_SCANCODE_3] ){

                        printf("\nTouche 3, Bus au départ de la ligne 3\n");
                        busSurStation(bus1, ligne3, depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){

                        printf("\nTouche ECHAP");
                        cont = 0;  //sortie de la boucle
                }


                //affichage du jeu à chaque tour

                //on efface toute la fenêtre
                efface_fenetre_texture(gRenderer);

                //Déplacement de sprite du bus sur la texture
                Deplace_Sprite(&gSpriteBus, gRenderer, incXDeplSpriteBus1,incYDeplSpriteBus1,getIdFrame(frame));

                //réaffichage à chaque tour de toutes les stations
                DessineUneLigneBus(ligne1, gSpriteArretBus, gRenderer);
                DessineUneLigneBus(ligne2, gSpriteArretBus, gRenderer);
                DessineUneLigneBus(ligne3, gSpriteArretBus, gRenderer);

                //affichage de la texture ainsi mis à jour
                maj_fenetre_texture(gRenderer);

                SDL_Delay(1); //valeur du délai modifiable en fonction de votre CPU
                ++frame;
            }
        //fin boucle du jeu
        }
	}


	//Free resources and close SDL
	free_Ltexture(&gSpriteBus);
	free_Ltexture(&gSpriteArretBus);
	close(gWindow, gRenderer);

    return 0;
}
