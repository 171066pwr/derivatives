#include "BaseEntityTest.h"
#include "SumTest.h"
#include "VariableTest.h"
#include "MultiplicationTest.h"
#include "PowerTest.h"

void runTests();

int main () {
    runTests();
    system("pause");
}

void runTests() {
    BaseEntityTest baseEntityTest;
    SumTest sumTest;
    VariableTest variableTest;
    MultiplicationTest multiplicationTest;
    PowerTest powerTest;

    baseEntityTest.runTest("BaseEntity tests");
    variableTest.runTest("Variable tests");
    sumTest.runTest("Sum tests");
    multiplicationTest.runTest("Multiplication tests");
    powerTest.runTest("Power tests");
}