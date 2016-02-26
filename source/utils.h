#include <cstdio>
#include <cstring>
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
//#define __LUA_SOUND_ // is currently unsafe
#define __DEBUG

void debugPrint(const char * debugText);
#ifndef __LUA_SOUND_
#include "sound.h"
bool audioIsActive = true;
bool audio_load(const char *audio, themeSound * aThemeSound){
	if (!audioIsActive) debugPrint("Audio is disabled.");
	FILE *file = fopen(audio, "rb");
	if(file != NULL && audioIsActive){
		fseek(file, 0, SEEK_END);
		aThemeSound->sndsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		aThemeSound->sndsize = aThemeSound->sndsize - 0x48;
		fseek(file, 0x48, SEEK_SET);
		aThemeSound->sndbuffer = (u8*)linearAlloc(aThemeSound->sndsize);
		fread(aThemeSound->sndbuffer, 1, aThemeSound->sndsize, file);
		fclose(file);
		if (aThemeSound->sndbuffer != NULL) {
            aThemeSound->loaded = true;
		}
		else {
            aThemeSound->loaded = false;
		}
	}
	else {
        aThemeSound->loaded = false;
	}

	if (aThemeSound->loaded) {
        aThemeSound->duration = aThemeSound->sndsize / 88244;
	}
	else {
        aThemeSound->duration = 0;
	}
	return aThemeSound->loaded;
}

void audio_play(themeSound * aThemeSound, bool loop) {
if (!audioIsActive) debugPrint("Audio is disabled.");
   if (aThemeSound->loaded && audioIsActive) {
    u32 flags;

    if (loop) {
        flags = SOUND_FORMAT_16BIT | SOUND_REPEAT;
    }
    else {
        flags = SOUND_FORMAT_16BIT;
    }

    csndPlaySound(aThemeSound->channel, flags, 44100, 1, 0, aThemeSound->sndbuffer, aThemeSound->sndbuffer, aThemeSound->sndsize);
   }
}

void audio_free(themeSound * aThemeSound) {
if (!audioIsActive) debugPrint("Audio is disabled.");
    if (audioIsActive) {
        memset(aThemeSound->sndbuffer, 0, aThemeSound->sndsize);
        GSPGPU_FlushDataCache(aThemeSound->sndbuffer, aThemeSound->sndsize);
        linearFree(aThemeSound->sndbuffer);
    }
}

void audio_stop(void){
if (!audioIsActive) debugPrint("Audio is disabled.");
    if (audioIsActive) {
        csndExecCmds(true);

        CSND_SetPlayState(0x8, 0);
        CSND_SetPlayState(0x9, 0);
        CSND_SetPlayState(0x10, 0);

        csndExecCmds(true);

        csndExecCmds(true);
    }
}
#else
#include "luaSound.hpp"
#endif
PrintConsole screen, debug;
std::string scorefile[8];
std::string buffer = "";
std::tuple<const char *, int> levnames[4] = {std::make_pair("First Level", 11), std::make_pair("Second Level", 12), std::make_pair("Another Level", 13), std::make_pair("Goo Lagoon", 10)};
int leveln = 0;
int maxlev = 3;
u8 consoletype;
#ifndef __LUA_SOUND_
themeSound sound1;
themeSound sound2; // backup just in case its needed
#endif

void debugPrint(const char * debugText) {
	#ifdef __DEBUG
		consoleSelect(&debug);
		printf("%s\n", debugText);
		consoleSelect(&screen);
	#endif
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

inline bool fexists (const std::string& name) {
  return ( access( name.c_str(), F_OK ) != -1 );
}