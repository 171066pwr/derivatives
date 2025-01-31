#include "DerivativesTest.h"
#include "../entities/Scalar.h"
#include "../entities/Variable.h"
#include "../entities/Sum.h"
#include "../entities/Multiplication.h"
#include "../entities/Power.h"

void DerivativesTest::testEvaluation() {
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

    Logger::important("Scalar derivative");
    BaseEntity *testEntity = zero->copy();
    expected = zero->copy();
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    testValue(testEntity, expected);
    Logger::important("Variable derivative");
    Logger::important("Power derivative");
    Logger::important("Sum derivative");
    Logger::important("Multiplication derivative");
}
