#include "BaseEntity.h"

#include "../utils/StringUtils.h"

BaseEntity::BaseEntity(double multiplier): multiplier(multiplier) {}

BaseEntity::BaseEntity(double multiplier, initializer_list<BaseEntity *> list): multiplier(multiplier) {
    addElements(list);
}

BaseEntity::~BaseEntity() {}

BaseEntity *BaseEntity::copy() {
    BaseEntity* copy = new BaseEntity(multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool BaseEntity::equals(const BaseEntity* entity) {
    bool result = multiplier == entity->multiplier;
    result = result && elements.size() == entity->elements.size();
    if(result)
        for(int i = 0; i < elements.size(); i++) {
            result = result && *elements[i] == *(entity->elements[i]);
        }
    return result;
}

std::string BaseEntity::toString() {
    string result = multiplier != 1 ? StringUtils::toString(this->multiplier) + "(" : "(";
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

bool BaseEntity::addElements(std::initializer_list<BaseEntity*> list) {
    for (BaseEntity *entity: list) {
        if (!addElement(entity))
            return false;
    }
    return true;
}

BaseEntity*  BaseEntity::evaluateFunction() {
    if (elements.size() > 0) {
        BaseEntity* evaluated;
        for(int i = 0; i < elements.size(); i++) {
            evaluated = elements[i]->evaluateFunction();
            //if evaluation returned a new object we are freeing memory of old object before losing reference to it, is that correct?
            //okay, I don't know how to do it without breaking the program, probably because in tests I didn't create them with new operator.
            //Now it works, just debugger crashes upon vector inspection - known bug, not fixed for 5 years.
            if(evaluated != elements[i]) {
                delete elements[i];
                elements[i] = evaluated;
            }
        }
    }
    return this;
}

/* It will return new object with all the variables replaced by their values. Variables of unknown value will remain.
 * Later it might be better to pass map of known variables (symbol-value pair) and VariableEntities could replace them based on this map.
 * Right now all know constants have to be coded in VariableEntity, which is also pretty handy solution, just not the best place for dictionary of constants.
 * Also - we are not freeing any memory here, because Evaluate Value explicitly creates new object, so we can evaluate for different X-es.
 * For consistency I should probably also do it while evaluating function, will think about it later.
*/
BaseEntity* BaseEntity::evaluateValue(double x) {
    BaseEntity* evaluated = new BaseEntity(multiplier);
    evaluateElementsValue(x, evaluated);
    return evaluated;
}

void BaseEntity::evaluateElementsValue(double x, BaseEntity *entity) {
    for(auto element: elements) {
        entity->addElement(element->evaluateValue(x));
    }
    entity->evaluateFunction();
}

//It will return new object
BaseEntity* BaseEntity::evaluateDerivative() {
    //Have to allocate on the heap (global storage) with new operator. Without that it would be only allocated locally on stack
    //And it would be lost when closing this function and stack frame; The space would be probably re-allocated to new frames.
    //Just remember that objects allocated globally have to be deleted manually!
    BaseEntity* derivative = new BaseEntity();
    for(auto element: elements) {
        derivative->addElement(element->evaluateDerivative());
    }
    //re-evaluate after derivative
    derivative->evaluateFunction();
    return derivative;
}
