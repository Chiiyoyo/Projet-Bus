#include "SDL.h"
#include "SDL_VSYNC.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



void init_LTexture(LTexture *l)
{
	//Initialize
	l->mTexture = NULL;
	l->mWidth = 0;
	l->mHeight = 0;
}

void close_LTexture(LTexture *l)
{
	//Deallocate
	free_Ltexture(l);
}

bool loadFromFile_LTexture(LTexture *l, SDL_Renderer* gRenderer, char* path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else
	{
		//Color key image  -> permet de definir la couleur qui sera considérée comme transparente, pour les operations de blit
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			fprintf(stderr, "ICI Unable to create texture from %s! SDL Error: %s dimmensions%d %d\n", path, SDL_GetError(),loadedSurface->w, loadedSurface->h );
		}
		else
		{
			//Get image dimensions
			setWidth_LTexture(l, loadedSurface->w);
			setHeight_LTexture(l, loadedSurface->h);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	setmTexture_LTexture(l, newTexture);
	return l->mTexture != NULL;
}

void free_Ltexture(LTexture *l)
{
	//Free texture if it exists
	if( l->mTexture != NULL )
	{
		SDL_DestroyTexture( l->mTexture );
		l->mTexture = NULL;
		l->mWidth = 0;
		l->mHeight = 0;
	}
}

void setColor_LTexture( LTexture *l, Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( l->mTexture, red, green, blue );
}

void setBlendMode_LTexture(LTexture *l, SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( l->mTexture, blending );
}

void setAlpha_LTexture(LTexture *l, Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( l->mTexture, alpha );
}

void render_LTexture(LTexture *l, SDL_Renderer* gRenderer, int x, int y, int frame)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, l->mWidth, l->mHeight };
	SDL_Rect* clip = &(l->mSpriteClips[frame]);  //soit l'image dans l'animation

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
		//printf("\n clip x1 = %d  y1 = %d  largeur = %d  hauteur = %d  frame = %d", x, y, clip->w, clip->h, frame);
	}

	//efface la fenetre -> fait à la main dans le main au final, cela évite un effet "blanchi" sur les sprites
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //SDL_RenderClear( gRenderer );

	//Render to screen
	SDL_RenderCopy( gRenderer, l->mTexture, clip, &renderQuad );  //Clip donne la partie de la texture à recopier sur le rendu
	//SDL_RenderCopy( gRenderer, l->mTexture, NULL, &renderQuad );  // NULL -> sur toute la fenetre ^^

	//maj à l'ecran de la texture -> fait à la main dans le main
    //SDL_RenderPresent(gRenderer);
}



//affiche le sprite à la pos (x,) et mémorise la pos dans sa structure

void Affiche_Sprite(LTexture *l, SDL_Renderer* gRenderer, int x, int y, int frame){
    //mémorise la position du sprite
    l->posX = x;
    l->posY = y;
    render_LTexture(l, gRenderer, x, y, frame / NUMBERFRAMESONSAMEPLACE);
    //printf("x = %d  y = %d\n", l->posX, l->posY);
}

void Deplace_Sprite(LTexture *l, SDL_Renderer* gRenderer, int incX, int incY, int frame){
    Affiche_Sprite(l, gRenderer, l->posX + incX, l->posY + incY, frame );
}

int getIdFrame(int frame){
    //permet d'affiche plusieurs fois le même sprite, pour effet visuel de glisser
    //retourne un entier entre 0 et 3
    //printf("\nidFrame=%d",(frame/(NUMBERFRAMESONSAMEPLACE*NBPASPOURAFFICHERUNDEPLACEMENT))%WALKING_ANIMATION_FRAMES);
    return (frame/(NUMBERFRAMESONSAMEPLACE*NBPASPOURAFFICHERUNDEPLACEMENT))%WALKING_ANIMATION_FRAMES;
}

void setPositionSprite(LTexture *l, int x, int y){
    l->posX = x;
    l->posY = y;
}

int getWidth_LTexture(LTexture *l)
{
	return l->mWidth;
}

int getHeight_LTexture(LTexture *l)
{
	return l->mHeight;
}

void setWidth_LTexture(LTexture *l, int pwidth){
    l->mWidth = pwidth;
}
void setHeight_LTexture(LTexture *l, int pheight){
    l->mHeight = pheight;
}

