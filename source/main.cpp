//
//  main.cpp
//  ASCIIJump3DS
//
//  Created by Jack Bruienne on 2/19/16.
//  Copyright © 2016 MCJack123. All rights reserved.
//

#include <cstdio>
#include <malloc.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <tuple>
#include <sys/unistd.h>
#ifndef _SYS_UNISTD_H_
#include <unistd.h>
#endif
#include <3ds.h>
#include <3ds/services/csnd.h>


// 3DS Top Screen Dimensions:
//     Width: 400 pixels / 50 chars (8px char width)
//	  Height: 240 pixels / 30 chars (8px char height)
// 3DS Bottom Screen Dimensions:
//     Width: 320 pixels / 40 chars (8px char width)
//    Height: Same as Top Screen

PrintConsole screen, debug;
std::string scorefile[8];
std::string buffer = "";
std::tuple<const char *, int> levnames[4] = {std::make_pair("First Level", 11), std::make_pair("Second Level", 12), std::make_pair("Another Level", 13), std::make_pair("Goo Lagoon", 10)};
bool debugMode = true;
int leveln = 0;
int maxlev = 3;
	char * levtext = (char*)malloc(40);
char * levtextt = (char*)malloc(40);
	char * pmtext = (char*)malloc(30);
	char * nmtext = (char*)malloc(30);
u8 consoletype;

/* The drawing board :)

//___\\   /---\     /---\   |--|  |--|\n\
||   ||  /  __|    / /-\_|  |  |  |  |\n\
||---||  \___  \  | |       |  |  |  |\n\
||---||  /     /   \ \-/-|  |  |  |  |\n\
||   ||  \----/     \---/   |--|  |--|\n\
 _____\n\
|__ __|  |-| |-|  |--\    /--|  |---\\n\
  | |    | | | |  | \ \  / / |  | () |\n\
 _| |    | | | |  | |\ \/ /| |  | __/\n\
| | |    | \_/ |  | | \__/ | |  | |\n\
\___/     \___/   |_|      |_|  |_|



     /|            1: Goo Lagoon           |\\n\
	/ |                                    | \\n\
   /  |   __________________________       |  \\n\
  /   |  |__________________________| 0%   |   \\n\
 |    |   __________________________       |    |\n\
  \   |  ||||||||||||||_____________| 50%  |   /\n\
   \  |   ______________________________   |  /\n\
    \ |  |             Go!              |  | /\n\
	 \|  |______________________________|  |/

*/

void debugPrint(const char * debugText) {
	if (debugMode) {
		consoleSelect(&debug);
		printf("%s\n", debugText);
		consoleSelect(&screen);
	}
}
int incIntWithMax(int& addend, int maximum, int minimum = 0) {
	if (addend == maximum) addend = minimum;
	else addend++;
	return addend;
}
int decIntWithMax(int& addend, int maximum, int minimum = 0) {
	if (addend == minimum) addend = maximum;
	else addend--;
	return addend;
}

template <class T>
void sleep(T time) {usleep(time * 1000000);}

// The main game
void runLevel(int levelid) {
	consoleSelect(&screen);
	printf("Not working now\n");
}
inline bool fexists (const std::string& name) {
  return ( access( name.c_str(), F_OK ) != -1 );
}

