#pragma once
#include <string>
#include <vector>
#include "level.h"

typedef struct audio {
    void *data,
    unsigned long len
} audio;
typedef struct rect {
    unsigned int width,
    unsigned int height
} rect;

enum keypress {
    KEY_PRESSED_NONE,
    KEY_PRESSED_UP,
    KEY_PRESSED_DOWN,
    KEY_PRESSED_LEFT,
    KEY_PRESSED_RIGHT,
    KEY_PRESSED_SELECT,
    KEY_PRESSED_JUMP,
    KEY_PRESSED_BACK,
    KEY_PRESSED_ICONCHANGE,
    KEY_EDIT_LEVEL,
    KEY_EDIT_CHANGE,
    KEY_EDIT_DELETE
}

extern void initialize();
extern void exit();
extern rect getScreenDimensions();
extern void print(std::string text);
extern void printScreen(std::vector<std::vector<Block> > blockmap, char[4][4] icon);
extern keypress getKey();
extern void playAudio(audio buf);
extern void stopAudio();
extern std::string readFile(std::string file);
extern void writeFile(std::string file, std::string text);
