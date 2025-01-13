#ifndef TESTS_VARIABLEENTITYTEST_H
#define TESTS_VARIABLEENTITYTEST_H

#include "EntityTest.h"

class VariableEntityTest: public EntityTest {
public:
    void runTest(string msg) override {
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
