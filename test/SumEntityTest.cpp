#include "SumEntityTest.h"
#include "../entities/SumEntity.h"
#include "../entities/ScalarEntity.h"
#include "../entities/VariableEntity.h"

void SumEntityTest::testSum() {
    Logger::important("Test SumEntity - evaluation");
    SumEntity* sum = new SumEntity(1, {new ScalarEntity(-5), new ScalarEntity(5), new ScalarEntity(1)});
    SumEntity* subSumA = new SumEntity(1, {new VariableEntity(2), new VariableEntity(3), new VariableEntity(2, 3), new VariableEntity("c", 0.1, 3)});
    SumEntity* subSumB = new SumEntity(1, {new VariableEntity(-2, 3), new VariableEntity("pi", -1), new VariableEntity(-4), new ScalarEntity(1.3)});

    Logger::important("Test merging scalars");
    testType<ScalarEntity>(printAndEvaluateFunction(sum), "Transormed SumEntity into ScalarEntity;", "Failed to transform scalar SumEntity into ScalarEntity!");

    Logger::important("Test merging variables");
    printAndEvaluateFunction(subSumA);
    subSumA->addElements({new VariableEntity(-2, 3), new VariableEntity("c", -0.1, 3)});
    testType<VariableEntity>(printAndEvaluateFunction(subSumA), "Transormed SumEntity into VariableEntity;",
                             "Failed to transform SumEntity into VariableEntity!");

    Logger::important("Test merging sums");
    sum->addElements({new VariableEntity("pi"), new VariableEntity(2, 3), new ScalarEntity(-0.3)});
    sum->addElements({subSumA, subSumB});
    subSumA->addElements({new VariableEntity("y", 1, -0.5), new VariableEntity("x", 1, 3)});
    printAndEvaluateFunction(sum);
    testCondition(sum->getSize() == 4, "Merged sums successfully", "Failed to merge sums!");
    delete sum, subSumA, subSumB;
}

void SumEntityTest::testMultiplier() {
    Logger::important("Test SumEntity - multiplier");
    BaseEntity* testEntity;
    Logger::important("Test multiplier 0");
    BaseEntity* sum = new SumEntity(0,{new ScalarEntity(-99), new VariableEntity("pi", 2, 30),
                                       new SumEntity(1, {new VariableEntity(1), new ScalarEntity(1000)})});
    printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 0");
    testCondition(*sum == *new ScalarEntity(0), "Multiplier 0 transformed to scalar 0", "Failed to transform multiplier 0 into scalar 0");
    delete sum;
    Logger::important("Test multiplier 1");
    sum = new SumEntity(1, {new ScalarEntity(1), new VariableEntity(1)});
    printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 1");
    testCondition(sum->getElement(0) == *(new ScalarEntity(1)) && sum->getElement(0) == *(new VariableEntity(1)),
                  "Multiplied by 1 correctly", "Failed to multiply by 1");
    delete sum;
    Logger::important("Test multiplier 2, function evaluation");
    sum = new SumEntity(2, {new ScalarEntity(1), new VariableEntity(1)});
    printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 2");
    testCondition(sum->getElement(0) == *(new ScalarEntity(2)) && sum->getElement(0) == *(new VariableEntity(2)),
                  "Multiplied by 2 correctly", "Failed to multiply by 2");
    delete sum;
    Logger::important("Test multiplier 2, raw value evaluation");
    sum = new SumEntity(2, {new ScalarEntity(1), new VariableEntity(1)});
    testEntity = printAndEvaluateValue(sum, 2, "Evaluated value");
    testCondition(testEntity->getElement(0) == *(new ScalarEntity(6)), "Evaluated for x=2 correctly", "Failed to evaluate value");
    delete sum, testEntity;
    Logger::important("Test multipliers on sum and subsum");
    sum = new SumEntity(3, {new ScalarEntity(1), new VariableEntity(2, 2),
            new SumEntity(2, {new ScalarEntity(1), new VariableEntity(2, 2)})});
    testEntity = printAndEvaluateValue(sum, 2, "Raw value evaluation for x=2");
    testCondition(testEntity->getElement(0) == *(new ScalarEntity(81)), "Correct result of 81", "Incorrect, should be 81");
    sum = printAndEvaluateFunction(sum, "Function evaluation");
    //TODO
    testCondition(sum->getElement(0) == *(new ScalarEntity(9)) && sum->getElement(1) == *(new VariableEntity(18, 2)),
                  "Correct result of 9+18x^2", "Incorrect, should be 9+18x^2");
    testCondition(printAndEvaluateValue(sum, 2, "Evaluating for x = 2")->getElement(0) == *(new ScalarEntity(81)),
                  "Correct result of 81", "Incorrect, should be 81");
    delete sum, testEntity;
}
