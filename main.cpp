#include<stdlib.h>
#include "test/BaseEntityTest.h"
#include "test/SumEntityTest.h"

using namespace std;

void runTests();

int main () {
    runTests();
}

void runTests() {
    BaseEntityTest baseEntityTest;
    SumEntityTest sumTest;

    baseEntityTest.runTest();
    sumTest.runTest();
}
