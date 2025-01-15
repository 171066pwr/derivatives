#include "PowerTest.h"
#include "../entities/Power.h"
#include "../entities/Variable.h"
#include "../entities/Sum.h"
#include "../entities/Multiplication.h"

void PowerTest::testEqualsOperators() {
    BaseEntity *scalar = new Scalar(3);
    BaseEntity *variable = new Variable();
    BaseEntity *sum = new Sum(1, {scalar, variable});
    BaseEntity *testEntity = new Power(2);
    BaseEntity *multi = new Multiplication(2, {variable, scalar});
    Logger::important("Testing constructors and toString");
    testEntity->addElement(scalar);
    testEntity = printAndEvaluateFunction(testEntity, "Scalar base");

    replace(testEntity, new Power(3, {variable}, 2));
    testEntity = printAndEvaluateFunction(testEntity, "Variable base");

    replace(testEntity, new Power(3, {sum}, 2));
    testEntity = printAndEvaluateFunction(testEntity, "Sum base");

    replace(testEntity, new Power(multi, sum));
    testEntity = printAndEvaluateFunction(testEntity, "Sum base, multiplication power");
}

void PowerTest::initialTest() {

}
