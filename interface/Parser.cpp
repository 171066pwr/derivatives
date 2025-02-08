#include "Parser.h"

#include <string>
#include "ParseException.h"
#include "../entities/BaseEntity.h"
#include "../entities/Multiplication.h"
#include "../entities/Sum.h"
#include "../entities/Variable.h"

BaseEntity *Parser::parseFromString(const string& str) const {
    int index = 0;
    return Parser::parse(str.c_str(), &index);
}

//2x + 3e
BaseEntity *Parser::parse(const char *source, int *index) const {
    vector<BaseEntity *> entities;
    LastParsed lastParsed = NOTHING;
    LastParsed parsed = NOTHING;
    Operation operation = NONE;
    Operation lastOperation = NONE;
    BaseEntity *current = nullptr;

    char c;
    int i = *index;
    double d = 1.0;
    char *ptr = nullptr;
    while (source[i] != '\0') {
        c = source[i];

        if (c >= '0' && c <= '9') {
            d = parseDouble(source, &i);
            current = new Scalar(d);
            parsed = ENTITY;
        } else if ((c >= 'a' && c <= 'z')) {
            string symbol = parseSymbol(source, &i);
            current = new Variable(symbol);
            parsed = ENTITY;
        }
        else if (c == '(') {
            ++i;
            current = parse(source, &i);
            parsed = ENTITY;
        }
        else if (c == ')') {
            ++i;
            break;
        } else {
            ++i;
            continue;
        }

        if (lastOperation == NONE) {
            if (lastParsed == ENTITY) {
                BaseEntity *last = entities[entities.size() - 1];
                BaseEntity *multi = new Multiplication(1.0, {last, current});
                entities.pop_back();
                entities.push_back(multi);
                lastParsed = MULTIPLICATION;
            } else if (lastParsed == MULTIPLICATION) {
                BaseEntity *multi = entities[entities.size() - 1];
                multi->addElement(current);
            } else if (lastParsed == NOTHING) {
                entities.push_back(current);
                lastParsed = parsed;
            }
        }
    }

    if (entities.empty())
        throw ParseException(i, "Entity body missing");
    if (entities.size() == 1) {
        return entities[0];
    }

    BaseEntity *result;
    switch(operation) {
        case PLUS:
        case MINUS:
            result = new Sum(1.0);
            break;
        case MULTIPLY:
            result = new Multiplication(1.0);
            break;
        default:
            throw ParseException(i,"Invalid operation");
    }
    for (BaseEntity * entity : entities) {
        result->addElement(entity);
    }
    return result;
}

double Parser::parseDouble(const char *source, int *index) const {
    double d = 0;
    char * ptr = nullptr;
    try {
        d = std::strtod(source + *index, &ptr);
        if (ptr != nullptr)
            *index = ptr - source;
        return d;
    } catch (std::out_of_range &e) {
        throw new ParseException(*index, source, "Exception while parsing number:");
    } catch (std::invalid_argument &e) {
        throw new ParseException(*index, source, "Exception while parsing number:");
    }
}

string Parser::parseSymbol(const char *source, int *index) const {
    char * ptr = nullptr;
    int i = *index;
    while (source[i] >= 'a' && source[i] <= 'z' && source[i] != '\0')
        ++i;
    string symbol(source + *index, source + *index + i);
    //if symbol not recognized, then return just single letter
    for (auto e: symbols) {
        if (strcmp(e.c_str(), symbol.c_str()) == 0) {
            *index = *index + i;
            return symbol;
        }
    }
    symbol = string(source + *index, source + *index + 1);
    *index = *index + 1;
    return symbol;
}
