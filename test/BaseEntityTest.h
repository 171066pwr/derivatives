#ifndef BASEENTITYTEST_H
#define BASEENTITYTEST_H
#include "EntityTest.h"

class BaseEntityTest: public EntityTest {
public:
    void runTest(const string &msg) override {
        EntityTest::runTest(msg);
        testOperators();
        testInterfaces();
    };
    
private:
    void testInterfaces();
    void testOperators();
};

#endif //BASEENTITYTEST_H
