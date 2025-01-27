#include "SumTest.h"
#include "../entities/Sum.h"
#include "../entities/Scalar.h"
#include "../entities/Variable.h"
#include "../entities/Multiplication.h"

void SumTest::testEqualsOperators() {
    BaseEntity *original = new Variable("pi", 2);
    BaseEntity *other = new Variable(2);
    BaseEntity *sum = new Sum(2, {original, other});
    BaseEntity *sum2 = new Sum(2, {original->copy(), other->copy()});
    Logger::important("test == operator:");
    testCondition(*sum == *sum2, "success", "failure");
    delete sum2;
    sum2 = new Sum(2, {other, original->copy()});
    Logger::important("test != operator:");
    testCondition(*sum != *sum2, "success", "failure");
    delete original, other, sum, sum2;
}

void SumTest::testSum() {
    Logger::important("Test Sum - evaluation");
    Sum *sum = new Sum(1, {new Scalar(-5), new Scalar(5), Scalar::one()});
    Sum *subSumA = new Sum(1, {new Variable(2), new Variable(3), new Variable("c", 0.1)});
    Sum *subSumB = new Sum(1, {new Variable(-2), new Variable("pi", -1), new Variable(-4), new Scalar(1.3)});
    BaseEntity *expected = Scalar::one();
    BaseEntity *testEntity = sum->copy();
    Logger::important("Test merging scalars");
    testEntity = printAndEvaluateFunction(testEntity);
    testValue(testEntity, expected);

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
    testValue(testEntity, expected);
    deleteMultiple({testEntity, expected, sum});
}

void SumTest::testMultiplier0() {
    Logger::important("Test Sum - multiplier");
    Logger::important("Test multiplier 0");
    BaseEntity *sum = new Sum(0, {new Scalar(-99), new Variable("pi", 2),
                                        new Sum(1, {new Variable(1), new Scalar(1000)})});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 0");
    testCondition(*sum == *(Scalar::zero()), "Multiplier 0 transformed to scalar 0",
                  "Failed to transform multiplier 0 into scalar 0");
    delete sum;
}

void SumTest::testMultiplier1() {
    Logger::important("Test multiplier 1");
    BaseEntity *sum = new Sum(1, {Scalar::one(), new Variable(1)});
    BaseEntity *expected = new Sum(1, {Scalar::one(), new Variable()});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 1");
    testCondition(*sum == *expected,
                  "Multiplied by 1 correctly", "Failed to multiply by 1");
    delete sum, expected;
}

void SumTest::testMultiplier2() {
    Logger::important("Test multiplier 2, isFunction evaluation");
    BaseEntity *sum = new Sum(2, {Scalar::one(), new Variable(1)});
    BaseEntity *expected = new Sum(1, {new Scalar(2), new Variable(2)});
    sum = printAndEvaluateFunction(sum, "Evaluated Function, multiplier: 2");
    testCondition(*sum == *expected,
                  "Multiplied by 2 correctly", "Failed to multiply by 2");
    delete sum;
}

void SumTest::testMultiplierValue() {
    BaseEntity *testEntity;
    Logger::important("Test multiplier 2, raw value evaluation");
    BaseEntity *sum = new Sum(2, {Scalar::one(), new Variable(1)});
    testEntity = printAndEvaluateValue(sum, 2, "Evaluated value");
    testValue(testEntity, new Scalar(6));
    delete sum, testEntity;
}

void SumTest::testMultiplierNested() {
    Logger::important("Test multipliers on sum and subsum");
    BaseEntity *sum = new Sum(3, {Scalar::one(), new Variable(2),
                                        new Sum(2, {Scalar::one(), new Variable(2)})});
    BaseEntity *testEntity = printAndEvaluateValue(sum, 2, "Raw value evaluation for x=2");
    testValue(testEntity, new Scalar(45));
    sum = printAndEvaluateFunction(sum, "Function evaluation");
    testValue(sum, new Sum(1, {new Scalar(9), new Variable(18)}));
    testValue(printAndEvaluateValue(sum, 2, "Evaluating for x = 2"), new Scalar(45));
    deleteMultiple({sum, testEntity});
}

void SumTest::testMergeEdgeCase() {
//    Logger::important("Test merge elements of different type but equal contents");
//    BaseEntity *sum = new Sum(1, {new Fraction(1, {new Variable(), new Variable}), new Power()});
//    BaseEntity *testEntity = printAndEvaluateValue(sum, 2, "Raw value evaluation for x=2");
//    testValue(testEntity, new Scalar(45));
//    sum = printAndEvaluateFunction(sum, "Function evaluation");
//    testValue(sum, new Sum(1, {new Scalar(9), new Variable(18)}));
//    testValue(printAndEvaluateValue(sum, 2, "Evaluating for x = 2"), new Scalar(45));
//    deleteMultiple({sum, testEntity});
}
