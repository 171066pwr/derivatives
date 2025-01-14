#include <algorithm>
#include "SumEntity.h"
#include <map>
#include "VariableEntity.h"

BaseEntity* SumEntity::copy() {
    BaseEntity* copy = new SumEntity(multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool SumEntity::equals(const BaseEntity *entity) {
    //If the new type to be casted to is a pointer the result is a nullptr on error. If it is a reference it throws an exception.
    //So we have to cast pointers or catch bad_cast
    const SumEntity* sum = dynamic_cast<const SumEntity*>(entity);
    if(sum == nullptr)
        return false;
    else
        return BaseEntity::equals(sum);
}

std::string SumEntity::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = (NumberUtils::doubleEquals(multiplier, 1.0) ?
                     "" :  NumberUtils::doubleEquals(multiplier, -1.0) ?
                           "-" : NumberUtils::toString(multiplier)) + "(";
    for(int i = 0; i < elements.size(); i++) {
        result += (elements[i]->getMultiplier() < 0.0) ? "(" + elements[i]->toString() + ")" : elements[i]->toString();
        if(elements[i] != elements.back() && elements[i+1]->getMultiplier() >= 0)
            result += " + ";
    }
    result += ")";
    return result;
}

bool SumEntity::addElement(BaseEntity * element) {
    if(!BaseEntity::addElement(element)){
        Logger::log("Failed to add element: " + element->toString());
        return false;
    }
    return true;
}

BaseEntity* SumEntity::evaluateFunction() {
    BaseEntity::evaluateFunction();
    mergeSums();
    mergeVariables();
    mergeScalars();
    applyMultiplier();
    if (elements.size() == 0)
        return new ScalarEntity(0);
    if (elements.size() == 1)
        return elements[0];
    updateAndGetIsFunction();
    return this;
}

BaseEntity* SumEntity::evaluateValue(double x) {
    BaseEntity* evaluated = new SumEntity(this->multiplier);
    BaseEntity::evaluateElementsValue(x, evaluated);
    return evaluated->evaluateFunction();
}

bool SumEntity::updateAndGetIsFunction() {
    isFunction = false;
    return BaseEntity::updateAndGetIsFunction();
}

void SumEntity::mergeSums() {
    vector<BaseEntity*> toErase;
    vector<BaseEntity*> toInsert;
    for(vector<BaseEntity*>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        //if subelement is also sum, we can merge them.
        if(SumEntity* s = dynamic_cast<SumEntity*>(*iter)) {
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

void SumEntity::mergeScalars() {
    vector<ScalarEntity*> scalars;
    for(vector<BaseEntity*>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(ScalarEntity* s = dynamic_cast<ScalarEntity*>(*iter)) {
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

void SumEntity::mergeVariables() {
    map<std::string, vector<VariableEntity*>> varMap;

    for(vector<BaseEntity*>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(VariableEntity* v = dynamic_cast<VariableEntity*>(*iter)) {
            //don't have to find it first; [] operator initializes value for unexisting key with default () constructor value.
                varMap[v->getSymbol()].push_back(v);
        }
    }

    for (auto const& x : varMap){
        vector<VariableEntity*> variables = x.second;
        for (int i = variables.size()-1; i > 0; i--) {
            variables[0]->add(*variables[i]);
            elements.erase(std::remove(elements.begin(), elements.end(), variables[i]), elements.end());
        }
        if (variables[0]->getMultiplier() == 0)
            elements.erase(std::remove(elements.begin(), elements.end(), variables[0]), elements.end());
    }
}

void SumEntity::applyMultiplier() {
    if (NumberUtils::doubleEquals(multiplier, 0)) {
        elements.clear();
    } else if (!NumberUtils::doubleEquals(multiplier, 1.0)) {
        for (auto element: elements) {
            element->multiplyByScalar(multiplier);
        }
        multiplier = 1;
    }
}
