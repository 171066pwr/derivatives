#ifndef SUMENTITYTEST_H
#define SUMENTITYTEST_H

#include "EntityTest.h"

class SumEntityTest: public EntityTest {
public:
    void runTest() override {
        testSum();
        testMultiplier0();
        testMultiplier1();
        testMultiplier2();
        testMultiplierValue();
        testMultiplierNested();
    }

private:
    void testSum();
    void testMultiplier0();
    void testMultiplier1();
    void testMultiplier2();
    void testMultiplierValue();
    void testMultiplierNested();
};

#endif //SUMENTITYTEST_H
