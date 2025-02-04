#include "Parser.h"

#include "ParseException.h"
#include "../entities/BaseEntity.h"
#include "../entities/Multiplication.h"
#include "../entities/Sum.h"
#include "../entities/Variable.h"

//2x + 3e
BaseEntity *Parser::parse(const char *source, int index) const {
    int depth = 0;
    char c;

    return new Multiplication(2.0, {new Variable(3), new Variable("y"), new Variable(), new Variable("y", 2), new Scalar(21.5)});

    // while(source[index] != '\0') {
    //     c = source[index];
    //     if (c >= '0' && c <= '9') {
    //         throw ParseException(index, source);
    //     }
    //     ++index;
    // }
    // return nullptr;
}

BaseEntity *Parser::parseFromString(const string& str) const {
    return Parser::parse(str.c_str(), 0);
}
