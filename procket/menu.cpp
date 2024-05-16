#define DEBUG_FD
#define DEBUG_RMAP_FILE
#define DEBUG_MENU
#define DEBUG_MOUSE_POS
#define DEBUG_KEY_EVENT
#define DEBUG_MAP_PAGE
#define DEBUG_CONFIG
//#define STUPID_SPAM




#include "menu.h"
#include "switch_page.h"
#include "FD_IO.h"
#include "Rmap_File.h"
//#include "Config_Utils.hpp"

#include "ext_deps/ANSI_Utils.h"

//Default menu option (Open)
int opt=1;







void CreateWindow() {
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
    SDL_DestroyTexture(open);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
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
    if(opt==1)  SDL_RenderCopy(Renderer, hopen, NULL, &ropen);else SDL_RenderCopy(Renderer, open, NULL, &ropen);    
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

    CreateWindow();

    //The initial state
    RenderMainMenu();


    while(IsPollingEvent()){
        RenderText();
	}

    ClearMemory();
    return EXIT_SUCCESS;
}
