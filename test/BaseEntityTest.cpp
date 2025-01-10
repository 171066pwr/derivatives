#include "BaseEntityTest.h"
#include "../entities/SumEntity.h"
#include "../entities/ScalarEntity.h"
#include "../entities/VariableEntity.h"

void BaseEntityTest::testInterfaces() {
    Logger::important("Test BaseEntity interface functions - inheritance");
    Logger::important("Test super constructor with initializer list");
    SumEntity* subSumA = new SumEntity();
    SumEntity* subSumB = new SumEntity(1, {new ScalarEntity(-1), new VariableEntity(1, 2)});
    SumEntity* subSubSum = new SumEntity(1, {new ScalarEntity(-42), new ScalarEntity(21), new VariableEntity(2), new VariableEntity(-3)});
    Logger::important("Test addElements with initializer list");
    subSumA->addElements({new VariableEntity(3), new VariableEntity("pi", 2, 2), new VariableEntity("e", 1, 0), new VariableEntity(0, 10), subSubSum});
    SumEntity* sum = new SumEntity(1, {new ScalarEntity(2), new ScalarEntity(20.00002), new VariableEntity(1), new VariableEntity(1, 2),
                                       new VariableEntity("pi", 1, 1), subSumA, subSumB});
    printAndEvaluateValue(sum, 2, "Evaluating value without evaluating function");
    printAndEvaluateFunction(sum, "Evaluating function");
    printAndEvaluateFunction(sum, "Second evaluation (should be already in final form): ");
    printAndEvaluateValue(sum, 2, "Evaluating value after evaluating function");

    //test ev1 == ev2?
    delete sum, subSubSum, subSumA, subSumB;
}
