#include "Fraction.h"
#include "../utils/Logger.h"
#include "NaN.h"
#include "Variable.h"
#include "Power.h"

BaseEntity *Fraction::copy() {
    return new Fraction(elements[1]->copy(), elements[0]->copy(), multiplier);
}

bool Fraction::equals(const BaseEntity *entity) {
    return typeEquals<Fraction>(entity) && BaseEntity::equals(entity);
}

bool Fraction::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Fraction>(entity) && BaseEntity::contentsEquals(entity);
}

std::string Fraction::toString() {
    if (elements.empty()) {
        return "0";
    }
    string result = NumberUtils::doubleEquals(multiplier, 1.0) ?
                    "" : NumberUtils::doubleEquals(multiplier, -1.0) ?
                         "-": NumberUtils::toString(multiplier) + "*";
    result += "(" + getNumerator()->toString() + ")" + "/(" + getDenominator()->toString() + ")";
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
    BaseEntity *result = handleEdgeCases();
    if(this != result)
        return result;
    multiplier = mergeMultipliers();
    BaseEntity::evaluateFunction();
    //Second evaluation in case of changes. I find it more ellegant than update flag and I don't care about memory.
    BaseEntity *copy = this->copy();
    result = splitSum();
    if(this == result) {
        result = swapPower();
        if (this == result)
            result = mergeOther();
        if (this == result) {
            if (*copy != *this) {
                delete(copy);
                return evaluateFunction();
            }
            delete(copy);
            return this;
        }
    }
    delete(copy);
    return result->evaluateFunction();
}

BaseEntity *Fraction::evaluateValue(double x, string variable) {
    BaseEntity *numerator = getNumerator()->evaluateValue(x, variable);
    BaseEntity *denominator = getDenominator()->evaluateValue(x, variable);
    BaseEntity *result = handleEdgeCases(numerator, denominator);
    if(this != result)
        return result;
    if(Scalar *m = dynamic_cast<Scalar *>(numerator)) {
        if(Scalar *n = dynamic_cast<Scalar *>(denominator)) {
            return new Scalar((multiplier * numerator->getMultiplier()) / denominator->getMultiplier());
        }
    }
    return evaluateAndDelete(new Fraction(denominator, numerator, multiplier));
}

BaseEntity * Fraction::evaluateDerivative(string variable) {
    if(!isFunction(variable))
        return Scalar::zero();
    Sum *numerator = new Sum();
    Multiplication *denominator = new Multiplication();
    Fraction *derivative = new Fraction(denominator, numerator, multiplier);

    numerator->addElements({new Multiplication(1.0, {
        this->getNumerator()->evaluateDerivative(variable), this->getDenominator()->copy()})});
    numerator->addElements({new Multiplication(-1.0, {
        this->getNumerator()->copy(), this->getDenominator()->evaluateDerivative(variable)})});

    denominator->addElements({new Multiplication(1.0, {getDenominator()->copy(), getDenominator()->copy()})});
    return derivative;
}

BaseEntity *Fraction::getNumerator() {
    return elements[0];
}

BaseEntity *Fraction::getDenominator() {
    return elements[1];
}

void Fraction::replaceNumerator(BaseEntity *numerator) {
    if (elements[0] != numerator) {
        delete elements[0];
        elements[0] = numerator;
    }
}

void Fraction::replaceDenominator(BaseEntity *denominator) {
    if (elements[1] != denominator) {
        delete elements[1];
        elements[1] = denominator;
    }
}

BaseEntity *Fraction::splitSum() {
    if(Sum *n = dynamic_cast<Sum *>(getNumerator())) {
        Sum *result = new Sum(multiplier);
        for(int i = 0; i < n->getSize(); i++) {
            result->addElement(new Fraction(getDenominator()->copy(), n->getElement(i)->copy()));
        }
        return result;
    }
    return this;
}

BaseEntity *Fraction::mergeOther() {
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
        //eliminate similar elements if it's division of multiplications
        if(Multiplication *n = dynamic_cast<Multiplication *>(numerator)) {
            mergeMultiplications(n, m);
        }
    }

    if(Multiplication *m = dynamic_cast<Multiplication *>(numerator)) {
        for (int i = 0; i < m->getSize(); i++) {
            if (denominator->equals(m->getElement(i))) {
                replaceDenominator(Scalar::one());
                m->replaceElement(m->getElement(i), Scalar::one());
                break;
            }
        }
    }
    replaceDenominator(getDenominator()->evaluateFunction());
    replaceNumerator(getNumerator()->evaluateFunction());

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
        multiplyByScalar(1.0/p->getAndResetMultiplier());
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

BaseEntity *Fraction::handleEdgeCases() {
    return handleEdgeCases(getNumerator(), getDenominator());
}

BaseEntity *Fraction::handleEdgeCases(BaseEntity *numerator, BaseEntity *denominator) {
    if(denominator->isZero())
        return new NaN();
    if(isZero() || numerator->isZero())
        return Scalar::zero();
    if(denominator == Scalar::one())
        return numerator->copy();
    return this;
}
