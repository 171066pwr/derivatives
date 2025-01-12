#include "BaseEntityTest.h"
#include "SumEntityTest.h"
#include "VariableEntityTest.h"

void runTests();

int main () {
    runTests();
    system("pause");
}

void runTests() {
    BaseEntityTest baseEntityTest;
    SumEntityTest sumTest;
    VariableEntityTest variableTest;

    baseEntityTest.runTest("BaseEntity tests");
    variableTest.runTest("VariableEntity tests");
    sumTest.runTest("SumEntity tests");
}