#include <algorithm>
#include "Sum.h"
#include "Variable.h"

BaseEntity *Sum::copy() {
    BaseEntity *copy = new Sum(multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool Sum::equals(const BaseEntity *entity) {
    return typeEquals<Sum>(entity) && BaseEntity::equals(entity);
}

bool Sum::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Sum>(entity) && BaseEntity::contentsEquals(entity);
}

std::string Sum::toString() {
    if (elements.empty()) {
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
    if (elements.empty()) {
        return Scalar::zero();
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
    if (isZero())
        return Scalar::zero();
    BaseEntity *evaluated = new Sum(this->multiplier);
    evaluateElementsValue(x, evaluated);
    return evaluateAndDelete(evaluated);
}

BaseEntity * Sum::evaluateDerivative() {
    if(!isFunction)
        return Scalar::zero();
    Sum *derivative = new Sum(this->multiplier);
    for (auto element : elements)
        derivative->addElement(element->evaluateDerivative());
    return derivative;
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
    if (isZero()) {
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
        if(!evaluated->isZero())
            std::replace(elements.begin(), elements.end(), entity, evaluated);
        deleteElement(entity);
    }
}
