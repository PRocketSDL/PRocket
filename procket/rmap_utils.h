#pragma once
#include <iostream>
#include <string>



#define MINI_CASE_SENSITIVE
#include "mINI.hpp"

//#define RMAP_IO_DEBUG

#include "map_page.h"


//Pt stocarea coordonatelor elementelor (Scrierea in format ini)
int rmapX_t1[MAX_ELEM];
int rmapY_t1[MAX_ELEM];

int rmapX_t2[MAX_ELEM];
int rmapY_t2[MAX_ELEM];

int rmapX_t3[MAX_ELEM];
int rmapY_t3[MAX_ELEM];

int rmapX_t4[MAX_ELEM];
int rmapY_t4[MAX_ELEM];

int rmapX_t5[MAX_ELEM];
int rmapY_t5[MAX_ELEM];

int rmapX_t6[MAX_ELEM];
int rmapY_t6[MAX_ELEM];

int rmapX_t7[MAX_ELEM];
int rmapY_t7[MAX_ELEM];

char Elem1[100];
char Elem2[100];
char Elem3[100];
char Elem4[100];
char Elem5[100];
char Elem6[100];
char Elem7[100];

char intX_t1[100];
char intY_t1[100];

char intX_t2[100];
char intY_t2[100];

char intX_t3[100];
char intY_t3[100];

char intX_t4[100];
char intY_t4[100];

char intX_t5[100];
char intY_t5[100];

char intX_t6[100];
char intY_t6[100];

char intX_t7[100];
char intY_t7[100];




/*typedef struct RmpStruct
{
    int ElemType[10];
    int ElemCount[MAX_ELEM];
    int PX;
    int PY;
}RmpStruct;*/



void WriteRMAP(const char * Rfile)
{
    std::string str(Rfile);
    mINI::INIFile rmap_file(str);

    mINI::INIStructure rmap;

    rmap_file.read(rmap);

    if(ctype[cntT1] == 1)
    {
        //Do stuff
        //rmapX_t1[cntT1] = {msX};
       // rmapY_t1[cntT1] = {msY};
        for(int i = 0; i < cntT1; i++)
        {
            sprintf(Elem1, "Element1_X%d", i);
            sprintf(intX_t1, "%d", msX[i]);
            sprintf(intY_t1, "%d", msY[i]);
            //std::cout << "E1 | X= " << rmapX_t1[i] << " Y= " << rmapY_t1[i] << "\n";
            rmap[Elem1]["Xpos"] = intX_t1;
            rmap[Elem1]["Ypos"] = intY_t1;
        }
    }
    else if(ctype[cntT2] == 2)
    {
        //Do stuff
        //rmapX_t2[cntT2] = msX;
        //rmapY_t2[cntT2] = msY;
        for(int i = 0; i < cntT2; i++)
        {
            sprintf(Elem2, "Element2_X%d", i);
            sprintf(intX_t2, "%d", msX[i]);
            sprintf(intY_t2, "%d", msY[i]);
            rmap[Elem2]["Xpos"] = intX_t2;
            rmap[Elem2]["Ypos"] = intY_t2;
        }
    }
    else if(ctype[cntT3] == 3)
    {
        //Do stuff
        //rmapX_t3[cntT3] = msX;
        //rmapY_t3[cntT3] = msY;
        for(int i = 0; i < cntT3; i++)
        {
            sprintf(Elem3, "Element3_X%d", i);
            sprintf(intX_t3, "%d", msX[i]);
            sprintf(intY_t3, "%d", msY[i]);
            rmap[Elem3]["Xpos"] = intX_t3;
            rmap[Elem3]["Ypos"] = intY_t3;
        }
    }
    else if(ctype[cntT4] == 4)
    {
        //Do stuff
        //rmapX_t4[cntT4] = msX;
        //rmapY_t4[cntT4] = msY;
        for(int i = 0; i < cntT4; i++)
        {
            sprintf(Elem4, "Element3_X%d", i);
            sprintf(intX_t4, "%d", msX[i]);
            sprintf(intY_t4, "%d", msY[i]);
            rmap[Elem4]["Xpos"] = intX_t4;
            rmap[Elem4]["Ypos"] = intY_t4;
        }
    }
    else if(ctype[cntT6] == 6)
    {
        //Do stuff
        //rmapX_t6[cntT6] = msX;
        //rmapY_t6[cntT6] = msY;
        for(int i = 0; i < cntT6; i++)
        {
            sprintf(Elem6, "Element3_X%d", i);
            sprintf(intX_t6, "%d", msX[i]);
            sprintf(intY_t6, "%d", msY[i]);
            rmap[Elem6]["Xpos"] = intX_t6;
            rmap[Elem6]["Ypos"] = intY_t6;
        }
    }
    else if(ctype[cntT7] == 7)
    {
        //Do stuff
        //rmapX_t7[cntT7] = msX;
        //rmapY_t7[cntT7] = msY;
        for(int i = 0; i < cntT7; i++)
        {
            sprintf(Elem7, "Element3_X%d", i);
            sprintf(intX_t7, "%d", msX[i]);
            sprintf(intY_t7, "%d", msY[i]);
            rmap[Elem7]["Xpos"] = intX_t7;
            rmap[Elem7]["Ypos"] = intY_t7;
        }
    }

    rmap_file.write(rmap);

}
