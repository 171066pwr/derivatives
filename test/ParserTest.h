#ifndef PARSERTEST_H
#define PARSERTEST_H
#include "EntityTest.h"
#include "../interface/Parser.h"


class ParserTest: public EntityTest {
public:
    void runTest(const string &msg) override {
        EntityTest::runTest(msg);
        // testParseEmpty();
        // testParseScalar();
        // testParseVariable();
        testNoOperationMultiply();
    }

private:
    void testParseEmpty();
    void testParseScalar();
    void testParseVariable();
    void testNoOperationMultiply();

    void parseWithException(string input, Parser p);
    BaseEntity *parseWithoutException(string input, Parser p);
};

#endif //PARSERTEST_H
