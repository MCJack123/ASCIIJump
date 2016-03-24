//The level definitions
#include <map>
#include <vector>
#include <sstream>
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

std::string level_map[4][8];
std::map<std::string, int> levn;
float ldel = 0.083333;
int cube = 0;
std::vector<std::vector<const char *> > cubes = {{"----","||-|","|-||","----"}, {"----","|[]|","|[]|","----"}, {"-][-","|=[|","|]=|","-][-"}, {"----","|][|","|LJ|","----"}};

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
std::tuple<std::vector<const char *>, bool> convertCharToCube(char charToCube) {
	bool willKill;
	std::vector<const char *> retvec;
	if (charToCube == 'B') {retvec = {"----", "|  |", "|  |", "----"}; willKill = false;}
	else if (charToCube == 'D') {retvec = {" || ", "-++-", "-++-", " || "}; willKill = false;}
	else if (charToCube == 'X') {retvec = {"    ", " /\\ ", "/  \\", "|__|"}; willKill = true;}
	else if (charToCube == 'x') {retvec = {"    ", "    ", " /\\ ", "/__\\"}; willKill = true;}
	else if (charToCube == 's') {retvec = {"    ", "    ", "    ", "/\\/\\"}; willKill = true;}
	else if (charToCube == '-') {retvec = {"----", "|__|", "    ", "    "}; willKill = false;}
	else if (charToCube == '\\') {retvec = {"\\   ", "|\\  ", "| \\ ", "|  \\"}; willKill = false;}
	else if (charToCube == '/') {retvec = {"   /", "  /|", " / |", "/  |"}; willKill = false;}
	else if (charToCube == 'F') {retvec = {"    ", "    ", "    ", "    "}; willKill = false;}
	else if (charToCube == ' ') {retvec = {"    ", "    ", "    ", "    "}; willKill = false;}
	else if (charToCube == '_') {retvec = {"    ", "    ", "----", "|__|"}; willKill = false;}
	else {retvec = {"none", "none", "none", "none"}; willKill = false; debugPrint("Unrecognized block!"); unrec_blocks++;}
	return std::make_tuple(retvec, willKill);
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
	
	//Stats of GeometryJump:
	// * 11 squares per second
	// * Jumps are 4 squares long, 3 squares high
	//ASCIIJump:
	// Each square will be 4x4 (except the top row will be 2 tall)...
	// ...so there will be 8 rows (of course) and 12 columns.
	
	// Just make it easy to access the level data
	std::string r1 = level_map[levelid][0];
	std::string r2 = level_map[levelid][1];
	std::string r3 = level_map[levelid][2];
	std::string r4 = level_map[levelid][3];
	std::string r5 = level_map[levelid][4];
	std::string r6 = level_map[levelid][5];
	std::string r7 = level_map[levelid][6];
	std::string r8 = level_map[levelid][7];
	std::string ra[8] = level_map[levelid];
	
	// This is it, the main loop!
	int attempts = 1;
	int y = 0;
	int y_orig = 0;
	bool jump = false;
    bool falling = false;
	std::string attemptss = "1";
	int percentage = 0;
	int xoh;
	int highscore = nmscore[levelid];
	for (int x = 0; (true); x++) {
		if (r1[x+11] == 'F') {printf("You win!"); sleep(3); break;}
		//if (y > 7) {y = 0; debugPrint("Y is greater than 7!");}
		char * terminal = (char*)malloc(2000);
		{sprintf(terminal, "%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s",\
(y==7 ? cubes[cube][2] : std::get<0>(convertCharToCube(r8[x]))[2]),\
std::get<0>(convertCharToCube(r8[x+1]))[2],\
std::get<0>(convertCharToCube(r8[x+2]))[2],\
std::get<0>(convertCharToCube(r8[x+3]))[2],\
std::get<0>(convertCharToCube(r8[x+4]))[2],\
std::get<0>(convertCharToCube(r8[x+5]))[2],\
std::get<0>(convertCharToCube(r8[x+6]))[2],\
std::get<0>(convertCharToCube(r8[x+7]))[2],\
std::get<0>(convertCharToCube(r8[x+8]))[2],\
std::get<0>(convertCharToCube(r8[x+9]))[2],\
std::get<0>(convertCharToCube(r8[x+10]))[2],\
std::get<0>(convertCharToCube(r8[x+11]))[2],\
(y==7 ? cubes[cube][3] : std::get<0>(convertCharToCube(r8[x]))[3]),\
std::get<0>(convertCharToCube(r8[x+1]))[3],\
std::get<0>(convertCharToCube(r8[x+2]))[3],\
std::get<0>(convertCharToCube(r8[x+3]))[3],\
std::get<0>(convertCharToCube(r8[x+4]))[3],\
std::get<0>(convertCharToCube(r8[x+5]))[3],\
std::get<0>(convertCharToCube(r8[x+6]))[3],\
std::get<0>(convertCharToCube(r8[x+7]))[3],\
std::get<0>(convertCharToCube(r8[x+8]))[3],\
std::get<0>(convertCharToCube(r8[x+9]))[3],\
std::get<0>(convertCharToCube(r8[x+10]))[3],\
std::get<0>(convertCharToCube(r8[x+11]))[3],\
(y==6 ? cubes[cube][0] : std::get<0>(convertCharToCube(r7[x]))[0]),\
(x<=6 ? "A" : std::get<0>(convertCharToCube(r7[x+1]))[0]),\
(x<=6 ? "t" : std::get<0>(convertCharToCube(r7[x+2]))[0]),\
(x<=6 ? "t" : std::get<0>(convertCharToCube(r7[x+3]))[0]),\
(x<=6 ? "e" : std::get<0>(convertCharToCube(r7[x+4]))[0]),\
(x<=6 ? "m" : std::get<0>(convertCharToCube(r7[x+5]))[0]),\
(x<=6 ? "p" : std::get<0>(convertCharToCube(r7[x+6]))[0]),\
(x<=6 ? "t" : std::get<0>(convertCharToCube(r7[x+7]))[0]),\
(x<=6 ? " " : std::get<0>(convertCharToCube(r7[x+8]))[0]),\
(x<=6 ? attemptss.c_str() : std::get<0>(convertCharToCube(r7[x+9]))[0]),\
(attempts > 9 ? "" : std::get<0>(convertCharToCube(r7[x+10]))[0]),\
(attempts > 99 ? "" : std::get<0>(convertCharToCube(r7[x+11]))[0]),\
(y==6 ? cubes[cube][1] : std::get<0>(convertCharToCube(r7[x]))[1]),\
std::get<0>(convertCharToCube(r7[x+1]))[1],\
std::get<0>(convertCharToCube(r7[x+2]))[1],\
std::get<0>(convertCharToCube(r7[x+3]))[1],\
std::get<0>(convertCharToCube(r7[x+4]))[1],\
std::get<0>(convertCharToCube(r7[x+5]))[1],\
std::get<0>(convertCharToCube(r7[x+6]))[1],\
std::get<0>(convertCharToCube(r7[x+7]))[1],\
std::get<0>(convertCharToCube(r7[x+8]))[1],\
std::get<0>(convertCharToCube(r7[x+9]))[1],\
std::get<0>(convertCharToCube(r7[x+10]))[1],\
std::get<0>(convertCharToCube(r7[x+11]))[1],\
(y==6 ? cubes[cube][2] : std::get<0>(convertCharToCube(r7[x]))[2]),\
std::get<0>(convertCharToCube(r7[x+1]))[2],\
std::get<0>(convertCharToCube(r7[x+2]))[2],\
std::get<0>(convertCharToCube(r7[x+3]))[2],\
std::get<0>(convertCharToCube(r7[x+4]))[2],\
std::get<0>(convertCharToCube(r7[x+5]))[2],\
std::get<0>(convertCharToCube(r7[x+6]))[2],\
std::get<0>(convertCharToCube(r7[x+7]))[2],\
std::get<0>(convertCharToCube(r7[x+8]))[2],\
std::get<0>(convertCharToCube(r7[x+9]))[2],\
std::get<0>(convertCharToCube(r7[x+10]))[2],\
std::get<0>(convertCharToCube(r7[x+11]))[2],\
(y==6 ? cubes[cube][3] : std::get<0>(convertCharToCube(r7[x]))[3]),\
std::get<0>(convertCharToCube(r7[x+1]))[3],\
std::get<0>(convertCharToCube(r7[x+2]))[3],\
std::get<0>(convertCharToCube(r7[x+3]))[3],\
std::get<0>(convertCharToCube(r7[x+4]))[3],\
std::get<0>(convertCharToCube(r7[x+5]))[3],\
std::get<0>(convertCharToCube(r7[x+6]))[3],\
std::get<0>(convertCharToCube(r7[x+7]))[3],\
std::get<0>(convertCharToCube(r7[x+8]))[3],\
std::get<0>(convertCharToCube(r7[x+9]))[3],\
std::get<0>(convertCharToCube(r7[x+10]))[3],\
std::get<0>(convertCharToCube(r7[x+11]))[3],\
(y==5 ? cubes[cube][0] : std::get<0>(convertCharToCube(r6[x]))[0]),\
std::get<0>(convertCharToCube(r6[x+1]))[0],\
std::get<0>(convertCharToCube(r6[x+2]))[0],\
std::get<0>(convertCharToCube(r6[x+3]))[0],\
std::get<0>(convertCharToCube(r6[x+4]))[0],\
std::get<0>(convertCharToCube(r6[x+5]))[0],\
std::get<0>(convertCharToCube(r6[x+6]))[0],\
std::get<0>(convertCharToCube(r6[x+7]))[0],\
std::get<0>(convertCharToCube(r6[x+8]))[0],\
std::get<0>(convertCharToCube(r6[x+9]))[0],\
std::get<0>(convertCharToCube(r6[x+10]))[0],\
std::get<0>(convertCharToCube(r6[x+11]))[0],\
(y==5 ? cubes[cube][1] : std::get<0>(convertCharToCube(r6[x]))[1]),\
std::get<0>(convertCharToCube(r6[x+1]))[1],\
std::get<0>(convertCharToCube(r6[x+2]))[1],\
std::get<0>(convertCharToCube(r6[x+3]))[1],\
std::get<0>(convertCharToCube(r6[x+4]))[1],\
std::get<0>(convertCharToCube(r6[x+5]))[1],\
std::get<0>(convertCharToCube(r6[x+6]))[1],\
std::get<0>(convertCharToCube(r6[x+7]))[1],\
std::get<0>(convertCharToCube(r6[x+8]))[1],\
std::get<0>(convertCharToCube(r6[x+9]))[1],\
std::get<0>(convertCharToCube(r6[x+10]))[1],\
std::get<0>(convertCharToCube(r6[x+11]))[1],\
(y==5 ? cubes[cube][2] : std::get<0>(convertCharToCube(r6[x]))[2]),\
std::get<0>(convertCharToCube(r6[x+1]))[2],\
std::get<0>(convertCharToCube(r6[x+2]))[2],\
std::get<0>(convertCharToCube(r6[x+3]))[2],\
std::get<0>(convertCharToCube(r6[x+4]))[2],\
std::get<0>(convertCharToCube(r6[x+5]))[2],\
std::get<0>(convertCharToCube(r6[x+6]))[2],\
std::get<0>(convertCharToCube(r6[x+7]))[2],\
std::get<0>(convertCharToCube(r6[x+8]))[2],\
std::get<0>(convertCharToCube(r6[x+9]))[2],\
std::get<0>(convertCharToCube(r6[x+10]))[2],\
std::get<0>(convertCharToCube(r6[x+11]))[2],\
(y==5 ? cubes[cube][3] : std::get<0>(convertCharToCube(r6[x]))[3]),\
std::get<0>(convertCharToCube(r6[x+1]))[3],\
std::get<0>(convertCharToCube(r6[x+2]))[3],\
std::get<0>(convertCharToCube(r6[x+3]))[3],\
std::get<0>(convertCharToCube(r6[x+4]))[3],\
std::get<0>(convertCharToCube(r6[x+5]))[3],\
std::get<0>(convertCharToCube(r6[x+6]))[3],\
std::get<0>(convertCharToCube(r6[x+7]))[3],\
std::get<0>(convertCharToCube(r6[x+8]))[3],\
std::get<0>(convertCharToCube(r6[x+9]))[3],\
std::get<0>(convertCharToCube(r6[x+10]))[3],\
std::get<0>(convertCharToCube(r6[x+11]))[3],\
(y==4 ? cubes[cube][0] : std::get<0>(convertCharToCube(r5[x]))[0]),\
std::get<0>(convertCharToCube(r5[x+1]))[0],\
std::get<0>(convertCharToCube(r5[x+2]))[0],\
std::get<0>(convertCharToCube(r5[x+3]))[0],\
std::get<0>(convertCharToCube(r5[x+4]))[0],\
std::get<0>(convertCharToCube(r5[x+5]))[0],\
std::get<0>(convertCharToCube(r5[x+6]))[0],\
std::get<0>(convertCharToCube(r5[x+7]))[0],\
std::get<0>(convertCharToCube(r5[x+8]))[0],\
std::get<0>(convertCharToCube(r5[x+9]))[0],\
std::get<0>(convertCharToCube(r5[x+10]))[0],\
std::get<0>(convertCharToCube(r5[x+11]))[0],\
(y==4 ? cubes[cube][1] : std::get<0>(convertCharToCube(r5[x]))[1]),\
std::get<0>(convertCharToCube(r5[x+1]))[1],\
std::get<0>(convertCharToCube(r5[x+2]))[1],\
std::get<0>(convertCharToCube(r5[x+3]))[1],\
std::get<0>(convertCharToCube(r5[x+4]))[1],\
std::get<0>(convertCharToCube(r5[x+5]))[1],\
std::get<0>(convertCharToCube(r5[x+6]))[1],\
std::get<0>(convertCharToCube(r5[x+7]))[1],\
std::get<0>(convertCharToCube(r5[x+8]))[1],\
std::get<0>(convertCharToCube(r5[x+9]))[1],\
std::get<0>(convertCharToCube(r5[x+10]))[1],\
std::get<0>(convertCharToCube(r5[x+11]))[1],\
(y==4 ? cubes[cube][2] : std::get<0>(convertCharToCube(r5[x]))[2]),\
std::get<0>(convertCharToCube(r5[x+1]))[2],\
std::get<0>(convertCharToCube(r5[x+2]))[2],\
std::get<0>(convertCharToCube(r5[x+3]))[2],\
std::get<0>(convertCharToCube(r5[x+4]))[2],\
std::get<0>(convertCharToCube(r5[x+5]))[2],\
std::get<0>(convertCharToCube(r5[x+6]))[2],\
std::get<0>(convertCharToCube(r5[x+7]))[2],\
std::get<0>(convertCharToCube(r5[x+8]))[2],\
std::get<0>(convertCharToCube(r5[x+9]))[2],\
std::get<0>(convertCharToCube(r5[x+10]))[2],\
std::get<0>(convertCharToCube(r5[x+11]))[2],\
(y==4 ? cubes[cube][3] : std::get<0>(convertCharToCube(r5[x]))[3]),\
std::get<0>(convertCharToCube(r5[x+1]))[3],\
std::get<0>(convertCharToCube(r5[x+2]))[3],\
std::get<0>(convertCharToCube(r5[x+3]))[3],\
std::get<0>(convertCharToCube(r5[x+4]))[3],\
std::get<0>(convertCharToCube(r5[x+5]))[3],\
std::get<0>(convertCharToCube(r5[x+6]))[3],\
std::get<0>(convertCharToCube(r5[x+7]))[3],\
std::get<0>(convertCharToCube(r5[x+8]))[3],\
std::get<0>(convertCharToCube(r5[x+9]))[3],\
std::get<0>(convertCharToCube(r5[x+10]))[3],\
std::get<0>(convertCharToCube(r5[x+11]))[3],\
(y==3 ? cubes[cube][0] : std::get<0>(convertCharToCube(r4[x]))[0]),\
std::get<0>(convertCharToCube(r4[x+1]))[0],\
std::get<0>(convertCharToCube(r4[x+2]))[0],\
std::get<0>(convertCharToCube(r4[x+3]))[0],\
std::get<0>(convertCharToCube(r4[x+4]))[0],\
std::get<0>(convertCharToCube(r4[x+5]))[0],\
std::get<0>(convertCharToCube(r4[x+6]))[0],\
std::get<0>(convertCharToCube(r4[x+7]))[0],\
std::get<0>(convertCharToCube(r4[x+8]))[0],\
std::get<0>(convertCharToCube(r4[x+9]))[0],\
std::get<0>(convertCharToCube(r4[x+10]))[0],\
std::get<0>(convertCharToCube(r4[x+11]))[0],\
(y==3 ? cubes[cube][1] : std::get<0>(convertCharToCube(r4[x]))[1]),\
std::get<0>(convertCharToCube(r4[x+1]))[1],\
std::get<0>(convertCharToCube(r4[x+2]))[1],\
std::get<0>(convertCharToCube(r4[x+3]))[1],\
std::get<0>(convertCharToCube(r4[x+4]))[1],\
std::get<0>(convertCharToCube(r4[x+5]))[1],\
std::get<0>(convertCharToCube(r4[x+6]))[1],\
std::get<0>(convertCharToCube(r4[x+7]))[1],\
std::get<0>(convertCharToCube(r4[x+8]))[1],\
std::get<0>(convertCharToCube(r4[x+9]))[1],\
std::get<0>(convertCharToCube(r4[x+10]))[1],\
std::get<0>(convertCharToCube(r4[x+11]))[1],\
(y==3 ? cubes[cube][2] : std::get<0>(convertCharToCube(r4[x]))[2]),\
std::get<0>(convertCharToCube(r4[x+1]))[2],\
std::get<0>(convertCharToCube(r4[x+2]))[2],\
std::get<0>(convertCharToCube(r4[x+3]))[2],\
std::get<0>(convertCharToCube(r4[x+4]))[2],\
std::get<0>(convertCharToCube(r4[x+5]))[2],\
std::get<0>(convertCharToCube(r4[x+6]))[2],\
std::get<0>(convertCharToCube(r4[x+7]))[2],\
std::get<0>(convertCharToCube(r4[x+8]))[2],\
std::get<0>(convertCharToCube(r4[x+9]))[2],\
std::get<0>(convertCharToCube(r4[x+10]))[2],\
std::get<0>(convertCharToCube(r4[x+11]))[2],\
(y==3 ? cubes[cube][3] : std::get<0>(convertCharToCube(r4[x]))[3]),\
std::get<0>(convertCharToCube(r4[x+1]))[3],\
std::get<0>(convertCharToCube(r4[x+2]))[3],\
std::get<0>(convertCharToCube(r4[x+3]))[3],\
std::get<0>(convertCharToCube(r4[x+4]))[3],\
std::get<0>(convertCharToCube(r4[x+5]))[3],\
std::get<0>(convertCharToCube(r4[x+6]))[3],\
std::get<0>(convertCharToCube(r4[x+7]))[3],\
std::get<0>(convertCharToCube(r4[x+8]))[3],\
std::get<0>(convertCharToCube(r4[x+9]))[3],\
std::get<0>(convertCharToCube(r4[x+10]))[3],\
std::get<0>(convertCharToCube(r4[x+11]))[3],\
(y==2 ? cubes[cube][0] : std::get<0>(convertCharToCube(r3[x]))[0]),\
std::get<0>(convertCharToCube(r3[x+1]))[0],\
std::get<0>(convertCharToCube(r3[x+2]))[0],\
std::get<0>(convertCharToCube(r3[x+3]))[0],\
std::get<0>(convertCharToCube(r3[x+4]))[0],\
std::get<0>(convertCharToCube(r3[x+5]))[0],\
std::get<0>(convertCharToCube(r3[x+6]))[0],\
std::get<0>(convertCharToCube(r3[x+7]))[0],\
std::get<0>(convertCharToCube(r3[x+8]))[0],\
std::get<0>(convertCharToCube(r3[x+9]))[0],\
std::get<0>(convertCharToCube(r3[x+10]))[0],\
std::get<0>(convertCharToCube(r3[x+11]))[0],\
(y==2 ? cubes[cube][1] : std::get<0>(convertCharToCube(r3[x]))[1]),\
std::get<0>(convertCharToCube(r3[x+1]))[1],\
std::get<0>(convertCharToCube(r3[x+2]))[1],\
std::get<0>(convertCharToCube(r3[x+3]))[1],\
std::get<0>(convertCharToCube(r3[x+4]))[1],\
std::get<0>(convertCharToCube(r3[x+5]))[1],\
std::get<0>(convertCharToCube(r3[x+6]))[1],\
std::get<0>(convertCharToCube(r3[x+7]))[1],\
std::get<0>(convertCharToCube(r3[x+8]))[1],\
std::get<0>(convertCharToCube(r3[x+9]))[1],\
std::get<0>(convertCharToCube(r3[x+10]))[1],\
std::get<0>(convertCharToCube(r3[x+11]))[1],\
(y==2 ? cubes[cube][2] : std::get<0>(convertCharToCube(r3[x]))[2]),\
std::get<0>(convertCharToCube(r3[x+1]))[2],\
std::get<0>(convertCharToCube(r3[x+2]))[2],\
std::get<0>(convertCharToCube(r3[x+3]))[2],\
std::get<0>(convertCharToCube(r3[x+4]))[2],\
std::get<0>(convertCharToCube(r3[x+5]))[2],\
std::get<0>(convertCharToCube(r3[x+6]))[2],\
std::get<0>(convertCharToCube(r3[x+7]))[2],\
std::get<0>(convertCharToCube(r3[x+8]))[2],\
std::get<0>(convertCharToCube(r3[x+9]))[2],\
std::get<0>(convertCharToCube(r3[x+10]))[2],\
std::get<0>(convertCharToCube(r3[x+11]))[2],\
(y==2 ? cubes[cube][3] : std::get<0>(convertCharToCube(r3[x]))[3]),\
std::get<0>(convertCharToCube(r3[x+1]))[3],\
std::get<0>(convertCharToCube(r3[x+2]))[3],\
std::get<0>(convertCharToCube(r3[x+3]))[3],\
std::get<0>(convertCharToCube(r3[x+4]))[3],\
std::get<0>(convertCharToCube(r3[x+5]))[3],\
std::get<0>(convertCharToCube(r3[x+6]))[3],\
std::get<0>(convertCharToCube(r3[x+7]))[3],\
std::get<0>(convertCharToCube(r3[x+8]))[3],\
std::get<0>(convertCharToCube(r3[x+9]))[3],\
std::get<0>(convertCharToCube(r3[x+10]))[3],\
std::get<0>(convertCharToCube(r3[x+11]))[3],\
(y==1 ? cubes[cube][0] : std::get<0>(convertCharToCube(r2[x]))[0]),\
std::get<0>(convertCharToCube(r2[x+1]))[0],\
std::get<0>(convertCharToCube(r2[x+2]))[0],\
std::get<0>(convertCharToCube(r2[x+3]))[0],\
std::get<0>(convertCharToCube(r2[x+4]))[0],\
std::get<0>(convertCharToCube(r2[x+5]))[0],\
std::get<0>(convertCharToCube(r2[x+6]))[0],\
std::get<0>(convertCharToCube(r2[x+7]))[0],\
std::get<0>(convertCharToCube(r2[x+8]))[0],\
std::get<0>(convertCharToCube(r2[x+9]))[0],\
std::get<0>(convertCharToCube(r2[x+10]))[0],\
std::get<0>(convertCharToCube(r2[x+11]))[0],\
(y==1 ? cubes[cube][1] : std::get<0>(convertCharToCube(r2[x]))[1]),\
std::get<0>(convertCharToCube(r2[x+1]))[1],\
std::get<0>(convertCharToCube(r2[x+2]))[1],\
std::get<0>(convertCharToCube(r2[x+3]))[1],\
std::get<0>(convertCharToCube(r2[x+4]))[1],\
std::get<0>(convertCharToCube(r2[x+5]))[1],\
std::get<0>(convertCharToCube(r2[x+6]))[1],\
std::get<0>(convertCharToCube(r2[x+7]))[1],\
std::get<0>(convertCharToCube(r2[x+8]))[1],\
std::get<0>(convertCharToCube(r2[x+9]))[1],\
std::get<0>(convertCharToCube(r2[x+10]))[1],\
std::get<0>(convertCharToCube(r2[x+11]))[1],\
(y==1 ? cubes[cube][2] : std::get<0>(convertCharToCube(r2[x]))[2]),\
std::get<0>(convertCharToCube(r2[x+1]))[2],\
std::get<0>(convertCharToCube(r2[x+2]))[2],\
std::get<0>(convertCharToCube(r2[x+3]))[2],\
std::get<0>(convertCharToCube(r2[x+4]))[2],\
std::get<0>(convertCharToCube(r2[x+5]))[2],\
std::get<0>(convertCharToCube(r2[x+6]))[2],\
std::get<0>(convertCharToCube(r2[x+7]))[2],\
std::get<0>(convertCharToCube(r2[x+8]))[2],\
std::get<0>(convertCharToCube(r2[x+9]))[2],\
std::get<0>(convertCharToCube(r2[x+10]))[2],\
std::get<0>(convertCharToCube(r2[x+11]))[2],\
(y==1 ? cubes[cube][3] : std::get<0>(convertCharToCube(r2[x]))[3]),\
std::get<0>(convertCharToCube(r2[x+1]))[3],\
std::get<0>(convertCharToCube(r2[x+2]))[3],\
std::get<0>(convertCharToCube(r2[x+3]))[3],\
std::get<0>(convertCharToCube(r2[x+4]))[3],\
std::get<0>(convertCharToCube(r2[x+5]))[3],\
std::get<0>(convertCharToCube(r2[x+6]))[3],\
std::get<0>(convertCharToCube(r2[x+7]))[3],\
std::get<0>(convertCharToCube(r2[x+8]))[3],\
std::get<0>(convertCharToCube(r2[x+9]))[3],\
std::get<0>(convertCharToCube(r2[x+10]))[3],\
std::get<0>(convertCharToCube(r2[x+11]))[3],\
(y==0 ? cubes[cube][0] : std::get<0>(convertCharToCube(r1[x]))[0]),\
std::get<0>(convertCharToCube(r1[x+1]))[0],\
std::get<0>(convertCharToCube(r1[x+2]))[0],\
std::get<0>(convertCharToCube(r1[x+3]))[0],\
std::get<0>(convertCharToCube(r1[x+4]))[0],\
std::get<0>(convertCharToCube(r1[x+5]))[0],\
std::get<0>(convertCharToCube(r1[x+6]))[0],\
std::get<0>(convertCharToCube(r1[x+7]))[0],\
std::get<0>(convertCharToCube(r1[x+8]))[0],\
std::get<0>(convertCharToCube(r1[x+9]))[0],\
std::get<0>(convertCharToCube(r1[x+10]))[0],\
std::get<0>(convertCharToCube(r1[x+11]))[0],\
(y==0 ? cubes[cube][1] : std::get<0>(convertCharToCube(r1[x]))[1]),\
std::get<0>(convertCharToCube(r1[x+1]))[1],\
std::get<0>(convertCharToCube(r1[x+2]))[1],\
std::get<0>(convertCharToCube(r1[x+3]))[1],\
std::get<0>(convertCharToCube(r1[x+4]))[1],\
std::get<0>(convertCharToCube(r1[x+5]))[1],\
std::get<0>(convertCharToCube(r1[x+6]))[1],\
std::get<0>(convertCharToCube(r1[x+7]))[1],\
std::get<0>(convertCharToCube(r1[x+8]))[1],\
std::get<0>(convertCharToCube(r1[x+9]))[1],\
std::get<0>(convertCharToCube(r1[x+10]))[1],\
std::get<0>(convertCharToCube(r1[x+11]))[1],\
(y==0 ? cubes[cube][2] : std::get<0>(convertCharToCube(r1[x]))[2]),\
std::get<0>(convertCharToCube(r1[x+1]))[2],\
std::get<0>(convertCharToCube(r1[x+2]))[2],\
std::get<0>(convertCharToCube(r1[x+3]))[2],\
std::get<0>(convertCharToCube(r1[x+4]))[2],\
std::get<0>(convertCharToCube(r1[x+5]))[2],\
std::get<0>(convertCharToCube(r1[x+6]))[2],\
std::get<0>(convertCharToCube(r1[x+7]))[2],\
std::get<0>(convertCharToCube(r1[x+8]))[2],\
std::get<0>(convertCharToCube(r1[x+9]))[2],\
std::get<0>(convertCharToCube(r1[x+10]))[2],\
std::get<0>(convertCharToCube(r1[x+11]))[2],\
(y==0 ? cubes[cube][3] : std::get<0>(convertCharToCube(r1[x]))[3]),\
std::get<0>(convertCharToCube(r1[x+1]))[3],\
std::get<0>(convertCharToCube(r1[x+2]))[3],\
std::get<0>(convertCharToCube(r1[x+3]))[3],\
std::get<0>(convertCharToCube(r1[x+4]))[3],\
std::get<0>(convertCharToCube(r1[x+5]))[3],\
std::get<0>(convertCharToCube(r1[x+6]))[3],\
std::get<0>(convertCharToCube(r1[x+7]))[3],\
std::get<0>(convertCharToCube(r1[x+8]))[3],\
std::get<0>(convertCharToCube(r1[x+9]))[3],\
std::get<0>(convertCharToCube(r1[x+10]))[3],\
std::get<0>(convertCharToCube(r1[x+11]))[3]);} // Prints the squares
		sleep(.01);
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
		if (((std::get<1>(convertCharToCube(ra[y][x])) && !jump)/* player on spike */ || (ra[y][x] != ' '))/* player in block */ && y < 7) {
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
        else if (jump && y == y_orig + 2) {jump = false; falling = true;}
        else if (!jump && /*ra[y-1][x] != ' ' && */(ra[y-1][x+1] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x+1]))) && y > 0 && (ra[y-1][x] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x])))) {y--; falling = true;}
        else if (!(!jump && /*ra[y-1][x] != ' ' && */(ra[y-1][x+1] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x+1]))) && y > 0 && (ra[y-1][x] == ' ' || std::get<1>(convertCharToCube(ra[y-1][x]))))) {falling = false;}
		xoh = x * 100;
		percentage = xoh / r8.length();
		#ifdef __DEBUG
		consoleSelect(&debug);
		printf("Percentage: %d\n", percentage);
		consoleSelect(&screen);
		#endif
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










