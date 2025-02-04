#ifndef MULTIPLICATIONENTITY_H
#define MULTIPLICATIONENTITY_H

#include "EntityTest.h"

class MultiplicationTest: public EntityTest {
public:
    void runTest(const string &msg) override {
        EntityTest::runTest(msg);
        testEqualsOperators();
        testMergeMultiplications();
        testMergeSums();
        testMergeVariablesAndPowers();
    }

private:
    void testEqualsOperators();
    void testMergeMultiplications();
    void testMergeSums();
    void testMergeVariablesAndPowers();
};

#endif //MULTIPLICATIONENTITY_H
