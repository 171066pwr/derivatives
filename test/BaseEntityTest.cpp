#define _USE_MATH_DEFINES
#include <cmath>
#include "BaseEntityTest.h"
#include "../entities/Sum.h"
#include "../entities/Scalar.h"
#include "../entities/Variable.h"

void BaseEntityTest::testOperators() {
    BaseEntity *original = new Scalar(25);
    BaseEntity *copy = original->copy();
    BaseEntity *other = new Scalar(20);
    Logger::important("Test == operator with scalar:");
    testCondition(*original == *copy, "success", "failure");
    Logger::important("Test != operator with scalar:");
    testCondition(*original != *other, "success", "failure");

    BaseEntity *sum = new Sum(3, {original, other});
    BaseEntity *sum2 = new Sum(3, {copy, other});
    Logger::important("Test == operator with subelements:");
    testCondition(*sum == *sum2, "success", "failure");
    sum2->addElement(original);
    Logger::important("Test != operator with subelements:");
    testCondition(*sum != *sum2, "success", "failure");

    BaseEntity *variable = new Variable(3);
    Logger::important("Test == operator for different Entity types:");
    testCondition(!(*sum == *variable), "success", "failure");
    sum2->addElement(original);
    Logger::important("Test != operator for different Entity types:");
    testCondition(*sum != *variable, "success", "failure");
}

void BaseEntityTest::testInterfaces() {
    BaseEntity *result;
    Logger::important("Test BaseEntity interface functions - inheritance");
    Logger::important("Test super constructor with initializer list");
    Sum *subSumA = new Sum();
    Sum *subSumB = new Sum(1, {new Scalar(-1), new Variable()});
    Sum *subSubSum = new Sum(1, {new Scalar(-42), new Scalar(21), new Variable(2), new Variable(-3)});
    Logger::important("Test addElements with initializer list");//0.00002 + 3x + 3pi + e
    subSumA->addElements({new Variable(3), new Variable("pi", 2), new Variable("e"), new Variable(0), subSubSum});
    Sum *sum = new Sum(1, {new Scalar(2), new Scalar(20.00002), new Variable(1), new Variable(-1),
                                       new Variable("pi"), subSumA, subSumB});
    result = new Scalar(6.00002 + 3* M_PI + M_E);
    testCondition(*printAndEvaluateValue(sum, 2, "Evaluating value without evaluating isFunction") == *result,
                  result->toString(), "Incorrect - should be " + result->toString());
    printAndEvaluateFunction(sum, "Evaluating isFunction");
    testCondition(sum == printAndEvaluateFunction(sum, "Second evaluation (should be already in final form): "), "correct", "incorrect");
    testCondition(*printAndEvaluateValue(sum, 2, "Evaluating value after evaluating isFunction") == *result,
                                        result->toString(), "Incorrect - should be " + result->toString());
    delete sum, subSubSum, subSumA, subSumB, result;
    Logger::important("Test updateAndGetFunction - function status propagation");
    subSumA = new Sum(1, {new Scalar(1), new Variable("pi")});
    subSumB = new Sum(1, {new Scalar(2), new Variable()});
    sum = new Sum(1, {new Variable("y"), subSumA, subSumB});
    testCondition(sum->getIsFunction(), "isFunction propagated without update", "isFunction not propagated with update");
    testCondition(sum->updateAndGetIsFunction(), "isFunction updated properly", "isFunction not updated");
    sum->addElement(new Variable(-1));
    testCondition(!printAndEvaluateFunction(sum, "Substracting function component, then updating function status:")->getIsFunction(), "isFunction updated on function evaluation", "isFunction not updated on function evaluation");
    delete sum, subSumA, subSumB;

};
