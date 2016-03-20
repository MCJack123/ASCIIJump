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
std::vector<const char *> cube = {"----", "|-||", "||-|", "----"};

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
"                                                                                                                                                             __       __         XXXX                                                             X    DDDDDDDDDDDDDD        ",\
"                                                                                                                                                            XXXX     XXXX        ----       X                                                 -             DDDDDD           ",\
"                                                                                                                                             -   -    DDDDDDDDDDDDDDDDDDDDDDDD          DDDDD                                             -                                  ",\
"                                                                                                                                         -              DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDX              X                         -                                      ",\
"                                                                                                                                     -                  DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD  ----       X             -             DDDDDDDDDDDDDDDDDD           ",\
"                                                          B                                                            X         -                      DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD           -------         -                        DDDDDDDDDDDD          ",\
"                                                      B   D                                            X        DDDDDDDDDDDDDD                          DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD                   -----                            DDDDDDDDDDDDD         ",\
"                 B              xX              XXBsssDsssDX                    XX     DDDDDDDDsssDDDDDDDDDDDsssDDDDDDDDDDDDDDssssssssssssssssssssssssssDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDssssssssssssssssssssssssssssssssssssssssssssssssssssDDDDDDDDDDDDDD        F");
	registerLevel(1, "", "", "", "", "", "", "", "C");
	registerLevel(2, "", "", "", "", "", "", "", "C");
	registerLevel(3, "", "", "", "", "", "", "", "C");
}
int unrec_blocks = 0;
std::tuple<std::vector<const char *>, bool> convertCharToCube(char charToCube) {
	bool willKill;
	std::vector<const char *> retvec;
	if (charToCube == 'B') {retvec = {"----", "|  |", "|  |", "----"}; willKill = false;}
	else if (charToCube == 'D') {retvec = {" || ", "-||-", "-||-", " || "}; willKill = false;}
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
(y==7 ? cube[2] : std::get<0>(convertCharToCube(r8[x]))[2]),\
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
(y==7 ? cube[3] : std::get<0>(convertCharToCube(r8[x]))[3]),\
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
(y==6 ? cube[0] : std::get<0>(convertCharToCube(r7[x]))[0]),\
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
(y==6 ? cube[1] : std::get<0>(convertCharToCube(r7[x]))[1]),\
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
(y==6 ? cube[2] : std::get<0>(convertCharToCube(r7[x]))[2]),\
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
(y==6 ? cube[3] : std::get<0>(convertCharToCube(r7[x]))[3]),\
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
(y==5 ? cube[0] : std::get<0>(convertCharToCube(r6[x]))[0]),\
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
(y==5 ? cube[1] : std::get<0>(convertCharToCube(r6[x]))[1]),\
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
(y==5 ? cube[2] : std::get<0>(convertCharToCube(r6[x]))[2]),\
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
(y==5 ? cube[3] : std::get<0>(convertCharToCube(r6[x]))[3]),\
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
(y==4 ? cube[0] : std::get<0>(convertCharToCube(r5[x]))[0]),\
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
(y==4 ? cube[1] : std::get<0>(convertCharToCube(r5[x]))[1]),\
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
(y==4 ? cube[2] : std::get<0>(convertCharToCube(r5[x]))[2]),\
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
(y==4 ? cube[3] : std::get<0>(convertCharToCube(r5[x]))[3]),\
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
(y==3 ? cube[0] : std::get<0>(convertCharToCube(r4[x]))[0]),\
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
(y==3 ? cube[1] : std::get<0>(convertCharToCube(r4[x]))[1]),\
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
(y==3 ? cube[2] : std::get<0>(convertCharToCube(r4[x]))[2]),\
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
(y==3 ? cube[3] : std::get<0>(convertCharToCube(r4[x]))[3]),\
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
(y==2 ? cube[0] : std::get<0>(convertCharToCube(r3[x]))[0]),\
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
(y==2 ? cube[1] : std::get<0>(convertCharToCube(r3[x]))[1]),\
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
(y==2 ? cube[2] : std::get<0>(convertCharToCube(r3[x]))[2]),\
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
(y==2 ? cube[3] : std::get<0>(convertCharToCube(r3[x]))[3]),\
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
(y==1 ? cube[0] : std::get<0>(convertCharToCube(r2[x]))[0]),\
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
(y==1 ? cube[1] : std::get<0>(convertCharToCube(r2[x]))[1]),\
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
(y==1 ? cube[2] : std::get<0>(convertCharToCube(r2[x]))[2]),\
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
(y==1 ? cube[3] : std::get<0>(convertCharToCube(r2[x]))[3]),\
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
(y==0 ? cube[0] : std::get<0>(convertCharToCube(r1[x]))[0]),\
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
(y==0 ? cube[1] : std::get<0>(convertCharToCube(r1[x]))[1]),\
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
(y==0 ? cube[2] : std::get<0>(convertCharToCube(r1[x]))[2]),\
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
(y==0 ? cube[3] : std::get<0>(convertCharToCube(r1[x]))[3]),\
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
		if ((bDown | bHeld) & KEY_START) break;
		if ((bDown | bHeld) && !jump && !falling && !std::get<1>(convertCharToCube(ra[y-1][x]))) {jump = true; y_orig = y++;}
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
	/*debugPrint("Outputting high score to file...");
	std::ofstream outf;
	outf.open("data/scores.txt", std::fstream::trunc);
	bool m;
	for (int l = 0; l <= 8; l++) {
		m = (l % 2 == 0);
		if (m) outf << pmscore[l/2] << std::endl;
		else outf << nmscore[(l-1)/2] << std::endl;
	}
	outf.close();
	*/
}










