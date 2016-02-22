//
//  3DSTerm.hpp
//  3DSTerm
//
//  Created by Homework User on 1/21/16.
//
//  Core functionality for 3DSTerm and all applications.

#ifndef _DSTerm_h
#define _DSTerm_h


#endif /* _DSTerm_h */
#include <cstdlib>
#include <string>
#include <map>
#include <3ds.h>

PrintConsole console, keyboard;
bool flase = false; //failsafe
int caps = 0;   // 0 means lowercase, 1 means caps lock, 2 means shift
u8 consoletype;
void cls() {
    consoleSelect(&console);
    consoleClear();
}

void clk() {
    consoleSelect(&keyboard);
    consoleClear();
}

std::tuple<u32, u32, u32> dsIn() {
	hidScanInput();
	return std::make_tuple(hidKeysDown(), hidKeysHeld(), hidKeysUp());
}

bool isButtonPressed(char button, bool wait = true) {
	APT_CheckNew3DS(&consoletype);
	if (wait) hidWaitForEvent(HIDEVENT_PAD0, false);
	hidScanInput();
	u32 kDown = hidKeysDown();
	u32 kHeld = hidKeysHeld();
	u32 kUp = hidKeysUp();
	if (!kDown && kHeld) kDown = kHeld;
	if (kDown && KEY_A && button == 'a') return 0;
	else if (kDown && KEY_B && button == 'b') return 0;
	else if (kDown && KEY_X && button == 'x') return 0;
	else if (kDown && KEY_Y && button == 'y') return 0;
	else if (kDown && KEY_L && button == 'l') return 0;
	else if (kDown && KEY_R && button == 'r') return 0;
	else if (kDown && KEY_START && button == 't') return 0;
	else if (kDown && KEY_SELECT && button == 'e') return 0;
	else if (kDown && KEY_UP && button == 'u') return 0;
	else if (kDown && KEY_DOWN && button == 'd') return 0;
	else if (kDown && KEY_LEFT && button == 'q') return 0;
	else if (kDown && KEY_RIGHT && button == 'e') return 0;
	else if (consoletype) {
		if (kDown && KEY_ZR && button == 'c') return 0;
		else if (kDown && KEY_ZL && button == 'z') return 0;
	}
	return 1;
}

bool input(std::string text = "") {
	bool retval = false;
	printf(text.c_str());
	while (!isButtonPressed('a', false)) if (isButtonPressed('t', false)) retval = true;
	printf("\n");
	return retval;
}
std::map<int, char> char_low_2 = {
        {1, '`'},
        {4, '1'},
        {7, '2'},
        {9, '3'},
        {12, '4'},
        {15, '5'},
        {17, '6'},
        {20, '7'},
        {23, '8'},
        {25, '9'},
        {28, '0'},
        {31, '-'},
        {33, '='}};
std::map<int, char> char_low_4 = {
        {8, 'q'},
        {11, 'w'},
        {13, 'e'},
        {16, 'r'},
        {18, 't'},
        {21, 'y'},
        {24, 'u'},
        {27, 'i'},
        {30, 'o'},
        {32, 'p'},
        {35, '['},
        {37, ']'},
        {40, '\\'}};
std::map<int, char> char_low_6 = {
        {9, 'a'},
        {12, 's'},
        {15, 'd'},
        {17, 'f'},
        {20, 'g'},
        {23, 'h'},
        {25, 'j'},
        {28, 'k'},
        {31, 'l'},
        {33, ';'},
        {36, '\''}};
std::map<int, char> char_low_8 = {
        {9, 'z'},
        {12, 'x'},
        {15, 'c'},
        {17, 'v'},
        {20, 'b'},
        {23, 'n'},
        {25, 'm'},
        {28, ','},
        {31, '.'},
        {33, '/'}};
std::map<int, char> char_up_2 = {
        {1, '~'},
        {4, '!'},
        {7, '@'},
        {9, '#'},
        {12, '$'},
        {15, '%'},
        {17, '^'},
        {20, '&'},
        {23, '*'},
        {25, '('},
        {28, ')'},
        {31, '_'},
        {33, '+'}};
std::map<int, char> char_up_4 = {
        {8, 'Q'},
        {11, 'W'},
        {13, 'E'},
        {16, 'R'},
        {18, 'T'},
        {21, 'Y'},
        {24, 'U'},
        {27, 'I'},
        {30, 'O'},
        {32, 'P'},
        {35, '{'},
        {37, '}'},
        {40, '|'}};
std::map<int, char> char_up_6 = {
        {9, 'A'},
        {12, 'S'},
        {15, 'D'},
        {17, 'F'},
        {20, 'G'},
        {23, 'H'},
        {25, 'J'},
        {28, 'K'},
        {31, 'L'},
        {33, ':'},
        {36, '\"'}};
std::map<int, char> char_up_8 = {
        {9, 'Z'},
        {12, 'X'},
        {15, 'C'},
        {17, 'V'},
        {20, 'B'},
        {23, 'N'},
        {25, 'M'},
        {28, '<'},
        {31, '>'},
        {33, '?'}};
