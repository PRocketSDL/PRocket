#pragma once


#define ElemCout_Debug


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include "textRendering.h"
#include "menu.h"

#define FD_DEBUG
#include "FD_IO.h"

#include "switch_page.h"
#define MAX_ELEM 1001
#include <string>


int msX[MAX_ELEM], msY[MAX_ELEM]; //for mouse inputs


bool map[720][1280];
int movPos;
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

//Variabile pt numararea si individualizarea elementelor de acelasi tip
int cntT1 = 0;
int cntT2 = 0;
int cntT3 = 0;
int cntT4 = 0;
int cntT5 = 0;
int cntT6 = 0;
int cntT7 = 0;



int ctype[MAX_ELEM] = {1};
int i;
struct pofint{
  int x;
  int y;
}; 

#include "rmap_utils.h"

pofint rpovif[100]; //pentru racheta;
int nr_rpovif;

struct aelem {
  int type;
  int d=0;           // pentru cerc
  int dc = 0;        //pentru stele (diametru caldura)
  int dm = 0;        //pentru gauri negre (diametru maxim) si pentru stele, pentru a calcula cat de aproape se poate afla racheta de aceasta stea.
  int temp = 0;      //pentru stele: 0-stea rece; 1-stea calduta; 2-stea calda; 3-stea foarte calda; 4-stea fierbinte.
  int x;             // generic
  int y;             // generic 
  short cycle = 0;
  int nrpovif = 0;
  pofint povif[100]; //pentru planeta mergatoare, asteroid si gauri negre
};

aelem E[MAX_ELEM]; //lista cu elementele
int nr_elem = 0;
void RenderMapPage();
void ClearMainGraphics();
void RenderMainMenu();


