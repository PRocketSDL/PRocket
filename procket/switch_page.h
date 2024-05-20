#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "menu.h"
#include "textRendering.h"

//All option pages
#include "map_page.hpp"
#include "settings_page.h"




void RenderMainMenu()
{
    //Msg | pos(x, y) | FontStruct | Font size | Texture | Rect | R | G | B | A

    CreateText("ROCKETSIM", WINDOW_WIDTH/4, WINDOW_HEIGHT/3, titleFont, 70, title, rtitle);
    CreateText("Open existing", WINDOW_WIDTH/12*5+5, WINDOW_HEIGHT/3, menuFont, 40, MenuOpen, ropen);
    CreateText("Create new map", WINDOW_WIDTH/12*5+10, WINDOW_HEIGHT/3+20, menuFont, 40, create, rcreate);
    CreateText("Settings", WINDOW_WIDTH/12*5-10, WINDOW_HEIGHT/3+40, menuFont, 40, sett, rsett);
    CreateText("Exit", WINDOW_WIDTH/12*5-10, WINDOW_HEIGHT/3+60, menuFont, 40, exitbtn, rexitbtn);

    //pentru scrisul rosu
    CreateText("Open existing", WINDOW_WIDTH/12*5+5, WINDOW_HEIGHT/2, menuFont, 40, hopen, ropen, 255, 0, 0, 255);
    CreateText("Create new map", WINDOW_WIDTH/12*5-10, WINDOW_HEIGHT/2+20, menuFont, 40, hcreate, rcreate, 255, 0, 0, 255);
    CreateText("Settings", WINDOW_WIDTH/12*5+30, WINDOW_HEIGHT/2+40, menuFont, 40, hsett, rsett, 255, 0, 0, 255);
    CreateText("Exit", WINDOW_WIDTH/12*5+50, WINDOW_HEIGHT/2+60, menuFont, 40, hexitbtn, rexitbtn, 255, 0, 0, 255);
}

//Clear all graphics before switching a different page option
void ClearMainGraphics()
{
    SDL_DestroyTexture(title);	
    SDL_DestroyTexture(MenuOpen);
    SDL_DestroyTexture(hopen);
    SDL_DestroyTexture(create);
    SDL_DestroyTexture(hcreate);
    SDL_DestroyTexture(sett);
    SDL_DestroyTexture(hsett);
    SDL_DestroyTexture(exitbtn);
    SDL_DestroyTexture(hexitbtn);
    #ifdef DEBUG_MENU
        std::cout << "[Menu Event] Clear main graphics\n";
    #endif
}

void SwitchPage(int menuState)
{
    //check the menu option number before switching
    if(menuState == 2)
    {
        ClearMainGraphics();
        RenderMapPage();
        #ifdef DEBUG_MENU
            std::cout << "[Page Switch Event] Create new map\n";
        #endif
    }

    if(menuState == 3)
    {
       ClearMainGraphics();
       RenderSettingsPage();
       #ifdef DEBUG_MENU
           std::cout << "[Page Switch event] Settings page\n";
       #endif
    }
}
