#define DEBUG_FD
#define DEBUG_RMAP_FILE
#define DEBUG_MENU
#define DEBUG_MOUSE_POS
#define DEBUG_KEY_EVENT
#define DEBUG_MAP_PAGE
#define DEBUG_CONFIG
#define DEBUG_FONT
//#define STUPID_SPAM




#include "menu.h"
#include "switch_page.h"
#include "FD_IO.h"
#include "Rmap_File.h"
//#include "Config_Utils.hpp"

#include "ext_deps/ANSI_Utils.h"

//Default menu option (Open)
int opt=1;





void LoadFonts()
{
    const uint8_t menuFontSize = 40;
    const uint8_t titleFontSize = 70;
    const uint8_t rocketFontSize = 5;
    menuFont = TTF_OpenFont("assets/fonts/menu_opt.ttf", menuFontSize);
    titleFont = TTF_OpenFont("assets/fonts/menu_font.ttf", titleFontSize);
    rocketFont = TTF_OpenFont("assets/fonts/rocket.otf", rocketFontSize);

    if(!menuFont)
    {
        XtermFG(FG, 196);
        std::cout << "Failed to load \"assets/fonts/menu_opt.ttf\"\n";
        CresetAll();
        exit(1);
    }
    #ifdef DEBUG_FONT
        else
        {
            std::cout << "[Font Loader] -> menu_opt.ttf loaded\n";
        }
    #endif

    if(!titleFont)
    {
        XtermFG(FG, 196);
        std::cout << "Failed to load \"assets/fonts/menu_font.ttf\"\n";
        CresetAll();
        exit(1);
    }
    #ifdef DEBUG_FONT
        else
        {
            std::cout << "[Font Loader] -> menu_font.ttf loaded\n";
        }
    #endif

    if(!rocketFont)
    {
        XtermFG(FG, 196);
        std::cout << "Failed to load \"assets/fonts/rocket.otf\"\n";
        CresetAll();
        exit(1);
    }
    #ifdef DEBUG_FONT
        else
        {
            std::cout << "[Font Loader] -> rocket.otf loaded\n";
        }
    #endif
}

void CreateSDLWindow() {
    Window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (!Window)
    {
        XtermFG(FG, 196);
        std::cout << "Failed to create window!\n";
        CresetAll();
    }

    Renderer = SDL_CreateRenderer(Window, -1, 0);

    if (!Renderer)
    {
        XtermFG(FG, 196);
        std::cout << "Failed to create renderer!\n";
        CresetAll();
    }
}


void ClearMemory() {
    SDL_DestroyTexture(title);	
    SDL_DestroyTexture(MenuOpen);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 //   SaveConfig();
    std::cout << "ClearMemory() function completed succcesfully " <<opt<<" "<<WindowEvent.type<<" "<<SDL_QUIT<<" "<<SDL_KEYUP<<" "<<SDL_KEYDOWN<<std::endl;
}

bool IsPollingEvent() {
    while(SDL_PollEvent(&WindowEvent)) {
        switch (WindowEvent.type) {
            case SDL_QUIT:
		          return false;
	          case SDL_KEYDOWN:
              //simple algorithms for switching menu options
              if(WindowEvent.key.keysym.sym == SDLK_UP)
              {
                  opt--;
                  opt = ( opt<1 ) ? 1 : opt;
		          WindowEvent.type= -1;
              }

              if(WindowEvent.key.keysym.sym == SDLK_DOWN)
              {
                  opt++;
                  opt = ( opt>4 ) ? 4 : opt;
		          WindowEvent.type= -1;
              }
              //Perfect!

               if(opt == 1 && WindowEvent.key.keysym.sym == SDLK_RETURN)
               {
                  #ifdef DEBUG_MENU
                    std::cout << "[Menu Event] -> Open existing + Open file dialog\n";
                  #endif
                  ReadRMAP();
               }

                if(opt == 2 && WindowEvent.key.keysym.sym == SDLK_RETURN)
                {
                  SwitchPage(opt);
                  #ifdef DEBUG_MENU
                    std::cout << "[Menu Event] -> Create new map\n";
                  #endif
                }

                if(opt == 3 && WindowEvent.key.keysym.sym == SDLK_RETURN)
                {
                  SwitchPage(opt);
                  #ifdef DEBUG_MENU
                    std::cout << "[Menu Event] -> Settings\n";
                  #endif
                }

                if(opt == 4 && WindowEvent.key.keysym.sym == SDLK_RETURN)
                {
                  #ifdef DEBUG_MENU
                    std::cout << "[Menu Event] -> Exit\n";
                  #endif
                  ClearMemory();
                  exit(0);
                }

                //if statement for returning back to the main menu by pressing the left key
                if(WindowEvent.key.keysym.sym == SDLK_LEFT)
                {
                  ClearMainGraphics();
                  RenderMainMenu();
                  #ifdef DEBUG_KEY_EVENT
                      std::cout << "[Key Event] -> Return main menu\n";
                  #endif
                }

            case SDL_MOUSEBUTTONDOWN:
              switch (WindowEvent.button.button)
              {
                case SDL_BUTTON_LEFT:
                  SDL_GetMouseState(&msX, &msY);
                  #ifdef DEBUG_MOUSE_POS
                    std::cout << "Left click\n";
                    std::cout << "Mouse pos on click: " << "x= " << msX << " y= " << msY << "\n";
                  #endif
                break;
                case SDL_BUTTON_RIGHT:
                  SDL_GetMouseState(&msX, &msY);
                  #ifdef DEBUG_MOUSE_POS
                    std::cout << "Right Click\n";
                    std::cout << "Mouse pos on click: " << "x= " << msX << " y= " << msY << "\n";
                  #endif
                break;
              }
            break;
		    break;
	        default:
		        break; 
        }
	    WindowEvent.type = -1;
    }
    return true;
}

void RenderText() {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0); //culoarea background-ului
    SDL_RenderClear(Renderer); 


    SDL_RenderCopy(Renderer, title, NULL, &rtitle);
    #ifdef STUPID_SPAM
    std::cout<< "Render copy: "<<WindowEvent.type<<std::endl; //Too much spam lmao
    #endif
    if(opt==1)  SDL_RenderCopy(Renderer, hopen, NULL, &ropen);else SDL_RenderCopy(Renderer, MenuOpen, NULL, &ropen);    
    if(opt==2)  SDL_RenderCopy(Renderer, hcreate, NULL, &rcreate);else SDL_RenderCopy(Renderer, create, NULL, &rcreate);
    if(opt==3)  SDL_RenderCopy(Renderer, hsett, NULL, &rsett);else SDL_RenderCopy(Renderer, sett, NULL, &rsett);
    if(opt==4)  SDL_RenderCopy(Renderer, hexitbtn, NULL, &rexitbtn);else SDL_RenderCopy(Renderer, exitbtn, NULL, &rexitbtn);

    SDL_RenderPresent(Renderer); // Render everything that's on the queue.
    SDL_Delay(20); // Delay to prevent CPU overhead
}




int main() {

    #if defined _WIN32 || defined _WIN64
        SetTerminal();
    #endif
   // ConfigInit();

    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    CreateSDLWindow();

    LoadFonts();

    //The initial state
    RenderMainMenu();


    while(IsPollingEvent()){
        RenderText();
        RenderMainMenu();
	}

    ClearMemory();
    return EXIT_SUCCESS;
}
