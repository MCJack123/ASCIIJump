//The level definitions
#include <map>
#include <vector>
#include <sstream>
#include <cstdarg>
#ifndef __ASCII3DS_UTILS_H_
#include "utils.h"
#endif
#define BOOL_STRING(a) (a)?"true":"false"

// 3DS Top Screen Dimensions:
//     Width: 400 pixels / 50 chars (8px char width)
//	  Height: 240 pixels / 30 chars (8px char height)
// 3DS Bottom Screen Dimensions:
//     Width: 320 pixels / 40 chars (8px char width)
//    Height: Same as Top Screen

std::string level_map[5][200]; // too much?
std::map<std::string, int> levn;
float ldel = 0.083333;
int cube = 0;
std::vector<std::vector<const char *> > cubes = {{"----","||-|","|-||","----"}, {"----","|[]|","|[]|","----"}, {"-][-","|=[|","|]=|","-][-"}, {"----","|][|","|LJ|","----"}};

void registerLevel(int levid, std::string fmt, ...) {	// This will make it easier to put levels in & adds portability. Arguments must be std::string.
	va_list args;
	std::string new_level[200];
	va_start(args, fmt);
	int count;
	for (count = 0; count <= 200 && std::string(fmt) != "\0"; count++) new_level[count] = va_arg(args, std::string);
	for (int cc = count, ccc = 0; cc >= 0; cc--, ccc++) level_map[levid][ccc] = new_level[cc];
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
"                                                                                                                                                             __       __         XXXX                                                             X    DDDDDDDDDDDDDD               ",\
"                                                                                                                                                            XXXX     XXXX        ----       X                                                 -             DDDDDD                  ",\
"                                                                                                                                             -   -    DDDDDDDDDDDDDDDDDDDDDDDD          DDDDD                                             -                                         ",\
"                                                                                                                                         -              DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDX              X                         -                                             ",\
"                                                                                                                                     -                  DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD  ----       X             -             DDDDDDDDDDDDDDDDDD\\                 ",\
"                                                          B                                                            X         -                      DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD           -------         -                        DDDDDDDDDDDD\\                ",\
"                                                      B   D                                            X        DDDDDDDDDDDDDD                          DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD                   -----                            DDDDDDDDDDDDD\\               ",\
"                 B              xX              XXBsssDsssDX                    XX     DDDDDDDDsssDDDDDDDDDDDsssDDDDDDDDDDDDDDssssssssssssssssssssssssssDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDssssssssssssssssssssssssssssssssssssssssssssssssssssDDDDDDDDDDDDDD\\              F");
	registerLevel(1, "", "", "", "", "", "", "", "C");
	registerLevel(2, "", "", "", "", "", "", "", "C");
	registerLevel(3, "", "", "", "", "", "", "", "C");
}
int unrec_blocks = 0;
std::tuple<std::vector<const char *>, bool, bool> convertCharToCube(char charToCube) {
	bool willKill, transparent;
	std::vector<const char *> retvec;
	if (charToCube == 'B') {retvec = {"----", "|  |", "|  |", "----"}; willKill = false; transparent = false;}
	else if (charToCube == 'D') {retvec = {" || ", "-++-", "-++-", " || "}; willKill = false; transparent = false;}
	else if (charToCube == 'X') {retvec = {"    ", " /\\ ", "/  \\", "|__|"}; willKill = true; transparent = false;}
	else if (charToCube == 'x') {retvec = {"    ", "    ", " /\\ ", "/__\\"}; willKill = true; transparent = false;}
	else if (charToCube == 's') {retvec = {"    ", "    ", "    ", "/\\/\\"}; willKill = true; transparent = false;}
	else if (charToCube == '-') {retvec = {"----", "|__|", "    ", "    "}; willKill = false; transparent = false;}
	else if (charToCube == '\\') {retvec = {"\\   ", "|\\  ", "| \\ ", "|  \\"}; willKill = false; transparent = false;}
	else if (charToCube == '/') {retvec = {"   /", "  /|", " / |", "/  |"}; willKill = false; transparent = false;}
	else if (charToCube == 'F') {retvec = {"    ", "    ", "    ", "    "}; willKill = false; transparent = true;}
	else if (charToCube == ' ') {retvec = {"    ", "    ", "    ", "    "}; willKill = false; transparent = true;}
	else if (charToCube == '^') {retvec = {"    ", "    ", "    ", "//\\\\"}; willKill = false; transparent = true;}
	else if (charToCube == 'n') {retvec = {"    ", "    ", "    ", "/--\\"}; willKill = false; transparent = true;}
	else if (charToCube == '_') {retvec = {"    ", "    ", "----", "|__|"}; willKill = false; transparent = false;}
	else if (charToCube == '\0') {retvec = {"    ", "    ", "    ", "    "}; willKill = false; transparent = true;}
	else {retvec = {"none", "none", "none", "none"}; willKill = false; debugPrint("Unrecognized block!"); unrec_blocks++; transparent = true;}
	return std::make_tuple(retvec, willKill, transparent);
}

