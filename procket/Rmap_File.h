#include <stdio.h>
#include <string.h>

//Enabling Lower or upper case chars
#define MINI_CASE_SENSITIVE
#include "ext_deps/mINI.hpp"
#include "ext_deps/ANSI_Utils.h"

#include "map_page.hpp"
#include "FD_IO.h"

//Funny Long ;DDD
#define STR_SIZE 55000



//MARK: WriteRMAP
void WriteRMAP()
{
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> Save File Dialog. Waiting For File Selection...\n";
    #endif
    SaveFileDialog();

    std::string str(rmap_o);
    mINI::INIFile RmapFile(str);
    mINI::INIStructure rmapStruct;
    RmapFile.read(rmapStruct);

    char ElemCount[STR_SIZE];
    char RType[STR_SIZE];
    char RXPos[STR_SIZE];
    char RYPos[STR_SIZE];
    
    #ifdef DEBUG_RMAP_FILE
        std::cout << "[Rmap File Debug] -> Write\n";
        std::cout << "[Rmap File Debug] -> Element count: " << nr_elem << "\n";
    #endif
    

    //Temp
    sprintf(ElemCount, "%d", nr_elem);
    rmapStruct["Main"]["TotalElemCount"] = ElemCount;

    for(int i = 0; i < nr_elem; i++)
    {
        sprintf(ElemCount, "Element_%d", i);
        sprintf(RType, "%d", E[i].ELtype);
        sprintf(RXPos, "%d", E[i].x);
        sprintf(RYPos, "%d", E[i].y);

        rmapStruct[ElemCount]["type"] = RType;
        rmapStruct[ElemCount]["Xpos"] = RXPos;
        rmapStruct[ElemCount]["Ypos"] = RYPos;

        #ifdef DEBUG_RMAP_FILE
            std::cout << "Type num: " << E[i].ELtype << " | " << "XPos: " << E[i].x << " | " << "YPos: " << E[i].y << "\n";
        #endif
    }

    bool WriteCheck = RmapFile.write(rmapStruct);

    //Chatch rmap file write errors
    if(!WriteCheck)
    {
        XtermFG(FG, 196);
        std::cout << "Err: ";
        CresetAll();
        std::cout << "Failed to write Rocket map file!\n";
    }
    #ifdef DEBUG_RMAP_FILE
        else
        {
            XtermFG(FG, 46);
            std::cout << "Success: ";
            CresetAll();
            std::cout << "Rocket map file written succesfully\n";
        }
    #endif
}

//MARK: ReadRMAP
//Todo later on...