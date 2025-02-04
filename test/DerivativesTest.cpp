#include "DerivativesTest.h"

#include "../entities/Fraction.h"
#include "../entities/Scalar.h"
#include "../entities/Variable.h"
#include "../entities/Sum.h"
#include "../entities/Multiplication.h"
#include "../entities/Power.h"
#include "../entities/UnsupportedDerivative.h"

void DerivativesTest::testEvaluation() {
    BaseEntity *zero = Scalar::zero();
    BaseEntity *one = Scalar::one();
    BaseEntity *scalar3 = new Scalar(3);
    BaseEntity *variable = new Variable();
    BaseEntity *variable3= new Variable(3);
    BaseEntity *y = new Variable("y");
    BaseEntity *power = new Power(2.0, variable->copy(), 2.0);
    BaseEntity *scalarPower = new Power(2.0, 3.0, 2.0);
    BaseEntity *expPower = new Power(variable->copy(), scalar3->copy(), 2.0);
    BaseEntity *sum = new Sum(2, {variable3->copy(), scalar3->copy()});
    BaseEntity *scalarSum = new Sum(2, {one->copy(), zero->copy(), scalar3->copy()});
    BaseEntity *multi = new Multiplication(2, {variable3->copy(), y->copy(), scalar3->copy()});
    BaseEntity *variableMulti = new Multiplication(2, {variable3->copy(), y->copy(), variable->copy(), scalar3->copy()});
    BaseEntity *scalarMulti = new Multiplication(2, {scalar3->copy(), y->copy(), scalar3->copy()});
    BaseEntity *expected = nullptr;


    BaseEntity *value = nullptr;
    double x = 2.0;

    Logger::important("Scalar derivative");
    BaseEntity *testEntity = zero->copy();
    expected = zero->copy();
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    testValue(testEntity, expected);

    Logger::important("Variable derivative");
    replace(testEntity,variable3->copy());
    replace(expected, scalar3->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    testValue(testEntity, expected);

    Logger::important("Variable derivative");
    replace(testEntity,variable3->copy());
    replace(expected, scalar3->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,y->copy());
    replace(expected, zero->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "differentiated by X"));
    testValue(testEntity, expected);

    replace(testEntity,variable3->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "differentiated by Y", "y"));
    testValue(testEntity, expected);

    replace(testEntity,y->copy());
    replace(expected, one->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "differentiated by Y", "y"));
    testValue(testEntity, expected);

    Logger::important("Power derivative");
    replace(testEntity,power->copy());
    replace(expected, new Variable(4));
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,scalarPower->copy());
    replace(expected, zero->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "base and power are scalars"));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,expPower->copy());
    replace(expected, new UnsupportedDerivative(expPower->copy()));
    replace(testEntity, printAndEvaluateDerivative(testEntity, "Unsupported (yet) exponential function"));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    Logger::important("Sum derivative");
    replace(testEntity,scalarSum->copy());
    replace(expected, zero->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "Scalar sum"));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,sum->copy());
    replace(expected, new Scalar(6.0));
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    Logger::important("Multiplication derivative");
    replace(testEntity,scalarMulti->copy());
    replace(expected, zero->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "Scalar multiplication"));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,multi->copy());
    replace(expected, new Variable("y", 18));
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,variableMulti->copy());
    replace(expected, new Sum(1.0, {
        new Multiplication(18.0, {new Variable("y"), variable->copy()}),
        new Multiplication(18.0, {variable->copy(), new Variable("y")})})) ;
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity, "It won't group unless sorting of elements is implemented"));
    testValue(testEntity, expected);

    Logger::important("Fraction derivative");
    replace(testEntity,new Fraction(y->copy(), scalarSum->copy(), 2.0));
    replace(expected, zero->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "Scalar fraction"));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,new Fraction(variable->copy(), variable3->copy(), 2.0));
    replace(expected, zero->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,new Fraction(variable3->copy(), scalar3->copy(), 2.0));
    replace(expected, new Power(-2.0, variable->copy(), -2.0));
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,new Fraction(variable3->copy(), scalar3->copy(), 2.0));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);
}

void DerivativesTest::investigation() {
    Logger::important("Investigating change of derivative variable...");
    BaseEntity *variable = new Variable();
    BaseEntity *variable3 = new Variable(3.0);
    BaseEntity *y = new Variable("y");
    BaseEntity *y2 = new Variable("y", 2.0);
    BaseEntity *scalar21 = new Scalar(21.5);
    BaseEntity *multi = new Multiplication(2.0, {variable3, y, variable, y2, scalar21});
    BaseEntity *derivative = multi->evaluateDerivative("x");
    BaseEntity *expected = new Multiplication(516.0, {variable->copy(), new Power(2, y->copy())});
    derivative = printAndEvaluateFunction(derivative);
    testValue(derivative, expected);

    Logger::important("Changing to dy");
    BaseEntity *derivativeY = multi->copy();
    replace(derivativeY, derivativeY->evaluateDerivative("y"));
    derivativeY = printAndEvaluateFunction(derivativeY);
    replace(expected, new Multiplication(516.0, {y->copy(), new Power(2, variable->copy())}));
    testValue(derivativeY, expected);

    deleteMultiple({multi, derivative, derivativeY});
}
