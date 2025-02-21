#include "loadfile.h"
#include <string>
#include <fstream>
#include <iostream>
std::string loadFile(std::string filedir){
    std::ifstream f(filedir, std::ios::binary | std::ios::ate);


    FILE* filep;

    std::string file = std::string();
    auto size = f.tellg();
    std::string file_contents(size, '\0');
    f.seekg(0);
    f.read(&file_contents[0], size);
    std::cout << file_contents;
    return file_contents;
}