void setmTexture_LTexture(LTexture *l,SDL_Texture* mT){
    l->mTexture = mT; //OU SDL_RenderCopy(renderer, texture, NULL, &dst);  //recipie une texture d'unité sur une autre (texture de tout le jeu)
}

bool init(SDL_Window* *gWindow, SDL_Renderer* *gRenderer)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		*gWindow = SDL_CreateWindow( "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( *gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			*gRenderer = SDL_CreateRenderer( *gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			if( *gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( *gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadSprite(LTexture *l, SDL_Renderer* gRenderer, char* path)
{
//recopie 4 fois le même sprite, permet une utilisation de 'Affiche_Sprite' et 'Deplace_Sprite' (qui s'attendent à une texture comprenant 4 zones)

	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !loadFromFile_LTexture(l, gRenderer, path ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
	    //on charge 4 parties issues d'une meme image: les rectangles (ou parties) ont une largeur de 1/4 de la largeur de l'image gloable
	    // dit autrement: UNE image contient UNE texture constituées de 4 zones (pour l'animation)

	    SDL_Rect dst = {0, 0, 0, 0};
	    SDL_QueryTexture(l->mTexture, NULL, NULL, &dst.w, &dst.h);
	    //printf("Dimension texture largeur %d    hauteur %d \n", dst.w, dst.h );

		//Set sprite clips
		l->mSpriteClips[ 0 ].x =     0;
		l->mSpriteClips[ 0 ].y =     0;
		l->mSpriteClips[ 0 ].w = dst.w;
		l->mSpriteClips[ 0 ].h = dst.h;

		l->mSpriteClips[ 1 ].x =     0;
		l->mSpriteClips[ 1 ].y =     0;
		l->mSpriteClips[ 1 ].w = dst.w;
		l->mSpriteClips[ 1 ].h = dst.h;

		l->mSpriteClips[ 2 ].x =     0;
		l->mSpriteClips[ 2 ].y =     0;
		l->mSpriteClips[ 2 ].w = dst.w;
		l->mSpriteClips[ 2 ].h = dst.h;

		l->mSpriteClips[ 3 ].x =     0;
		l->mSpriteClips[ 3 ].y =     0;
		l->mSpriteClips[ 3 ].w = dst.w;
		l->mSpriteClips[ 3 ].h = dst.h;
	}

	return success;
}

bool loadAnimation(LTexture *l, SDL_Renderer* gRenderer, char* path) //charge une image qui stocke 4 textures
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !loadFromFile_LTexture(l, gRenderer, path ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
	    //on charge 4 parties issues d'une meme image: les rectangles (ou parties) ont une largeur de 1/4 de la largeur de l'image gloable
	    // dit autrement: UNE image contient UNE texture constituées de 4 zones (pour l'animation)

	    SDL_Rect dst = {0, 0, 0, 0};
	    SDL_QueryTexture(l->mTexture, NULL, NULL, &dst.w, &dst.h);
	    //printf("Dimension texture largeur %d    hauteur %d \n", dst.w, dst.h );

		//Set sprite clips
		l->mSpriteClips[ 0 ].x =     0;
		l->mSpriteClips[ 0 ].y =     0;
		l->mSpriteClips[ 0 ].w = (dst.w/4);
		l->mSpriteClips[ 0 ].h = dst.h;

        l->mSpriteClips[ 1 ].x = (dst.w/4);
		l->mSpriteClips[ 1 ].y =     0;
		l->mSpriteClips[ 1 ].w = (dst.w/4);
		l->mSpriteClips[ 1 ].h = dst.h;

        l->mSpriteClips[ 2 ].x = (dst.w/4)*2;
		l->mSpriteClips[ 2 ].y =     0;
		l->mSpriteClips[ 2 ].w = (dst.w/4);
		l->mSpriteClips[ 2 ].h = dst.h;

        l->mSpriteClips[ 3 ].x = (dst.w/4)*3;
		l->mSpriteClips[ 3 ].y =     0;
		l->mSpriteClips[ 3 ].w = (dst.w/4);
		l->mSpriteClips[ 3 ].h = dst.h;
	}

	return success;
}

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer)
{
	//Free loaded images
	// a faire dans le main avec free_Ltexture


	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void efface_fenetre_texture(SDL_Renderer* gRenderer){
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
}

void maj_fenetre_texture(SDL_Renderer* gRenderer){
    SDL_RenderPresent(gRenderer);
}

void message(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }

}

