#include <algorithm>
#include "MultiplicationEntity.h"
#include "../utils/Logger.h"
#include "../utils/NumberUtils.h"
#include "ScalarEntity.h"

BaseEntity *MultiplicationEntity::copy() {
    BaseEntity* copy = new MultiplicationEntity(multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool MultiplicationEntity::equals(const BaseEntity *entity) {
    const MultiplicationEntity* sum = dynamic_cast<const MultiplicationEntity*>(entity);
    if(sum == nullptr)
        return false;
    else
        return BaseEntity::equals(sum);
}

std::string MultiplicationEntity::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = (NumberUtils::doubleEquals(multiplier, 1.0) ?
                     "" :  NumberUtils::doubleEquals(multiplier, -1.0) ?
                           "-": NumberUtils::toString(multiplier)) + "(";
    for(int i = 0; i < elements.size(); i++) {
        result += (elements[i]->getMultiplier() < 0.0) ? "(" + elements[i]->toString() + ")" : elements[i]->toString();
        if(elements[i] != elements.back() && elements[i+1]->getMultiplier() >= 0)
            result += " * ";
    }
    result += ")";
    return result;
}

bool MultiplicationEntity::addElement(BaseEntity *element) {
    if(!BaseEntity::addElement(element)){
        Logger::log("Failed to add element: " + element->toString());
        return false;
    }
    return true;
}

BaseEntity *MultiplicationEntity::evaluateFunction() {
    BaseEntity::evaluateFunction();
    if(NumberUtils::doubleEquals(multiplier, 0.0) || NumberUtils::doubleEquals(multiplier *= mergeMultipliers(), 0.0))
        return new ScalarEntity(0);
    mergeMultiplications();
    return this;
}

BaseEntity *MultiplicationEntity::evaluateValue(double x) {
    BaseEntity* evaluated = new MultiplicationEntity(this->multiplier);
    BaseEntity::evaluateElementsValue(x, evaluated);
    return evaluated->evaluateFunction();
}

bool MultiplicationEntity::updateAndGetIsFunction() {
    isFunction = false;
    return BaseEntity::updateAndGetIsFunction();
}

double MultiplicationEntity::mergeMultipliers() {
    double mergedMultiplier = 1.0;
    vector<ScalarEntity*> scalars;
    for (int i = 0; i < elements.size(); i++) {
        if (NumberUtils::doubleEquals(elements[i]->getMultiplier(), 0.0)) {
            mergedMultiplier = 0.0;
            break;
        }
        if(ScalarEntity* s = dynamic_cast<ScalarEntity*>(elements[i])) {
            scalars.push_back(s);
        }
        mergedMultiplier *= elements[i]->getAndResetMultiplier();
    }
    if(NumberUtils::doubleEquals(mergedMultiplier, 0.0)) {
        for (int i = 0; i < elements.size(); i++) {
            delete elements[i];
        }
        elements.clear();
    } else {
        for (int i = scalars.size()-1; i > 0; i--) {
            elements.erase(std::remove(elements.begin(), elements.end(), scalars[i]), elements.end());
        }
    }
    return mergedMultiplier;
}

void MultiplicationEntity::mergeMultiplications() {
    vector<BaseEntity*> toErase;
    vector<BaseEntity*> toInsert;
    for(vector<BaseEntity*>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        //if subelement is also multiplication, we can merge them.
        if(MultiplicationEntity* s = dynamic_cast<MultiplicationEntity*>(*iter)) {
            toInsert.insert(toInsert.end(), s->elements.begin(), s->elements.end());
            toErase.push_back(*iter);
        }
    }
    for (auto e: toErase) {
        elements.erase(std::remove(elements.begin(), elements.end(), e), elements.end());
    }
    elements.insert(this->elements.end(), toInsert.begin(), toInsert.end());
}


void MultiplicationEntity::mergeVariables() {
/*
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
*/
}

