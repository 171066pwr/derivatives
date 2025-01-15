#define _USE_MATH_DEFINES
#include <cmath>
#include "VariableTest.h"
#include "../entities/Variable.h"

void VariableTest::testEqualsOperators() {
    BaseEntity *original = new Variable("pi", 2);
    BaseEntity *copy = original->copy();
    BaseEntity *other = new Variable(2);
    Logger::important("test == operator:");
    testCondition(*original == *copy, "success", "failure");
    Logger::important("test != operator:");
    testCondition(*original != *other, "success", "failure");
    delete original, copy, other;
}

void VariableTest::testVariableEvaluation() {
    Logger::important("Test variable evaluation:");
    BaseEntity *variable = new Variable("pi", 1);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Scalar(M_PI), "success", "failure");
    delete variable;
    variable = new Variable("e", 2);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Scalar(2*M_E), "success", "failure");
    delete variable;
    variable = new Variable(3);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Scalar(9), "success", "failure");
    delete variable;
    variable = new Variable("y", 2);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Variable("y", 2), "success", "failure");
    delete variable;
    variable = new Variable(0);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Scalar(0), "success", "failure");
    delete variable;
    variable = new Variable("pi", 0);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Scalar(0), "success", "failure");
    delete variable;
    variable = new Variable("y", 0);
    testCondition(*printAndEvaluateValue(variable, 3) == *new Scalar(0), "success", "failure");
    delete variable;
}

void VariableTest::testFunctionCheck() {
    Logger::important("Test isFunction check:");
    BaseEntity *variable = new Variable("pi");
    testCondition(!variable->getIsFunction(), "pi is not a function", "pi is not a function");
    delete variable;
    variable = new Variable();
    testCondition(variable->getIsFunction(), "x is a function", "x is a function");
    delete variable;
    variable = new Variable("y");
    testCondition(!variable->getIsFunction(), "y is not a function if we substitute for x", "y is not a function if we substitute for x");
    Logger::important("Changing substitute to y...");
    Variable::changeSubstituteSymbol("y");
    testCondition(variable->updateAndGetIsFunction(), "y is a function now", "y is a function now");
    Logger::important("Changing substitute back to x");
    Variable::changeSubstituteSymbol("x");
    delete variable;
}
