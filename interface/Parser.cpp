#include "Parser.h"

#include <algorithm>
#include <string>
#include "ParseException.h"
#include "../entities/BaseEntity.h"
#include "../entities/Fraction.h"
#include "../entities/Multiplication.h"
#include "../entities/Power.h"
#include "../entities/Sum.h"
#include "../entities/Variable.h"

BaseEntity *Parser::parseFromString(const string& str) const {
    int index = 0;
    return parse(str.c_str(), &index);
}

//2x + 3e
BaseEntity *Parser::parse(const char *source, int *index) const {
    vector<BaseEntity *> entities;
    Status prevStatus;
    Status status;
    Status nextStatus;

    // Parsed lastParsed = NOTHING;
    // Parsed parsed = NOTHING;
    Operation operation = NONE;
    Operation lastOperation = NONE;

    //int i = *index;

    while (status.parsed != END) {
        status = parseNext(source, index);

        if (status.parsed == NOTHING) {
            continue;
        }
        if (status.parsed == OPERATOR) {
            if (prevStatus.parsed == OPERATOR) {
                throw ParseException(*index, "Double operator");
            }
            if (prevStatus.parsed != ENTITY && status.op != MINUS) {
                throw ParseException(*index, "missing left operand");
            }
        }
        if (status.parsed == ENTITY) {
            if (prevStatus.parsed == ENTITY) {
                if (lastOperation == NONE) {
                    BaseEntity *multi = new Multiplication(1.0, {prevStatus.entity, status.entity});
                    entities.pop_back();
                    entities.push_back(multi);
                    lastOperation = MULTIPLICATION;
                } else if (lastOperation == MULTIPLICATION) {
                    BaseEntity *multi = entities[entities.size() - 1];
                    multi->addElement(status.entity);
                }
            } else if (prevStatus.parsed == OPERATOR) {
                switch (prevStatus.op) {
                    case MINUS:
                        status.entity->invertSign();
                    case PLUS:
                        entities.push_back(status.entity);
                        lastOperation = NONE;
                        break;
                    case MULTIPLY:
                        if (lastOperation == NONE) {
                            BaseEntity *multi = new Multiplication(1.0, {entities[entities.size() -1], status.entity});
                            entities.pop_back();
                            entities.push_back(multi);
                            lastOperation = MULTIPLICATION;
                        } else {
                            BaseEntity *multi = entities[entities.size() - 1];
                            multi->addElement(status.entity);
                        }
                        break;
                    case DIVIDE:
                        {
                            BaseEntity *fraction = new Fraction(status.entity, entities[entities.size() -1], 1.0);
                            entities.pop_back();
                            entities.push_back(fraction);
                        }
                        break;
                    case POWER:
                        {
                            if(lastOperation == MULTIPLICATION) {
                                BaseEntity *previous = entities[entities.size() - 1];
                                BaseEntity *base = previous->popLastElement();
                                previous->addElement(new Power(status.entity, base));
                            } else {
                                BaseEntity *base = entities[entities.size() - 1];
                                entities.pop_back();
                                entities.push_back(new Power(status.entity, base));
                            }
                        }
                        break;
                    default:
                        throw ParseException(*index, "Unknown operator");
                }
            } else {
                entities.push_back(status.entity);
            }
// if (lastOperation == NONE) {
//     if (lastParsed == ENTITY) {
//         BaseEntity *last = entities[entities.size() - 1];
//         BaseEntity *multi = new Multiplication(1.0, {last, current});
//         entities.pop_back();
//         entities.push_back(multi);
//         lastParsed = MULTIPLICATION;
//     } else if (lastParsed == MULTIPLICATION) {
//         BaseEntity *multi = entities[entities.size() - 1];
//         multi->addElement(current);
//     } else if (lastParsed == NOTHING) {
//         entities.push_back(current);
//         lastParsed = parsed;
//     }
// } else if (lastOperation == NONE) {}
        }

        if (status.parsed == END) {
            if (prevStatus.parsed == OPERATOR) {
                throw ParseException(*index, "Missing right operand");
            }
        }
        prevStatus = status;
    }


    if (entities.size() == 0) {
        throw ParseException(*index, "Empty expression");
    }
    if (entities.size() == 1) {
        return entities[0];
    }
    BaseEntity *result = new Sum();
    result->addElements(entities);
    return result;


    // BaseEntity *result;
    // switch(operation) {
    //     case PLUS:
    //     case MINUS:
    //         result = new Sum(1.0);
    //         break;
    //     case MULTIPLY:
    //         result = new Multiplication(1.0);
    //         break;
    //     default:
    //         throw ParseException(i,"Invalid operation");
    // }
    // for (BaseEntity * entity : entities) {
    //     result->addElement(entity);
    // }
    // return result;
}

Parser::Status Parser::parseNext(const char *source, int *index) const {
    char c = source[*index];
    Status status;
    int i = *index;

    if (c == '\0' || c == ')') {
        status.parsed = END;
    }
    else if (c == ' ' || c == '\n') {
        status.parsed = NOTHING;
    }
    else if (c >= '0' && c <= '9') {
        double d = parseDouble(source, &i);
        status.parsed = ENTITY;
        status.entity = new Scalar(d);
    }
    else if ((c >= 'a' && c <= 'z')) {
        string symbol = parseSymbol(source, &i);
        status.parsed = ENTITY;
        status.entity = new Variable(symbol);
    }
    else if (c == '(') {
        status.parsed = ENTITY;
        i++;
        status.entity = parse(source, &i);
    }
    else if (c == '+') {
        status.parsed = OPERATOR;
        status.op = PLUS;
    }
    else if (c == '-') {
        status.parsed = OPERATOR;
        status.op = MINUS;
    }
    else if (c == '*') {
        status.parsed = OPERATOR;
        status.op = MULTIPLY;
    }
    else if (c == '/') {
        status.parsed = OPERATOR;
        status.op = DIVIDE;
    }
    else if (c == '^') {
        status.parsed = OPERATOR;
        status.op = POWER;
    }
    else {
        throw ParseException(*index, source, "Illegal character ");
    }
    *index = status.entity == nullptr ? i+1 : i;
    return status;
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
        throw ParseException(*index, source, "Exception while parsing number:");
    } catch (std::invalid_argument &e) {
        throw ParseException(*index, source, "Exception while parsing number:");
    }
}

string Parser::parseSymbol(const char *source, int *index) const {
    char * ptr = nullptr;
    int i = *index;
    string symbol;
    while (source[i] >= 'a' && source[i] <= 'z' && source[i] != '\0') {
        ++i;
        symbol = string(source + *index, source + i);
        if (std::find(symbols.begin(), symbols.end(), symbol) != symbols.end()) {
            *index = i;
            return symbol;
        }
    }
    //if symbol not recognized, then return just single letter
    symbol = string(source + *index, source + *index + 1);
    *index += 1;
    return symbol;
}
