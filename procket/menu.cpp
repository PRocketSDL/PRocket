#include "menu.h"
#include "switch_page.h"


//Default menu option (Open)
int opt=1;


//Char variable to store the file name of the rmap file
char open_rmap[1024];
FILE *f;

//#define debug
//Maybe we are gonna need this :thinking:

void CreateWindow() {
    Window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (!Window)
        std::cout << "\x1b[38;5;196mFailed to create window!\x1b[0\n";
    
    Renderer = SDL_CreateRenderer(Window, -1, 0);

    if (!Renderer)
        std::cout << "\x1b[38;5;196mFailed to create renderer!\x1b[0\n";
}


void ClearMemory() {
    SDL_DestroyTexture(title);	
    SDL_DestroyTexture(open);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
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
                std::cout << "[Menu Event] Open existing + Open file dialog\n";

                //Execute the shell command for returning the open file dialog window
                f = popen("zenity --file-selection --title='Select rocket map file'", "r");
                fgets(open_rmap, 1024, f);
                if(strlen(open_rmap) == 0)
                    std::cout << "File selection: none\n";
        
                else
                    std::cout << "File selection: " << open_rmap << "\n";
            }

            if(opt == 2 && WindowEvent.key.keysym.sym == SDLK_RETURN)
            {
                SwitchPage(opt);
                std::cout << "[Menu Event] Create new map\n";
            }

            if(opt == 3 && WindowEvent.key.keysym.sym == SDLK_RETURN)
            {
                SwitchPage(opt);
                std::cout << "[Menu Event] Settings\n";
            }

            if(opt == 4 && WindowEvent.key.keysym.sym == SDLK_RETURN)
            {
                std::cout << "[Menu Event] Exit\n";
                ClearMemory();
                exit(0);
            }

            //if statement for returning back to the main menu by pressing the left key
            if(WindowEvent.key.keysym.sym == SDLK_LEFT)
            {
                ClearMainGraphics();
                RenderMainMenu();
		std::cout << "[Key Event] Return main menu\n";
            }
            
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
    #ifdef debug 
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
    CreateWindow();

    //The initial state
    RenderMainMenu();

 
    while(IsPollingEvent()){
        RenderText();
	}

    ClearMemory();
    return EXIT_SUCCESS;
}
