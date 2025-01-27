#ifndef DERIVATIVES_LOGGER_H
#define DERIVATIVES_LOGGER_H

#include <iostream>

using namespace std;

class Logger {
public:
    static inline void log(string s) {
        cout << s << endl;
    }

    static void logWithColor(const string &s, const string &color) {
        string c = "\033[" + color + "m" + s + "\033[0m";
        log(c);
    };

    static void warn(const string& s){
        logWithColor(s, "31");
    };

    static void important(const string& s){
        logWithColor(s, "93");
    };

    static void success(const string& s){
        logWithColor(s, "92");
    };
};

#endif //DERIVATIVES_LOGGER_H
