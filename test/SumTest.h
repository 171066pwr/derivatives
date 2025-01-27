#ifndef SUMENTITYTEST_H
#define SUMENTITYTEST_H

#include "EntityTest.h"

class SumTest: public EntityTest {
public:
    void runTest(string msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testSum();
        testMultiplier0();
        testMultiplier1();
        testMultiplier2();
        testMultiplierValue();
        testMultiplierNested();
    }

private:
    void testEqualsOperators();
    void testSum();
    void testMultiplier0();
    void testMultiplier1();
    void testMultiplier2();
    void testMultiplierValue();
    void testMultiplierNested();
    void testMergeEdgeCase();
};

#endif //SUMENTITYTEST_H
