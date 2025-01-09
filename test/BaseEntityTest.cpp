#include "BaseEntityTest.h"
#include "../entities/SumEntity.h"
#include "../entities/ScalarEntity.h"
#include "../entities/VariableEntity.h"

void BaseEntityTest::testInterfaces() {
    Logger::important("Test BaseEntity interface functions - inheritance");
    SumEntity* sum = new SumEntity();
    SumEntity* subSumA = new SumEntity();
    SumEntity* subSumB = new SumEntity();
    SumEntity* subSubSum = new SumEntity();
    ScalarEntity* two = new ScalarEntity(2);
    ScalarEntity* twenty = new ScalarEntity(20.00002);
    ScalarEntity* ssBminus1 = new ScalarEntity(-1);
    ScalarEntity* sssMinus42 = new ScalarEntity(-42);
    ScalarEntity* sss21 = new ScalarEntity(21);
    VariableEntity* ssBx2 = new VariableEntity(1, 2);
    VariableEntity* sss2x = new VariableEntity(2);
    VariableEntity* sssMinus3x = new VariableEntity(-3);
    VariableEntity* x = new VariableEntity(1);
    VariableEntity* ssA3x = new VariableEntity(3);
    VariableEntity* x2 = new VariableEntity(1, 2);
    VariableEntity* pi = new VariableEntity("pi", 1, 1);
    VariableEntity* ssA2pi2 = new VariableEntity("pi", 2, 2);
    VariableEntity* ssAe0 = new VariableEntity("e", 1, 0);
    VariableEntity* ssA0X = new VariableEntity(0, 10);

    subSubSum -> addElements({sssMinus42, sss21, sss2x, sssMinus3x});
    subSumA -> addElements({ssA3x, ssA2pi2, ssAe0, ssA0X, subSubSum});
    subSumB -> addElements({ssBminus1, ssBx2});
    sum -> addElements({two, twenty, x, x2, pi, subSumA, subSumB});
    cout << sum -> toString() << endl;
    cout << sum -> evaluateValue(2) -> toString() << endl;
    sum -> evaluateFunction();
    cout << sum -> toString() << endl;
    sum -> evaluateFunction();
    cout << sum -> toString() << endl;
    cout << sum -> evaluateValue(2) -> toString() << endl << endl;
    delete sum, subSubSum, subSumA, subSumB;
}
