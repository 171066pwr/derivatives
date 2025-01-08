#include "BaseEntity.h"

BaseEntity::BaseEntity() {
}

BaseEntity::~BaseEntity() {
}

std::string BaseEntity::toString() {
    string result = "(";
    for(auto element: elements) {
        result += element->toString() + " ";
    }
    result += ")";
    return result;
}

bool BaseEntity::addElement(BaseEntity * element) {
    elements.push_back(element);
    return true;
}

void BaseEntity::evaluateFunction() {
    for(auto element: elements) {
        element->evaluateFunction();
    }
}

/* It will return new object with all the variables replaced by their values. Variables of unknown value will remain.
 * Later it might be better to pass map of known variables (symbol-value pair) and VariableEntities could replace them based on this map.
 * Right now all know constants have to be coded in VariableEntity, which is also pretty handy solution, just not the best place for dictionary of constants.
*/
BaseEntity* BaseEntity::evaluateValue(double x) {
    BaseEntity * evaluated = new BaseEntity();
    for(auto element: elements) {
        evaluated -> addElement(element->evaluateValue(x));
    }
    //re-evaluate afterwards to group result
    evaluated -> evaluateFunction();
    return evaluated;
}

//It will return new object
BaseEntity* BaseEntity::evaluateDerivative() {
    //Have to allocate on the heap (global storage) with new operator. Without that it would be only allocated locally on stack
    //And it would be lost when closing this function and stack frame; The space would be probably re-allocated to new frames.
    //Just remember that objects allocated globally have to be deleted manually!
    BaseEntity * derivative = new BaseEntity();
    for(auto element: elements) {
        derivative -> addElement(element->evaluateDerivative());
    }
    //re-evaluate after derivative
    derivative -> evaluateFunction();
    return derivative;
}
