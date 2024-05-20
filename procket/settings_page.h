#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "textRendering.h"



void RenderSettingsPage()
{
    CreateText("Settings placeholder", WINDOW_WIDTH/3, WINDOW_HEIGHT/3, menuFont, 70, title, rtitle);
}
