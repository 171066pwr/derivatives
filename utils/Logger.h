#ifndef DERIVATIVES_LOGGER_H
#define DERIVATIVES_LOGGER_H

#include <iostream>

using namespace std;

class Logger {
public:
    static void log(string s) {
        cout << s << endl;
    }
};

#endif //DERIVATIVES_LOGGER_H
