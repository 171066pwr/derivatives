#include "SumEntity.h"

std::string SumEntity::toString() {
    string result = "(";
    for(auto element: elements) {
        result += element -> toString();
        if(element != elements.back())
            result += " + ";
    }
    result += ")";
    return result;
}

bool SumEntity::addElement(BaseEntity * element) {
    if(!BaseEntity::addElement(element)){
        Logger::log("Failed to add element: " + element -> toString());
        return false;
    }
    return true;
}

bool SumEntity::addElements(std::initializer_list<BaseEntity*> list) {
    for(BaseEntity * entity: list) {
        if(!addElement(entity))
            return false;
    }
    return true;
}

BaseEntity* SumEntity::evaluateFunction() {
    return BaseEntity::evaluateFunction();
}

BaseEntity* SumEntity::evaluateValue(double x) {
    BaseEntity* evaluated = new SumEntity();
    BaseEntity::evaluateValue(x, evaluated);

    return evaluated;
}
