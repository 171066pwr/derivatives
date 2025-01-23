#include "Power.h"
#include <cmath>
#include "../utils/Logger.h"
#include "Multiplication.h"

Power::~Power() {
    deleteAndZero(power);
}

BaseEntity *Power::copy() {
    BaseEntity* copy = new Power(power->copy(), multiplier);
    if(elements.size() > 0)
        copy->addElement(getBase()->copy());
    return copy;
}

bool Power::equals(const BaseEntity *entity) {
    const Power *e = dynamic_cast<const Power *>(entity);
    if(e == nullptr)
        return false;
    else
        return (*this->power == *e->power) && BaseEntity::equals(e);
}

bool Power::equalsExceptMultiplier(const BaseEntity *entity) {
    const Power *e = dynamic_cast<const Power *>(entity);
    if(e == nullptr)
        return false;
    else
        return (*this->power == *e->power) && contentsEquals(entity);
}

bool Power::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Power>(entity) && BaseEntity::contentsEquals(entity);
}

std::string Power::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = NumberUtils::doubleEquals(multiplier, 1.0) ?
                     "" : NumberUtils::doubleEquals(multiplier, -1.0) ?
                           "-": NumberUtils::toString(multiplier) + "*";
    result += "(" + elements[0]->toString() + ")" + "^";
    result += NumberUtils::doubleEquals(power->getMultiplier(), 1.0) ? power ->toString() : "(" + power->toString() + ")";
    return result;
}

bool Power::addElement(BaseEntity *element) {
    if(elements.size() == 1) {
        Logger::log("This power already has base");
        return false;
    }
    return BaseEntity::addElement(element);
}

BaseEntity *Power::evaluateFunction() {
    if(NumberUtils::doubleEquals(multiplier, 0.0))
        return new Scalar(0);
    BaseEntity::evaluateFunction();
    power = evaluateAndDelete(power);
    BaseEntity *result = handleEdgeCases();
    if(result != this)
        return result;
    splitMultiplications();
    mergePower();
    return this;
}

BaseEntity *Power::evaluateValue(double x) {
    BaseEntity *result = handleEdgeCases();
    if(result != this)
        return result;
    BaseEntity *evPower = power->copy()->evaluateValue(x);
    BaseEntity *evBase = getBase()->copy()->evaluateValue(x);
    Power newPower = Power(evPower, evBase, this->multiplier);
    return newPower.evaluateValue(x);
}

bool Power::updateAndGetIsFunction() {
    return BaseEntity::updateAndGetIsFunction();
}

//it doesn't really help when calculating derivative, might drop it...
//or rather it hints that calculating derivative should come first, then grouping later for better presentation.
void Power::mergePower() {
    if(Power *m = dynamic_cast<Power *>(getBase())) {
        Multiplication *newPower = new Multiplication(1, {power, m->power->copy()});
        power = newPower->evaluateAndDelete(newPower);
        replaceBase(m->getBase()->copy());
    }
}

BaseEntity *Power::splitMultiplications() {
    if(Multiplication *m = dynamic_cast<Multiplication *>(getBase())) {
        if(m->getSize() > 1) {
            Multiplication *product = new Multiplication(multiplier);
            for(int i = 0; i < m->getSize(); i++) {
                product->addElement(new Power(this->power->copy(), m->getElement(i)->copy()));
            }
            return product;
        }
    }
    return this;
}

BaseEntity *Power::getBase() {
    if(elements.size() >0)
        return elements[0];
    return nullptr;
}

void Power::replaceBase(BaseEntity *base) {
    delete elements[0];
    elements[0] = base;
}

BaseEntity *Power::getPower() {
    return power;
}

bool Power::mergePower(Power *pwr) {
    if(*getBase() == *pwr->getBase()) {
        BaseEntity *newPower = new Sum(1, {power, pwr->power->copy()});
        replace(power, newPower->evaluateAndDelete(newPower));
        this->multiplier *= pwr->getMultiplier();
        return true;
    }
    return false;
}

void Power::addToPower(double increase) {
    BaseEntity *newPower = new Sum(1, {power, new Scalar(increase)});
    power = newPower->evaluateAndDelete(newPower);
}

BaseEntity *Power::handleEdgeCases() {
    if(power == nullptr)
        return new Scalar(1);
    if(Scalar *s = dynamic_cast<Scalar *>(power)) {
        if (NumberUtils::doubleEquals(s->getMultiplier(), 0.0))
            return new Scalar(1);
        if (typeEquals<Scalar>(getBase())) {
            return new Scalar(multiplier * pow(getBase()->getMultiplier(), power->getMultiplier()));
        }
    }
    if(elements.size() == 0)
        return new Scalar(0);
    return this;
}
