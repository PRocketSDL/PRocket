#pragma once


#include <iostream>
#include <cmath>
#include <string>
#include <queue>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



#include "textRendering.h"
#include "menu.h"
#include "switch_page.h"
#include "textRendering.h"

#define MAX_ELEM 1001
#define SDL_DELAY 500
//pentru algortimul lui lee
bool map[720][1280];
int n,m, b[720][1280];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
const char* dir="SNEV";
char steps[1001];
long long int nrsteps;
int curstep=-1;

int defx = 30;
int defy = 30;
int shipx = defx;
int shipy = defy;

int posr;
bool finpon = true;
bool roadcalc;
//Tipuri:
//1-punct
//2-planeta statica
//3-planeta mergatoare
//4-soare/stea 
//5-asteroid
//6-punct de interes
//7-gaura neagra

//Tipuri speciale (nu pot fi puse de utilizator):
//8-punct interes planeta (PIP)
//9-asteroid static 
//10 - gaura neagra cu diametru maxim

int ctype = 1;
int i;
struct pofint{
  int x;
  int y;
};   
struct pofintline{
  int x;
  int y;
  int x2;
  int y2;
};
pofint rpovif[100];  // pentru racheta;
int nr_rpovif;

pofintline lines[100]; //pentru trasarea traseului facut de utilizator
int nr_lines=1;

struct aelem {
  int ELtype;
  int d=0;           // pentru planete statice/mergatoare.
  int dc = 0;        // pentru stele (diametru caldura)
  int dm = 0;        // pentru gauri negre (diametru maxim) si pentru stele, pentru a calcula cat de aproape se poate afla racheta de aceasta stea.
  int temp = 0;      // pentru stele: 0-stea rece; 1-stea calduta; 2-stea calda; 3-stea foarte calda; 4-stea fierbinte.
  int x;             // generic
  int y;             // generic 
  short cycle = 0;
  int nrpovif = 0; //pentru planeta mergatoare, asteroid si gauri negre
  pofint povif[100]; // pentru planeta mergatoare, asteroid si gauri negre
};

aelem E[MAX_ELEM]; //lista cu elementele
int nr_elem = 0;
void RenderMapPage();
void ClearMainGraphics();
void RenderMainMenu();

void MakeElem(int X, int Y){
  std::cout<<"got here!";
  if(ctype == 1){
    E[nr_elem].ELtype = 1;
}
  if(ctype == 2){
    E[nr_elem].ELtype = 2;
    E[nr_elem].d = 10;
}
  if(ctype == 3 || ctype == 5){
    if(finpon){
   if(ctype == 3){   E[nr_elem].ELtype = 3;}
      else{ E[nr_elem].ELtype = 5; }
      E[nr_elem].d = 10;
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
      E[nr_elem].ELtype = 8;
      posr++;
    }

  }
  if(ctype == 6){
    E[nr_elem].ELtype = 6;
    E[nr_elem].x = X/10;
    E[nr_elem].y = Y/10;
    rpovif[nr_rpovif].x = X/10;
    rpovif[nr_rpovif].y = Y/10;
    nr_rpovif++;
  }
  if(ctype == 7){
    E[nr_elem].ELtype = 7;
    E[nr_elem].d = 1;
    E[nr_elem].dm = E[nr_elem].d*15;
    E[nr_elem].cycle = 2;
  }
  if(ctype == 4){
    E[nr_elem].ELtype = 4;
    E[nr_elem].temp = 2;
    E[nr_elem].d = 10 + E[nr_elem].temp*2;
    E[nr_elem].dm = E[nr_elem].d * E[nr_elem].temp + 2;
  }
  if(ctype == 0){
    lines[nr_lines].x = lines[nr_lines-1].x2;
    lines[nr_lines].y = lines[nr_lines-1].y2;
    lines[nr_lines].x2 = X/10;
    lines[nr_lines].y2 = Y/10;
    nr_lines++;
  }
if(ctype == 1 || ctype == 2 || (ctype == 3 && !finpon) || (ctype == 5 && !finpon) || ctype == 7 || ctype == 4){
  E[nr_elem].x = X/10;
  E[nr_elem].y = Y/10;
}
if(ctype!=6){
	roadcalc = false;
	curstep = 0;
}
}



//MARK: #include "Rmap_File.h"

#include "Rmap_File.h"
//DO NOT TOUCH IT!!!


void clearb(){
  for(int i=0;i<720;i++)
    for(int j=0;j<1280;j++)
      b[i][j] = 0;


}
bool inmat(int i, int j){
  return i>=0 && j>=1 && i<=720 && j<=1280;
}
/*
magie!
d=0 -> jos (Sud)
d=1 -> sus (Nord)
d=2 -> stanga (Vest)
d=3 -> dreapta (Est)
*/