void MakeElem(int X, int Y){
  if(ctype[nr_elem] == 1){
    E[nr_elem].type = 1;
    cntT1 ++;
}
  if(ctype[nr_elem] == 2){
    E[nr_elem].type = 2;
    E[nr_elem].d = 25;
    cntT2 ++;
}
  if(ctype[nr_elem] == 3 || ctype[nr_elem] == 5){
    if(finpon){
   if(ctype[nr_elem] == 3){   E[nr_elem].type = 3;}
      else{ E[nr_elem].type = 5; }
      E[nr_elem].d = 25;
      E[nr_elem].x = E[nr_elem-movPos].x;
      E[nr_elem].y = E[nr_elem-movPos].y;
      for(int i=0;i<movPos;i++){
        E[nr_elem].povif[i].x = E[nr_elem - movPos + i].x;
        E[nr_elem].povif[i].y = E[nr_elem - movPos + i].y;
      }
      
      E[nr_elem].nrpovif = movPos;
      movPos = 0;
    }
    else{
      E[nr_elem].type = 8;
      movPos++;
    }

    cntT3 ++;

  }
  if(ctype[nr_elem] == 6){
    E[nr_elem].type = 6;
    E[nr_elem].x = X/2;
    E[nr_elem].y = Y/2;
    rpovif[nr_rpovif].x = X/2;
    rpovif[nr_rpovif].y = Y/2;
    nr_rpovif++;
    cntT6 ++;
  }
  if(ctype[nr_elem] == 7){
    E[nr_elem].type = 7;
    E[nr_elem].d = 4;
    E[nr_elem].dm = E[nr_elem].d*16;
    E[nr_elem].cycle = 2;
    cntT7 ++;
  }
  if(ctype[nr_elem] == 4){
    E[nr_elem].type = 4;
    E[nr_elem].temp = 2;
    E[nr_elem].d = 15;
    E[nr_elem].dm = E[nr_elem].d * E[nr_elem].temp + 5;
    cntT4 ++;
  }
if(ctype[nr_elem] == 1 || ctype[nr_elem] == 2 || (ctype[nr_elem] == 3 && !finpon) || (ctype[nr_elem] == 5 && !finpon) || ctype[nr_elem] == 7 || ctype[nr_elem] == 4){
  E[nr_elem].x = X/2;
  E[nr_elem].y = Y/2;
}
}
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
                SDL_GetMouseState(&msX[nr_elem], &msY[nr_elem]);
                std::cout << "Mouse pos on click: " <<  msX<<" "<<msY<<'\n';
                MakeElem(msX[nr_elem], msY[nr_elem]);
                nr_elem++;
                break;
            
        }
        
        
	    case SDL_KEYDOWN:
          
            if(WindowEvent.key.keysym.sym == SDLK_1)
              if(finpon)
              ctype[nr_elem] = 1;
            if(WindowEvent.key.keysym.sym == SDLK_2)
              if(finpon)
              ctype[nr_elem] = 2;
            if(WindowEvent.key.keysym.sym == SDLK_3)
              if(movPos == 0 && finpon){
                 ctype[nr_elem] = 3;
                 finpon = false;
              }
            if(WindowEvent.key.keysym.sym == SDLK_4)
              ctype[nr_elem] = 4;
            if(WindowEvent.key.keysym.sym == SDLK_6)
              ctype[nr_elem] = 6;
            if(WindowEvent.key.keysym.sym == SDLK_5)
              if(movPos == 0 && finpon){
              ctype[nr_elem] = 5;
              finpon = false;
              }
            if(WindowEvent.key.keysym.sym == SDLK_7)
              ctype[nr_elem] = 7;

            if(WindowEvent.key.keysym.sym == SDLK_s)
            {
              SaveFileDialog();
              WriteRMAP(rmap_o);
            }
            if(WindowEvent.key.keysym.sym == SDLK_LEFT)
            {
              SDL_RenderSetScale(Renderer, 1, 1);
                ClearMainGraphics();
                RenderMainMenu();
            }
            std::cout <<'\n'<< "ctype: "<<ctype[nr_elem]<<'\n';
            #ifdef ElemCout_Debug
              std::cout << "Element Count: " << nr_elem << "\n";
              std::cout << "Elem type1: " << cntT1 << "\n";
              std::cout << "Elem type2: " << cntT2 << "\n";
              std::cout << "Elem type3: " << cntT3 << "\n";
              std::cout << "Elem type4: " << cntT4 << "\n";
              std::cout << "Elem type5: " << cntT5 << "\n";
              std::cout << "Elem type6: " << cntT6 << "\n";
              std::cout << "Elem type7: " << cntT7 << "\n";
            #endif
            /*rmapX[nr_elem] = msX;
            rmapY[nr_elem] = msY;
            if(WindowEvent.key.keysym.sym == SDLK_t)
            {
              //+1 pt ca pozitile sunt = 0 (initial)
              for(int i = 0; i < nr_elem+1; i++)
              {
                std::cout << "Test: X= " << rmapX[i] << " | " << "Y= " << rmapY[i] << "\n";
              }
            }*/
            if(WindowEvent.key.keysym.sym == SDLK_RETURN && !finpon && movPos > 0){
              finpon = true;
              MakeElem(msX[nr_elem], msY[nr_elem]);
              nr_elem++;
            }
            if(finpon) std::cout<<"Is true \n";
              else std::cout<<"Is false \n";

            
        break;
        }
    }
    return true;
}
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
           // screen.pixel(centreX + x, centreY + y, vect);
        }
      if(parts>=3){
             SDL_RenderDrawPointF(Renderer, centreX-x, centreY-y);
 
             map[centreY-y][centreX-x] = false;
          //  screen.pixel(centreX - x, centreY - y, vect);
      }
       if(parts>=4){
            SDL_RenderDrawPointF(Renderer, centreX-x, centreY+y);
             map[centreY+y][centreX-x] = false;
       }
       if(parts>=5){
           SDL_RenderDrawPointF(Renderer, centreX+y, centreY-x);
             map[centreY-x][centreX+y] = false;
       }
          //  screen.pixel(centreX + y, centreY - x, vect);
       if(parts>=6){
            SDL_RenderDrawPointF(Renderer, centreX+y, centreY+x);
             map[centreY+x][centreX+y] = false;
       }
         //  screen.pixel(centreX + y, centreY + x)
       if(parts>=7){
           SDL_RenderDrawPointF(Renderer, centreX-y,  centreY-x);
             map[centreY-x][centreX-y] = false;
       }
          // screen.pixel(centreX - y, centreY - x, vect);
       if(parts>=8){
           SDL_RenderDrawPointF(Renderer, centreX-y, centreY+x);
             map[centreY+x][centreX-y] = false;
        //   screen.pixel(centreX - y, centreY + x, vect);
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
      if(E[i].type == 1)
        point(E[i].x, E[i].y);
      if(E[i].type == 2)
        circle(E[i].x, E[i].y, E[i].d);
      if(E[i].type == 3){
        if(E[i].cycle == E[i].nrpovif) E[i].cycle = 0;
        circle(E[i].povif[E[i].cycle].x, E[i].povif[E[i].cycle].y, E[i].d);
        E[i].cycle ++;
      }


      if(E[i].type == 8){
        SDL_SetRenderDrawColor(Renderer, 137, 139, 140, 200);
        point(E[i].x, E[i].y);
      }
      if(E[i].type == 6){
         SDL_SetRenderDrawColor(Renderer, 36, 226, 52, 230);
         point(E[i].x, E[i].y);
      }
    if(E[i].type == 5){
        SDL_SetRenderDrawColor(Renderer, 112, 63, 0, 240);
        if(E[i].cycle == E[i].nrpovif){ 
          E[i].type = 9; 
          E[i].x = E[i].povif[E[i].cycle-1].x; 
          E[i].y = E[i].povif[E[i].cycle-1].y;
          circle(E[i].x, E[i].y, E[i].d);
        }
        else{
        circle(E[i].povif[E[i].cycle].x, E[i].povif[E[i].cycle].y, E[i].d);
       E[i].cycle++;}
     }
    if(E[i].type == 9){
      SDL_SetRenderDrawColor(Renderer, 122, 63, 0, 240);
      circle(E[i].x, E[i].y, E[i].d);
    }
    if(E[i].type == 7){
        SDL_SetRenderDrawColor(Renderer, 71, 5, 89, 210);
        if(E[i].d == E[i].dm){
            E[i].type = 10;
        }
        circle(E[i].x, E[i].y, E[i].d);
        E[i].d += E[i].cycle;
    }
    if(E[i].type == 10){
      SDL_SetRenderDrawColor(Renderer, 71, 5, 89, 210);
      circle(E[i].x, E[i].y, E[i].d);
    }
    if(E[i].type == 4){
      SDL_SetRenderDrawColor(Renderer, 252, 240, 10, 240);
      circle(E[i].x, E[i].y, E[i].d);
      SDL_SetRenderDrawColor(Renderer, 137, 139, 140, 150);
      circle(E[i].x, E[i].y, E[i].dm);
    }
    }
    
   // for(int i=0;i<=nrterm;i++){
//	if(!term[i].contr) continue
	//	else line(term[i].x-term[i].di/3, term[i].y-term[i].di/3, term[i].x+term[i].di/3, term[i].y+term[i].di/3);
//	cout<<term[i].x<<" "<<term[i].y<<" "<<term[i].di<<endl;
		SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);  
    SDL_Delay(500);
}
	



void RenderMapPage()
{
  SDL_RenderSetScale(Renderer, 2, 2);
   while(IsPollingEventM()){
      Render();
   }
}
