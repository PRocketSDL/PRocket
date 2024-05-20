#pragma once

#include <iostream>
#include <fstream>

#include "ext_deps/ANSI_Utils.h"
#include "ext_deps/init/ini.hpp"
#include "FD_IO.h"


void LoadConfig()
{
    const auto readConf = init::read_ini("config.ini");
    const auto& ReadFP = readConf.at("FilePath");

    std::string InFile;
    std::string OutFile;

    ReadFP.at("input").get_to(InFile);
    ReadFP.at("output").get_to(OutFile);

    #ifdef DEBUG_CONFIG
        std::cout << "Config loaded\n";
        std::cout << "Config data: input= " << InFile << "\noutput= " << OutFile << "\n";
    #endif
}

void ConfigInit()
{
    std::ifstream config;
    init::ini configStruct;
    config.open("config.ini");
    if(!config)
    {
        #ifdef DEBUG_CONFIG
            std::cout << "config.ini not found.\nCreating config.ini\n";
        #endif
        configStruct["FilePath"];
        init::write_ini(configStruct, "config.ini");
        #ifdef DEBUG_CONFIG
            std::cout << "config.ini created\n";
        #endif
    }
    else
    {
        #ifdef DEBUG_CONFIG
            std::cout << "config.ini found\n";
        #endif
        LoadConfig();
    }
}

void SaveConfig()
{
    init::ini readConfStruct;
    if(strlen(rmap_i) == 0 || strlen(rmap_o) == 0)
    {
        std::cout << "No save params\n";
    }
    else
    {
        readConfStruct["FilePath"]["input"] = rmap_i;
        readConfStruct["FilePath"]["output"] = rmap_o;
        init::write_ini(readConfStruct, "config.ini");
        #ifdef DEBUG_CONFIG
            std::cout << "config.ini saved\n";
        #endif
    }
}