#include "MultiplicationTest.h"
#include "../entities/Variable.h"
#include "../entities/Multiplication.h"
#include "../entities/Power.h"

void MultiplicationTest::testEqualsOperators() {
    BaseEntity *original = new Variable("pi", 2);
    BaseEntity *other = new Variable(2);
    BaseEntity *multi = new Multiplication(2, {original, other});
    BaseEntity *multi2 = new Multiplication(2, {original->copy(), other->copy()});
    Logger::important("test == operator:");
    testCondition(*multi == *multi2, "success", "failure");
    delete multi2;
    multi2 = new Multiplication(2, {other, original->copy()});
    Logger::important("test != operator:");
    testCondition(*multi != *multi2, "success", "failure");
    deleteMultiple({original, other, multi, multi2});
}

void MultiplicationTest::testMergeMultiplications() {
    Logger::important("Test merge scalars");
    BaseEntity *multi = new Multiplication(1, {new Scalar(5), new Scalar(3)});
    BaseEntity *testEntity = multi->copy();
    BaseEntity *expected = new Scalar(15);

    testEntity = printAndEvaluateValue(testEntity, 2, "raw evaluation");
    testCondition(*testEntity == *expected, "correct", "should be 15");

    testEntity = multi->copy();
    testEntity = printAndEvaluateFunction(testEntity, "function evaluation");
    testCondition(*testEntity == *expected, "correct", "should be 15");

    testEntity = replace(testEntity, multi->copy());
    testEntity->addElements({new Variable(2), new Variable("pi", 3)});
    expected = replace(expected, new Multiplication(90, {new Variable(), new Variable("pi")}));
    testCondition(*(testEntity = printAndEvaluateFunction(testEntity, "Test add element and evaluate variables")) == *expected, "correct", "should be 90(x*pi)");
    deleteMultiple({testEntity, expected});

    Logger::important("Test merge multiplications");
    BaseEntity *subA = new Multiplication(1.0/5, {new Scalar(5), new Scalar(1), new Variable(2)});
    BaseEntity *subB = new Multiplication(2, {new Scalar(5), new Variable(), new Variable("y", 1.0/2)});
    testEntity = multi->copy();
    testEntity->addElements({subA, subB});
    replace(testEntity, printAndEvaluateFunction(testEntity));
    expected = new Multiplication(150, {new Variable("y"), new Power(2, new Variable())});
    testCondition(*testEntity == *expected, "correct", "should be " + expected->toString());
    deleteMultiple({testEntity, expected, multi}); // can't delete subA, subB - they were deleted during evaluation as subelements! Deleting again will result in segfault!
}

void MultiplicationTest::testMergeSums() {
    Logger::important("Test merge sums");
    BaseEntity *sumA = new Sum(1, {new Scalar(2), new Variable()});
    BaseEntity *sumB = new Sum(1, {new Scalar(-2), new Variable()});
    BaseEntity *testEntity = new Multiplication(1, {sumA->copy(), sumB->copy()});
    BaseEntity *expected = new Sum(1, {new Scalar(-4), new Power(2, new Variable())});
    testEntity = printAndEvaluateFunction(testEntity, "Evaluating sum multiplication");
    testCondition(*testEntity == *expected, "correct", "should be " + expected->toString());

    replace(testEntity, new Multiplication(
            1, {new Sum(1, {new Scalar(-2), new Variable()}), new Scalar(2)}));
    testEntity = printAndEvaluateFunction(testEntity, "Evaluate (-2 + x) * 2");
    replace(expected, new Sum(1, {new Scalar(-4), new Variable(2)}));
    testCondition(*testEntity == *expected, "correct", "should be -4 + 2x");

    BaseEntity *multi = new Multiplication(2, {new Scalar(2), new Scalar(3), new Variable(2)});
    replace(testEntity, multi->copy());
    testEntity->addElements({sumA->copy(), sumB->copy()});
    testEntity = printAndEvaluateFunction(testEntity, "Evaluated mixed entities");
    replace(expected, new Sum(1, {new Variable(-96), new Multiplication(24, {new Variable(), new Variable(), new Variable()})}));
    testCondition(*testEntity == *expected, "correct", "should be (-96x + 24(x*x*x)");
    deleteMultiple({testEntity, expected, multi});
}