void drum(int destx, int desty){
     nrsteps = 0;
    if(shipx == destx && shipy == desty)
      return ;
    else{
      for(int d=0;d<=3;++d){
        int xnou = destx+dx[d];
        int ynou = desty+dy[d];
        if(inmat(xnou, ynou) && b[xnou][ynou] == b[destx][desty]-1){
          drum(xnou, ynou);
          steps[nrsteps++] = dir[d];
          std::cout<<"D"<<dir[d]<<" ";
          break;
        }
      }
    }
    std::cout<<"NRSTEPS:"<<nrsteps;


}

void lee(int istart, int jstart){

  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  clearb();
  std::queue <std::pair<int, int>> Q;
  Q.push(std::make_pair(istart, jstart));
  b[istart][jstart] = 0;
  while(!Q.empty()){
    int x = Q.front().first;
    int y = Q.front().second;
    Q.pop();
    for(int d=0;d<=3;++d){
      int inou = dx[d]+x;
      int jnou = dy[d]+y;
      if(inmat(inou, jnou) &&!map[inou][jnou]&& b[inou][jnou] == 0){

        b[inou][jnou] = b[x][y]+1;
        Q.push(std::make_pair(inou, jnou));
        SDL_RenderDrawPoint(Renderer, inou, jnou);
      }
    }


  }

//  for(int i=0;i<720;i++, std::cout<<'\n')
  //  for(int j=0;j<1280;j++)
    // std::cout<< b[i][j]<<" ";
    std::cout<<"XR:"<<rpovif[0].x<<" "<<"YR:"<<rpovif[0].y<<'\n';
    std::cout<<b[rpovif[0].x][rpovif[0].y];
    drum(rpovif[0].x, rpovif[0].y);

   for(int i=0;i<nrsteps;i++)
     std::cout<<steps[i]<<" ";
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
            if(WindowEvent.key.keysym.sym == SDLK_0){
              ctype = 0;
            }
            if(WindowEvent.key.keysym.sym == SDLK_LEFT)
            {
              SDL_RenderSetScale(Renderer, 1, 1);
                ClearMainGraphics();
                RenderMainMenu();
            }
	     if(WindowEvent.key.keysym.sym == SDLK_a){
              lee(shipx, shipy);
              roadcalc = true;
            }
        if(WindowEvent.key.keysym.sym == SDLK_b){
                shipx = defx;
                shipy = defy;
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
  if(inmat(x, y)) map[int(x)][int(y)] = true;
}
//linie obstacol
void lineob(float x1, float y1, float x2, float y2){
             float dx = x2-x1;
             float dy = y2 - y1;
             float length = std::sqrt(dx*dx+dy*dy);
             float angle = std::atan2(dy, dx);
             for(float i=0;i<length;i++){
                            SDL_RenderDrawPointF(Renderer, x1+std::cos(angle)*i, y1 + std::sin(angle)*i);
                            map[int(y1+std::sin(angle)*i)][int(x1+std::cos(angle)*i)] = true;
             }

  };
//linie desen
void line(float x1, float y1, float x2, float y2){
             float dx = x2-x1;
             float dy = y2 - y1;
             float length = std::sqrt(dx*dx+dy*dy);
             float angle = std::atan2(dy, dx);
             for(float i=0;i<length;i++){
                            SDL_RenderDrawPointF(Renderer, x1+std::cos(angle)*i, y1 + std::sin(angle)*i);
                            
             }

  };


void circle(int x, int y, int d){
    int circle_radius = d/2;
        for (int t = 0; t < 360; t++)
        {

            point(x+circle_radius*std::cos(t), y+circle_radius*std::sin(t));
        }


}

//
//drawribbon(int optrib)
//
//optrib - > pentru a specifica functiei ce element sa arate
//
//
void drawribbon(int optrib){
    lineob(0, WINDOW_HEIGHT/25, WINDOW_WIDTH, WINDOW_HEIGHT/25);
    if(optrib==1){
        point(10, 15);
        CreateText("Element selectat -> point", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("Un punct normal, pentru a perfectiona hartile", 30, 15, "menu_opt.ttf", 15, sett, rsett);

    }
    if(optrib==2){
       circle(10, 15, 10); 
        CreateText("Element selectat -> planeta statica", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("O simpla planeta nemiscatoare, in forma de cerc.", 30, 15, "menu_opt.ttf", 15, sett, rsett);
    }
    if(optrib==3){
        circle(10, 15, 10);
        point(10, 15);
        CreateText("Element selectat -> planeta mergatoare.", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("O planeta cu o miscare definita.", 30, 15, "menu_opt.ttf", 15, sett, rsett);
    }
    if(optrib==4){
       circle(10, 15, 20);
       circle(10, 15, 10);
       CreateText("Element selectat -> stea", 25, 0, "menu_opt.ttf", 20, create, rcreate);
       CreateText("O stea definita de raza ei de caldura.", 30, 15, "menu_opt.ttf", 15, sett, rsett);
    }
    if(optrib==5){
       circle(10, 15, 10);
        CreateText("Element selectat -> asteroid", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("La fel ca planeta mergatoare, doar ca nu isi repeta traseul", 30, 15, "menu_opt.ttf", 15, sett, rsett);
    }
    if(optrib==6){
        point(10, 15);
        CreateText("Element selectat -> punct de interes", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("Punctul la care racheta trebuie sa ajunga.", 30, 15, "menu_opt.ttf", 15, sett, rsett);
    }
    if(optrib==7){
        circle(10, 15, 20);
        CreateText("Element selectat -> gaura neagra", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("Acestui element i se poate selecta marimea, crescand dreptat spre marimea maxima.", 30, 15, "menu_opt.ttf", 15, sett, rsett);

    }
    if(optrib==0){
        line(5, 5, 10, 20);
        CreateText("Element selectat -> 'linia imaginara'", 25, 0, "menu_opt.ttf", 20, create, rcreate);
        CreateText("O linie pentru a trasa un traseu posibil al rachetei.", 30, 5, "menu_opt.ttf", 15, sett, rsett);

    }

}





void Render() {
    SDL_RenderClear(Renderer);   
    SDL_SetRenderDrawColor(Renderer, 255,255, 255, 255); 
    SDL_RenderCopy(Renderer, image_texture, NULL, &rimage);
    SDL_RenderCopy(Renderer, title, NULL, &rtitle);
    SDL_RenderSetScale(Renderer, 2, 2);
    drawribbon(ctype);
    
    SDL_RenderCopy(Renderer, create, NULL, &rcreate);
    SDL_RenderCopy(Renderer, sett, NULL, &rsett);
    SDL_RenderSetScale(Renderer, 10, 10);
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


      if(E[i].ELtype == 8){
        SDL_SetRenderDrawColor(Renderer, 137, 139, 140, 200);
        point(E[i].x, E[i].y);
      }
      if(E[i].ELtype == 6){
         SDL_SetRenderDrawColor(Renderer, 36, 226, 52, 230);
         SDL_RenderDrawPoint(Renderer, E[i].x, E[i].y);
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
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
        for(int i=1;i<nr_lines;i++){
              line(lines[i].x, lines[i].y, lines[i].x2, lines[i].y2);      
        }
    
    
        if(roadcalc){
        curstep++;
        std::cout<<"A";
        if(steps[curstep]=='N'){ 
            shipy-=1;
            CreateText("N", 115, 55, "menu_opt.ttf", 15, title, rtitle);
        }
        if(steps[curstep]=='S'){
            shipy+=1;
            CreateText("S", 115, 55, "menu_opt.ttf", 15, title, rtitle);
        }
        if(steps[curstep]=='E'){
            shipx+=1;
            CreateText("E", 115, 55, "menu_opt.ttf", 15, title, rtitle);
        }
        if(steps[curstep]=='V'){ 
            shipx-=1;
            CreateText("V", 115, 55, "menu_opt.ttf", 15, title, rtitle);
        }


      std::cout<<"shipx:"<<shipx<<'\n'<<"shipy:"<<shipy<<" "<<curstep;
      }
    
//	std::cout<<"curstep:"<<curstep<<'\n';

    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);

    point(shipx, shipy);
    CreateText("R", shipx, shipy+2, "rocket.otf", 5, open, ropen, 0, 0, 255, 255);
    SDL_RenderCopy(Renderer, open, NULL, &ropen);//functia este aici pentru a rezolva un bug
                                                 //unde scrisul nu urmarea bine racheta

	SDL_RenderPresent(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);  



    SDL_Delay(SDL_DELAY);
}




void RenderMapPage()
{
  lines[0].x = 30;
  lines[0].y = 30;
  lines[0].x2 = 30;
  lines[0].y2 = 30;
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  image = IMG_Load("bg.png");
  image_texture = SDL_CreateTextureFromSurface(Renderer, image);
  SDL_FreeSurface(image);
  rimage.x = 0;
  rimage.y = 0;
  rimage.w = WINDOW_WIDTH/10;
  rimage.h = WINDOW_HEIGHT/10;

  SDL_RenderSetScale(Renderer, 10, 10);
   while(IsPollingEventM()){
      Render();
   }
   IMG_Quit();
}
