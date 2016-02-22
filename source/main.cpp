//
//  main.cpp
//  ASCIIJump3DS
//
//  Created by Jack Bruienne on 2/19/16.
//  Copyright © 2016 MCJack123. All rights reserved.
//

#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <tuple>
#include <sys/unistd.h>
#ifndef _SYS_UNISTD_H_
#include <unistd.h>
#endif
#include "3DSTerm.hpp"

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
bool debugMode = false;
int leveln = 1;
	char * levtext = (char*)malloc(40);
	char * pmtext = (char*)malloc(30);
	char * nmtext = (char*)malloc(30);

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

template <class T>
int numDigits(T number) {
    int digits = 0;
    if (number < 0) digits = 1; // remove this line if '-' counts as a digit (negatives will not be handled in this program)
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}
template <class U>
void sleep(U time) {usleep(time * 1000000);}

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
	if (debugMode) printf("\nDebug mode is on");
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
	    scorefile[i] = buffer;
		std::getline(in, buffer);
		consoleSelect(&debug);
		if (debugMode) printf("%d\n", i);
		consoleSelect(&screen);
		i++;
	}
	while (!(in.bad() || in.eof()));
	scorefile[i] = buffer;
	std::getline(in, buffer);
	in.close();
	i = 0;
	debugPrint("The scores.txt file:");
	for (std::string score : scorefile) {
		if (score == "" || score.c_str() == nullptr) break;
		nmscore[i] = atoi(scorefile[i+1].substr(0, scorefile[i+1].find("|") - 1).c_str());
		pmscore[i] = atoi(scorefile[i+1].substr(scorefile[i+1].find("|") + 1).c_str());
		consoleSelect(&debug);
		if (debugMode) printf("%d: %s\n", i, score.c_str());
		i++;
	}
		consoleClear();
		consoleSelect(&console);
		consoleClear();
	sleep(2);
	debugPrint("Starting program...");
	while (aptMainLoop()) {
		//The menu
		sprintf(levtext, "%d: %s", leveln, std::get<0>(levnames[leveln]));
		debugPrint("Creating level name text...");
		for (int j = 0, k = (36 - std::get<1>(levnames[leveln]) - 3) / 2, l = (36 - std::get<1>(levnames[leveln]) - 3) % 2; j <= k; j++) {
			if (l == 1 && j < k) {sprintf(levtext, "  %s ", levtext); break;}
			else sprintf(levtext, " %s ", levtext);
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
		fflush(stdout);
		consoleSelect(&console);
		consoleClear();
		sleep(1);
		int errnom = printf("\n\n\n\n\n\n\n\n\n\n     /|%s|\\\n\
	/ |                                    | \\\n\
   /  |    _________________________       |  \\\n\
  /   |   |%s| %d%%   |   \\\n\
 |    |    _________________________       |    |\n\
  \\   |   |%s| %d%%  |   /\n\
   \\  |   ______________________________   |  /\n\
    \\ |  |             Go!              |  | /\n\
	 \\|  |______________________________|  |/\n", levtext, nmtext, nmscore[leveln], pmtext, pmscore[leveln]);
		fflush(stdout);
		if (consoleSelect(&debug) == &debug) {debugPrint("It printed to debug!"); consoleSelect(&debug); sleep(3);}
		printf("%d\n", errnom);
		printf("Press start now to exit.\n");
		hidScanInput();
		u32 kDown = hidKeysDown();
		bool cont = true;
		do {
    		hidScanInput();
			kDown = hidKeysDown();
			if (kDown & KEY_START) cont=false;
		} while (cont);
		break;
	}
	debugPrint("Exiting...");
	csndExit();
	gfxExit();
	sleep(0.5);
	return 0;
}