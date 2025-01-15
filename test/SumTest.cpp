#include "SumTest.h"
#include "../entities/Sum.h"
#include "../entities/Scalar.h"
#include "../entities/Variable.h"

void SumTest::testEqualsOperators() {
    BaseEntity *original = new Variable("pi", 2);
    BaseEntity *copy = original->copy();
    BaseEntity *other = new Variable(2);
    BaseEntity *sum = new Sum(2, {original, other});
    BaseEntity *sum2 = new Sum(2, {copy, other});
    Logger::important("test == operator:");
    testCondition(*sum == *sum2, "success", "failure");
    delete sum2;
    sum2 = new Sum(2, {other, copy});
    Logger::important("test != operator:");
    testCondition(*sum != *sum2, "success", "failure");
    delete original, copy, other, sum, sum2;
}

void SumTest::testSum() {
    Logger::important("Test Sum - evaluation");
    Sum *sum = new Sum(1, {new Scalar(-5), new Scalar(5), new Scalar(1)});
    Sum *subSumA = new Sum(1, {new Variable(2), new Variable(3), new Variable("c", 0.1)});
    Sum *subSumB = new Sum(1, {new Variable(-2), new Variable("pi", -1), new Variable(-4), new Scalar(1.3)});
    BaseEntity *expected = new Scalar(1);
    BaseEntity *testEntity = sum->copy();
    Logger::important("Test merging scalars");
    testCondition(*(testEntity = printAndEvaluateFunction(testEntity)) == *expected, "correct", "should be (1)");

    Logger::important("Test merging variables");
    replace(testEntity, subSumA->copy());
    testEntity = printAndEvaluateFunction(testEntity);
    testEntity->addElements({new Variable(-2), new Variable("c", -0.1)});
    testEntity = printAndEvaluateFunction(testEntity);
    replace(expected, new Variable(3));
    testCondition(*testEntity == *expected, "Transformed Sum into Variable",
                             "Failed to transform Sum into Variable!");

    Logger::important("Test merging sums");
    replace(testEntity, sum->copy());
    testEntity->addElements({new Variable("pi"), new Variable(2), new Scalar(-0.3)});
    testEntity->addElements({subSumA, subSumB});
    subSumA->addElements({new Variable("y"), new Variable(-1)});
    subSumB->addElements({new Variable("c", -0.1)});
    replace(expected, new Sum(1, {new Scalar(2), new Variable("y")}));
    testEntity = printAndEvaluateFunction(testEntity);
    testCondition(*testEntity == *expected, "Merged sums successfully", "should be (2+y)");
    delete testEntity, expected, sum, subSumA, subSumB;
}

void SumTest::testMultiplier0() {
    Logger::important("Test Sum - multiplier");
    Logger::important("Test multiplier 0");
    BaseEntity *sum = new Sum(0, {new Scalar(-99), new Variable("pi", 2),
                                        new Sum(1, {new Variable(1), new Scalar(1000)})});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 0");
    testCondition(*sum == *(new Scalar(0)), "Multiplier 0 transformed to scalar 0",
                  "Failed to transform multiplier 0 into scalar 0");
    delete sum;
}

void SumTest::testMultiplier1() {
    Logger::important("Test multiplier 1");
    BaseEntity *sum = new Sum(1, {new Scalar(1), new Variable(1)});
    BaseEntity *expected = new Sum(1, {new Scalar(), new Variable()});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 1");
    testCondition(*sum == *expected,
                  "Multiplied by 1 correctly", "Failed to multiply by 1");
    delete sum, expected;
}

void SumTest::testMultiplier2() {
    Logger::important("Test multiplier 2, isFunction evaluation");
    BaseEntity *sum = new Sum(2, {new Scalar(1), new Variable(1)});
    BaseEntity *expected = new Sum(1, {new Scalar(2), new Variable(2)});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 2");
    testCondition(*sum == *expected,
                  "Multiplied by 2 correctly", "Failed to multiply by 2");
    delete sum;
}

void SumTest::testMultiplierValue() {
    BaseEntity *testEntity;
    Logger::important("Test multiplier 2, raw value evaluation");
    BaseEntity *sum = new Sum(2, {new Scalar(1), new Variable(1)});
    testEntity = printAndEvaluateValue(sum, 2, "Evaluated value");
    testCondition(*testEntity == *new Scalar(6), "correct", "should be 6");
    delete sum, testEntity;
}

void SumTest::testMultiplierNested() {
    Logger::important("Test multipliers on sum and subsum");
    BaseEntity *testEntity;
    BaseEntity *sum = new Sum(3, {new Scalar(1), new Variable(2),
                                        new Sum(2, {new Scalar(1), new Variable(2)})});
    testEntity = printAndEvaluateValue(sum, 2, "Raw value evaluation for x=2");
    testCondition(*testEntity == *new Scalar(45), "Correct result of 45", "Incorrect, should be 45");
    sum = printAndEvaluateFunction(sum, "Function evaluation");
    testCondition(*sum == *new Sum(1, {new Scalar(9), new Variable(18)}),
                  "correct", "should be 9+18x");
    testCondition(*printAndEvaluateValue(sum, 2, "Evaluating for x = 2") == *new Scalar(45),
                  "correct", "should be 45");
    delete sum, testEntity;
}
