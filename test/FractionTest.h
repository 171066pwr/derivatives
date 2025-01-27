#ifndef TESTS_FRACTIONTEST_H
#define TESTS_FRACTIONTEST_H


#include "EntityTest.h"

class FractionTest: public EntityTest {
public:
    void runTest(string msg) override {
        EntityTest::runTest(msg);
        testEvaluation();
    }

private:
    void testEvaluation();
};


#endif //TESTS_FRACTIONTEST_H
