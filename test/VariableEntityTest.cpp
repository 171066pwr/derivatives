#define _USE_MATH_DEFINES
#include <cmath>
#include "VariableEntityTest.h"
#include "../entities/VariableEntity.h"

void VariableEntityTest::testEqualsOperators() {
    BaseEntity* original = new VariableEntity("pi", 2, 3);
    BaseEntity* copy = original->copy();
    BaseEntity* other = new VariableEntity(2, 4);
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
}