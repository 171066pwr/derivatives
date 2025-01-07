cmake_minimum_required(VERSION 3.5)
project(Derivatives)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp entities/BaseEntity.cpp entities/BaseEntity.h entities/Parser.cpp entities/Parser.h entities/ScalarEntity.cpp entities/ScalarEntity.h entities/VariableEntity.cpp entities/VariableEntity.h utils/StringUtils.cpp utils/StringUtils.h entities/SumEntity.cpp entities/SumEntity.h utils/Logger.cpp utils/Logger.h)
add_executable(Derivatives ${SOURCE_FILES} entities/ScalarEntity.cpp entities/ScalarEntity.h)