#include "util.h"

class Block {
    bool clear;
    bool harmful;
    int system;
    char block[4][4];
    char symbol;
public:
    Block(char sym, char bl[4][4], bool cl = false, bool harm = false, int sys = 0) {
        clear = cl;
        harmful = harm;
        system = sys;
        block = bl;
        symbol = sym;
    }
}

std::vector<Block> blocks = {
    Block('B', {"----", "|  |", "|  |", "----"}),
    Block('D', {" || ", "-++-", "-++-", " || "}),
    Block('X', {"    ", " /\\ ", "/  \\", "|__|"}),
    Block('x', {"    ", "    ", " /\\ ", "/__\\"}),
    Block('s', {"    ", "    ", "    ", "/\\/\\"}),
    Block('-', {"----", "|__|", "    ", "    "}),
    Block('\\', {"\\   ", "|\\  ", "| \\ ", "|  \\"}),
    Block('/', {"   /", "  /|", " / |", "/  |"}),
    Block('F', {" \\|-", " -| ", " >| ", " /|_"}),
    Block(' ', {"    ", "    ", "    ", "    "}),
    Block('^', {"    ", "    ", "    ", "//\\\\"}),
    Block('n', {"    ", "    ", "    ", "/--\\"}),
    Block('_', {"    ", "    ", "----", "|__|"}),
    Block('\0', {"    ", "    ", "    ", "    "})
};
std::map<char, Block> = {
    {'B', blocks[0]}, 
    {'D', blocks[1]}, 
    {'X', blocks[2]}, 
    {'x', blocks[3]}, 
    {'s', blocks[4]}, 
    {'-', blocks[5]}, 
    {'\\', blocks[6]}, 
    {'/', blocks[7]}, 
    {'F', blocks[8]}, 
    {' ', blocks[9]}, 
    {'^', blocks[10]}, 
    {'n', blocks[11]}, 
    {'_', blocks[12]}, 
    {'\0', blocks[13]}
};

class Level {
    std::string name = "";
    float normalCompletion = 0.0;
    float practiceCompletion = 0.0;
    audio_t song = nullaudio();
    std::vector<std::vector<Block> > level();
    // This is for online levels only
    int levelid = -1;
    std::string description = "";
}
