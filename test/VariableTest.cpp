#define _USE_MATH_DEFINES
#include <cmath>
#include "VariableTest.h"
#include "../entities/Variable.h"

void VariableTest::testEqualsOperators() {
    BaseEntity *original = new Variable("pi", 2);
    BaseEntity *other = new Variable(2);
    Logger::important("test == operator:");
    testCondition(*original == *original->copy(), "success", "failure");
    Logger::important("test != operator:");
    testCondition(*original != *other, "success", "failure");
    deleteMultiple({original, other});
}

void VariableTest::testVariableEvaluation() {
    Logger::important("Test variable evaluation:");
    BaseEntity *variable = new Variable("pi", 1);
    testValue(printAndEvaluateValue(variable, 3), new Scalar(M_PI));
    replace(variable, new Variable("e", 2));
    testValue(printAndEvaluateValue(variable, 3), new Scalar(2*M_E));
    replace(variable, new Variable(3));
    testValue(printAndEvaluateValue(variable, 3), new Scalar(9));
    replace(variable, new Variable("y", 2));
    testValue(printAndEvaluateValue(variable, 3), new Variable("y", 2));
    replace(variable, new Variable(0));
    testValue(printAndEvaluateValue(variable, 3), Scalar::zero());
    replace(variable, new Variable("pi", 0));
    testValue(printAndEvaluateValue(variable, 3), Scalar::zero());
    replace(variable, new Variable("y", 0));
    testValue(printAndEvaluateValue(variable, 3), Scalar::zero());
    delete variable;
}

void VariableTest::testFunctionCheck() {
    Logger::important("Test isFunction check:");
    BaseEntity *variable = new Variable("pi");
    testCondition(!variable->isFunction("x"), "pi is not a function", "pi is not a function");
    replace(variable, new Variable());
    testCondition(variable->isFunction("x"), "x is a function", "x is a function");
    replace(variable, new Variable("y"));
    testCondition(!variable->isFunction("x"), "y is not a function if we substitute for x", "y is not a function if we substitute for x");
    Logger::important("Now treating y as variable");
    testCondition(variable->isFunction("y"), "y is a function now", "y is a function now");
    delete variable;
}
