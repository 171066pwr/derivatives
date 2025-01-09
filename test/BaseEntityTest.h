#ifndef BASEENTITYTEST_H
#define BASEENTITYTEST_H
#include "EntityTest.h"

class BaseEntityTest: public EntityTest {
public:
    void runTest() override {
        testInterfaces();
    };
private:
    void testInterfaces();
};

#endif //BASEENTITYTEST_H
