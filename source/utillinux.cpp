#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include "util.h"
#include "base64.h"

void initialize() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void exit() {
    endscr();
}

rect getScreenDimensions() {
    rect retval;
    retval.width = COLUMNS;
    retval.height = LINES;
    return retval;
}

void print(std::string text) {
    waddstr(stdscr, text.c_str());
    wrefresh(stdscr);
}

void printScreen(std::vector<std::vector<Block> > blockmap, char[4][4] icon) {
    move(0, 0);
    wrefresh(stdscr);
    std::vector<std::vector<char> > screen;
    for (int x = 0; x < COLUMNS; x++) for (int y = 0; y < LINES; y++) mvwaddch(stdscr, y, x, blockmap[x/4][y/4].block[x%4][y%4]);
    for (int x = 5; x < 9; x++) for (int y = LINES - 4; y < LINES; y++) mvwaddch(stdscr, y, x, icon[x-5][y-LINES+4]);
}

void moveCursor(int x, int y) {
    move(y, x);
    wrefresh(stdscr);
}

keypress getkey() {
    int ch = getch();
    if (ch == KEY_UP) return KEY_PRESSED_UP;
    else if (ch == KEY_DOWN) return KEY_PRESSED_DOWN;
    else if (ch == KEY_LEFT) return KEY_PRESSED_LEFT;
    else if (ch == KEY_RIGHT) return KEY_PRESSED_RIGHT;
    else if (ch == KEY_ENTER) return KEY_PRESSED_SELECT;
    else if (ch == KEY_BACKSPACE) return KEY_EDIT_DELETE;
    else if (ch == ' ') return KEY_PRESSED_JUMP;
    else if (ch == 27) return KEY_PRESSED_BACK;
    else if (ch == 'c') return KEY_PRESSED_ICONCHANGE;
    else if (ch == 'e') return KEY_EDIT_LEVEL;
    else if (ch == 9) return KEY_EDIT_CHANGE;
    else return KEY_PRESSED_NONE;
}

void playAudio(audio buf) {
    //need to find audio library
}

void stopAudio() {
    //need to find audio library
}

std::string readFile(std::string file) {
    std::ifstream in;
    in.open(file.c_str());
    std::string retval, line;
    while (std::getline(in, line)) retval += line + "\n";
    in.close();
    return retval;
}

void writeFile(std::string file, std::string text) {
    std::ofstream out;
    out.open(file.c_str());
    out << text;
    out.close();
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
