#include <string>
#include <vector>

typedef char *audio;

enum keypress {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SELECT,
    KEY_JUMP,
    KEY_BLOCKCHANGE,
    KEY_LEVELEDIT,
    KEY_EDITCHANGE
}

extern void initialize();
extern void exit();
extern void print(std::string text);
extern keypress getKey();
extern void playAudio(audio buf);
