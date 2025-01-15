#ifndef MULTIPLICATIONENTITY_H
#define MULTIPLICATIONENTITY_H

#include "EntityTest.h"

class MultiplicationTest: public EntityTest {
public:
    void runTest(string msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testMergeMultiplications();
        testMergeSums();
    }

private:
    void testEqualsOperators();
    void testMergeMultiplications();
    void testMergeSums();

};

#endif //MULTIPLICATIONENTITY_H
