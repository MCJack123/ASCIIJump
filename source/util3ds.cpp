#include <3ds.h>
#include <cstdio>
#include "base64.h"
#include "util.h"

PrintConsole screen, debug;

void initialize(int argc, const char * argv[]) {
    gfxInitDefault();
    consoleInit(GFX_TOP, &screen);
    consoleInit(GFX_BOTTOM, &debug);
    consoleSelect(&screen);
    csndInit();
    fsInit();
}

void exit() {
    fsExit();
    csndExit();
    gfxExit();
}

rect getScreenDimensions() {
    rect retval;
    retval.width = screen.consoleWidth;
    retval.height = screen.consoleHeight;
    return retval;
}

void print(std::string text) {
    printf("%s\n", text.c_str());
}

void debugPrint(std::string text) {
    if (debugEnabled) {
        consoleSelect(&debug);
        printf("%s\n", text);
        consoleSelect(&screen);
    }
}

void printScreen(std::vector<std::vector<Block> > blockmap, char[4][4] icon) {
    moveCursor(0, 0);
    std::vector<std::vector<char> > screen;
    for (int x = 0; x < COLUMNS; x++) for (int y = 0; y < LINES; y++) printf("%s%c", CONSOLE_ESC(std::string(std::string(y) + ";" + std::string(x) + "H").c_str()), blockmap[x/4][y/4].block[x%4][y%4]);
    for (int x = 5; x < 9; x++) for (int y = LINES - 4; y < LINES; y++) printf("%s%c", CONSOLE_ESC(std::string(std::string(y) + ";" + std::string(x) + "H").c_str()), icon[x-5][y-LINES+4]);
}

void moveCursor(int x, int y) {
    printf(CONSOLE_ESC(std::string(std::string(y) + ";" + std::string(x) + "H").c_str()));
}

void clearScreen() {
    consoleClear();
}

keypress getKey() {
    hidScanInput();
    u32 kDown = hidKeysDown() | hidKeysHeld();
    if (kDown & KEY_A) return KEY_PRESSED_JUMP;
    else if (kDown & KEY_B) return KEY_PRESSED_BACK;
    else if (kDown & KEY_X) return KEY_PRESSED_ICONCHANGE;
    else if (kDown & KEY_Y) return KEY_EDIT_LEVEL;
    else if (kDown & KEY_UP) return KEY_PRESSED_UP;
    else if (kDown & KEY_DOWN) return KEY_PRESSED_DOWN;
    else if (kDown & KEY_LEFT) return KEY_PRESSED_LEFT;
    else if (kDown & KEY_RIGHT) return KEY_PRESSED_RIGHT;
    else if (kDown & KEY_SELECT) return KEY_PRESSED_SELECT;
    else if (kDown & KEY_L) return KEY_EDIT_DELETE;
    else if (kDown & KEY_R) return KEY_EDIT_CHANGE;
    else return KEY_PRESSED_NONE;
}

void playAudio(audio buf) {
    CSND_SetPlayState(0x8, 0);
    csndPlaySound(0x8, SOUND_ONE_SHOT | SOUND_FORMAT_16BIT, 44100, 1.0, 0.0, buf.data, NULL, buf.len);
}

void stopAudio() {
    CSND_SetPlayState(0x8, 0);
}

std::string readFile(std::string file) {
    char buf[1024];
    FILE *fp;
    std::string out;
    
    fp = fopen(file.c_str(), "r");
    if (fp) {
        while (fread(buf, 1, sizeof buf, fp) > 0)
            out += std::string(buf);
        if (ferror(fp)) {
            return "";
        }
        fclose(fp);
    }
    return out;
}

void writeFile(std::string file, std::string text) {
    FILE *fp;
    fp = fopen(file.c_str(), "w");
    fprintf(fp, text.c_str());
    fclose(fp);
}

Level unserializeLevel(Json::Value level) {
    Level retval;
    retval.name = level["name"].stringValue();
    retval.normalCompletion = level["normalCompletion"].floatValue();
    retval.practiceCompletion = level["practiceCompletion"].floatValue();
    retval.levelid = level["levelid"].intValue();
    retval.description = level["description"].stringValue();
    for (int x = 0; x < level["level"].size(); x++) {
        retval.level[x] = std::vector<Block>();
        for (int y = 0; y < level["level"][x].size(); y++) {
            char block[4][4];
            Json::Value bv = level["level"][x][y];
            for (int z = 0; z < 4; z++) block[z] = bv["block"][z].stringValue();
            retval.level[x][y] = Block(bv["symbol"].stringValue()[0], block, bv["clear"].boolValue(), bv["harmful"].boolValue(), bv["system"].intValue());
        }
    }
    std::string audio_b64 = base64_decode(*const_cast<std::string const>(level["song"].stringValue()));
    retval.song.data = &audio_b64[0];
    retval.song.len = audio_b64.length();
    return retval;
}

Json::Value serializeLevel(Level level) {
    Json::Value retval(objectValue);
    retval["name"] = Json::Value(level.name);
    retval["normalCompletion"] = Json::Value(level.normalCompletion);
    retval["practiceCompletion"] = Json::Value(level.practiceCompletion);
    retval["levelid"] = Json::Value(level.levelid);
    retval["description"] = Json::Value(level.description);
    retval["level"] = Json::Value(arrayValue);
    for (int x = 0; x < level.level.size(); x++) {
        retval["level"][x] = Json::Value(arrayValue);
        for (int y = 0; y < level["level"][x].size(); y++) {
            Json::Value block(objectValue);
            Block bv = level.level[x][y];
            block["block"] = Json::Value(arrayValue);
            for (int z = 0; z < 4; z++) block["block"][z] = Json::Value(bv.block[z]);
            block["symbol"] = Json::Value(std::string(bv.symbol));
            block["clear"] = Json::Value(bv.clear);
            block["harmful"] = Json::Value(bv.harmful);
            block["system"] = Json::Value(bv.system);
            retval["level"][x][y] = block;
        }
    }
    retval["song"] = Json::Value(base64_encode(const_cast<const unsigned char *>((unsigned char *)retval.song.data), retval.song.len));
    return retval;
}
