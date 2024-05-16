#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#if defined _WIN32 || defined _WIN64
    #include <windows.h>
#endif



#define StrSize 1024

char rmap_i[StrSize];
char rmap_o[StrSize];

FILE *f;


//MARK: Open FD
void OpenFileDialog()
{
    //stuff
    #ifdef __linux__
        f = popen("zenity --file-selection --file-filter='*.rmap' --filename='.rmap' --title='Select rocket map file'", "r");
        fgets(rmap_i, StrSize, f);
        #ifdef DEBUG_FD
            if(strlen(rmap_o) == 0)
                std::cout << "[File Dialog] -> Selection: none\n";
        
            else
                std::cout << "[File Dialog] -> Selection: " << rmap_i << "\n";
        #endif
    #endif

    #if defined _WIN32 || defined _WIN64
        //To do...
    #endif
}


//MARK: Save FD
void SaveFileDialog()
{
    #ifdef __linux__
    f = popen("zenity --file-selection --save --file-filter='*.rmap' --filename='.rmap' --title='Save Rocket Map'", "r");
        fgets(rmap_o, StrSize, f);
        #ifdef DEBUG_FD
            if(strlen(rmap_o) == 0)
            {
                std::cout << "[File Dialog] -> Save: none\n";
            }
            else
            {
                //sprintf(rmap_o, "%s", ".rmap");
                std::cout << "[File Dialog] -> Save: " << rmap_o << "\n";
            }
        #endif
    #endif

    #if defined _WIN32 || defined _WIN64
        //To do...
    #endif
}
