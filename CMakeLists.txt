cmake_minimum_required(VERSION 3.5)
project(Derivatives)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++ -static -lpthread")

set(SOURCE_FILES main.cpp entities/BaseEntity.cpp entities/BaseEntity.h interface/Parser.cpp interface/Parser.h entities/Scalar.cpp entities/Scalar.h entities/Variable.cpp entities/Variable.h utils/NumberUtils.cpp utils/NumberUtils.h entities/Sum.cpp entities/Sum.h utils/Logger.h
        test/SumTest.cpp
        test/SumTest.h
        test/BaseEntityTest.cpp
        test/BaseEntityTest.h
        test/EntityTest.h
        test/MultiplicationTest.cpp
        test/MultiplicationTest.h
        entities/Multiplication.cpp
        entities/Multiplication.h entities/Power.cpp entities/Power.h
        entities/Fraction.cpp
        entities/Fraction.h entities/NaN.cpp entities/NaN.h
        entities/UnsupportedDerivative.cpp
        entities/UnsupportedDerivative.h
        interface/ParseException.h
        interface/BasicMenu.cpp
        interface/BasicMenu.h
)

add_executable(Derivatives ${SOURCE_FILES})

project(Tests)

set(TEST_FILES test/MainTest.cpp entities/BaseEntity.cpp entities/BaseEntity.h interface/Parser.cpp interface/Parser.h entities/Scalar.cpp entities/Scalar.h entities/Variable.cpp entities/Variable.h utils/NumberUtils.cpp utils/NumberUtils.h entities/Sum.cpp entities/Sum.h utils/Logger.h
        test/SumTest.cpp
        test/SumTest.h
        test/BaseEntityTest.cpp
        test/BaseEntityTest.h
        test/EntityTest.h
        test/MultiplicationTest.cpp
        test/MultiplicationTest.h
        entities/Multiplication.cpp
        entities/Multiplication.h test/VariableTest.cpp test/VariableTest.h entities/Power.cpp entities/Power.h test/PowerTest.cpp test/PowerTest.h
        entities/Fraction.cpp
        entities/Fraction.h entities/NaN.cpp entities/NaN.h test/FractionTest.cpp test/FractionTest.h
        test/TestReport.cpp
        test/TestReport.h
        test/DerivativesTest.cpp
        test/DerivativesTest.h
        entities/UnsupportedDerivative.cpp
        entities/UnsupportedDerivative.h
        interface/ParseException.h
)

add_executable(Tests ${TEST_FILES})