#include "BaseEntityTest.h"
#include "DerivativesTest.h"
#include "SumTest.h"
#include "VariableTest.h"
#include "MultiplicationTest.h"
#include "PowerTest.h"
#include "FractionTest.h"
#include "ParserTest.h"

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
    FractionTest fractionTest;
    DerivativesTest derivativesTest;
    ParserTest parserTest;

    baseEntityTest.runTest("BaseEntity tests");
    variableTest.runTest("Variable tests");
    sumTest.runTest("Sum tests");
    multiplicationTest.runTest("Multiplication tests");
    powerTest.runTest("Power tests");
    fractionTest.runTest("Fraction tests");
    derivativesTest.runTest("Derivatives tests");
    parserTest.runTest("Parser tests");
}