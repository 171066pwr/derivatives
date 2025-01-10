#include <algorithm>
#include "SumEntity.h"

#include <map>

#include "VariableEntity.h"

std::string SumEntity::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = multiplier != 1 ? StringUtils::toString(this->multiplier) + "(" : "(";
    for(int i = 0; i < elements.size(); i++) {
        result += elements[i]->toString();
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
    applyMultiplier();
    mergeSums();
    mergeVariables();
    mergeScalars();
    if (elements.size() == 0)
        return new ScalarEntity(0);
    if (elements.size() == 1)
        return elements[0];
    return this;
}

BaseEntity* SumEntity::evaluateValue(double x) {
    BaseEntity* evaluated = new SumEntity(this->multiplier);
    BaseEntity::evaluateElementsValue(x, evaluated);
    return evaluated;
}

void SumEntity::applyMultiplier() {
    if (multiplier == 0) {
        elements.clear();
    } else if (multiplier != 1) {
        for (auto element: elements) {
            element->multiplyByScalar(multiplier);
        }
        multiplier = 1;
    }
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
        elements.erase(std::remove(elements.begin(), elements.end(), e), elements.end());
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
    if (scalars.size() > 1) {
        for (int i = scalars.size()-1; i > 0; i--) {
            scalars[0]->add(*scalars[i]);
            elements.erase(std::remove(elements.begin(), elements.end(), scalars[i]), elements.end());
        }
    }
    if (scalars.size()  == 1 && scalars[0]->getMultiplier() == 0)
        elements.erase(std::remove(elements.begin(), elements.end(), scalars[0]), elements.end());
}

void SumEntity::mergeVariables() {
    typedef std::pair<std::string, double> VarKey;
    typedef map<VarKey, vector<VariableEntity*>> VarMap;
    VarMap varMap;

    for(vector<BaseEntity*>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(VariableEntity* v = dynamic_cast<VariableEntity*>(*iter)) {
            VarKey key = {v->getSymbol(), v->getPower()};
            if (varMap.find(key) != varMap.end()) {
                varMap[key].push_back(v);
            } else {
                vector<VariableEntity*> variables;
                variables.push_back(v);
                varMap.insert({key, variables});
            }
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
