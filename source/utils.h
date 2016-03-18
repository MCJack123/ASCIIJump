#ifndef __ASCII3DS_UTILS_H_
#define __ASCII3DS_UTILS_H_
#endif
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
//#define __DEBUG // will enable debugPrint() --v--

void debugPrint(const char * debugText); // this function
#ifndef __LUA_SOUND_
#include "sound.h"
#else
#include "luaSound.hpp"
#endif
PrintConsole screen, debug;
std::string scorefile[8];
std::string buffer = "";
std::tuple<const char *, int> levnames[4] = {std::make_pair("First Level", 11), std::make_pair("Second Level", 12), std::make_pair("Another Level", 13), std::make_pair("Goo Lagoon", 10)};
int leveln = 0;
int maxlev = 3;
int nmscore[4];
int pmscore[4];
u8 consoletype;
#ifndef __LUA_SOUND_
themeSound sound1;
themeSound sound2; // backup just in case its needed
#endif

void debugPrint(const char * debugText) { // here
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

void clearAll() {
	consoleSelect(&debug);
	consoleClear();
	consoleSelect(&screen);
	consoleClear();
}