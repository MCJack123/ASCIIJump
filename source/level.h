#include "util.h"

class Block {
  bool clear;
  bool harmful;
  bool system;
  char block[4][4];
public:
  init(char bl[4][4]);
  bool hitBlock(bool top);
}

std::vector

class Level {
  std::string name = "";
  float normalCompletion = 0.0;
  float practiceCompletion = 0.0;
  audio_t song = nullaudio();
  std::vector<std::vector<Block> > level();
  // This is for online levels only
  int levelid = -1;
  std::string description;
}
