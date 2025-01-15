cmake_minimum_required(VERSION 3.5)
project(Derivatives)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp entities/BaseEntity.cpp entities/BaseEntity.h entities/Parser.cpp entities/Parser.h entities/Scalar.cpp entities/Scalar.h entities/Variable.cpp entities/Variable.h utils/NumberUtils.cpp utils/NumberUtils.h entities/Sum.cpp entities/Sum.h utils/Logger.h
        test/SumTest.cpp
        test/SumTest.h
        test/BaseEntityTest.cpp
        test/BaseEntityTest.h
        test/EntityTest.h
        test/MultiplicationTest.cpp
        test/MultiplicationTest.h
        entities/Multiplication.cpp
        entities/Multiplication.h utils/ConsoleUtils.cpp utils/ConsoleUtils.h entities/Power.cpp entities/Power.h)

add_executable(Derivatives ${SOURCE_FILES})

project(Tests)

set(TEST_FILES test/MainTest.cpp entities/BaseEntity.cpp entities/BaseEntity.h entities/Parser.cpp entities/Parser.h entities/Scalar.cpp entities/Scalar.h entities/Variable.cpp entities/Variable.h utils/NumberUtils.cpp utils/NumberUtils.h entities/Sum.cpp entities/Sum.h utils/Logger.h
        test/SumTest.cpp
        test/SumTest.h
        test/BaseEntityTest.cpp
        test/BaseEntityTest.h
        test/EntityTest.h
        test/MultiplicationTest.cpp
        test/MultiplicationTest.h
        entities/Multiplication.cpp
        entities/Multiplication.h utils/ConsoleUtils.cpp utils/ConsoleUtils.h test/VariableTest.cpp test/VariableTest.h entities/Power.cpp entities/Power.h test/PowerTest.cpp test/PowerTest.h)

add_executable(Tests ${TEST_FILES})