std::map<int, char> char_locs_nil = {
	{0, '0'}
};
std::string keyboardLow = "\
---------------------------------\n\
|`|1|2|3|4|5|6|7|8|9|0|-|=| del |\n\
|-------------------------------|\n\
|    |q|w|e|r|t|y|u|i|o|p|[|]|\\|\n\
|-------------------------------|\n\
|ocaps|a|s|d|f|g|h|j|k|l|;|\'|ret|\n\
|-------------------------------|\n\
|shift|z|x|c|v|b|n|m|,|.|/|shift|\n\
|-------------------------------|\n\
|             space             |\n\
---------------------------------";
std::string keyboardUp="\
---------------------------------\n\
|~|!|@|#|$|%|^|&|*|(|)|_|+| del |\n\
|-------------------------------|\n\
|     |Q|W|E|R|T|Y|U|I|O|P|{|}|||\n\
|-------------------------------|\n\
|Icaps|A|S|D|F|G|H|J|K|L|:|\"|ret|\n\
|-------------------------------|\n\
|shift|Z|X|C|V|B|N|M|<|>|?|shift|\n\
|-------------------------------|\
|             space             |\n\
---------------------------------";
bool intBetween(int number, int min, int max) {
    if (number >= min && number <= max) return true;
    else return false;
}
char getChar(int caps_stat) {
	hidScanInput();
    touchPosition touch;
	s16 keyX, keyY, touchX, touchY = 0;
	do {
	//printf("touchX: %d\tkeyX: %d\ttouchY: %d\tkeyY: %d\n", touchX, keyX, touchY, keyY);
	hidScanInput();
	hidTouchRead(&touch);
	touchX = touch.px;
	touchY = touch.py;
    keyX = touchX / 6;
    keyY = (touchY - 4) / 6;
                if (keyY == 2 && intBetween(keyX, 36, 42)) {/*printf("2"); usleep(1000000); printf("\b");*/ if (caps == 0) return 'E'; else return 'e';}
                else if (keyY == 6) {
					//printf("6"); usleep(1000000); printf("\b");
                    if (intBetween(keyX, 1, 7)) {caps = 1; return '\0';}
                    else if (intBetween(keyX, 38, 42)) {if (caps == 0) return '!'; else return '1';}
                }
                else if (keyY == 9) {
					//printf("9"); usleep(1000000); printf("\b");
                    if (intBetween(keyX, 1, 7) || intBetween(keyX, 36, 42)) {caps = 2; return '\0';}
                }
	//else if (kDown && KEY_X) {if (caps == 0) return 'B'; else return 'b';}
	//else if (kDown && KEY_START) {if (caps == 0) return 'D'; else return 'd';}
	} while (touchX == 0 && touchY == 0);
	//printf("touchX: %d\tkeyX: %d\ttouchY: %d\tkeyY: %d\n", touchX, keyX, touchY, keyY);
	std::map<int, char> char_locs_2, char_locs_4, char_locs_6, char_locs_8;
    if (caps_stat == 0) {char_locs_2 = char_low_2; char_locs_4 = char_low_4; char_locs_6 = char_low_6; char_locs_8 = char_low_8;}
    else {char_locs_2 = char_up_2; char_locs_4 = char_up_4; char_locs_6 = char_up_6; char_locs_8 = char_up_8;}
	char typedKey;
	bool invalid = flase;
    try {
		if (keyY == 2) typedKey = char_locs_2[keyX];
		else if (keyY == 4) typedKey = char_locs_4[keyX];
		else if (keyY == 6) typedKey = char_locs_6[keyX];
		else if (keyY == 9) typedKey = char_locs_8[keyX];
		else if (keyY == 12) typedKey = ' ';
		else typedKey = char_locs_nil[keyX];
	}
    catch (const std::out_of_range& oor) {
		//printf("Invalid key. keyX: %d\tkeyY: %d\n", keyX, keyY); invalid=true;
    }
		/*if (keyY == 2) {printf("2"); usleep(1000000); printf("\b");}
		else if (keyY == 4) {printf("4"); usleep(1000000); printf("\b");}
		else if (keyY == 6) {printf("6"); usleep(1000000); printf("\b");}
		else if (keyY == 9) {printf("9"); usleep(1000000); printf("\b");}*/
	
	/*if (!invalid) {printf("%c", typedKey);
	usleep(1000000);
	printf("\b");}*/
    if (caps_stat == 2) {
        caps = 0;
        clk();
        printf(keyboardLow.c_str());
        consoleSelect(&console);
    }
    if (caps == 1 && caps_stat == 0) {
        clk();
        printf(keyboardUp.c_str());
        consoleSelect(&console);
    }
    if (caps == 2) {
        clk();
        printf(keyboardUp.c_str());
        consoleSelect(&console);
    }
    return typedKey;
}

inline bool fexists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}