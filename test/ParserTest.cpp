#include "ParserTest.h"

#include "../entities/Multiplication.h"
#include "../entities/Sum.h"
#include "../interface/ParseException.h"

void ParserTest::testParseEmpty() {
    Logger::important("Test parse empty string");
    Parser p = Parser();
    string input;
    parseWithException(input, p);

    input = "(()";
    parseWithException(input, p);
}

void ParserTest::testParseScalar() {
    Logger::important("Test parse scalar");
    Parser p = Parser();
    string input = "112";
    BaseEntity *expected = new Scalar(112.0);
    BaseEntity *result = p.parseFromString(input);
    printComparison(result, expected, "multi-digit integer");
    testValue(result, expected);

    input = "11.2";
    result = p.parseFromString(input);
    replace(expected, new Scalar(11.2));
    printComparison(result, expected, "multi-digit decimal");
    testValue(result, expected);

    deleteMultiple({result, expected});
}

void ParserTest::testParseVariable() {
    Logger::important("Test parse variable");
    Parser p = Parser();
    string input = "x";
    BaseEntity *expected = new Variable();
    BaseEntity *result = p.parseFromString(input);
    printComparison(result, expected, "x");
    testValue(result, expected);

    input = "y";
    result = p.parseFromString(input);
    replace(expected, new Variable("y"));
    printComparison(result, expected, "y");
    testValue(result, expected);

    input = "pi";
    result = p.parseFromString(input);
    replace(expected, new Variable("pi"));
    printComparison(result, expected, "multi-char symbol");
    testValue(result, expected);

    deleteMultiple({result, expected});
}

void ParserTest::testNoOperationMultiply() {
    Logger::important("Test default multiply without '*' sign");
    Parser p = Parser();
    string input = "2.1x";
    BaseEntity *expected = new Multiplication(1.0, {new Scalar(2.1), new Variable()});
    BaseEntity *result = parseWithoutException(input, p);
    if (result != nullptr) {
        printComparison(result, expected, input);
        testValue(result, expected);
    }

    input = "xy";
    replace(result, parseWithoutException(input, p));
    if (result != nullptr) {
        replace(expected, new Multiplication(1.0, {new Variable(), new Variable("y")}));
        printComparison(result, expected, input);
        testValue(result, expected);
    }

    input = "xpi";
    replace(result, parseWithoutException(input, p));
    if (result != nullptr) {
        replace(expected, new Multiplication(1.0, {new Variable(), new Variable("pi")}));
        printComparison(result, expected, input);
        testValue(result, expected);
    }

    input = "pix";
    replace(result, parseWithoutException(input, p));
    if (result != nullptr) {
        replace(expected, new Multiplication(1.0, {new Variable("pi"), new Variable()}));
        printComparison(result, expected, input);
        testValue(result, expected);
    }

    input = "xy2.1(x(1.2ypi)";
    replace(result, parseWithoutException(input, p));
    if (result != nullptr) {
        replace(expected, new Multiplication(1.0, {new Variable(), new Variable("y"),
            new Multiplication(1.0, {new Variable("x"), new Multiplication(1.0,
                {new Scalar(1.2), new Variable("y"), new Variable("pi")})
            })
        }));
        printComparison(result, expected, input);
        testValue(result, expected);
    }

    deleteMultiple({result, expected});
}

void ParserTest::parseWithException(string input, Parser p) {
    try {
        BaseEntity *result = p.parseFromString(input);
    } catch (ParseException &e) {
        Logger::success(input + ": " + e.what());
        return;
    }
    Logger::warn("Should throw exception on input: " + input);
}

BaseEntity *ParserTest::parseWithoutException(string input, Parser p) {
    try {
        return p.parseFromString(input);
    } catch (ParseException &e) {
        Logger::warn(input + ": " + e.what());
        return nullptr;
    }
}
