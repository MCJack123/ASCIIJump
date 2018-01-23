#pragma once
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
    Block('X', {"    ", " /\\ ", "/  \\", "|__|"}, false, true),
    Block('x', {"    ", "    ", " /\\ ", "/__\\"}, false, true),
    Block('s', {"    ", "    ", "    ", "/\\/\\"}, false, true),
    Block('-', {"----", "|__|", "    ", "    "}),
    Block('\\', {"\\   ", "|\\  ", "| \\ ", "|  \\"}),
    Block('/', {"   /", "  /|", " / |", "/  |"}),
    Block('F', {" \\|-", " -| ", " >| ", " /|_"}, true, false, 1),
    Block(' ', {"    ", "    ", "    ", "    "}, true),
    Block('^', {"    ", "    ", "    ", "//\\\\"}, false, false, 2),
    Block('n', {"    ", "    ", "    ", "/--\\"}, false, false, 3),
    Block('_', {"    ", "    ", "----", "|__|"}),
    Block('\0', {"    ", "    ", "    ", "    "}, true),
    Block('(', {" (( ", "((  ", "((  ", " (( "}, true, false, 4),
    Block(')', {" )) ", "  ))", "  ))", " )) "}, true, false, 5)
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
    {'\0', blocks[13]},
    {'(', blocks[14]},
    {')', blocks[15]}
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

class LevelRunner {
    int mode = 0;
    Level currentLevel;
    int x = 0;
    int y = 0;
public:
    LevelRunner(Level theLevel) {
        currentLevel = theLevel;
    }
    
    void runFrame();
private:
    std::vector<void(**)()> renderFuncs;
}
