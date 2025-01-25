#ifndef TESTS_CONSOLEUTILS_H
#define TESTS_CONSOLEUTILS_H

#include <wincon.h>
#include "stdlib.h"

using namespace std;

class ConsoleUtils {
private:
    static WORD defaultColors;
    static CONSOLE_SCREEN_BUFFER_INFO getBufferInfo();
public:
    ConsoleUtils();

    static short getConsoleColors();
    static short getConsoleFrontColor();
    static short getConsoleBackColor();
    static void setConsoleFrontColor(short color);
    static void setConsoleBackColor(short color);
    static void resetConsoleColors();
    static void resetFrontColor();
    static void resetBackColor();
};

#endif //TESTS_CONSOLEUTILS_H
