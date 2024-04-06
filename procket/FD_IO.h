#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>



#define StrSize 1024

char rmap_i[StrSize];
char rmap_o[StrSize];

FILE *f;


void OpenFileDialog()
{
    //stuff
    #ifdef __linux__
        f = popen("zenity --file-selection --file-filter='*.rmap' --title='Select rocket map file'", "r");
        fgets(rmap_i, StrSize, f);
        #ifdef FD_DEBUG
            if(strlen(rmap_o) == 0)
                std::cout << "File selection: none\n";
        
            else
                std::cout << "File selection: " << rmap_i << "\n";
        #endif
    #endif

    #if defined _WIN32 || defined _WIN64
        //To do...
    #endif
}

void SaveFileDialog()
{
    #ifdef __linux__
    f = popen("zenity --file-selection --save --file-filter='*.rmap' --title='Save Rocket Map'", "r");
        fgets(rmap_o, StrSize, f);
        #ifdef FD_DEBUG
            if(strlen(rmap_o) == 0)
                std::cout << "File save: none\n";
        
            else
                std::cout << "File save: " << rmap_o << "\n";
        #endif
    #endif

    #if defined _WIN32 || defined _WIN64
        //To do...
    #endif
}
