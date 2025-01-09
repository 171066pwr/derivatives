#include "SumEntityTest.h"
#include "../entities/SumEntity.h"
#include "../entities/ScalarEntity.h"
#include "../entities/VariableEntity.h"

void SumEntityTest::testSum() {
    BaseEntity* testEntity;
    SumEntity* sum = new SumEntity();
    SumEntity* subSumA = new SumEntity();
    SumEntity* subSumB = new SumEntity();

    Logger::important("Test merging scalars");
    sum->addElements({new ScalarEntity(-5), new ScalarEntity(5), new ScalarEntity(1)});
    cout << sum->toString() << " = ";
    if(ScalarEntity* s = dynamic_cast<ScalarEntity*>(testEntity = sum -> evaluateFunction())) {
        cout << testEntity -> toString() << endl;
        Logger::success("Transormed SumEntity into ScalarEntity;");
    }
    else
        cout << testEntity -> toString() << endl;
        Logger::warn("Failed to transform scalar SumEntity into ScalarEntity!");

    Logger::important("Test merging variables");
    subSumA->addElements({new VariableEntity(2), new VariableEntity(3), new VariableEntity(2, 3), new VariableEntity("c", 0.1, 3)});
    cout << subSumA->toString() << " = " << subSumA -> evaluateFunction() -> toString() << endl;
    subSumA->addElements({new VariableEntity(-2, 3), new VariableEntity("c", -0.1, 3)});
    cout << subSumA->toString() << " = ";
    if(VariableEntity* s = dynamic_cast<VariableEntity*>(testEntity = subSumA->evaluateFunction())) {
        cout << testEntity -> toString() << endl;
        Logger::success("Transormed SumEntity into VariableEntity;");
    } else {
        cout << testEntity -> toString() << endl;
        Logger::warn("Failed to transform SumEntity into VariableEntity!");
    }

    Logger::important("Test merging sums");
    sum->addElements({new VariableEntity("pi"), new VariableEntity(2, 3), new ScalarEntity(-0.3)});
    sum->addElements({subSumA, subSumB});
    subSumA->addElements({new VariableEntity("y", 1, -0.5), new VariableEntity("x", 1, 3)});
    subSumB->addElements({new VariableEntity(-2, 3), new VariableEntity("pi", -1), new VariableEntity(-4), new ScalarEntity(1.3)});
    cout << sum->toString() << " = " << sum -> evaluateFunction() -> toString() << endl;
    if(sum->getSize() == 4) {
        Logger::success("Merged sums successfully");
    } else {
        Logger::warn("Failed to merge sums!");
    }
    delete testEntity, sum, subSumA, subSumB;
}

//TODO
void SumEntityTest::testMultiplier() {
    Logger::important("Test multiplier 0");

    Logger::important("Test multiplier 1");

    Logger::important("Test multiplier 2");

    Logger::important("Test multipliers on sum and subsum");

}
