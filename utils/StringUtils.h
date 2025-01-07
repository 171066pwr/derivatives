#ifndef DERIVATIVES_UTILITIES_H
#define DERIVATIVES_UTILITIES_H

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class StringUtils {
private:
    static std::stringstream ss;
    static int globalPrecision;
    static void clearSS();
public:
    StringUtils();
    static string toString(double d);
    static string toString(int d);
    static void setGlobalPrecision(int precision);
};

#endif //DERIVATIVES_UTILITIES_H
