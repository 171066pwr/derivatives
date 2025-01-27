#include "NaN.h"
#include "../utils/Logger.h"

const string NaN::NOT_A_NUMBER = "NaN";

BaseEntity *NaN::copy() {
    return new NaN();
}

std::string NaN::toString() {
    return NOT_A_NUMBER;
}

bool NaN::addElement(BaseEntity *element) {
    Logger::log("Can't add to " + NOT_A_NUMBER);
}

BaseEntity *NaN::evaluateFunction() {
    return this;
}

BaseEntity *NaN::evaluateValue(double x) {
    return this;
}

bool NaN::updateAndGetIsFunction() {
    return true;
}
