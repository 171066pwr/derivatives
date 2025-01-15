#include "Power.h"
#include "../utils/NumberUtils.h"
#include "../utils/Logger.h"
#include "Multiplication.h"

Power::~Power() {
    deleteAndZero(power);
}

BaseEntity *Power::copy() {
    BaseEntity* copy = new Power(power->copy(), multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool Power::equals(const BaseEntity *entity) {
    const Power *e = dynamic_cast<const Power *>(entity);
    if(e == nullptr)
        return false;
    else
        return (*this->power == *e->power) && BaseEntity::equals(e);
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
    result += elements[0]->toString() + "^";
    result += power->toString();
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
    BaseEntity::evaluateFunction();
    power = evaluatePower();

    return this;
}

BaseEntity *Power::evaluateValue(double x) {
    return BaseEntity::evaluateValue(x);
}

bool Power::updateAndGetIsFunction() {
    return BaseEntity::updateAndGetIsFunction();
}

bool Power::addPower(Power power) {
    return false;
}

bool Power::multiplyPower(Power power) {
    return false;
}

BaseEntity *Power::evaluatePower() {
    return power = evaluateAndDelete(power);
}

BaseEntity *Power::splitMultiplications() {
    if(elements[0]->getSize() <2 || !typeEquals<Multiplication>(elements[0]))
        return this;
    Multiplication *m = dynamic_cast<Multiplication *>(elements[0]);
    Multiplication *product = new Multiplication(multiplier);
    for(int i = 0; i < m->getSize(); i++) {
        product->addElement(new Power(this->power->copy(), m->getElement(i)->copy()));
    }
    deleteAndZero(power);

}
