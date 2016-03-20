//
//  main.cpp
//  ASCIIJump3DS
//
//  Created by Jack Bruienne on 2/19/16.
//  Copyright © 2016 MCJack123. All rights reserved.
//

#ifndef __ASCII3DS_UTILS_H_
#include "utils.h"
#endif
#include "level.h"

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
// 3DS Top Screen Dimensions:
//     Width: 400 pixels / 50 chars (8px char width)
//	  Height: 240 pixels / 30 chars (8px char height)
// 3DS Bottom Screen Dimensions:
//     Width: 320 pixels / 40 chars (8px char width)
//    Height: 240 pixels / 30 chars (8px char height)

int main() {
	gfxInitDefault();
	consoleInit(GFX_TOP, &screen);
	consoleInit(GFX_BOTTOM, &debug);
	consoleSelect(&screen);
	csndInit();
	APT_CheckNew3DS(&consoletype);
	//Loading screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n               Console Type: %s\n                ASCIIJump for 3DS", consoletype ? "New3DS" : "Old3DS");
	//hidScanInput();
	//u32 dDown = hidKeysDown();
	//u32 dHeld = hidKeysHeld();
	#ifdef __DEBUG
	printf("\n                 Debug mode is on");
	#endif
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
	// Load the scores from scores.txt
	debugPrint("Reading scores from sdmc://3ds/ASCIIJump3DS/data/scores.txt (yes, it is easy to hack the scores now)");
	std::ifstream in;
	if (!dirExists("data/")) printf("You are missing the data folder. Please put a folder named 'data' next to the executable, and put a 'scores.txt' file in with random scores.");
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
	if (fexists("data/background_loop.bin")) {
		#ifndef __LUA_SOUND_
		if (!audio_load("/3ds/ASCIIJump3DS/data/background_loop.bin", &sound1)) {debugPrint("The song was unable to load."); sleep(3); goto End;}
		#endif
	} else {debugPrint("File doesn't exist!"); sleep(3); goto End;}
	levelInit();
		consoleClear();
		consoleSelect(&screen);
		consoleClear();
	debugPrint("Starting program...");
	while (aptMainLoop()) {
	#ifndef __LUA_SOUND_
		audio_stop();
		audio_play(&sound1, true);
		//#else
		//void *wav = (void*)"/3ds/ASCIIJump3DS/data/background_loop.wav";
		//streamWAV_CSND(wav);
		#endif
		//The menu
		char * levtext = (char*)malloc(40);
		char * levtextt = (char*)malloc(40);
		char * pmtext = (char*)malloc(30);
		char * nmtext = (char*)malloc(30);
		sprintf(levtext, "%d: %s", leveln + 1, std::get<0>(levnames[leveln]));
		debugPrint(levtext);
		debugPrint("Creating level name text...");
		for (int j = 0, k = (36 - std::get<1>(levnames[leveln]) - 3) / 2, l = (36 - std::get<1>(levnames[leveln]) - 3) % 2; j <= k - 1; j++) {
			if (l == 1 && j > 94) {sprintf(levtextt, " %s ", levtext); levtext = levtextt; break;}
			else sprintf(levtextt, " %s ", levtext);
			levtext = levtextt;
			consoleSelect(&debug);
			#ifdef __DEBUG
			printf(".");
			#endif
			consoleSelect(&screen);
		}
		debugPrint("\nCreating practice mode bar text...");
		for (int i = 0; i <= 100; i += 4) {
			if (i <= pmscore[leveln]) sprintf(pmtext, "%s|", pmtext);
			else sprintf(pmtext, "%s_", pmtext);
			consoleSelect(&debug);
			#ifdef __DEBUG 
			printf(".");
			#endif
			consoleSelect(&screen);
		}
		debugPrint("\nCreating normal mode bar text...");
		for (int i = 0; i <= 100; i += 4) {
			if (i <= nmscore[leveln]) sprintf(nmtext, "%s|", nmtext);
			else sprintf(nmtext, "%s_", nmtext);
			consoleSelect(&debug);
			#ifdef __DEBUG 
			printf(".");
			#endif
		}
		#ifdef __DEBUG 
		printf(levtext);
		#endif
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
  /   |   |%s|%d%% |   \\\n\
 |    |    __________________________     |    |\n\
  \\   |   |%s|%d%% |   /\n\
   \\  |   ______________________________  |  /\n\
    \\ |  |             Go!              | | /\n\
	  \\|  |______________________________| |/\n", levtext, nmtext, nmscore[leveln], pmtext, pmscore[leveln]);
		//printf("Press start now to exit.\n");
		hidScanInput();
		u32 kDown = hidKeysDown();
		bool cont = false;
		do {
    		hidScanInput();
			kDown = hidKeysDown();
			if (kDown) {
				if (kDown & KEY_START) goto End;
				else if (kDown & KEY_RIGHT) {incIntWithMax(leveln, maxlev); break;}
				else if (kDown & KEY_LEFT) {decIntWithMax(leveln, maxlev); break;}
				else if (kDown & KEY_R) {incIntWithMax(leveln, maxlev); break;}
				else if (kDown & KEY_L) {decIntWithMax(leveln, maxlev); break;}
				else if (kDown & KEY_A) {consoleClear(); printf("\n\n\n\n\n\n\n\n\n\n     /|%s|\\\n\
	 / |                                   | \\\n\
   /  |    __________________________     |  \\\n\
  /   |   |%s|%d%% |   \\\n\
 |    |    __________________________     |    |\n\
  \\   |   |%s|%d%% |   /\n\
   \\  |   ______________________________  |  /\n\
    \\ |  ||||||||||||||Go!||||||||||||||| | /\n\
	  \\|  |______________________________| |/\n", levtext, nmtext, nmscore[leveln], pmtext, pmscore[leveln]); cont = true; break;}
			}
		} while (true);
		if (cont) runLevel(leveln);
	}
	End:
	debugPrint("Exiting...");
	#ifndef __LUA_SOUND_
	audio_free(&sound1);
	#endif
	csndExit();
	gfxExit();
	sleep(0.5);
	return 0;
}