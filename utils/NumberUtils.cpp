#include "NumberUtils.h"
#include <cmath>

std::stringstream NumberUtils::ss;
int NumberUtils::globalPrecision;
double NumberUtils::globalEpsilon = 1e-14;
NumberUtils STRING_UTILS_INITIALIZER;

NumberUtils::NumberUtils() {
    setGlobalPrecision(7);
}

string NumberUtils::toString(double d) {
    clearSS();
    ss << d;
    return ss.str();
}

string NumberUtils::toString(int d) {
    clearSS();
    ss << d;
    return ss.str();
}

void NumberUtils::clearSS() {
    ss.str(std::string());
}

void NumberUtils::setGlobalPrecision(int precision) {
    globalPrecision = precision;
    ss << std::setprecision(globalPrecision);
}

void NumberUtils::setGlobalEpsilon(double epsilon) {
    globalEpsilon = epsilon;
}

bool NumberUtils::doubleEquals(double a, double b) {
    double maxOrOne = max(1.0, max(fabs(a), fabs(b)));
    return std::fabs(a - b) < globalEpsilon * maxOrOne;

}
