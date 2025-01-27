#include "PowerTest.h"
#include "../entities/Power.h"
#include "../entities/Variable.h"
#include "../entities/Sum.h"
#include "../entities/Multiplication.h"

void PowerTest::testEqualsOperators() {
    Logger::important("Test equals operator");
    BaseEntity *scalar = new Scalar(3);
    BaseEntity *variable = new Variable();
    BaseEntity *sum = new Sum(1, {variable->copy(), scalar->copy()});
    BaseEntity *multi = new Multiplication(2, {variable->copy(), scalar->copy()});

    BaseEntity *testEntity = new Power(multi->copy(), sum->copy(), 12);
    BaseEntity *expected = testEntity->copy();

    printComparison(testEntity, expected);
    testCondition(*testEntity == *expected, "correct", "failure");

    testEntity->getElement(0)->addElement(variable->copy());
    printComparison(testEntity, expected, "Base differs");
    testCondition(*testEntity != *expected, "correct", "failure");

    replace(testEntity, new Power(2, sum->copy(), 3));
    replace(expected, new Power(3, sum->copy(), 3));
    printComparison(testEntity, expected, "Power differs");
    testCondition(*testEntity != *expected, "correct", "failure");
    deleteMultiple({scalar, variable, sum, multi, testEntity, expected});
}

void PowerTest::testEvaluation() {
    BaseEntity *zero = Scalar::zero();
    BaseEntity *one = Scalar::one();
    BaseEntity *scalar3 = new Scalar(3);
    BaseEntity *variable = new Variable();
    BaseEntity *variable2 = new Variable(2);
    BaseEntity *y = new Variable("y");
    BaseEntity *sum = new Sum(1, {variable2, scalar3});
    BaseEntity *testEntity = new Power(2, scalar3->copy());
    BaseEntity *multi = new Multiplication(2, {variable2->copy(), scalar3->copy()});
    BaseEntity *expected;
    double x = 2.0;
    Logger::important("Testing evaluation");

    testEntity = printAndEvaluateFunction(testEntity, "Scalar base");
    testValue(testEntity, expected = new Scalar(9));

    replace(testEntity, new Power(3, {variable2->copy()}, 2));
    testEntity = printAndEvaluateFunction(testEntity, "Variable base");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(128));
    testValue(testEntity, expected);

    replace(testEntity, new Power(3, {sum->copy()}, 2));
    testEntity = printAndEvaluateFunction(testEntity, "Sum base");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(686));
    testValue(testEntity, expected);

    replace(testEntity, new Power(multi->copy(), sum->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "Sum base, multiplication power");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(191581231380566414401.0));
    testValue(testEntity, expected);

    BaseEntity *power = new Power(variable2->copy(), variable2->copy());
    replace(testEntity, new Power(scalar3->copy(), power->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "Power base, scalar power");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(16777216.0));
    testValue(testEntity, expected);

    replace(testEntity, new Power(variable2->copy(), power->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "Power base, variable power");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(4294967296.0));
    testValue(testEntity, expected);

    replace(testEntity, new Power(new Power(variable->copy(), variable->copy()), power->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "Power base, power power - without multipliers");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(4294967296.0));
    testValue(testEntity, expected);

    replace(power, new Power(variable2->copy(), variable2->copy(), 0.25));
    replace(testEntity, new Power(power->copy(), power->copy(), 2));
    testEntity = printAndEvaluateFunction(testEntity, "Power base, power power");
    replace(testEntity, printAndEvaluateValue(testEntity, 1));
    replace(expected, new Scalar(8.0));
    testValue(testEntity, expected);

    replace(testEntity, new Power(zero->copy(), zero->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "Zero base, zero power");
    replace(testEntity, printAndEvaluateValue(testEntity, 1));
    testValue(testEntity, one);

    replace(testEntity, new Power(zero->copy(), scalar3->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "3 base, zero power");
    replace(testEntity, printAndEvaluateValue(testEntity, 1));
    testValue(testEntity, one);

    replace(testEntity, new Power(zero->copy(), variable2->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "variable base, zero power");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    testValue(testEntity, one);

    replace(testEntity, new Power(scalar3->copy(), zero->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "zero base, 3 power");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    testValue(testEntity, zero);

    replace(testEntity, new Power(scalar3->copy(), one->copy(), 2));
    testEntity = printAndEvaluateFunction(testEntity, "2 multiplier, 1 base, 3 power");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    replace(expected, new Scalar(2));
    testValue(testEntity, expected);

    replace(testEntity, new Power(zero->copy(), one->copy(), 0));
    testEntity = printAndEvaluateFunction(testEntity, "0 multiplier, 1 base, 0 power");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    testValue(testEntity, zero);

    replace(testEntity, new Power(zero->copy(), one->copy(), 3));
    testEntity = printAndEvaluateFunction(testEntity, "3 multiplier, 1 base, 0 power");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    testValue(testEntity, scalar3);

    replace(testEntity, new Power(one->copy(), variable->copy(), 1));
    testEntity = printAndEvaluateFunction(testEntity, "x base, 1 power");
    replace(expected, variable->copy());
    testValue(testEntity, expected);
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    replace(expected, new Scalar(2));
    testValue(testEntity, expected);

    replace(testEntity, new Power(y->copy(), variable->copy()));
    replace(expected, new Power(y->copy(), new Scalar(2)));
    testEntity = printAndEvaluateFunction(testEntity, "x base, y power");
    testCondition(testEntity->getIsFunction(), "is function", "is not function");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    testValue(testEntity, expected);
    testCondition(!testEntity->getIsFunction(), "is not function", "is function");

    replace(testEntity, new Power(variable->copy(), y->copy()));
    replace(expected, new Power(2, y->copy()));
    testEntity = printAndEvaluateFunction(testEntity, "y base, x power");
    testCondition(testEntity->getIsFunction(), "is function", "is not function");
    replace(testEntity, printAndEvaluateValue(testEntity, 2));
    testValue(testEntity, expected);
    testCondition(!testEntity->getIsFunction(), "is not function", "is function");

    deleteMultiple({sum, testEntity, expected, multi, zero, one, y, variable});
}
