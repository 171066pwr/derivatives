#include "Parser.h"

#include "ParseException.h"
#include "../entities/BaseEntity.h"

//2x + 3e
BaseEntity *Parser::parse(const char *source, int index) const {
    int depth = 0;
    char c;

    while(source[index] != '\0') {
        c = source[index];
        if (c >= '0' && c <= '9') {
            throw ParseException(index, source);
        }
        ++index;
    }
    return nullptr;
}

BaseEntity *Parser::parseFromString(const string& str) const {
    return Parser::parse(str.c_str(), 0);
}
