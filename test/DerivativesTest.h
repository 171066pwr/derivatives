#ifndef DERIVATIVESTEST_H
#define DERIVATIVESTEST_H
#include "EntityTest.h"

class DerivativesTest: public EntityTest {
public:
    void runTest(const string &msg) override {
        EntityTest::runTest(msg);
        testEvaluation();
        investigation();
    }

private:
    void testEvaluation();
    void investigation();
};

#endif //DERIVATIVESTEST_H
