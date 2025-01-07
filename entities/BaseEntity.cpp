#include "BaseEntity.h"

BaseEntity::BaseEntity() {
}

BaseEntity::~BaseEntity() {
}

std::string BaseEntity::toString() {
    string result = "(";
    for(auto element: elements) {
        result += element->toString();
    }
    result += ")";
    return result;
}

bool BaseEntity::addElement(BaseEntity * element) {
    elements.push_back(element);
    return true;
}
