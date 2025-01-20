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
    testValue(testEntity, expected);

    testEntity = multi->copy();
    testEntity = printAndEvaluateFunction(testEntity, "function evaluation");
    testValue(testEntity, expected);

    testEntity = replace(testEntity, multi->copy());
    testEntity->addElements({new Variable(2), new Variable("pi", 3)});
    expected = replace(expected, new Multiplication(90, {new Variable(), new Variable("pi")}));
    testEntity = printAndEvaluateFunction(testEntity, "Test add element and evaluate variables");
    testValue(testEntity, expected);
    deleteMultiple({testEntity, expected});

    Logger::important("Test merge multiplications");
    BaseEntity *subA = new Multiplication(1.0/5, {new Scalar(5), new Scalar(1), new Variable(2)});
    BaseEntity *subB = new Multiplication(2, {new Scalar(5), new Variable(), new Variable("y", 1.0/2)});
    testEntity = multi->copy();
    testEntity->addElements({subA, subB});
    replace(testEntity, printAndEvaluateFunction(testEntity));
    expected = new Multiplication(150, {new Variable("y"), new Power(2, new Variable())});
    testValue(testEntity, expected);
    deleteMultiple({testEntity, expected, multi}); // can't delete subA, subB - they were deleted during evaluation as subelements! Deleting again will result in segfault!
}

void MultiplicationTest::testMergeSums() {
    Logger::important("Test merge sums");
    BaseEntity *sumA = new Sum(1, {new Scalar(2), new Variable()});
    BaseEntity *sumB = new Sum(1, {new Scalar(-2), new Variable()});
    BaseEntity *testEntity = new Multiplication(1, {sumA->copy(), sumB->copy()});
    BaseEntity *expected = new Sum(1, {new Scalar(-4), new Power(2, new Variable())});
    testEntity = printAndEvaluateFunction(testEntity, "Evaluating sum multiplication");
    testValue(testEntity, expected);

    replace(testEntity, new Multiplication(
            1, {new Sum(1, {new Scalar(-2), new Variable()}), new Scalar(2)}));
    testEntity = printAndEvaluateFunction(testEntity, "Evaluate (-2 + x) * 2");
    replace(expected, new Sum(1, {new Scalar(-4), new Variable(2)}));
    testValue(testEntity, expected);

    BaseEntity *multi = new Multiplication(2, {new Scalar(2), new Scalar(3), new Variable(2)});
    replace(testEntity, multi->copy());
    testEntity->addElements({sumA->copy(), sumB->copy()});
    testEntity = printAndEvaluateFunction(testEntity, "Evaluated mixed entities");
    replace(expected, new Sum(1, {new Variable(-96), new Power(3, new Variable(), 24)}));
    testValue(testEntity, expected);
    deleteMultiple({testEntity, expected, multi});
}

void MultiplicationTest::testMergeVariablesAndPowers() {
    Logger::important("Test merge variables");
    BaseEntity *testSubject = new Multiplication(1, {new Variable(), new Variable(2), new Variable(3)});
    BaseEntity *expected = new Power(3, new Variable(), 6);
    testSubject = printAndEvaluateFunction(testSubject);
    testValue(testSubject, expected);

    Logger::important("Test merge variables with constants and scalars");
    replace(testSubject, new Multiplication(1, {new Scalar(2), new Variable(), new Variable(2), new Variable("pi"), new Variable(3)}));
    replace(expected, new Multiplication(12, {new Variable("pi"), new Power(3, new Variable())}));
    testSubject = printAndEvaluateFunction(testSubject);
    testValue(testSubject, expected);

    Logger::important("Test merge variables with power");
    replace(testSubject, new Multiplication(1, {new Variable(), new Power(3, new Variable(), 2), new Variable(2)}));
    replace(expected, new Power(5, new Variable(), 4));
    testSubject = printAndEvaluateFunction(testSubject);
    testValue(testSubject, expected);

    Logger::important("Test merge powers");
    replace(testSubject, new Multiplication(1, {new Power(3, new Variable(), 2), new Power(2, new Variable(), 2)}));
    testSubject = printAndEvaluateFunction(testSubject);
    testValue(testSubject, expected);
}

