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
    mergeMultiplications();
    mergeVariables();
    mergeScalars();
    mergeMultiplier();
    if (elements.size() == 0) {
        delete this;
        return new Scalar(0);
    }
    if (elements.size() == 1) {
        BaseEntity *element = elements[0];
        delete this;
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
            toErase.push_back(*iter);
        }
    }
    //Erase merged SumEntities in separate loop - iterator invalidates on modification
    for (auto e: toErase) {
        deleteElement(e);
    }
    elements.insert(this->elements.end(), toInsert.begin(), toInsert.end());
}

void Sum::mergeScalars() {
    vector<Scalar *> scalars;
    for(vector<BaseEntity *>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(Scalar *s = dynamic_cast<Scalar *>(*iter)) {
            scalars.push_back(s);
        }
    }
    for (int i = scalars.size()-1; i > 0; i--) {
        scalars[0]->add(*scalars[i]);
        deleteElement(scalars[i]);
    }
    if (scalars.size() == 1 && NumberUtils::doubleEquals(scalars[0]->getMultiplier(), 0.0))
        elements.erase(std::remove(elements.begin(), elements.end(), scalars[0]), elements.end());
}

void Sum::mergeVariables() {
    map<std::string, vector<Variable *>> varMap;

    for(vector<BaseEntity *>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(Variable *v = dynamic_cast<Variable *>(*iter)) {
            //don't have to find it first; [] operator initializes value for unexisting key with default () constructor value.
                varMap[v->getSymbol()].push_back(v);
        }
    }

    for (auto const& x : varMap){
        vector<Variable *> variables = x.second;
        for (int i = variables.size()-1; i > 0; i--) {
            variables[0]->add(*variables[i]);
            elements.erase(std::remove(elements.begin(), elements.end(), variables[i]), elements.end());
        }
        if (variables[0]->getMultiplier() == 0)
            elements.erase(std::remove(elements.begin(), elements.end(), variables[0]), elements.end());
    }
}

void Sum::mergeMultiplications() {
    vector<Multiplication *> multiplications;
    for(int i = 0; i < elements.size() && elements.size() > 1; i++) {
        if(Multiplication *s = dynamic_cast<Multiplication *>(elements[i])) {
            multiplications.push_back(s);
        }
    }

    for(int i = 0; i < multiplications.size() && elements.size() > 1; i++){
        for(int j = i+1; j < multiplications.size(); j++) {
            if(multiplications[i]->contentsEquals(multiplications[j])) {
                multiplications[i]->addToMultiplier(multiplications[j]->getMultiplier());
                deleteElement(multiplications[j]);
                multiplications.erase(multiplications.begin() + j);
                j--;
            }
            evaluateAndReplaceElement(multiplications[i]);
        }
    }
}

void Sum::mergeMultiplier() {
    if (NumberUtils::doubleEquals(multiplier, 0)) {
        elements.clear();
    } else if (!NumberUtils::doubleEquals(multiplier, 1.0)) {
        for (auto element: elements) {
            element->multiplyByScalar(multiplier);
        }
        multiplier = 1;
    }
}
