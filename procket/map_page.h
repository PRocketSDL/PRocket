#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "menu.h"
#include "textRendering.h"




void RenderMapPage()
{
    CreateText("Map placeholder", WINDOW_WIDTH/3, WINDOW_HEIGHT/3, OPT_MENU_FONT, 70, title, rtitle);
}
