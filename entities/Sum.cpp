#include <algorithm>
#include "Sum.h"
#include <map>
#include "Variable.h"
#include "Multiplication.h"

BaseEntity *Sum::copy() {
    BaseEntity *copy = new Sum(multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool Sum::equals(const BaseEntity *entity) {
    //If the new type to be casted to is a pointer the result is a nullptr on error. If it is a reference it throws an exception.
    //So we have to cast pointers or catch bad_cast
    return typeEquals<Sum>(entity) && BaseEntity::equals(entity);
}

std::string Sum::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = (NumberUtils::doubleEquals(multiplier, 1.0) ?
                     "" :  NumberUtils::doubleEquals(multiplier, -1.0) ?
                           "-" : NumberUtils::toString(multiplier)) + "(";
    for(int i = 0; i < elements.size(); i++) {
        result += elements[i]->toString();
        if(elements[i] != elements.back())
            result += (elements[i+1]->getMultiplier() >= 0) ? " + " : " ";
    }
    result += ")";
    return result;
}

BaseEntity *Sum::evaluateFunction() {
    BaseEntity::evaluateFunction();
    mergeSums();
    mergeContents();
    mergeMultiplier();
    if (elements.size() == 0) {
        return new Scalar(0);
    }
    if (elements.size() == 1) {
        BaseEntity *element = elements[0];
        elements.clear();
        return element;
    }
    updateAndGetIsFunction();
    return this;
}

BaseEntity *Sum::evaluateValue(double x) {
    BaseEntity *evaluated = new Sum(this->multiplier);
    BaseEntity::evaluateElementsValue(x, evaluated);
    return evaluated->evaluateFunction();
}

bool Sum::updateAndGetIsFunction() {
    isFunction = false;
    return BaseEntity::updateAndGetIsFunction();
}

void Sum::mergeSums() {
    vector<BaseEntity *> toErase;
    vector<BaseEntity *> toInsert;
    for(vector<BaseEntity *>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        //if subelement is also sum, we can merge them.
        if(Sum *s = dynamic_cast<Sum *>(*iter)) {
            toInsert.insert(toInsert.end(), s->elements.begin(), s->elements.end());
            s->elements.clear();
            toErase.push_back(*iter);
        }
    }
    for (auto e: toErase) {
        deleteElement(e);
    }
    elements.insert(this->elements.end(), toInsert.begin(), toInsert.end());
}

void Sum::mergeContents() {
    for(int i = 0; i < elements.size() && elements.size() > 1; i++){
        bool updated = false;
        for(int j = i+1; j < elements.size(); j++) {
            if(elements[i]->equalsExceptMultiplier(elements[j])) {
                elements[i]->addToMultiplier(elements[j]->getMultiplier());
                deleteElement(elements[j]);
                updated = true;
                j--;
            }
        }
        if (updated) {
            evaluateAndReplaceElement(elements[i]);
            i--;
        }
    }
}

void Sum::mergeMultiplier() {
    if (NumberUtils::doubleEquals(multiplier, 0.0)) {
        for(int i = elements.size() -1; i >= 0; i--)
            deleteElement(elements[i]);
    } else if (!NumberUtils::doubleEquals(multiplier, 1.0)) {
        for (auto element: elements) {
            element->multiplyByScalar(multiplier);
        }
        multiplier = 1;
    }
}

void Sum::evaluateAndReplaceElement(BaseEntity *entity) {
    BaseEntity* evaluated = entity->evaluateFunction();
    if(evaluated != entity) {
        if(!NumberUtils::doubleEquals(evaluated->getMultiplier(), 0.0))
            std::replace(elements.begin(), elements.end(), entity, evaluated);
        deleteElement(entity);
    }
}
