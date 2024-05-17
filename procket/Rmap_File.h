#pragma once

#include <stdio.h>
#include <string.h>


#include "ext_deps/init/ini.hpp"
#include "ext_deps/ANSI_Utils.h"

#include "map_page.hpp"
#include "switch_page.h"
#include "FD_IO.h"


#define STR_SIZE 55000



//MARK: WriteRMAP
void WriteRMAP()
{
    init::ini rmapStruct;

    if(strlen(rmap_o) == 0)
    {
        #ifdef DEBUG_RMAP_FILE
            std::cout << "[Rmap File Debug] -> No File Saved. Waiting For File Selection...\n";
        #endif
        SaveFileDialog();
    }
    
    char ElemCount[STR_SIZE];
    char ResultPath[STR_SIZE];
    
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> Write\n";
        std::cout << "[Rmap File Debug] -> Element count: " << nr_elem << "\n";
    #endif

    //Auto-append the file extension to the path only once
    sprintf(ResultPath, "%s%s", rmap_o, ".rmap");
    
    //Write the element count to be parsed latter by ReadRMAP()
    rmapStruct["Main"]["TotalElemCount"] = nr_elem;
    
    for(int i = 0; i < nr_elem; i++)
    {
        sprintf(ElemCount, "Element_%d", i);
        rmapStruct[ElemCount]["type"] = E[i].ELtype;
        rmapStruct[ElemCount]["Xpos"] = E[i].x;
        rmapStruct[ElemCount]["Ypos"] = E[i].y;
        if(E[i].ELtype == 2 || E[i].ELtype==7) rmapStruct[ElemCount]["D"] = E[i].d;
        if(E[i].ELtype == 4 || E[i].ELtype == 7) rmapStruct[ElemCount]["Dm"] = E[i].dm;
        if(E[i].ELtype == 4) rmapStruct[ElemCount]["Temp"] = E[i].temp;
      

        #ifdef DEBUG_RMAP_FILE
            std::cout << "Type num: " << E[i].ELtype << " | " << "XPos: " << E[i].x << " | " << "YPos: " << E[i].y << "\n";
        #endif
    }
    init::write_ini(rmapStruct, ResultPath);
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> File - " << ResultPath << " updated\n";
    #endif
}

//MARK: ReadRMAP
void ReadRMAP()
{
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> Load rmap file. Waiting for file selection...\n";
    #endif

    OpenFileDialog();

    const auto rmapStrIn = init::read_ini(rmap_i);

    //The parameters to be stored after parsing the rmap file
    int InElemCount;
    int Xin;
    int Yin;
    int InType;
    int Diam;
    int Dm;
    int Temp;
    
    //Something is fucked up here
    const auto& MainHeader = rmapStrIn.at("Main");
    MainHeader.at("TotalElemCount").get_to(InElemCount);
    char ElemSect[STR_SIZE];
    std::cout<<"A"<<'\n';
    ClearMainGraphics();
    std::cout<<"B"<<'\n';
    for(int i = 0; i < InElemCount; i++)
    {
        sprintf(ElemSect, "Element_%d", i);
        const auto& ElSects = rmapStrIn.at(ElemSect);
        ElSects.at("Xpos").get_to(Xin);
        ElSects.at("Ypos").get_to(Yin);
        ElSects.at("type").get_to(InType);
        if(InType == 2 || InType == 7) ElSects.at("D").get_to(Diam);
        if(InType == 4 || InType == 7) ElSects.at("Dm").get_to(Dm);
        if(InType == 4) ElSects.at("Temp").get_to(Temp);
        if(InType != 3 || InType!= 8 ){
          if(InType == 10) ctype = 4;
            else ctype = InType;
          MakeElem(Xin, Yin);
          nr_elem++;
        }
        #ifdef DEBUG_RMAP_FILE
            std::cout << "[Rmap File Debug] -> Load state" << " Element_" << i << " | Xpos=  " << Xin << " | Ypos= " << Yin << " | type= " << InType << "\n";
        #endif
    }
    
    RenderMapPage();
}