//To allow customization of the cube
int changeCube() {
	consoleSelect(&screen);
	consoleClear();
	while (true) {
	consoleClear();
	printf("Select a cube:\n\n");
	int i = 0;
	do {	// yes, i know there is an easier way to do this, but i'm too lazy after doing all this work to go change it now
		if (cubes.size() - i < 6) {
			if (cubes.size() - i < 5) {
				if (cubes.size() - i < 4) {
					if (cubes.size() - i < 3) {
						if (cubes.size() - i < 2) {
							if (cube - i == 0) printf("|%s|\n|%s|\n|%s|\n|%s|\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3]);
							else printf(" %s\n %s\n %s\n %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3]);
						}
						else {
							if (cube - i == 0) printf("|%s|   %s\n|%s|   %s\n|%s|   %s\n|%s|   %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3]);
							else if (cube - i == 1) printf(" %s   |%s|\n %s   |%s|\n %s   |%s|\n %s   |%s|\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3]);
							else printf(" %s    %s\n %s    %s\n %s    %s\n %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3]);
						}
					}
					else {
						if (cube - i == 0) printf("|%s|   %s    %s\n|%s|   %s    %s\n|%s|   %s    %s\n|%s|   %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3]);
						else if (cube - i == 1) printf(" %s   |%s|   %s\n %s   |%s|   %s\n %s   |%s|   %s\n %s   |%s|   %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3]);
						else if (cube - i == 2) printf(" %s    %s   |%s|\n %s    %s   |%s|\n %s    %s   |%s|\n %s    %s   |%s|\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3]);
						else printf(" %s    %s    %s\n %s    %s    %s\n %s    %s    %s\n %s    %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3]);
					}
				}
				else {
					if (cube - i == 0) printf("|%s|   %s    %s    %s\n|%s|   %s    %s    %s\n|%s|   %s    %s    %s\n|%s|   %s    %s    %s\n", cubes[i+0][0], cubes[i+1][0], cubes[i+2][0], cubes[i+3][0], cubes[i+0][1], cubes[i+1][1], cubes[i+2][1], cubes[i+3][1], cubes[i+0][2], cubes[i+1][2], cubes[i+2][2], cubes[i+3][2], cubes[i+0][3], cubes[i+1][3], cubes[i+2][3], cubes[i+3][3]);
					else if (cube - i == 1) printf(" %s   |%s|   %s    %s\n %s   |%s|   %s    %s\n %s   |%s|   %s    %s\n %s   |%s|   %s    %s\n", cubes[i+0][0], cubes[i+1][0], cubes[i+2][0], cubes[i+3][0], cubes[i+0][1], cubes[i+1][1], cubes[i+2][1], cubes[i+3][1], cubes[i+0][2], cubes[i+1][2], cubes[i+2][2], cubes[i+3][2], cubes[i+0][3], cubes[i+1][3], cubes[i+2][3], cubes[i+3][3]);
					else if (cube - i == 2) printf(" %s    %s   |%s|   %s\n %s    %s   |%s|   %s\n %s    %s   |%s|   %s\n %s    %s   |%s|   %s\n", cubes[i+0][0], cubes[i+1][0], cubes[i+2][0], cubes[i+3][0], cubes[i+0][1], cubes[i+1][1], cubes[i+2][1], cubes[i+3][1], cubes[i+0][2], cubes[i+1][2], cubes[i+2][2], cubes[i+3][2], cubes[i+0][3], cubes[i+1][3], cubes[i+2][3], cubes[i+3][3]);
					else if (cube - i == 3) printf(" %s    %s    %s   |%s|\n %s    %s    %s   |%s|\n %s    %s    %s   |%s|\n %s    %s    %s   |%s|\n", cubes[i+0][0], cubes[i+1][0], cubes[i+2][0], cubes[i+3][0], cubes[i+0][1], cubes[i+1][1], cubes[i+2][1], cubes[i+3][1], cubes[i+0][2], cubes[i+1][2], cubes[i+2][2], cubes[i+3][2], cubes[i+0][3], cubes[i+1][3], cubes[i+2][3], cubes[i+3][3]);
					else printf(" %s    %s    %s    %s\n %s    %s    %s    %s\n %s    %s    %s    %s\n %s    %s    %s    %s\n", cubes[i+0][0], cubes[i+1][0], cubes[i+2][0], cubes[i+3][0], cubes[i+0][1], cubes[i+1][1], cubes[i+2][1], cubes[i+3][1], cubes[i+0][2], cubes[i+1][2], cubes[i+2][2], cubes[i+3][2], cubes[i+0][3], cubes[i+1][3], cubes[i+2][3], cubes[i+3][3]);
				}
			}
			else {
				if (cube - i == 0) printf("|%s|   %s    %s    %s    %s\n|%s|   %s    %s    %s    %s\n|%s|   %s    %s    %s    %s\n|%s|   %s    %s    %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3]);
				else if (cube - i == 1) printf(" %s   |%s|   %s    %s    %s\n %s   |%s|   %s    %s    %s\n %s   |%s|   %s    %s    %s\n %s   |%s|   %s    %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3]);
				else if (cube - i == 2) printf(" %s    %s   |%s|   %s    %s\n %s    %s   |%s|   %s    %s\n %s    %s   |%s|   %s    %s\n %s    %s   |%s|   %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3]);
				else if (cube - i == 3) printf(" %s    %s    %s   |%s|   %s\n %s    %s    %s   |%s|   %s\n %s    %s    %s   |%s|   %s\n %s    %s    %s   |%s|   %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3]);
				else if (cube - i == 4) printf(" %s    %s    %s    %s   |%s|\n %s    %s    %s    %s   |%s|\n %s    %s    %s    %s   |%s|\n %s    %s    %s    %s   |%s|\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3]);
				else printf(" %s    %s    %s    %s    %s\n %s    %s    %s    %s    %s\n %s    %s    %s    %s    %s\n %s    %s    %s    %s    %s\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3]);
			}
		}
		else {
			if (cube - i == 0) printf("|%s|   %s    %s    %s    %s    %s \n|%s|   %s    %s    %s    %s    %s \n|%s|   %s    %s    %s    %s    %s \n|%s|   %s    %s    %s    %s    %s \n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
			else if (cube - i == 1) printf(" %s   |%s|   %s    %s    %s    %s \n %s   |%s|   %s    %s    %s    %s \n %s   |%s|   %s    %s    %s    %s \n %s   |%s|   %s    %s    %s    %s \n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
			else if (cube - i == 2) printf(" %s    %s   |%s|   %s    %s    %s \n %s    %s   |%s|   %s    %s    %s \n %s    %s   |%s|   %s    %s    %s \n %s    %s   |%s|   %s    %s    %s \n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
			else if (cube - i == 3) printf(" %s    %s    %s   |%s|   %s    %s \n %s    %s    %s   |%s|   %s    %s \n %s    %s    %s   |%s|   %s    %s \n %s    %s    %s   |%s|   %s    %s \n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
			else if (cube - i == 4) printf(" %s    %s    %s    %s   |%s|   %s \n %s    %s    %s    %s   |%s|   %s \n %s    %s    %s    %s   |%s|   %s \n %s    %s    %s    %s   |%s|   %s \n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
			else if (cube - i == 5) printf(" %s    %s    %s    %s    %s   |%s|\n %s    %s    %s    %s    %s   |%s|\n %s    %s    %s    %s    %s   |%s|\n %s    %s    %s    %s    %s   |%s|\n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
			else printf(" %s    %s    %s    %s    %s    %s \n %s    %s    %s    %s    %s    %s \n %s    %s    %s    %s    %s    %s \n %s    %s    %s    %s    %s    %s \n", cubes[i+0][0], cubes[i+0][1], cubes[i+0][2], cubes[i+0][3], cubes[i+1][0], cubes[i+1][1], cubes[i+1][2], cubes[i+1][3], cubes[i+2][0], cubes[i+2][1], cubes[i+2][2], cubes[i+2][3], cubes[i+3][0], cubes[i+3][1], cubes[i+3][2], cubes[i+3][3], cubes[i+4][0], cubes[i+4][1], cubes[i+4][2], cubes[i+4][3], cubes[i+5][0], cubes[i+5][1], cubes[i+5][2], cubes[i+5 ][3]);
		}
		printf("\n");
		i += 6;
	} while (i < (int) cubes.size());
	while (true) {
		hidScanInput();
		u32 nDown = hidKeysHeld();
		if (nDown & KEY_B) return cube;
		else if (nDown & KEY_A) return cube;
		else if (nDown & KEY_RIGHT) {if (cube < (int) cubes.size() - 1) cube++; break;}
		else if (nDown & KEY_LEFT) {if (cube > 0) cube--; break;}
		else if (nDown & KEY_UP) {if (cube - 6 > 0) cube -= 6; break;}
		else if (nDown & KEY_DOWN) {if (cube + 6 < (int) cubes.size() - 1) cube += 6; break;}
	}
	#ifdef __DEBUG
	consoleSelect(&debug);
	printf("Cube selected: %d\n", cube);
	consoleSelect(&screen);
	#endif
	sleep(.25);
	}
	FS_Archive core_out;
	FS_Path core_path;
	core_path.data = "data/cube.txt";
	core_path.type = PATH_ASCII;
	u32 cfbuf;
	FSUSER_OpenFileDirectly(&cfbuf, core_out, core_path, FS_OPEN_CREATE, NULL);
	std::stringstream cubestrstr;
	cubestrstr << cube;
	std::string cubestr = cubestrstr.str(); // too much 'str'!
	FSFILE_Write(cfbuf, NULL, 0, cubestr.c_str(), 1, FS_WRITE_FLUSH);
	FSFILE_Close(cfbuf);
	return cube;
}

// Now, let's actually make the game!
void runLevel(int levelid) {
	// First, set up the music
	if (level_map[levelid][0] == "C") {printf("Coming soon!"); sleep(1); return;}
	consoleSelect(&screen);
	sleep(1);
	debugPrint("Loading song...");
	#ifndef __LUA_SOUND_
	audio_stop();
	char * levmus = (char*)malloc(20);
	sprintf(levmus, "/3ds/ASCIIJump3DS/data/level%d.bin", levelid);
	if (!audio_load(levmus, &sound1)) debugPrint("");
	#endif
	clearAll();
	#ifndef __LUA_SOUND_
	audio_play(&sound1, false);
	#endif
	
	// Stats of GeometryJump:
	//  * 11 squares per second
	//  * Jumps are 4 squares long, 3 squares high
	// ASCIIJump:
	//  Each square will be 4x4 (except the top row will be 2 tall)...
	//  ...so there will be 8 rows (of course) and 12 columns.
	
	// Just make it easy to access the level data
	std::string ra[200] = level_map[levelid];
	
	// This is it, the main loop!
	int attempts = 1;
	int y = 0;
	int y_orig = 0;
	int y_showing = -4;
	bool jump = false;
    bool falling = false;
	bool jumpPad = false;
	std::string attemptss = "1";
	int percentage = 0;
	int xoh;
	int highscore = nmscore[levelid];
	for (int x = 0; (true); x++) {
		if (ra[1][x+11] == 'F') {printf("You win!"); sleep(3); break;}
		//if (y > 7) {y = 0; debugPrint("Y is greater than 7!");}
		char * terminal = (char*)malloc(2000);
		// Re-writing inefficient code, this is to print
		for (unsigned int linen = makeUnsigned_i(y_showing); linen < makeUnsigned_i(y_showing); linen++) {
			for (int iter = 0; iter < 13; iter++) {
				for (int linenn = 0; linenn < 5; linenn++) {
					if (iter == 2) sprintf(terminal, "%s", cubes[cube][linenn]);
					sprintf(terminal, "%s", std::get<0>(convertCharToCube(ra[linen][iter]))[linenn]);
				}
			}
		}
		consoleClear();
		printf(terminal);
		#ifdef __DEBUG
		if (unrec_blocks > 5) {
		consoleSelect(&debug);
		printf("Unrecognized blocks: %d\n", unrec_blocks);
		consoleSelect(&screen);
		}
		consoleSelect(&debug);
		printf("X: %d\tY: %d\tFall: %s\tJump: %s\n", x, y, BOOL_STRING(falling), BOOL_STRING(jump));
		consoleSelect(&screen);
		#endif
		unrec_blocks = 0;
		if (((std::get<1>(convertCharToCube(ra[y][x])) && !jump)/* player on spike */ || (!std::get<2>(convertCharToCube(ra[y][x]))))/* player in block */ && y < 200) {
			std::stringstream ss;
			ss<<(++attempts);
			attemptss = ss.str();
			x = 0;
			y = 0;
			jump = false;
			if (percentage > nmscore[levelid]) {printf("High Score! %d%%", percentage); highscore = percentage;}
			#ifndef __LUA_SOUND_
			audio_stop();
			#endif
			printf("You died!");
			sleep(1);
			#ifndef __LUA_SOUND_
			audio_play(&sound1, false);
			#endif
		} // You died!
		hidScanInput();
		u32 bDown = hidKeysDown();
		u32 bHeld = hidKeysHeld();
		touchPosition touch;
		hidTouchRead(&touch);
		if ((bDown | bHeld) & KEY_START) break;
		if (((bDown | bHeld) || (touch.px != 0 || touch.py != 0)) && !jump && !falling && !std::get<1>(convertCharToCube(ra[y-1][x]))) {jump = true; y_orig = y++;}
		else if (jump && y == y_orig + 1) {y++; jump = false; falling = true;}
		else if (jumpPad && y == y_orig + 1) {y++; jumpPad = false; jump = true; y_orig = y;}
        else if (jump && y == y_orig + 2) {jump = false; falling = true;}
        else if (!jump && /*ra[y-1][x] != ' ' && */(ra[y-1][x+1] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x+1]))) && y > 0 && (ra[y-1][x] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x])))) {y--; falling = true;}
        else if (!(!jump && /*ra[y-1][x] != ' ' && */(ra[y-1][x+1] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x+1]))) && y > 0 && (ra[y-1][x] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x]))))) {falling = false;}
		else if (y < 8) {if ((ra[y][x] == 'n') || (ra[y][x] == '^')) {if (ra[y][x] == '^') jumpPad = true; else jump = true; y_orig = y++;}}
		xoh = x * 100;
		percentage = xoh / ra[8].length();
		consoleSelect(&debug);
		printf("Percentage: %d\n", percentage);
		consoleSelect(&screen);
		y_showing = y - 4;
		sleep(ldel);
	}
	#ifndef __LUA_SOUND_
	audio_stop();
	#endif
	clearAll();
	nmscore[levelid] = highscore;
	debugPrint("Outputting high score to file...");
	FS_Archive score_out;
	FS_Path score_path;
	score_path.data = "data/scores.txt";
	score_path.type = PATH_ASCII;
	u32 fbuf;
	FSUSER_OpenFileDirectly(&fbuf, score_out, score_path, FS_OPEN_CREATE, NULL);
	bool m;
	std::stringstream outf;
	for (int l = 0; l <= 8; l++) {
		m = (l % 2 == 0);
		if (m) outf << pmscore[l/2] << std::endl;
		else outf << nmscore[(l-1)/2] << std::endl;
	}
	std::string output = outf.str();
	FSFILE_Write(fbuf, NULL, 0, output.c_str(), output.size(),FS_WRITE_FLUSH);
	FSFILE_Close(fbuf);
}

void chooseCustomLevel() {
	consoleSelect(&screen);
	consoleClear();
	printf("In the data folder, you can create eight custom levels to be used by ASCIIJump. \nThese levels are saved as plain text files named with this naming scheme:\ncustom-<1-8>.ajl\nYou can type in the level code with your favorite text editor and save it.\n");
	int levelEnabled = 1;
	std::vector<int> levelsFound;
		debugPrint("Checking files...");
		if (!fexists("data/custom-1.ajl") && !fexists("data/custom-2.ajl") && !fexists("data/custom-3.ajl") && !fexists("data/custom-4.ajl") && !fexists("data/custom-5.ajl") && !fexists("data/custom-6.ajl") && !fexists("data/custom-7.ajl") && !fexists("data/custom-8.ajl")) {printf("No custom levels detected. Please create the custom levels before playing them.\n"); sleep(3); return;}
		debugPrint("Files found.");
		if (fexists("data/custom-1.ajl")) {levelsFound.push_back(1);}
		if (fexists("data/custom-2.ajl")) {levelsFound.push_back(2);}
		if (fexists("data/custom-3.ajl")) {levelsFound.push_back(3);}
		if (fexists("data/custom-4.ajl")) {levelsFound.push_back(4);}
		if (fexists("data/custom-5.ajl")) {levelsFound.push_back(5);}
		if (fexists("data/custom-6.ajl")) {levelsFound.push_back(6);}
		if (fexists("data/custom-7.ajl")) {levelsFound.push_back(7);}
		if (fexists("data/custom-8.ajl")) {levelsFound.push_back(8);}
	debugPrint("Entering loop...");
	while (true) {
		if (fexists("data/custom-1.ajl")) {if (levelsFound[levelEnabled-1] == 1) printf("[Slot 1]\n"); else printf(" Slot 1\n");}
		if (fexists("data/custom-2.ajl")) {if (levelsFound[levelEnabled-1] == 2) printf("[Slot 2]\n"); else printf(" Slot 2\n");}
		if (fexists("data/custom-3.ajl")) {if (levelsFound[levelEnabled-1] == 3) printf("[Slot 3]\n"); else printf(" Slot 3\n");}
		if (fexists("data/custom-4.ajl")) {if (levelsFound[levelEnabled-1] == 4) printf("[Slot 4]\n"); else printf(" Slot 4\n");}
		if (fexists("data/custom-5.ajl")) {if (levelsFound[levelEnabled-1] == 5) printf("[Slot 5]\n"); else printf(" Slot 5\n");}
		if (fexists("data/custom-6.ajl")) {if (levelsFound[levelEnabled-1] == 6) printf("[Slot 6]\n"); else printf(" Slot 6\n");}
		if (fexists("data/custom-7.ajl")) {if (levelsFound[levelEnabled-1] == 7) printf("[Slot 7]\n"); else printf(" Slot 7\n");}
		if (fexists("data/custom-8.ajl")) {if (levelsFound[levelEnabled-1] == 8) printf("[Slot 8]\n"); else printf(" Slot 8\n");}
		bool exit = false;
		debugPrint("Looking for input...");
		while (true) {
			hidScanInput();
			u32 lDown = hidKeysDown();
			if (lDown & KEY_B) {exit = true; break;}
			else if (lDown & KEY_UP) {decIntWithMax(levelEnabled, levelsFound.size(), levelsFound[0]); break;}
			else if (lDown & KEY_DOWN) {incIntWithMax(levelEnabled, levelsFound.size(), levelsFound[0]); break;}
			else if (lDown & KEY_A) {
				debugPrint("Reading in custom level...");
				std::ifstream levin;
				char * levpath = (char*)malloc(25);
				sprintf(levpath, "data/custom-%d.ajl", levelEnabled);
				levin.open(levpath);
				std::string buffer;
				for (int m = 7; m > -1; m--) {
					std::getline(levin, buffer);
					level_map[4][m] = buffer;
					#ifdef __DEBUG
					consoleSelect(&debug);
					printf("Buffer %d: %s\nMap %d: %s\n\n", m, buffer.c_str(), m, level_map[4][m].c_str());
					sleep(.5);
					consoleSelect(&screen);
					#endif
				}
				levin.close();
				debugPrint("Checking level for finish...");
				if (level_map[4][0][level_map[4][0].length()-1] != 'F') {printf("You forgot to put an 'F' at the end of your level. Please edit it immediately, as it will not work right. But for now, the F will be put in at the end.\n"); /*level_map[4][0].append("F");*/}
				#ifdef __DEBUG
				consoleSelect(&debug);
				printf("Here's the level:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\nDel: del", level_map[4][7].substr(0, 39).c_str(), level_map[4][6].substr(0, 39).c_str(), level_map[4][5].substr(0, 39).c_str(), level_map[4][4].substr(0, 39).c_str(), level_map[4][3].substr(0, 39).c_str(), level_map[4][2].substr(0, 39).c_str(), level_map[4][1].substr(0, 39).c_str(), level_map[4][0].substr(0, 39).c_str());
				sleep(.5);
				printf("\b\b");
				sleep(2.5);
				consoleSelect(&screen);
				#endif
				debugPrint("Running level...");
				runLevel(4);
				exit = true;
				break;
			}
			sleep(.25);
		}
		consoleClear();
		if (exit) break;
	}
	sleep(.3);
}










