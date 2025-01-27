#include "Power.h"
#include <cmath>
#include "../utils/Logger.h"
#include "Multiplication.h"

BaseEntity *Power::copy() {
    return new Power(elements[1]->copy(), elements[0]->copy(), multiplier);
}

bool Power::equals(const BaseEntity *entity) {
    const Power *e = dynamic_cast<const Power *>(entity);
    if(e == nullptr)
        return false;
    return BaseEntity::equals(e);
}

bool Power::equalsExceptMultiplier(const BaseEntity *entity) {
    const Power *e = dynamic_cast<const Power *>(entity);
    if(e == nullptr)
        return false;
    return contentsEquals(entity);
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
    result += NumberUtils::doubleEquals(getPower()->getMultiplier(), 1.0) ? getPower()->toString() : "(" + getPower()->toString() + ")";
    return result;
}

bool Power::addElement(BaseEntity *element) {
    if(elements.size() > 1) {
        Logger::log("This power already has both elements");
        return false;
    }
    return BaseEntity::addElement(element);
}

BaseEntity *Power::evaluateFunction() {
    if(isZero())
        return Scalar::zero();
    BaseEntity::evaluateFunction();
    BaseEntity *result = handleEdgeCases();
    if(result != this)
        return result;
    splitMultiplications();
    mergePower();
    return this;
}

BaseEntity *Power::evaluateValue(double x) {
    if (isZero())
        return Scalar::zero();
    BaseEntity *result = handleEdgeCases();
    if(result != this)
        return result;
    BaseEntity *evPower = getPower()->copy()->evaluateValue(x);
    BaseEntity *evBase = getBase()->copy()->evaluateValue(x);
    Power *newPower = new Power(evPower, evBase, this->multiplier);

    if (*getPower() == *evPower && *getBase() == *evBase) {
        return newPower;
    }
    return newPower->evaluateValue(x);
}

bool Power::updateAndGetIsFunction() {
    return BaseEntity::updateAndGetIsFunction();
}

//it doesn't really help when calculating derivative, might drop it...
//or rather it hints that calculating derivative should come first, then grouping later for better presentation.
void Power::mergePower() {
    if(Power *m = dynamic_cast<Power *>(getBase())) {
        Multiplication *newPower = new Multiplication(1, {getPower()->copy(), m->getPower()->copy()});
        replacePower(evaluateAndDelete(newPower));
        replaceBase(m->getBase()->copy());
    }
}

BaseEntity *Power::splitMultiplications() {
    if(Multiplication *m = dynamic_cast<Multiplication *>(getBase())) {
        if(m->getSize() > 1) {
            Multiplication *product = new Multiplication(multiplier);
            for(int i = 0; i < m->getSize(); i++) {
                product->addElement(new Power(getPower()->copy(), m->getElement(i)->copy()));
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
    return elements[1];
}

void Power::replacePower(BaseEntity *power) {
    delete elements[1];
    elements[1] = power;
}

bool Power::mergePower(Power *pwr) {
    if(*getBase() == *pwr->getBase()) {
        BaseEntity *newPower = new Sum(1, {getPower()->copy(), pwr->getPower()->copy()});
        replacePower(evaluateAndDelete(newPower));
        this->multiplier *= pwr->getMultiplier();
        return true;
    }
    return false;
}

void Power::addToPower(double increase) {
    addToPower(new Scalar(increase));
}

void Power::addToPower(BaseEntity *increase) {
    BaseEntity *newPower = new Sum(1, {getPower()->copy(), increase->copy()});
    replacePower(evaluateAndDelete(newPower));
}

BaseEntity *Power::handleEdgeCases() {
    if(getPower() == nullptr)
        return new Scalar(multiplier);
    if (getPower()->isZero())
        return new Scalar(multiplier);
    if(Scalar *s = dynamic_cast<Scalar *>(getPower())) {
        if (*s == *Scalar::one()) {
            BaseEntity *copy = getBase()->copy();
            copy->multiplyByScalar(multiplier);
            return copy;
        }
        if(Scalar *base = dynamic_cast<Scalar *>(getBase())) {
            if (NumberUtils::doubleEquals(base->getMultiplier(), 1.0))
                return new Scalar(multiplier);
            return new Scalar(multiplier * pow(base->getMultiplier(), getPower()->getMultiplier()));
        }
    }
    if(elements.size() == 0)
        return Scalar::zero();
    return this;
}
