#include "Fraction.h"
#include "../utils/Logger.h"
#include "NaN.h"
#include "Variable.h"
#include "Power.h"

BaseEntity *Fraction::copy() {
    return new Fraction(elements[1]->copy(), elements[0]->copy(), multiplier);
}

bool Fraction::equals(const BaseEntity *entity) {
    const Fraction *e = dynamic_cast<const Fraction *>(entity);
    if(e == nullptr)
        return false;
    return BaseEntity::equals(e);
}

bool Fraction::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Fraction>(entity) && BaseEntity::contentsEquals(entity);
}

std::string Fraction::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = NumberUtils::doubleEquals(multiplier, 1.0) ?
                    "" : NumberUtils::doubleEquals(multiplier, -1.0) ?
                         "-": NumberUtils::toString(multiplier) + "*";
    result += "(" + elements[0]->toString() + ")" + "/(" + getDenominator()->toString() + ")";
    return result;
}

bool Fraction::addElement(BaseEntity *element) {
    if(elements.size() > 1) {
        Logger::log("This fraction already has both elements");
        return false;
    }
    return BaseEntity::addElement(element);
}

BaseEntity *Fraction::evaluateFunction() {
    BaseEntity *result = evaluateZero();
    if(this != result)
        return result;
    multiplier = mergeMultipliers();
    BaseEntity::evaluateFunction();
    result = splitSum();
    if(this != result)
        return result->evaluateFunction();
    result = swapPower();
    if(this != result)
        return result->evaluateFunction();
    result = mergeFraction();
    if(this != result)
        return result->evaluateFunction();
    return this;
}

BaseEntity *Fraction::evaluateValue(double x) {
    BaseEntity *numerator = getNumerator()->evaluateValue(x);
    BaseEntity *denominator = getDenominator()->evaluateValue(x);
    BaseEntity *result =evaluateZero(numerator, denominator);
    if(this != result)
        return result;
    if(Scalar *m = dynamic_cast<Scalar *>(numerator)) {
        if(Scalar *n = dynamic_cast<Scalar *>(denominator)) {
            return new Scalar(mergeMultipliers());
        }
    }
    return evaluateAndDelete(new Fraction(denominator, numerator, multiplier));
}

bool Fraction::updateAndGetIsFunction() {
    isFunction = false;
    return BaseEntity::updateAndGetIsFunction();
}

BaseEntity *Fraction::getNumerator() {
    return elements[0];
}

BaseEntity *Fraction::getDenominator() {
    return elements[1];
}

void Fraction::replaceNumerator(BaseEntity *numerator) {
    delete elements[0];
    elements[0] = numerator;

}

void Fraction::replaceDenominator(BaseEntity *denominator) {
    delete elements[0];
    elements[0] = denominator;

}

BaseEntity *Fraction::splitSum() {
    if(Sum *n = dynamic_cast<Sum *>(getNumerator())) {
        Sum *result = new Sum(multiplier);
        for(int i = 0; i < n->getSize(); i++) {
            result->addElement(new Fraction(getDenominator()->copy(), n->copy()));
        }
        return result;
    }
    return this;
}

BaseEntity *Fraction::mergeFraction() {
    BaseEntity *numerator = getNumerator();
    BaseEntity *denominator = getDenominator();

    if(numerator->equalsExceptMultiplier(denominator)) {
        return new Scalar(mergeMultipliers());
    }
    if(Scalar *n = dynamic_cast<Scalar *>(denominator)) {
        return numeratorTimesMultiplier();
    }
    if(Multiplication *m = dynamic_cast<Multiplication *>(denominator)) {
        for(int i = 0; i < m->getSize(); i++) {
            if(numerator->equals(m->getElement(i))) {
                replaceNumerator(Scalar::one());
                m->replaceElement(m->getElement(i), Scalar::one());
                numerator = getNumerator();
                break;
            }
        }
        if(Multiplication *n = dynamic_cast<Multiplication *>(numerator)) {
            mergeMultiplications(n, m);
        }
    }

    if(Power *p = dynamic_cast<Power *>(getNumerator())) {
        if(Variable *n = dynamic_cast<Variable *>(getDenominator())) {
            if(n->equals(p->getBase())) {
                p->addToPower(-1.0);
                p->multiplyByScalar(multiplier);
                return p->copy();
            }
        }
    }
    return this;
}

void Fraction::mergeMultiplications(Multiplication *dividend, Multiplication *divisor) {
    for(int i = 0; i < dividend->getSize(); i++) {
        for(int j = 0; j < divisor->getSize(); j++) {
            BaseEntity *topElement = dividend->getElement(i);
            BaseEntity *bottomElement = divisor->getElement(j);
            if(*topElement == *bottomElement) {
                dividend->replaceElement(topElement, Scalar::one());
                divisor->replaceElement(bottomElement, Scalar::one());
                continue;
            }
            //if divisor element is power, we can just invert power sign and move it to the dividend
            if(Power *p = dynamic_cast<Power *>(bottomElement)) {
                p->invertSign();
                dividend->addElement(p->copy());
                divisor->replaceElement(bottomElement, Scalar::one());
            }
        }
    }
}

BaseEntity *Fraction::swapPower() {
    if(Power *p = dynamic_cast<Power *>(getDenominator())) {
        p->getPower()->invertSign();
        return new Multiplication(multiplier, {p->copy(), getNumerator()->copy()});
    }
    return this;
}

double Fraction::mergeMultipliers() {
    return (multiplier * getNumerator()->getAndResetMultiplier()) / getDenominator()->getAndResetMultiplier();
}

BaseEntity *Fraction::numeratorTimesMultiplier() {
    BaseEntity *copy = getNumerator()->copy();
    copy->multiplyByScalar(multiplier);
    return copy;
}

BaseEntity *Fraction::evaluateZero() {
    return evaluateZero(getNumerator(), getDenominator());
}

BaseEntity *Fraction::evaluateZero(BaseEntity *numerator, BaseEntity *denominator) {
    if(denominator->isZero())
        return new NaN();
    if(isZero() || numerator->isZero())
        return Scalar::zero();
    return this;
}