int main() {
	gfxInitDefault();
	consoleInit(GFX_TOP, &screen);
	consoleInit(GFX_BOTTOM, &debug);
	consoleSelect(&screen);
	csndInit();
	APT_CheckNew3DS(&consoletype);
	//Loading screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n               Console Type: %s\n                ASCIIJump for 3DS", consoletype ? "New3DS" : "Old3DS");
	hidScanInput();
	u32 dDown = hidKeysDown();
	u32 dHeld = hidKeysHeld();
	if ((dDown || dHeld) & KEY_X) debugMode = true;
	if (debugMode) printf("\n                 Debug mode is on");
	sleep(2);
	consoleClear();
	sleep(1);
	printf("\n\n\n\n\n\n\n\n\n      //___\\\\   /---\\     /---\\   |--|  |--|\n\
      ||   ||  /  __|    / /-\\_|  |  |  |  |\n\
      ||---||  \\___  \\  | |       |  |  |  |\n\
      ||---||  /     /   \\ \\-/-|  |  |  |  |\n\
      ||   ||  \\----/     \\---/   |--|  |--|\n\
       _____\n\
      |__ __|  |-| |-|  |--\\    /--|  |---\\\n\
        | |    | | | |  | \\ \\  / / |  | () |\n\
       _| |    | | | |  | |\\ \\/ /| |  | __/\n\
      | | |    | \\_/ |  | | \\__/ | |  | |\n\
      \\___/     \\___/   |_|      |_|  |_|");
	consoleSelect(&debug);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n               Loading...\n\n");
	int nmscore[4];
	int pmscore[4];
	// Load the scores from scores.txt
	debugPrint("Reading scores from sdmc://3ds/ASCIIJump3DS/data/scores.txt (yes, it is easy to hack the scores now)\nHere's some numbers:");
	std::ifstream in;
	in.open("data/scores.txt");
	int i = 0;
	do {
	    if (i % 2 == 0) {std::getline(in, buffer); pmscore[i/2] = atoi(buffer.c_str());}
		else {std::getline(in, buffer); nmscore[(i-1)/2] = atoi(buffer.c_str());}
		i++;
	}
	while (!(in.bad() || in.eof()));
	in.close();
	debugPrint("Loading song...");
	u8* sndbuffer;
    bool playing = false;
	if (fexists("data/background.raw")) {
    FILE *file = fopen("data/background.raw", "rb");
	debugPrint("Song loaded.");
    fseek(file, 0, SEEK_END);
    off_t sndsize = ftell(file);
    sndbuffer = (u8*)linearAlloc(sndsize);
    fseek(file, 0, SEEK_SET);
	debugPrint("Reading file...");
    off_t bytesRead = fread(sndbuffer, 1, sndsize, file);
    fclose(file);
	debugPrint("File read.");
	csndPlaySound(0x8, CSND_LOOPMODE_NORMAL, 32000, 1.0, 0.0, sndbuffer, sndbuffer, (u32)sndsize);
	} else debugPrint("File doesn't exist!");
		consoleClear();
		consoleSelect(&screen);
		consoleClear();
	debugPrint("Starting program...");
	while (aptMainLoop()) {
		//The menu
		sprintf(levtext, "%d: %s", leveln + 1, std::get<0>(levnames[leveln]));
		debugPrint(levtext);
		debugPrint("Creating level name text...");
		for (int j = 0, k = (36 - std::get<1>(levnames[leveln]) - 3) / 2, l = (36 - std::get<1>(levnames[leveln]) - 3) % 2; j <= k - 1; j++) {
			if (l == 1 && j > 94) {sprintf(levtextt, " %s ", levtext); levtext = levtextt; break;}
			else sprintf(levtextt, " %s ", levtext);
			levtext = levtextt;
			consoleSelect(&debug);
			if (debugMode) printf(".");
			consoleSelect(&screen);
		}
		debugPrint("\nCreating practice mode bar text...");
		for (int i = 0; i <= 100; i += 4) {
			if (i <= pmscore[leveln]) sprintf(pmtext, "%s|", pmtext);
			else sprintf(pmtext, "%s_", pmtext);
			consoleSelect(&debug);
			if (debugMode) printf(".");
			consoleSelect(&screen);
		}
		debugPrint("\nCreating normal mode bar text...");
		for (int i = 0; i <= 100; i += 4) {
			if (i <= nmscore[leveln]) sprintf(nmtext, "%s|", nmtext);
			else sprintf(nmtext, "%s_", nmtext);
			consoleSelect(&debug);
			if (debugMode) printf(".");
		}
		if (debugMode) printf(levtext);
		//if (debugMode) sleep(4);
		sleep(.2);
		consoleClear();
		printf("\n\n\n\n\n\n\n\n\n //___\\\\   /---\\     /---\\   |--|  |--|\n\
 ||   ||  /  __|    / /-\\_|  |  |  |  |\n\
 ||---||  \\___  \\  | |       |  |  |  |\n\
 ||---||  /     /   \\ \\-/-|  |  |  |  |\n\
 ||   ||  \\----/     \\---/   |--|  |--|\n\
  _____\n\
 |__ __|  |-| |-|  |--\\    /--|  |---\\\n\
   | |    | | | |  | \\ \\  / / |  | () |\n\
  _| |    | | | |  | |\\ \\/ /| |  | __/\n\
 | | |    | \\_/ |  | | \\__/ | |  | |\n\
 \\___/     \\___/   |_|      |_|  |_|\n");
		consoleSelect(&screen);
		consoleClear();
		printf("\n\n\n\n\n\n\n\n\n\n     /|%s|\\\n\
	 / |                                   | \\\n\
   /  |    __________________________     |  \\\n\
  /   |   |%s|%d%%  |   \\\n\
 |    |    __________________________     |    |\n\
  \\   |   |%s|%d%%  |   /\n\
   \\  |   ______________________________  |  /\n\
    \\ |  |             Go!              | | /\n\
	  \\|  |______________________________| |/\n", levtext, nmtext, nmscore[leveln], pmtext, pmscore[leveln]);
		//printf("Press start now to exit.\n");
		hidScanInput();
		u32 kDown = hidKeysDown();
		bool cont = true;
		do {
    		hidScanInput();
			kDown = hidKeysDown();
			if (kDown) {
				if (KEY_START) goto End;
				else if (KEY_LEFT) {incIntWithMax(leveln, maxlev); cont = false;}
				else if (KEY_RIGHT) {decIntWithMax(leveln, maxlev); cont = false;}
				else if (KEY_A) {runLevel(leveln); cont = false;}
			}
		} while (cont);
	}
	End:
	debugPrint("Exiting...");
	csndExit();
	gfxExit();
	sleep(0.5);
	return 0;
}