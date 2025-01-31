#include "DerivativesTest.h"
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
    BaseEntity *expPower = new Power(variable->copy(), scalar3->copy(), 2.0);
    BaseEntity *sum = new Sum(1, {variable3->copy(), scalar3->copy()});
    BaseEntity *multi = new Multiplication(2, {variable3->copy(), y->copy(), scalar3->copy()});
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
    Variable::changeSubstituteSymbol("y");
    replace(testEntity, printAndEvaluateDerivative(testEntity, "differentiated by Y"));
    testValue(testEntity, expected);

    replace(testEntity,y->copy());
    replace(expected, one->copy());
    replace(testEntity, printAndEvaluateDerivative(testEntity, "differentiated by Y"));
    testValue(testEntity, expected);
    Variable::changeSubstituteSymbol("x");

    Logger::important("Power derivative");
    replace(testEntity,power->copy());
    replace(expected, new Variable(4));
    replace(testEntity, printAndEvaluateDerivative(testEntity));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    replace(testEntity,expPower->copy());
    replace(expected, new UnsupportedDerivative(expPower->copy()));
    replace(testEntity, printAndEvaluateDerivative(testEntity, "Unsupported (yet) exponential function"));
    replace(testEntity, printAndEvaluateFunction(testEntity));
    testValue(testEntity, expected);

    Logger::important("Sum derivative");
    Logger::important("Multiplication derivative");
}
