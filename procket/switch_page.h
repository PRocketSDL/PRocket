#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "menu.h"
#include "textRendering.h"

//All option pages
#include "map_page.cpp"
#include "settings_page.h"




void RenderMainMenu()
{
    CreateText("PROCKET", WINDOW_WIDTH/3, WINDOW_HEIGHT/3, MAIN_TITLE_FONT, 70, title, rtitle);

    CreateText("Open existing", WINDOW_WIDTH/2, WINDOW_HEIGHT/3, OPT_MENU_FONT,  40, open, ropen);
    CreateText("Create new map", WINDOW_WIDTH/2, WINDOW_HEIGHT/3+20, OPT_MENU_FONT, 40, create, rcreate);
    CreateText("Settings", WINDOW_WIDTH/2, WINDOW_HEIGHT/3+40, OPT_MENU_FONT, 40, sett, rsett);
    CreateText("Exit", WINDOW_WIDTH/2, WINDOW_HEIGHT/3+60, OPT_MENU_FONT, 40, exitbtn, rexitbtn);
   
    //pentru scrisul rosu
    CreateText("Open existing", WINDOW_WIDTH/3, WINDOW_HEIGHT/2, OPT_MENU_FONT,  40, hopen, ropen, 255, 0, 0, 255);
    CreateText("Create new map", WINDOW_WIDTH/3, WINDOW_HEIGHT/2+20, OPT_MENU_FONT, 40, hcreate, rcreate, 255, 0, 0, 255);
    CreateText("Settings", WINDOW_WIDTH/3, WINDOW_HEIGHT/2+40, OPT_MENU_FONT, 40, hsett, rsett, 255, 0, 0, 255);
    CreateText("Exit", WINDOW_WIDTH/3, WINDOW_HEIGHT/2+60, OPT_MENU_FONT, 40, hexitbtn, rexitbtn, 255, 0, 0, 255);
}

//Clear all graphics before switching a different page option
void ClearMainGraphics()
{
    SDL_DestroyTexture(title);	
    SDL_DestroyTexture(open);
    SDL_DestroyTexture(hopen);
    SDL_DestroyTexture(create);
    SDL_DestroyTexture(hcreate);
    SDL_DestroyTexture(sett);
    SDL_DestroyTexture(hsett);
    SDL_DestroyTexture(exitbtn);
    SDL_DestroyTexture(hexitbtn);
    std::cout << "[Menu Event] Clear main graphics\n";
}

void SwitchPage(int menuState)
{
    //check the menu option number before switching
    if(menuState == 2)
    {
        ClearMainGraphics();
        RenderMapPage();
        std::cout << "[Page Switch Event] Create new map\n";
    }

    if(menuState == 3)
    {
       ClearMainGraphics();
       RenderSettingsPage();
       std::cout << "[Page Switch event] Settings page\n";
    }
}
