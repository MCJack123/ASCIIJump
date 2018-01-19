#include <string>
#include <vector>

typedef char *audio;

enum keypress {
    KEY_PRESSED_NONE,
    KEY_PRESSED_UP,
    KEY_PRESSED_DOWN,
    KEY_PRESSED_LEFT,
    KEY_PRESSED_RIGHT,
    KEY_PRESSED_SELECT,
    KEY_PRESSED_JUMP,
    KEY_PRESSED_BLOCKCHANGE,
    KEY_PRESSED_LEVELEDIT,
    KEY_PRESSED_EDITCHANGE
}

extern void initialize();
extern void exit();
extern void print(std::string text);
extern keypress getKey();
extern void playAudio(audio buf);
