#pragma once


#include <iostream>
#include <cmath>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "textRendering.h"
#include "menu.h"
#include "switch_page.h"


#define MAX_ELEM 1001
#define SDL_DELAY 100

bool map[720][1280];
int posr;
bool finpon = true;

//Tipuri:
//1-punct
//2-planeta statica
//3-planeta mergatoare
//4-soare/stea 
//5-asteroid
//6-punct de interes
//7-gaura neagra

//Tipuri speciale:
//8-punct interes planeta (P.I.P.)
//9-asteroid static 
//10 - gaura neagra cu diametru maxim

int ctype = 1;
int i;
struct pofint{
  int x;
  int y;
};   

pofint rpovif[100];  // pentru racheta;
int nr_rpovif;

struct aelem {
  int ELtype;
  int d=0;           // pentru cerc
  int dc = 0;        // pentru stele (diametru caldura)
  int dm = 0;        // pentru gauri negre (diametru maxim) si pentru stele, pentru a calcula cat de aproape se poate afla racheta de aceasta stea.
  int temp = 0;      // pentru stele: 0-stea rece; 1-stea calduta; 2-stea calda; 3-stea foarte calda; 4-stea fierbinte.
  int x;             // generic
  int y;             // generic 
  short cycle = 0;
  int nrpovif = 0;
  pofint povif[100]; // pentru planeta mergatoare, asteroid si gauri negre
};

aelem E[MAX_ELEM]; //lista cu elementele
int nr_elem = 0;
void RenderMapPage();
void ClearMainGraphics();
void RenderMainMenu();


void MakeElem(int X, int Y){
  if(ctype == 1){
    E[nr_elem].ELtype = 1;
}
  if(ctype == 2){
    E[nr_elem].ELtype = 2;
    E[nr_elem].d = 25;
}
  if(ctype == 3 || ctype == 5){
    if(finpon){
   if(ctype == 3){   E[nr_elem].ELtype = 3;}
      else{ E[nr_elem].ELtype = 5; }
      E[nr_elem].d = 25;
      E[nr_elem].x = E[nr_elem-posr].x;
      E[nr_elem].y = E[nr_elem-posr].y;
      for(int i=0;i<posr;i++){
        E[nr_elem].povif[i].x = E[nr_elem - posr + i].x;
        E[nr_elem].povif[i].y = E[nr_elem - posr + i].y;
      }

      E[nr_elem].nrpovif = posr;
      posr = 0;
    }
    else{
      E[nr_elem].ELtype = 4;
      posr++;
    }

  }
  if(ctype == 6){
    E[nr_elem].ELtype = 6;
    E[nr_elem].x = X/2;
    E[nr_elem].y = Y/2;
    rpovif[nr_rpovif].x = X/2;
    rpovif[nr_rpovif].y = Y/2;
    nr_rpovif++;
  }
  if(ctype == 7){
    E[nr_elem].ELtype = 7;
    E[nr_elem].d = 4;
    E[nr_elem].dm = E[nr_elem].d*16;
    E[nr_elem].cycle = 2;
  }
  if(ctype == 4){
    E[nr_elem].ELtype = 4;
    E[nr_elem].temp = 2;
    E[nr_elem].d = 15;
    E[nr_elem].dm = E[nr_elem].d * E[nr_elem].temp + 5;
  }
if(ctype == 1 || ctype == 2 || (ctype == 3 && !finpon) || (ctype == 5 && !finpon) || ctype == 7 || ctype == 4){
  E[nr_elem].x = X/2;
  E[nr_elem].y = Y/2;
}
}

//MARK: #include "Rmap_File.h"
#include "Rmap_File.h"
//DO NOT TOUCH IT!!!

