#ifndef TESTS_POWERTEST_H
#define TESTS_POWERTEST_H


#include "EntityTest.h"

class PowerTest: public EntityTest {
public:
    void runTest(string msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testConstructorsAndToString();
    }

private:
    void testEqualsOperators();
    void testConstructorsAndToString();
};

#endif //TESTS_POWERTEST_H
