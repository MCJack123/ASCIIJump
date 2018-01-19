#import <AVFoundation/AVFoundation.h>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include "util.h"

void initialize() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void exit() {
    endscr();
}

void print(std::string text) {
    waddstr(stdscr, text.c_str());
}
