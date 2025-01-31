#ifndef DERIVATIVESTEST_H
#define DERIVATIVESTEST_H
#include "EntityTest.h"

class DerivativesTest: public EntityTest {
public:
    void runTest(string msg) override {
        EntityTest::runTest(msg);
        testEvaluation();
    }

private:
    void testEvaluation();
};

#endif //DERIVATIVESTEST_H
