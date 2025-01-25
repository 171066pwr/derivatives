#include <algorithm>
#include "Multiplication.h"
#include "../utils/NumberUtils.h"
#include "Scalar.h"
#include "Variable.h"
#include "Power.h"

BaseEntity *Multiplication::copy() {
    BaseEntity *copy = new Multiplication(multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool Multiplication::equals(const BaseEntity *entity) {
    return typeEquals<Multiplication>(entity) && BaseEntity::equals(entity);
}

bool Multiplication::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Multiplication>(entity) && BaseEntity::contentsEquals(entity);
}

std::string Multiplication::toString() {
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

BaseEntity *Multiplication::evaluateFunction() {
    BaseEntity::evaluateFunction();
    if(NumberUtils::doubleEquals(multiplier *= mergeMultipliers(), 0.0)) {
        return Scalar::zero();
    }
    mergeMultiplications();
    mergeVariables();
    mergePowers();
    if (elements.size() == 1) {
        elements[0]->multiplyByScalar(multiplier);
        return evaluateAndDelete(elements[0]);
    }
    updateAndGetIsFunction();
    return mergeSums();
}

BaseEntity *Multiplication::evaluateValue(double x) {
    if (isZero())
        return Scalar::zero();
    BaseEntity *evaluated = new Multiplication(this->multiplier);
    evaluateElementsValue(x, evaluated);
    return evaluated->evaluateFunction();
}

bool Multiplication::updateAndGetIsFunction() {
    isFunction = false;
    return BaseEntity::updateAndGetIsFunction();
}

double Multiplication::mergeMultipliers() {
    double mergedMultiplier = 1.0;
    vector<Scalar *> scalars;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->isZero()) {
            mergedMultiplier = 0.0;
            break;
        }
        if(Scalar *s = dynamic_cast<Scalar *>(elements[i])) {
            scalars.push_back(s);
        }
        mergedMultiplier *= elements[i]->getAndResetMultiplier();
    }
    if(NumberUtils::doubleEquals(mergedMultiplier, 0.0)) {
        for (int i = 0; i < elements.size(); i++) {
            deleteAndZero(elements[i]);
        }
        elements.clear();
    } else {
        for (int i = scalars.size()-1; i > 0; i--) {
            elements.erase(std::remove(elements.begin(), elements.end(), scalars[i]), elements.end());
            deleteAndZero(scalars[i]);
        }

        if(elements.size() > 1 && scalars.size() > 0) {
            elements.erase(std::remove(elements.begin(), elements.end(), scalars[0]), elements.end());
            deleteAndZero(scalars[0]);
        }
    }
    return mergedMultiplier;
}

void Multiplication::mergeMultiplications() {
    vector<BaseEntity *> toErase;
    vector<BaseEntity *> toInsert;
    for(vector<BaseEntity *>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        //if subelement is also multiplication, we can merge them.
        if(Multiplication *s = dynamic_cast<Multiplication *>(*iter)) {
            toInsert.insert(toInsert.end(), s->elements.begin(), s->elements.end());
            toErase.push_back(*iter);
        }
    }
    for (auto e: toErase) {
        elements.erase(std::remove(elements.begin(), elements.end(), e), elements.end());
    }
    elements.insert(this->elements.end(), toInsert.begin(), toInsert.end());
}

void Multiplication::mergeVariables() {
    map<std::string, vector<Variable *>> varMap;
    vector<Power *> mergedPowers;

    for(vector<BaseEntity *>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(Variable *v = dynamic_cast<Variable *>(*iter)) {
            varMap[v->getSymbol()].push_back(v);
        }
    }

    for (auto const& x : varMap){
        vector<Variable *> variables = x.second;
        if(variables.size() > 1) {
            addElement(new Power(variables.size(), variables[0]->copy()));
            for (int i = variables.size() - 1; i >= 0; i--) {
                deleteElement(variables[i]);
            }
        }
    }
}

void Multiplication::mergePowers() {
    map<std::string, vector<Variable *>> varMap;
    vector<Power *> powers;
    for(vector<BaseEntity *>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        if(Power *v = dynamic_cast<Power *>(*iter)) {
            powers.push_back(v);
        }
        if(Variable *v = dynamic_cast<Variable *>(*iter)) {
            varMap[v->getSymbol()].push_back(v);
        }
    }
    for(int i = 0; i < powers.size(); i++) {
        Power *power = powers[i];
        for(int j = 0; j < elements.size(); j++) {
            if(elements[j] == powers[i])
                continue;

            if(Variable *v = dynamic_cast<Variable *>(elements[j])) {
                if(*power->getBase() == *v) {
                    power->addToPower(1.0);
                    deleteElement(elements[j]);
                    j--;
                }
            } else if(Power *p = dynamic_cast<Power *>(elements[j])) {
                if(*power->getBase() == *p->getBase()) {
                    if(power->mergePower(p))
                        powers.erase(std::remove(powers.begin(), powers.end(), elements[j]), powers.end());
                    deleteElement(elements[j]);
                    j--;
                }
            }
        }
    }
}

BaseEntity *Multiplication::mergeSums() {
    for (int i = 0; i < elements.size(); i++) {
        if (Sum *s = dynamic_cast<Sum *>(elements[i])) {
            BaseEntity *result = sumProduct(s);
            deleteElement(elements[i]);
            BaseEntity *evaluated = result->evaluateFunction();
            if (evaluated != result)
                delete result;
            return evaluated;
        }
    }
    return this;
}

BaseEntity *Multiplication::sumProduct(Sum *sum) {
    Sum *product = new Sum();
    for(int i = 0; i < sum->getSize(); i++) {
        Multiplication *copyWithoutSum = copyAllWithoutSelected(sum);
        copyWithoutSum->addElement(sum->getElement(i)->copy());
        product->addElement(copyWithoutSum);
    }
    return product;
}

Multiplication *Multiplication::copyAllWithoutSelected(BaseEntity *selected) {
    Multiplication *copy = new Multiplication(multiplier);
    for(auto element: elements){
        if(element != selected)
            copy->addElement(element->copy());
    }
    return copy;
}