bool IsPollingEventM() {
    while(SDL_PollEvent(&WindowEvent)) {

        switch (WindowEvent.type) {
            case SDL_QUIT:
        		    return false;
                break;

        case SDL_MOUSEBUTTONDOWN:
        switch (WindowEvent.button.button)
        {
            case SDL_BUTTON_LEFT:
                SDL_GetMouseState(&msX, &msY);
                #ifdef DEBUG_MAP_PAGE
                    std::cout << "[Map Page Debug] -> Mouse Pos (X, Y): " <<  msX<<" | "<<msY<<'\n';
                #endif
                MakeElem(msX, msY);
                nr_elem++;
                break;

        }


	    case SDL_KEYDOWN:

            if(WindowEvent.key.keysym.sym == SDLK_1)
              if(finpon)
              ctype = 1;
            if(WindowEvent.key.keysym.sym == SDLK_2)
              if(finpon)
              ctype = 2;
            if(WindowEvent.key.keysym.sym == SDLK_3)
              if(posr == 0 && finpon){
                 ctype = 3;
                 finpon = false;
              }
            if(WindowEvent.key.keysym.sym == SDLK_4)
              ctype = 4;
            if(WindowEvent.key.keysym.sym == SDLK_6)
              ctype = 6;
            if(WindowEvent.key.keysym.sym == SDLK_5)
              if(posr == 0 && finpon){
              ctype = 5;
              finpon = false;
              }
            if(WindowEvent.key.keysym.sym == SDLK_7)
              ctype = 7;
            if(WindowEvent.key.keysym.sym == SDLK_LEFT)
            {
              SDL_RenderSetScale(Renderer, 1, 1);
                ClearMainGraphics();
                RenderMainMenu();
            }
            #ifdef DEBUG_MAP_PAGE
                std::cout <<'\n'<< "ctype: "<<ctype<<'\n';
            #endif
            //Left Ctrl+S || Right Ctrl+S
            if(WindowEvent.key.keysym.sym == SDLK_s)
            {
              WriteRMAP();
            }

            if(WindowEvent.key.keysym.sym == SDLK_t)
            {
              ReadRMAP();
            }
            const Uint8 *numKeys = SDL_GetKeyboardState(NULL);
            
            std::cout << "num keys pressed: " << numKeys << "\n";
            if(WindowEvent.key.keysym.sym == SDLK_RETURN && !finpon && posr > 0){
              finpon = true;
              MakeElem(msX, msY);
              nr_elem++;
            }
            #ifdef DEBUG_MAP_PAGE
                if(finpon) 
                    std::cout<<"Is true \n";
                else 
                    std::cout<<"Is false \n";
            #endif
        break;
        }
    }
    return true;
}
//MARK: SDL Pol Event End
void point(float x, float y){
  SDL_RenderDrawPointF(Renderer, x, y);
  map[int(x)][int(y)] = false;
}

 void line(float x1, float y1, float x2, float y2){
             float dx = x2-x1;
             float dy = y2 - y1;
             float length = std::sqrt(dx*dx+dy*dy);
             float angle = std::atan2(dy, dx);
             for(float i=0;i<length;i++){
                            SDL_RenderDrawPointF(Renderer, x1+std::cos(angle)*i, y1 + std::sin(angle)*i);
                            map[int(y1+std::sin(angle)*i)][int(x1+std::cos(angle)*i)] = false;
             }

  };



