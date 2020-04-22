#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

//Background
extern char _binary_background_png_start[];
extern char _binary_background_png_end[];
//Asteroids tileset
extern char _binary_tileset_png_start[];
extern char _binary_tileset_png_end[];
//Font
extern char _binary_font_ttf_start[];
extern char _binary_font_ttf_end[];

//Assets
TTF_Font *font;
SDL_Texture *background;
SDL_Texture *tileset;

//Another stuff
SDL_Window *win;
SDL_Point wins; //window size
SDL_Renderer *ren;

//load assets function
int loadAssets()
{
	font = TTF_OpenFontRW(
		SDL_RWFromConstMem(
			_binary_font_ttf_start,
			_binary_font_ttf_end
			-
			_binary_font_ttf_start
		),
		0,
		16
	);
	if(!font)
	{
		printf("Unable load internal fonts.\n");
		return 1;
	}
	SDL_Surface *temp = IMG_Load_RW(
		SDL_RWFromConstMem(
			_binary_background_png_start,
			_binary_background_png_end
			-
			_binary_background_png_start
		),
		0
	);
	if(!temp)
	{
		printf("Unable load background.\n");
	}
	//background = SDL_CreateTextureFromSurface();
	
	SDL_FreeSurface(temp);
	
	return 0;
}



int initSDL() //Sdl lib safe init
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("SDL _INIT:[%s]\n",SDL_GetError());
		return 1;
	}
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("IMG _INIT:[%s]\n",IMG_GetError());
		
		SDL_Quit();
		
		return 1;
	}
	if(TTF_Init() == -1)
	{
		printf("TTF_INIT:[%s]\n",TTF_GetError());
		
		IMG_Quit();
		SDL_Quit();
		
		return 1;
	}
	//SDL_CreateWindowAndRenderer();
	
	return 0;
}

int main(int argc, char *argv[])
{
	if(initSDL() && loadAssets()) return 1;
	
}