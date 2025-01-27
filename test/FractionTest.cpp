#include "FractionTest.h"
#include "../entities/Multiplication.h"
#include "../entities/Power.h"
#include "../entities/Variable.h"
#include "../entities/Fraction.h"
#include "../entities/NaN.h"

void FractionTest::testEvaluation() {
    BaseEntity *zero = Scalar::zero();
    BaseEntity *one = Scalar::one();
    BaseEntity *scalar3 = new Scalar(3);
    BaseEntity *variable = new Variable();
    BaseEntity *variable2 = new Variable(2);
    BaseEntity *y = new Variable("y");
    BaseEntity *power = new Power(2.0, variable->copy(), 2);
    BaseEntity *sum = new Sum(1, {variable2, scalar3});
    BaseEntity *multi = new Multiplication(2, {variable2->copy(), scalar3->copy()});
    BaseEntity *expected;
    double x = 2.0;
    Logger::important("Testing evaluation");

    BaseEntity *testEntity = new Fraction(zero->copy(), one->copy(), x);
    testEntity = printAndEvaluateFunction(testEntity, "Division by 0");
    testType<NaN>(testEntity, testEntity->toString(), "should be NaN");

    replace(testEntity, new Fraction(scalar3->copy(), zero->copy(), x));
    testEntity = printAndEvaluateFunction(testEntity, "0 numerator");
    expected = zero;
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(scalar3->copy(), variable->copy(), 0.0));
    testEntity = printAndEvaluateFunction(testEntity, "0 multiplicator");
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(one->copy(), scalar3->copy(), 2.0));
    testEntity = printAndEvaluateFunction(testEntity, "scalar / scalar");
    expected = new Scalar(6);
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(scalar3->copy(), one->copy(), 1.0));
    testEntity = printAndEvaluateFunction(testEntity, "scalar / scalar, less than 1");
    replace(expected, new Scalar(1.0/3.0));
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(scalar3->copy(), variable->copy(), 2.0));
    testEntity = printAndEvaluateFunction(testEntity, "variable / scalar");
    replace(expected, new Variable(2.0/3.0));
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(variable->copy(), scalar3->copy(), 1.0));
    testEntity = printAndEvaluateFunction(testEntity, "scalar / variable");
    replace(expected, new Fraction(variable->copy(), one->copy(), 3.0));
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(variable2->copy(), variable->copy(), 3.0));
    testEntity = printAndEvaluateFunction(testEntity, "variable / variable");
    replace(expected, new Scalar(1.5));
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(variable2->copy(), power->copy(), 2.0));
    testEntity = printAndEvaluateFunction(testEntity, "power / variable");
    replace(expected, new Variable(2.0));
    testValue(testEntity, expected);

    replace(testEntity, new Fraction(power->copy(), power->copy(), 2.0));
    testEntity = printAndEvaluateFunction(testEntity, "Equal power / power");
    replace(expected, new Scalar(2.0));
    testValue(testEntity, expected);
}
