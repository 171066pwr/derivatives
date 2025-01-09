#ifndef SUMENTITYTEST_H
#define SUMENTITYTEST_H

#include "EntityTest.h"

class SumEntityTest: public EntityTest {
public:
    void runTest() override {
        testSum();
        testMultiplier();
    }

private:
    void testSum();
    void testMultiplier();
};

#endif //SUMENTITYTEST_H
