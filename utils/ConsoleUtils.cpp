
#include <wincon.h>
#include "ConsoleUtils.h"

WORD ConsoleUtils::defaultColors;
ConsoleUtils CONSOLE_UTILS_INITIALIZER;

ConsoleUtils::ConsoleUtils() {
    defaultColors = getBufferInfo().wAttributes;
}

CONSOLE_SCREEN_BUFFER_INFO ConsoleUtils::getBufferInfo() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        GetConsoleScreenBufferInfo(hOut, &bufferInfo);
        return bufferInfo;
}

short ConsoleUtils::getConsoleColors() {
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo = getBufferInfo();
    return bufferInfo.wAttributes;
}

short ConsoleUtils::getConsoleFrontColor() {
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo = getBufferInfo();
    unsigned short color = bufferInfo.wAttributes << 12;
    return color >> 12;
}

short ConsoleUtils::getConsoleBackColor() {
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo = getBufferInfo();
    return bufferInfo.wAttributes >> 4;
}

void ConsoleUtils::setConsoleFrontColor(short color) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    unsigned short mask = 0xfff0 & getConsoleColors();
    mask = mask ^ color;
    SetConsoleTextAttribute(hOut, mask);
}

void ConsoleUtils::setConsoleBackColor(short color) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    unsigned short mask = 0xff0f & getConsoleColors();
    mask = mask ^ (color << 4);
    SetConsoleTextAttribute(hOut, mask);
}

void ConsoleUtils::resetConsoleColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, defaultColors);
}

void ConsoleUtils::resetFrontColor() {
    unsigned short color = defaultColors << 12 >> 12;
    setConsoleFrontColor(color);
}

void ConsoleUtils::resetBackColor() {
    unsigned short color = defaultColors >> 4;
    setConsoleBackColor(color);
}
