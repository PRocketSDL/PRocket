#pragma once

#include <stdio.h>
#include <string.h>


#include "ext_deps/init/ini.hpp"
#include "ext_deps/ANSI_Utils.h"

#include "map_page.hpp"
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
    
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> Write\n";
        std::cout << "[Rmap File Debug] -> Element count: " << nr_elem << "\n";
    #endif
    
    //Write the element count to be parsed latter by ReadRMAP()
    printf(ElemCount, "%d", nr_elem);
    rmapStruct["Main"]["TotalElemCount"] = ElemCount;

    for(int i = 0; i < nr_elem; i++)
    {
        sprintf(ElemCount, "Element_%d", i);
        rmapStruct[ElemCount]["type"] = E[i].ELtype;
        rmapStruct[ElemCount]["Xpos"] = E[i].x;
        rmapStruct[ElemCount]["Ypos"] = E[i].y;
        #ifdef DEBUG_RMAP_FILE
            std::cout << "Type num: " << E[i].ELtype << " | " << "XPos: " << E[i].x << " | " << "YPos: " << E[i].y << "\n";
        #endif
    }
    init::write_ini(rmapStruct, rmap_o);
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> File - " << rmap_o << " updated\n";
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
    const auto& MainHeader = rmapStrIn.at("Main");
    MainHeader.at("TotalElemCount").get_to(InElemCount);

    char ElemSect[STR_SIZE];

    for(int i = 0; i < InElemCount; i++)
    {
        sprintf(ElemSect, "Element_%d", i);
        const auto& ElSects = rmapStrIn.at(ElemSect);
        ElSects.at("Xpos").get_to(Xin);
        ElSects.at("Ypos").get_to(Yin);
        ElSects.at("type").get_to(InType);
        #ifdef DEBUG_RMAP_FILE
            std::cout << "[Rmap File Debug] -> Load state" << " Element_" << i << " | Xpos=  " << Xin << " | Ypos= " << Yin << " | type= " << InType << "\n";
        #endif
    }
}
