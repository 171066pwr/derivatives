cmake_minimum_required(VERSION 3.5)
project(Derivatives)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp entities/BaseEntity.cpp entities/BaseEntity.h entities/Parser.cpp entities/Parser.h entities/ScalarEntity.cpp entities/ScalarEntity.h entities/VariableEntity.cpp entities/VariableEntity.h utils/StringUtils.cpp utils/StringUtils.h entities/SumEntity.cpp entities/SumEntity.h utils/Logger.h
        test/SumEntityTest.cpp
        test/SumEntityTest.h
        test/BaseEntityTest.cpp
        test/BaseEntityTest.h
        test/EntityTest.h
        test/MultiplicationEntityTest.cpp
        test/MultiplicationEntityTest.h
        entities/MultiplicationEntity.cpp
        entities/MultiplicationEntity.h utils/ConsoleUtils.cpp utils/ConsoleUtils.h)

add_executable(Derivatives ${SOURCE_FILES})

project(Tests)

set(TEST_FILES test/MainTest.cpp entities/BaseEntity.cpp entities/BaseEntity.h entities/Parser.cpp entities/Parser.h entities/ScalarEntity.cpp entities/ScalarEntity.h entities/VariableEntity.cpp entities/VariableEntity.h utils/StringUtils.cpp utils/StringUtils.h entities/SumEntity.cpp entities/SumEntity.h utils/Logger.h
        test/SumEntityTest.cpp
        test/SumEntityTest.h
        test/BaseEntityTest.cpp
        test/BaseEntityTest.h
        test/EntityTest.h
        test/MultiplicationEntityTest.cpp
        test/MultiplicationEntityTest.h
        entities/MultiplicationEntity.cpp
        entities/MultiplicationEntity.h utils/ConsoleUtils.cpp utils/ConsoleUtils.h)

add_executable(Tests ${TEST_FILES})