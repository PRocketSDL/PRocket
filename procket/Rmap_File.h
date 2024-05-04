#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>

#if defined _WIN32 || defined _WIN64
    #include <windows.h>
    #include <commdlg.h>
    #include <io.h>
#endif



#define StrSize 1024

char rmap_i[StrSize];
char rmap_o[StrSize];

FILE *f;

#if defined _WIN32 || defined _WIN64
    void SymRem(char text[], char symbol, char* clean)
    {
        size_t i,j;
        for(i = 0, j = 0; i < strlen(text); i++)
        {
            if(text[i] != symbol)
            {
                clean[j++] = text[i];
            }
        }
        clean[j] = '\0';
    }
#endif


//MARK: Open FD
void OpenFileDialog()
{
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
        char FixedPath[260];
        OPENFILENAME ofn;

        ZeroMemory(&ofn, sizeof(ofn));

        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = "Rocket Map Files Files\0*.rmap\0";
        ofn.lpstrFile = rmap_i;
        ofn.nMaxFile = sizeof(rmap_i);
        ofn.lpstrTitle = "Select Rocket Map File";
        ofn.Flags = OFN_DONTADDTORECENT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXTENSIONDIFFERENT;

        if(!GetOpenFileName(&ofn))
        {
            #ifdef DEBUG_FD
                std::cout << "[File Dialog] -> Selection: none\n";
            #endif
            memset(rmap_i, 0, sizeof(rmap_i));
        }
        SymRem(rmap_i, '\"', FixedPath);
        #ifdef DEBUG_FD
            std::cout << "[File Dialog] -> Selection: " << rmap_i << "\n";
        #endif
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
                std::cout << "[File Dialog] -> Save: " << rmap_o << "\n";
            }
        #endif
    #endif

    #if defined _WIN32 || defined _WIN64
        char FixedPath[260];
        OPENFILENAME ofn;
        //char temPath[StrSize];

        ZeroMemory(&ofn, sizeof(ofn));

        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = "Rocket Map Files Files\0*.rmap\0";
        ofn.lpstrFile = rmap_o;
        ofn.nMaxFile = sizeof(rmap_o);
        ofn.lpstrTitle = "Save Rocket Map Files";
        ofn.Flags = OFN_DONTADDTORECENT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if(!GetSaveFileName(&ofn))
        {
            #ifdef DEBUG_FD
                std::cout << "[File Dialog] -> Selection: none\n";
            #endif
            memset(rmap_o, 0, sizeof(rmap_o));
        }
        else
        {
            SymRem(rmap_o, '\"', FixedPath);
            #ifdef DEBUG_FD
                std::cout << "[File Dialog] -> Selection: " << rmap_o << "\n";
            #endif
        }
    #endif
}
