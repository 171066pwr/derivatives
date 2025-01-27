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
    BaseEntity *power = new Power(2.0, variable->copy(), 2.0);
    BaseEntity *sum = new Sum(1, {variable2->copy(), scalar3->copy()});
    BaseEntity *multi = new Multiplication(2, {variable2->copy(), y->copy(), scalar3->copy()});
    BaseEntity *expected = nullptr;
    BaseEntity *value = nullptr;
    double x = 2.0;
    Logger::important("Testing evaluation");
    BaseEntity *testEntity = new Fraction(zero->copy(), one->copy(), x);
    testEntity = printAndEvaluateFunction(testEntity, "division by 0");
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
    replace(value, printAndEvaluateValue(testEntity, x, "variable / variable"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Scalar(1.5));
    testValue(testEntity, expected);
    testValue(value, expected);

    replace(testEntity, new Fraction(variable2->copy(), power->copy(), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "power / variable"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Variable(2.0));
    testValue(testEntity, expected);
    replace(expected, new Scalar(4.0));
    testValue(value, expected);

    replace(testEntity, new Fraction(power->copy(), power->copy(), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "equal power / power"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Scalar(2.0));
    testValue(testEntity, expected);
    testValue(value, expected);

    replace(testEntity, new Fraction(new Power(-3.5, variable->copy(), 4.0), power->copy(), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "power / power"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Power(5.5, variable->copy()));
    testValue(testEntity, expected);
    replace(expected, new Scalar(45.254833995939));
    testValue(value, expected);

    replace(testEntity, new Fraction(multi->copy(), multi->copy(), 4.0));
    replace(value, printAndEvaluateValue(testEntity, x, "equal multiplication / multiplication"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Scalar(4.0));
    testValue(testEntity, expected);
    testValue(value, expected);


    replace(testEntity, new Fraction(multi->copy(), new Multiplication(2, {variable2->copy(), y->copy()}), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "multiplication / multiplication"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Scalar(2.0/3.0));
    testValue(testEntity, expected);
    testValue(value, expected);

    replace(testEntity, new Fraction(y->copy(), new Multiplication(2, {variable2->copy(), y->copy()}), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "multiplication / variable"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Variable(8.0));
    testValue(testEntity, expected);
    replace(expected, new Scalar(16.0));
    testValue(value, expected);

    replace(testEntity, new Fraction(new Multiplication(2, {variable2->copy(), y->copy()}), y->copy(), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "variable / multiplication"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Fraction(variable->copy(), Scalar::one(), 0.5));
    testValue(testEntity, expected);
    replace(expected, new Scalar(0.25));
    testValue(value, expected);

    replace(testEntity, new Fraction(variable2->copy(), sum->copy(), 2.0));
    replace(value, printAndEvaluateValue(testEntity, x, "sum / variable"));
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Sum(1.0, {new Scalar(2), new Fraction(variable->copy(), Scalar::one(), 3.0)}));
    testValue(testEntity, expected);
    replace(expected, new Scalar(3.5));
    testValue(value, expected);

    deleteMultiple({testEntity, expected, zero, one, scalar3, variable, variable2, y, power, sum, multi});
}
