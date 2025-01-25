#ifndef DERIVATIVES_UTILITIES_H
#define DERIVATIVES_UTILITIES_H

#include <sstream>
#include <iomanip>

using namespace std;

class NumberUtils {
private:
    static std::stringstream ss;
    static int globalPrecision;
    static double globalEpsilon;
    static void clearSS();
public:
    NumberUtils();
    static string toString(double d);
    static string toString(int d);
    static void setGlobalPrecision(int precision);
    static void setGlobalEpsilon(double epsilon);
    static bool doubleEquals(double a, double b);
};

#endif //DERIVATIVES_UTILITIES_H
