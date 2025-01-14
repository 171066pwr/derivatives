#define _USE_MATH_DEFINES
#include <cmath>
#include "VariableEntityTest.h"
#include "../entities/VariableEntity.h"

void VariableEntityTest::testEqualsOperators() {
    BaseEntity* original = new VariableEntity("pi", 2);
    BaseEntity* copy = original->copy();
    BaseEntity* other = new VariableEntity(2);
    Logger::important("test == operator:");
    testCondition(*original == *copy, "success", "failure");
    Logger::important("test != operator:");
    testCondition(*original != *other, "success", "failure");
    delete original, copy, other;
}

void VariableEntityTest::testVariableEvaluation() {
    Logger::important("Test variable evaluation:");
    BaseEntity* variable = new VariableEntity("pi", 1);
    testCondition(*printAndEvaluateValue(variable, 3) == *new ScalarEntity(M_PI), "success", "failure");
    delete variable;
    variable = new VariableEntity("e", 2);
    testCondition(*printAndEvaluateValue(variable, 3) == *new ScalarEntity(2*M_E), "success", "failure");
    delete variable;
    variable = new VariableEntity(3);
    testCondition(*printAndEvaluateValue(variable, 3) == *new ScalarEntity(9), "success", "failure");
    delete variable;
    variable = new VariableEntity("y", 2);
    testCondition(*printAndEvaluateValue(variable, 3) == *new VariableEntity("y", 2), "success", "failure");
    delete variable;
    variable = new VariableEntity(0);
    testCondition(*printAndEvaluateValue(variable, 3) == *new ScalarEntity(0), "success", "failure");
    delete variable;
    variable = new VariableEntity("pi", 0);
    testCondition(*printAndEvaluateValue(variable, 3) == *new ScalarEntity(0), "success", "failure");
    delete variable;
    variable = new VariableEntity("y", 0);
    testCondition(*printAndEvaluateValue(variable, 3) == *new ScalarEntity(0), "success", "failure");
    delete variable;
}

void VariableEntityTest::testFunctionCheck() {
    Logger::important("Test isFunction check:");
    BaseEntity* variable = new VariableEntity("pi");
    testCondition(!variable->getIsFunction(), "pi is not a function", "pi is not a function");
    delete variable;
    variable = new VariableEntity();
    testCondition(variable->getIsFunction(), "x is a function", "x is a function");
    delete variable;
    variable = new VariableEntity("y");
    testCondition(!variable->getIsFunction(), "y is not a function if we substitute for x", "y is not a function if we substitute for x");
    Logger::important("Changing substitute to y...");
    VariableEntity::changeSubstituteSymbol("y");
    testCondition(variable->updateAndGetIsFunction(), "y is a function now", "y is a function now");
    Logger::important("Changing substitute back to x");
    VariableEntity::changeSubstituteSymbol("x");
    delete variable;
}
