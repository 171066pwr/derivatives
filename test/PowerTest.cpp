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
    BaseEntity *scalar = new Scalar(3);
    BaseEntity *variable = new Variable(2);
    BaseEntity *sum = new Sum(1, {variable, scalar});
    BaseEntity *testEntity = new Power(2);
    BaseEntity *multi = new Multiplication(2, {variable, scalar});
    BaseEntity *expected;
    double x = 2.0;
    Logger::important("Testing constructors and toString");

    testEntity->addElement(scalar->copy());
    testEntity = printAndEvaluateFunction(testEntity, "Scalar base");
    testValue(testEntity, expected = new Scalar(9));

    replace(testEntity, new Power(3, {variable->copy()}, 2));
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

    BaseEntity *power = new Power(variable->copy(), variable->copy(), 0.25);
    replace(testEntity, new Power(power->copy(), power->copy(), 2));
    testEntity = printAndEvaluateFunction(testEntity, "Power base, power power");
    replace(testEntity, printAndEvaluateValue(testEntity, x));
    replace(expected, new Scalar(191581231380566414401.0));
    testValue(testEntity, expected);

    deleteMultiple({scalar, variable, sum, testEntity, multi});
}
