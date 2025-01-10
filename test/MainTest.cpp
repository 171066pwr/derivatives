#include "BaseEntityTest.h"
#include "SumEntityTest.h"

void runTests();

int main () {
    runTests();
    system("pause");
}

void runTests() {
    BaseEntityTest baseEntityTest;
    SumEntityTest sumTest;

    baseEntityTest.runTest();
    sumTest.runTest();
}