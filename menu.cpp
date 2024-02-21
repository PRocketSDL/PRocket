#include "menu.h"

int opt=1;

void CreateWindow() {
    Window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!Window)
        std::cout << "There was a problem creating the window.";
    Renderer = SDL_CreateRenderer(Window, -1, 0);
    if (!Renderer)
        std::cout << "There was a problem creating the renderer.";
}

void CreateText(const char* message, int x, int y, const char* font_name,  int font_size, SDL_Texture* &TextTexture, SDL_Rect &TextRect,    Uint8 R=255, Uint8 G=255, Uint8 B=255, Uint8 A=255) {
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_name, font_size);
    if (!font)
        std::cout << "Couldn't find/init open ttf font named " <<font_name<<std::endl;
    TextSurface = TTF_RenderText_Solid(font, message, {R, G, B, A});
    TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    TextRect.x = x; // Center horizontaly
    TextRect.y = y; // Center verticaly
    TextRect.w = TextSurface->w;
    TextRect.h = TextSurface->h;

    
    // After you create the texture you can release the surface memory allocation because we actually render the texture not the surface.
    SDL_FreeSurface(TextSurface);
    

    TTF_Quit();
}

bool IsPollingEvent() {
    while(SDL_PollEvent(&WindowEvent)) {
	
        switch (WindowEvent.type) {
            case SDL_QUIT:
		 return false;
	    case SDL_KEYDOWN:
		opt++;
		opt = ( opt>4 ) ? 1 : opt;
		WindowEvent.type= -1;
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
   std::cout<<WindowEvent.type<<std::endl;
   if(opt==1)  SDL_RenderCopy(Renderer, hopen, NULL, &ropen);else SDL_RenderCopy(Renderer, open, NULL, &ropen);    
   if(opt==2)  SDL_RenderCopy(Renderer, hcreate, NULL, &rcreate);else SDL_RenderCopy(Renderer, create, NULL, &rcreate);
   if(opt==3)  SDL_RenderCopy(Renderer, hsett, NULL, &rsett);else SDL_RenderCopy(Renderer, sett, NULL, &rsett);
   if(opt==4)  SDL_RenderCopy(Renderer, hexitbtn, NULL, &rexitbtn);else SDL_RenderCopy(Renderer, exitbtn, NULL, &rexitbtn);
   
    SDL_RenderPresent(Renderer); // Render everything that's on the queue.
    SDL_Delay(20); // Delay to prevent CPU overhead
}


void ClearMemory() {
    SDL_DestroyTexture(title);	
    SDL_DestroyTexture(open);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    std::cout << "ClearMemory() function completed succcesfully" <<opt<<" "<<WindowEvent.type<<" "<<SDL_QUIT<<" "<<SDL_KEYUP<<" "<<SDL_KEYDOWN<<std::endl;
}

int main() {
    CreateWindow();

    CreateText("PROCKET", WINDOW_WIDTH/3, WINDOW_HEIGHT/4, "menu_font.ttf", 70, title, rtitle);

    CreateText("Open existing", WINDOW_WIDTH/2, WINDOW_HEIGHT/3, "menu_opt.ttf",  40, open, ropen);
    CreateText("Create new map", WINDOW_WIDTH/2, WINDOW_HEIGHT/3+20, "menu_opt.ttf", 40, create, rcreate);
    CreateText("Settings", WINDOW_WIDTH/2, WINDOW_HEIGHT/3+40, "menu_opt.ttf", 40, sett, rsett);
    CreateText("Exit", WINDOW_WIDTH/2, WINDOW_HEIGHT/3+60, "menu_opt.ttf", 40, exitbtn, rexitbtn);
   
    //pentru scrisul rosu
    CreateText("Open existing", WINDOW_WIDTH/3, WINDOW_HEIGHT/3, "menu_opt.ttf",  40, hopen, ropen, 255, 0, 0, 255);
    CreateText("Create new map", WINDOW_WIDTH/3, WINDOW_HEIGHT/3+20, "menu_opt.ttf", 40, hcreate, rcreate, 255, 0, 0, 255);
    CreateText("Settings", WINDOW_WIDTH/3, WINDOW_HEIGHT/3+40, "menu_opt.ttf", 40, hsett, rsett, 255, 0, 0, 255);
    CreateText("Exit", WINDOW_WIDTH/3, WINDOW_HEIGHT/3+60, "menu_opt.ttf", 40, hexitbtn, rexitbtn, 255, 0, 0, 255);
 
    while(IsPollingEvent()){
    RenderText();

	
	}

    
    ClearMemory();
    return EXIT_SUCCESS;
}