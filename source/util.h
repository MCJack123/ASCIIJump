#include <string>
#include <vector>

typedef struct audio {
    void *data,
    unsigned long len
} audio;

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
extern void print(std::string text);
extern keypress getKey();
extern void playAudio(audio buf);
extern void stopAudio();
std::string readFile(std::string file);
void writeFile(std::string file, std::string text);
