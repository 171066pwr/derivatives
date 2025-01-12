#ifndef TESTS_VARIABLEENTITYTEST_H
#define TESTS_VARIABLEENTITYTEST_H

#include "EntityTest.h"

class VariableEntityTest: public EntityTest {
public:
    void runTest(string msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testVariableEvaluation();
    }
private:
    void testEqualsOperators();
    void testVariableEvaluation();
};


#endif //TESTS_VARIABLEENTITYTEST_H
