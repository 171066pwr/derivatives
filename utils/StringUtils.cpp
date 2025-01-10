#include "StringUtils.h"

int StringUtils::globalPrecision;
std::stringstream StringUtils::ss;
StringUtils STRING_UTILS_INITIALIZER;

StringUtils::StringUtils() {
    setGlobalPrecision(7);
}

string StringUtils::toString(double d) {
    clearSS();
    ss << d;
    return ss.str();
}

string StringUtils::toString(int d) {
    clearSS();
    ss << d;
    return ss.str();
}

void StringUtils::clearSS() {
    ss.str(std::string());
}

void StringUtils::setGlobalPrecision(int precision) {
    globalPrecision = precision;
    ss << std::setprecision(globalPrecision);
}
