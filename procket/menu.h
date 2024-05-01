#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 
const char* WINDOW_TITLE = "PRocket";
const char* FONT_NAME = "assets/fonts/menu_font.ttf";
const char* MAIN_TITLE_FONT = "assets/fonts/menu_font.ttf";
const char* OPT_MENU_FONT = "assets/fonts/menu_opt.ttf";
const int FONT_SIZE = 60;
const int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

int msX, msY;

SDL_Window* Window; // Window created by SDL.
SDL_Renderer* Renderer; // The renderer that shows our textures.
SDL_Renderer* Renderergray;
SDL_Renderer* Renderergreen;
SDL_Renderer* Rendererbrown;
SDL_Event WindowEvent; // Event capturer from SDL Window.
SDL_Event event; //For the mouse events
SDL_Surface* TextSurface; //variabila temporara. 
SDL_Texture* title;

SDL_Texture* open;
SDL_Texture* create;
SDL_Texture* sett;
SDL_Texture* exitbtn;


SDL_Texture* hopen;
SDL_Texture* hcreate;
SDL_Texture* hsett;
SDL_Texture* hexitbtn;


SDL_Rect rtitle;
SDL_Rect ropen;
SDL_Rect rcreate;
SDL_Rect rsett;
SDL_Rect rexitbtn;
