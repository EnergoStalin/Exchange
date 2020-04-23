#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <random>
#include <ctime>
#include <stdarg.h>

#define TILE_SIZE_X 124
#define TILE_SIZE_Y 124

#define POOL_SIZE 100

struct Asteroid
{
	Asteroid()
	{
		rotation = 0;
		active = 0;
	}
	Asteroid(Asteroid &a)
	{
		rotation = a.rotation;
		pos = a.pos;
		speed = a.speed;
		padding = a.padding;
		active = a.active;
	}
	Asteroid(
		SDL_Point p,
		SDL_Point sp,
		SDL_Rect pd,
		bool a
	) : Asteroid()
	{
		this->pos = p;
		this->speed = sp;
		this->padding = pd;
		active = a;
	}
	double rotation;
	SDL_Point pos;
	SDL_Point speed;
	SDL_Rect padding;
	bool active;
};

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
SDL_Point wins = {800,800}; //window size
SDL_Renderer *ren;
Asteroid *asteroids;

//load assets function
int loadAssets()
{
	//Load font
	font = TTF_OpenFontRW(
		SDL_RWFromConstMem(
			_binary_font_ttf_start,
			_binary_font_ttf_end
			-
			_binary_font_ttf_start
		),
		1,
		16
	);
	if(!font)
	{
		printf("Unable load internal fonts.\n");
		return 1;
	}

	//Load background
	SDL_Surface *temp = IMG_Load_RW(
		SDL_RWFromConstMem(
			_binary_background_png_start,
			_binary_background_png_end
			-
			_binary_background_png_start
		),
		1
	);
	if(!temp)
	{
		printf("Unable load background.\n");
		TTF_CloseFont(font);

		return 1;
	}
	background = SDL_CreateTextureFromSurface(ren, temp);	
	SDL_FreeSurface(temp);
	
	//Load Tileset
	temp = IMG_Load_RW(
		SDL_RWFromConstMem(
			_binary_tileset_png_start,
			_binary_tileset_png_end
			-
			_binary_tileset_png_start
		),
		1
	);
	if(!temp)
	{
		printf("Unable load background.\n");
		TTF_CloseFont(font);
		SDL_DestroyTexture(background);

		return 1;
	}
	tileset = SDL_CreateTextureFromSurface(ren, temp);	
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
	SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &win, &ren);

	return 0;
}

void quitSDL()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_DestroyTexture(background);
	SDL_DestroyTexture(tileset);

	TTF_CloseFont(font);

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

bool processEvent(SDL_Event &e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			return false;
		break;
		case SDL_WINDOWEVENT:
			switch(e.window.event)
			{
				case SDL_WINDOWEVENT_RESIZED:
					wins = {e.window.data1,e.window.data2};
				break;
			}
		break;
	}

	return true;
}

void render()
{
	static SDL_Rect dst;
	SDL_RenderCopy(ren, background, NULL, NULL);
	for(int i = 0; i < POOL_SIZE; i++)
	{
		if(!asteroids[i].active) continue;
		dst = {asteroids[i].pos.x,asteroids[i].pos.y,asteroids[i].padding.w,asteroids[i].padding.h};
		SDL_RenderCopyEx(ren, tileset, &asteroids[i].padding, &dst, asteroids[i].rotation, NULL, SDL_FLIP_NONE);
	}
}

double accumulate = 0;
int spawn_interval = 100;
void update(double &dt)
{
	accumulate += dt;

	if(accumulate >= spawn_interval)
	{
		for (int i = 0; i < POOL_SIZE; ++i)
		{
			if(!asteroids[i].active)
			{
				asteroids[i] = Asteroid({rand()%wins.x,-124}, {(rand()%RAND_MAX) ? rand()%10 : -(rand()%10),rand()%10}, {TILE_SIZE_X*(rand()%8),TILE_SIZE_Y*(rand()%8),TILE_SIZE_X,TILE_SIZE_Y}, true);
				//printf("Spawn asteriod. x: %d, y: %d, sx: %d,sy: %d,px: %d,py: %d\n",asteroids[i].pos.x,asteroids[i].pos.y,asteroids[i].speed.x,asteroids[i].speed.y,asteroids[i].padding.x,asteroids[i].padding.y);
				break;
			}
		}
		accumulate = 0;
	}

	for (int i = 0; i < POOL_SIZE; ++i)
	{
		if(asteroids[i].active)
		{
			if(((asteroids[i].pos.x + asteroids[i].padding.w) > wins.x && asteroids[i].speed.x > 0) || asteroids[i].pos.x < 0) asteroids[i].speed.x = -asteroids[i].speed.x;
			if(asteroids[i].pos.y >= wins.x || asteroids[i].pos.y < -TILE_SIZE_Y || (asteroids[i].pos.x > wins.x))
			{
				asteroids[i].active = false;
				asteroids[i].rotation = 0;
				//printf("Delete asteriod. x: %d, y: %d, sx: %d,sy: %d,px: %d,py: %d\n",asteroids[i].pos.x,asteroids[i].pos.y,asteroids[i].speed.x,asteroids[i].speed.y,asteroids[i].padding.x,asteroids[i].padding.y);
			}
			else
			{
				asteroids[i].pos.x += asteroids[i].speed.x;
				asteroids[i].pos.y += asteroids[i].speed.y;
				asteroids[i].rotation++;
			}
		}
	}
}

void loop()
{
	bool run = true;
	SDL_Event e;
	SDL_Surface *text;
	SDL_Texture *textt;
	SDL_Rect text_rect;
	double dt;
	Uint64 last;
	while(run)
	{
		Uint64 now = SDL_GetPerformanceCounter();
		dt = (double)(now - last) * 1000 / SDL_GetPerformanceFrequency();
		last = now;

		while(SDL_PollEvent(&e))
		{
			run = processEvent(e);
		}

		update(dt);
		render();
		text = TTF_RenderText_Solid(font, std::to_string(1000/dt).c_str(), {255,255,255,0});
		textt = SDL_CreateTextureFromSurface(ren, text);
		text_rect = {wins.x-text->w,wins.y-text->h,text->w,text->h};

		SDL_RenderCopy(ren, textt, NULL, &text_rect);

		SDL_FreeSurface(text);
		SDL_DestroyTexture(textt);

		SDL_RenderPresent(ren);

		SDL_Delay(16);
	}
}

int main(int argc, char *argv[])
{
	if(initSDL()) return 1;
	if(loadAssets()) return 1;
	asteroids = (Asteroid*)calloc(sizeof(Asteroid)*100,1);

	loop();

	quitSDL();
	free(asteroids);

	return 0;
}