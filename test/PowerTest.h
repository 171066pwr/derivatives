#ifndef TESTS_POWERTEST_H
#define TESTS_POWERTEST_H

#include "EntityTest.h"

class PowerTest: public EntityTest {
public:
    void runTest(const string &msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testEvaluation();
    }

private:
    void testEqualsOperators();
    void testEvaluation();
};

#endif //TESTS_POWERTEST_H
