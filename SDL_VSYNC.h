#include "SDL.h"
#include <stdbool.h>

#ifndef SDL_VSYNC_H_INCLUDED
#define SDL_VSYNC_H_INCLUDED


//Screen dimension constants
#define SCREEN_WIDTH   700
#define SCREEN_HEIGHT  700

//Walking animation
#define WALKING_ANIMATION_FRAMES 4   //effet d'animation sur 4 images
#define NUMBERFRAMESONSAMEPLACE  2   // nombre de fois que l'on redessine chaque sprite avant de le déplacer
#define NBPASPOURAFFICHERUNDEPLACEMENT 4

typedef struct {
    //The actual hardware texture
    SDL_Texture* mTexture;

    //tableau des dimansions (localisation) pour les 4 sprites
    SDL_Rect mSpriteClips[ WALKING_ANIMATION_FRAMES ];

    //Image dimensions (contenant 4 sprites)
    int mWidth;
    int mHeight;

    //position coin sup gauche où est affichée la texture dans la fenetre (renderer)
    int posX;
    int posY;

    //dist du prochain affichage   (posXarrivéeA - PosXdepartB)/NBIMAGESPOURLEDEPLACEMENT_A_VERS_B
    int incX;
    int incY;
}LTexture;

//assesseurs et utilitaires
void init_LTexture(LTexture *l);
void close_LTexture(LTexture *l);
bool loadFromFile_LTexture(LTexture *l, SDL_Renderer* gRenderer, char* path );
void free_Ltexture(LTexture *l);
void setColor_LTexture( LTexture *l, Uint8 red, Uint8 green, Uint8 blue );

//Set blending
void setBlendMode_LTexture(LTexture *l, SDL_BlendMode blending );

//Set alpha modulation
void setAlpha_LTexture(LTexture *l, Uint8 alpha );

//Renders texture at given point
//void render_LTexture(LTexture *l, SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip ); //SDL_Rect* clip = NULL
void render_LTexture(LTexture *l, SDL_Renderer* gRenderer, int x, int y, int frame);
void Affiche_Sprite(LTexture *l, SDL_Renderer* gRenderer, int x, int y, int frame);
void Deplace_Sprite(LTexture *l, SDL_Renderer* gRenderer, int incX, int incY, int frame);
int getIdFrame(int frame);
void setPositionSprite(LTexture *l, int x, int y);

//assesseurs
int getWidth_LTexture(LTexture *l);
int getHeight_LTexture(LTexture *l);
void setWidth_LTexture(LTexture *l, int pwidth);
void setHeight_LTexture(LTexture *l, int pheight);
void setmTexture_LTexture(LTexture *l,SDL_Texture* mT);
//fin assesseurs et utilitaires

//fonctions de plus haut niveau

//Starts up SDL and creates window
bool init(SDL_Window* *gWindow, SDL_Renderer* *gRenderer);

//Loads media
bool loadSprite(LTexture *l, SDL_Renderer* gRenderer, char* path);
bool loadAnimation(LTexture *l, SDL_Renderer* gRenderer, char* path);

//Frees media and shuts down SDL
void close(SDL_Window* gWindow, SDL_Renderer* gRenderer);
void efface_fenetre_texture(SDL_Renderer* gRenderer);
void maj_fenetre_texture(SDL_Renderer* gRenderer);

void message(char *myTitle, char *myMessage);


#endif // SDL_VSYNC_H_INCLUDED
