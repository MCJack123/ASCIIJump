#include <string>
#include <vector>

typedef char *audio;

extern void initialize();
extern void exit();
extern void print(std::string text);
extern char getKey();
extern void playAudio(audio buf);
