#include "BaseEntity.h"
#include <algorithm>
#include "../utils/NumberUtils.h"
#include "Scalar.h"

BaseEntity::BaseEntity(double multiplier): multiplier(multiplier) {}

BaseEntity::BaseEntity(double multiplier, initializer_list<BaseEntity *> list): multiplier(multiplier) {
    addElements(list);
}

BaseEntity::~BaseEntity() {
    for(int i = elements.size()-1; i > 0 ;--i){
        deleteAndZero(elements[i]);
    }
}

BaseEntity *BaseEntity::copy() {
    BaseEntity *copy = new BaseEntity(multiplier);
    for(int i = 0; i < elements.size(); i++){
        copy->addElement(elements[i]->copy());
    }
    return copy;
}

bool BaseEntity::equals(const BaseEntity *entity) {
    bool result = NumberUtils::doubleEquals(multiplier, entity->multiplier);
    return result && contentsEquals(entity);
}

bool BaseEntity::equalsExceptMultiplier(const BaseEntity *entity) {
    return contentsEquals(entity);
}

//it requires sort or compare by maps so it can ignore order...
bool BaseEntity::contentsEquals(const BaseEntity *entity) {
    //map of contents and their count. I can't use pointers here, but then - how can I use overridden operators/equals?
    //std::map<BaseEntity, double>
    bool result = elements.size() == entity->elements.size();
    if(result)
        for(int i = 0; i < elements.size(); i++) {
            result = result && *elements[i] == *(entity->elements[i]);
        }
    return result;
}

std::string BaseEntity::toString() {
    string result = !NumberUtils::doubleEquals(multiplier, 1.0) ? NumberUtils::toString(this->multiplier) + "(" : "(";
    for(int i = 0; i < elements.size(); i++){
        result += elements[i]->toString() + " ";
    }
    result += ")";
    return result;
}

bool BaseEntity::addElement(BaseEntity * element) {
    elements.push_back(element);
    return true;
}

bool BaseEntity::addElements(std::initializer_list<BaseEntity *> list) {
    for (BaseEntity *entity: list) {
        if (!addElement(entity))
            return false;
    }
    return true;
}

BaseEntity * BaseEntity::evaluateFunction() {
    if (isZero())
        return Scalar::zero();

    if (elements.size() > 0) {
        BaseEntity *evaluated;
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
 * Right now all know constants have to be coded in Variable, which is also pretty handy solution, just not the best place for dictionary of constants.
 * Also - we are not freeing any memory here, because Evaluate Value explicitly creates new object, so we can evaluate for different SUBSTITUTE_SYMBOL-es.
 * For consistency I should probably also do it while evaluating isFunction, will think about it later.
*/
BaseEntity *BaseEntity::evaluateValue(double x) {
    return evaluateValue(x, "x");
}

BaseEntity * BaseEntity::evaluateValue(double x, string variable) {
    if (isZero())
        return Scalar::zero();
    return this;
}

void BaseEntity::evaluateElementsValue(double x, string variable, BaseEntity *entity) {
    for(int i = 0; i < elements.size(); i++)
        entity->addElement(elements[i]->evaluateValue(x, variable));
}

BaseEntity * BaseEntity::recursiveFunctionEvaluation() {
    BaseEntity *result = this->evaluateFunction();
    if (*this != *result)
        replace(result, result->recursiveFunctionEvaluation());
    return result;
}

BaseEntity *BaseEntity::evaluateDerivative(string variable) {
    if(!isFunction(variable))
        return Scalar::zero();
    return copy();
}

bool BaseEntity::isFunction(string symbol) {
    for(auto & element : elements) {
        if (element->isFunction(symbol))
            return true;
    }
    return false;
}

BaseEntity *BaseEntity::evaluateAndDelete(BaseEntity *entity) {
    BaseEntity* evaluated = entity->evaluateFunction();
    if(evaluated != entity)
        deleteAndZero(entity);
    return evaluated;
}

void BaseEntity::deleteElement(BaseEntity *element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    deleteAndZero(element);
}

void BaseEntity::replaceElement(BaseEntity *oldElement, BaseEntity *newElement) {
    std::replace(elements.begin(), elements.end(), oldElement, newElement);
    deleteAndZero(oldElement);
}
