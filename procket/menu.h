#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
 
const char* WINDOW_TITLE = "PRocket";
const char* FONT_NAME = "menu_font.ttf";
const int FONT_SIZE = 60;
int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
 
SDL_Window* Window; // Window created by SDL.
SDL_Renderer* Renderer; // The renderer that shows our textures.
SDL_Event WindowEvent; // Event capturer from SDL Window.
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
