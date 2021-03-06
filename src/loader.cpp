#include "loader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

RomLoader::RomLoader()
{
}

RomLoader::~RomLoader()
{
}

void RomLoader::load_rom(string fileName, Memory *memory, uint16_t offset)
{
    // TODO: Protect against buffer overflow, odd filesize, etc.
    // TODO: Optimize for buffering

    // Read ROM file as byte stream and write to memory
    basic_ifstream<char> file(fileName, ios::binary);
    vector<char> fileBytes = vector<char>(istreambuf_iterator<char>(file), istreambuf_iterator<char>());

    if (fileBytes.empty())
        throw runtime_error("Invalid ROM");

    for (uint16_t addr = 0; addr < fileBytes.size(); addr++)
    {
        memory->write(addr + offset, fileBytes[addr]);
    }
}