void circle(int32_t centreX, int32_t centreY,
      int32_t diameter, int32_t parts=8){


      int32_t x = (diameter/2 - 1);
      int32_t y = 0;
      int32_t tx = 1;
      int32_t ty = 1;
      int32_t error = (tx - diameter);


      while (x >= y)
      {
         //  Each of the following renders an octant of the circle
        if(parts>=1){
             SDL_RenderDrawPointF(Renderer, centreX+x, centreY-y);
             map[centreY-y][centreX+x] = false;
        }
        if(parts>=2){
             SDL_RenderDrawPointF(Renderer, centreX+x, centreY+y);

             map[centreY+y][centreX+x] = false;
        }
      if(parts>=3){
             SDL_RenderDrawPointF(Renderer, centreX-x, centreY-y);

             map[centreY-y][centreX-x] = false;
      }
       if(parts>=4){
            SDL_RenderDrawPointF(Renderer, centreX-x, centreY+y);
             map[centreY+y][centreX-x] = false;
       }
       if(parts>=5){
           SDL_RenderDrawPointF(Renderer, centreX+y, centreY-x);
             map[centreY-x][centreX+y] = false;
       }
       if(parts>=6){
            SDL_RenderDrawPointF(Renderer, centreX+y, centreY+x);
             map[centreY+x][centreX+y] = false;
       }
       if(parts>=7){
           SDL_RenderDrawPointF(Renderer, centreX-y,  centreY-x);
             map[centreY-x][centreX-y] = false;
       }
       if(parts>=8){
           SDL_RenderDrawPointF(Renderer, centreX-y, centreY+x);
             map[centreY+x][centreX-y] = false;
       }
        if (error <= 0)
        {
           ++y;
           error += ty;
           ty += 2;
        }

        if (error > 0)
        {
          --x;
          tx += 2;
          error += (tx - diameter);
        }
    }

}

void Render() {
    SDL_RenderClear(Renderer);   
    SDL_SetRenderDrawColor(Renderer, 255,255, 255, 255); 
    SDL_RenderCopy(Renderer, title, NULL, &rtitle);
    SDL_RenderCopy(Renderer, open, NULL, &ropen);  
    for(i = 0;i<nr_elem;i++){
      SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
      if(E[i].ELtype == 1)
        point(E[i].x, E[i].y);
      if(E[i].ELtype == 2)
        circle(E[i].x, E[i].y, E[i].d);
      if(E[i].ELtype == 3){
        if(E[i].cycle == E[i].nrpovif) E[i].cycle = 0;
        circle(E[i].povif[E[i].cycle].x, E[i].povif[E[i].cycle].y, E[i].d);
        E[i].cycle ++;
      }


      if(E[i].ELtype == 4){
        SDL_SetRenderDrawColor(Renderer, 137, 139, 140, 200);
        point(E[i].x, E[i].y);
      }
      if(E[i].ELtype == 6){
         SDL_SetRenderDrawColor(Renderer, 36, 226, 52, 230);
         point(E[i].x, E[i].y);
      }
    if(E[i].ELtype == 5){
        SDL_SetRenderDrawColor(Renderer, 112, 63, 0, 240);
        if(E[i].cycle == E[i].nrpovif){ 
          E[i].ELtype = 9; 
          E[i].x = E[i].povif[E[i].cycle-1].x; 
          E[i].y = E[i].povif[E[i].cycle-1].y;
          circle(E[i].x, E[i].y, E[i].d);
        }
        else{
        circle(E[i].povif[E[i].cycle].x, E[i].povif[E[i].cycle].y, E[i].d);
       E[i].cycle++;}
     }
    if(E[i].ELtype == 9){
      SDL_SetRenderDrawColor(Renderer, 122, 63, 0, 240);
      circle(E[i].x, E[i].y, E[i].d);
    }
    if(E[i].ELtype == 7){
        SDL_SetRenderDrawColor(Renderer, 71, 5, 89, 210);
        if(E[i].d == E[i].dm){
            E[i].ELtype = 10;
        }
        circle(E[i].x, E[i].y, E[i].d);
        E[i].d += E[i].cycle;
    }
    if(E[i].ELtype == 10){
      SDL_SetRenderDrawColor(Renderer, 71, 5, 89, 210);
      circle(E[i].x, E[i].y, E[i].d);
    }
    if(E[i].ELtype == 4){
      SDL_SetRenderDrawColor(Renderer, 252, 240, 10, 240);
      circle(E[i].x, E[i].y, E[i].d);
      SDL_SetRenderDrawColor(Renderer, 137, 139, 140, 150);
      circle(E[i].x, E[i].y, E[i].dm);
    }
    }
		SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);  
    SDL_Delay(SDL_DELAY);
}




void RenderMapPage()
{
  SDL_RenderSetScale(Renderer, 2, 2);
   while(IsPollingEventM()){
      Render();
   }
}
