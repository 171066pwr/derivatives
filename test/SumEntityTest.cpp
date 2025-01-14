#include "SumEntityTest.h"
#include "../entities/SumEntity.h"
#include "../entities/ScalarEntity.h"
#include "../entities/VariableEntity.h"

void SumEntityTest::testEqualsOperators() {
    BaseEntity* original = new VariableEntity("pi", 2);
    BaseEntity* copy = original->copy();
    BaseEntity* other = new VariableEntity(2);
    BaseEntity* sum = new SumEntity(2, {original, other});
    BaseEntity* sum2 = new SumEntity(2, {copy, other});
    Logger::important("test == operator:");
    testCondition(*sum == *sum2, "success", "failure");
    delete sum2;
    sum2 = new SumEntity(2, {other, copy});
    Logger::important("test != operator:");
    testCondition(*sum != *sum2, "success", "failure");
    delete original, copy, other, sum, sum2;
}

void SumEntityTest::testSum() {
    Logger::important("Test SumEntity - evaluation");
    SumEntity* sum = new SumEntity(1, {new ScalarEntity(-5), new ScalarEntity(5), new ScalarEntity(1)});
    SumEntity* subSumA = new SumEntity(1, {new VariableEntity(2), new VariableEntity(3), new VariableEntity("c", 0.1)});
    SumEntity* subSumB = new SumEntity(1, {new VariableEntity(-2), new VariableEntity("pi", -1), new VariableEntity(-4), new ScalarEntity(1.3)});

    Logger::important("Test merging scalars");
    testType<ScalarEntity>(printAndEvaluateFunction(sum), "Transormed SumEntity into ScalarEntity;", "Failed to transform scalar SumEntity into ScalarEntity!");

    Logger::important("Test merging variables");
    printAndEvaluateFunction(subSumA);
    subSumA->addElements({new VariableEntity(-2), new VariableEntity("c", -0.1)});
    testType<VariableEntity>(printAndEvaluateFunction(subSumA), "Transormed SumEntity into VariableEntity;",
                             "Failed to transform SumEntity into VariableEntity!");

    Logger::important("Test merging sums");
    sum->addElements({new VariableEntity("pi"), new VariableEntity(2), new ScalarEntity(-0.3)});
    sum->addElements({subSumA, subSumB});
    subSumA->addElements({new VariableEntity("y"), new VariableEntity("x")});
    testCondition(*printAndEvaluateFunction(sum) == *new SumEntity(1, {new ScalarEntity(2), new VariableEntity("y")}), "Merged sums successfully", "Failed to merge sums!");
    delete sum, subSumA, subSumB;
}

void SumEntityTest::testMultiplier0() {
    Logger::important("Test SumEntity - multiplier");
    Logger::important("Test multiplier 0");
    BaseEntity *sum = new SumEntity(0, {new ScalarEntity(-99), new VariableEntity("pi", 2),
                                        new SumEntity(1, {new VariableEntity(1), new ScalarEntity(1000)})});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 0");
    testCondition(*sum == *(new ScalarEntity(0)), "Multiplier 0 transformed to scalar 0",
                  "Failed to transform multiplier 0 into scalar 0");
    delete sum;
}

void SumEntityTest::testMultiplier1() {
    Logger::important("Test multiplier 1");
    BaseEntity *sum = new SumEntity(1, {new ScalarEntity(1), new VariableEntity(1)});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 1");
    testCondition(sum->getElement(0) == *(new ScalarEntity(1)) && sum->getElement(0) == *(new VariableEntity(1)),
                  "Multiplied by 1 correctly", "Failed to multiply by 1");
    delete sum;
}

void SumEntityTest::testMultiplier2() {
    Logger::important("Test multiplier 2, isFunction evaluation");
    BaseEntity *sum = new SumEntity(2, {new ScalarEntity(1), new VariableEntity(1)});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 2");
    testCondition(sum->getElement(0) == *new ScalarEntity(2) && sum->getElement(0) == *(new VariableEntity(2)),
                  "Multiplied by 2 correctly", "Failed to multiply by 2");
    delete sum;
}

void SumEntityTest::testMultiplierValue() {
    BaseEntity* testEntity;
    Logger::important("Test multiplier 2, raw value evaluation");
    BaseEntity *sum = new SumEntity(2, {new ScalarEntity(1), new VariableEntity(1)});
    testEntity = printAndEvaluateValue(sum, 2, "Evaluated value");
    testCondition(*testEntity == *new ScalarEntity(6), "Evaluated for x=2 correctly", "Failed to evaluate value");
    delete sum, testEntity;
}

void SumEntityTest::testMultiplierNested() {
    Logger::important("Test multipliers on sum and subsum");
    BaseEntity* testEntity;
    BaseEntity *sum = new SumEntity(3, {new ScalarEntity(1), new VariableEntity(2),
                                        new SumEntity(2, {new ScalarEntity(1), new VariableEntity(2)})});
    testEntity = printAndEvaluateValue(sum, 2, "Raw value evaluation for x=2");
    testCondition(*testEntity == *new ScalarEntity(45), "Correct result of 45", "Incorrect, should be 45");
    sum = printAndEvaluateFunction(sum, "Function evaluation");
    testCondition(*sum == *new SumEntity(1, {new ScalarEntity(9), new VariableEntity(18)}),
                  "correct", "should be 9+18x");
    testCondition(*printAndEvaluateValue(sum, 2, "Evaluating for x = 2") == *new ScalarEntity(45),
                  "correct", "should be 45");
    delete sum, testEntity;
}
