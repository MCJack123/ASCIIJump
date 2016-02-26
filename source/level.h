//The level definitions
#include <string>
#include <map>
//#include "utils.h"

std::string level_map[4][8];
std::map<std::string, int> levn;

void registerLevel(int levid, std::string f8, std::string f7, std::string f6, std::string f5, std::string f4, std::string f3, std::string f2, std::string f1) {	// This will make it easier to put levels in & adds portability.
	level_map[levid][0] = f1;
	level_map[levid][1] = f2;
	level_map[levid][2] = f3;
	level_map[levid][3] = f4;
	level_map[levid][4] = f5;
	level_map[levid][5] = f6;
	level_map[levid][6] = f7;
	level_map[levid][7] = f8;
}

void levelInit() {
	// For easiness: to address the levels by name (if not needed, will be removed)
	int i = 0;
	for (std::tuple<const char *, int> levname : levnames) {
		levn[std::get<0>(levname)] = i;
		i++;
	}
	i = 0;
	// Now the fun part: making the level layouts. I am going to write multi-line for ease of use.
	registerLevel(0,\
	"                                                                                                                                            --       --          XXXX ",\
	"                                                                                                                                           XXXX     XXXX         ---- ",\
	"                                                                                                                                DDDDDDDDDDDDDDDDDDDDDDDDDDD                D",\
	"                                                                                                                           -    DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",\
	"                                                                                                                      -            DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",\
	"                                        B                                                                        -                 DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",\
	"                                    B   B                                                      X           -                       DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",\
	"        B           xX          BsssBsssBX                BBBBBBBBBBsssBBBBBBBBBBBBsssBBBBBBBBBBBBBBBBBBsssssssssssssssssssssssssssDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
}

void runLevel(int levelid) {
	consoleSelect(&screen);
	#ifndef __LUA_SOUND_
	audio_stop();
	#endif
}