#ifndef TESTS_VARIABLEENTITYTEST_H
#define TESTS_VARIABLEENTITYTEST_H

#include "EntityTest.h"

class VariableTest: public EntityTest {
public:
    void runTest(const string &msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testVariableEvaluation();
        testFunctionCheck();
    }
private:
    void testEqualsOperators();
    void testVariableEvaluation();
    void testFunctionCheck();
};

#endif //TESTS_VARIABLEENTITYTEST_H
