#ifndef DERIVATIVES_LOGGER_H
#define DERIVATIVES_LOGGER_H

#include <iostream>
#include "ConsoleUtils.h"

using namespace std;

class Logger {
private:

public:
    static inline void log(string s) {
        cout << s << endl;
    }

    static void logWithColor(string s, short color = 0) {
        ConsoleUtils::setConsoleFrontColor(color);
        log(s);
        ConsoleUtils::resetFrontColor();
    };

    static void warn(string s){
        logWithColor(s, 4);
    };

    static void important(string s){
        logWithColor(s, 6);
    };

    static void success(string s){
        logWithColor(s, 2);
    };
};

#endif //DERIVATIVES_LOGGER_H
