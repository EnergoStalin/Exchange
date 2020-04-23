//REquire SDL2mixer SDL2 tinyfiledialogs curses
//Compile
//g++ -I../lib audio.cpp ../lib/tinyfiledialogs/tinyfiledialogs.c -o audio -lSDL2 -lSDL2_mixer -lcurses


#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <curses.h>
#include "tinyfiledialogs/tinyfiledialogs.h"

int main(int argc, const char **argv)
{

	if(Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) { printf("%s\n", "Audio system was broken."); return 1; }

	char *filename = NULL;
	if(argc == 1)
	{
		const char *filterPatterns[] = {"*.mp3"};
		filename = (char*)tinyfd_openFileDialog("Select Audio To Play.",".",1,filterPatterns,NULL,0);
	}
	else
	{
		filename = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));
		if(filename == NULL) printf("Malloc error\n");
		strcpy(filename,argv[1]);
	}

	Mix_OpenAudio(44800, AUDIO_S16SYS, 2, 640);
	Mix_Music *music = Mix_LoadMUS(filename);
	if(!music) { printf("Cant load file [%s]\tMIX:[%s]\n", filename,Mix_GetError()); return 1; }


	Mix_PlayMusic(music, 1);

	initscr();
	SDL_Point wnd_size = {getmaxx(stdscr),getmaxy(stdscr)};
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	while(!SDL_QuitRequested())
	{
		int c = getch();
		switch(c)
		{
			case 'q':
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
			break;
			case 'p':
				(!Mix_PausedMusic()) ? Mix_PauseMusic() : Mix_ResumeMusic();
			break;
			case KEY_RESIZE:
				wnd_size = {getmaxx(stdscr),getmaxy(stdscr)};
			break;
		}
		clear();
		printw("Playing %s\n", filename);
		printw("x: %d\ty: %d\n", wnd_size.x,wnd_size.y);
		SDL_Delay(250);
	}

	endwin();

	Mix_FreeMusic(music);
	Mix_Quit();

	free(filename);

	return 0;
}