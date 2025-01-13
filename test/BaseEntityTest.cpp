#define _USE_MATH_DEFINES
#include <cmath>
#include "BaseEntityTest.h"
#include "../entities/SumEntity.h"
#include "../entities/ScalarEntity.h"
#include "../entities/VariableEntity.h"

void BaseEntityTest::testOperators() {
    BaseEntity* original = new ScalarEntity(25);
    BaseEntity* copy = original->copy();
    BaseEntity* other = new ScalarEntity(20);
    Logger::important("Test == operator with scalar:");
    testCondition(*original == *copy, "success", "failure");
    Logger::important("Test != operator with scalar:");
    testCondition(*original != *other, "success", "failure");

    BaseEntity* sum = new SumEntity(3, {original, other});
    BaseEntity* sum2 = new SumEntity(3, {copy, other});
    Logger::important("Test == operator with subelements:");
    testCondition(*sum == *sum2, "success", "failure");
    sum2->addElement(original);
    Logger::important("Test != operator with subelements:");
    testCondition(*sum != *sum2, "success", "failure");

    BaseEntity* variable = new VariableEntity(3);
    Logger::important("Test == operator for different Entity types:");
    testCondition(!(*sum == *variable), "success", "failure");
    sum2->addElement(original);
    Logger::important("Test != operator for different Entity types:");
    testCondition(*sum != *variable, "success", "failure");
}

void BaseEntityTest::testInterfaces() {
    BaseEntity* result;
    Logger::important("Test BaseEntity interface functions - inheritance");
    Logger::important("Test super constructor with initializer list");
    SumEntity* subSumA = new SumEntity();
    SumEntity* subSumB = new SumEntity(1, {new ScalarEntity(-1), new VariableEntity()});
    SumEntity* subSubSum = new SumEntity(1, {new ScalarEntity(-42), new ScalarEntity(21), new VariableEntity(2), new VariableEntity(-3)});
    Logger::important("Test addElements with initializer list");//0.00002 + 3x + 3pi + e
    subSumA->addElements({new VariableEntity(3), new VariableEntity("pi", 2), new VariableEntity("e"), new VariableEntity(0), subSubSum});
    SumEntity* sum = new SumEntity(1, {new ScalarEntity(2), new ScalarEntity(20.00002), new VariableEntity(1), new VariableEntity(-1),
                                       new VariableEntity("pi", 1), subSumA, subSumB});
    result = new ScalarEntity(6.00002 + 3* M_PI + M_E);
    testCondition(*printAndEvaluateValue(sum, 2, "Evaluating value without evaluating isFunction") == *result,
                  result->toString(), "Incorrect - should be " + result->toString());
    printAndEvaluateFunction(sum, "Evaluating isFunction");
    testCondition(sum == printAndEvaluateFunction(sum, "Second evaluation (should be already in final form): "), "correct", "incorrect");
    testCondition(*printAndEvaluateValue(sum, 2, "Evaluating value after evaluating isFunction") == *result,
                                        result->toString(), "Incorrect - should be " + result->toString());
    delete sum, subSubSum, subSumA, subSumB, result;
}
