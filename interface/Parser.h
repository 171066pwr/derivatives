#ifndef DERIVATIVES_PARSABLEENTITY_H
#define DERIVATIVES_PARSABLEENTITY_H

#include <string>
#include <utility>
#include <vector>
#include "../entities/BaseEntity.h"
#include "../entities/Variable.h"

using namespace std;

class Parser {
    enum Parsed {
        NOTHING,
        ENTITY,
        OPERATOR,
        END
    };

    enum Operator {
        EMPTY,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        POWER
    };

    enum Operation {
        NONE,
        MULTIPLICATION
    };

    struct Status {
        Parsed parsed;
        Operator op;
        BaseEntity *entity;

        Status() {
            parsed = NOTHING;
            op = EMPTY;
            entity = nullptr;
        }
    };

    vector<string> symbols;
    BaseEntity *parse(const char *source, int *index) const;
    Status parseNext(const char *source, int *index) const;
    double parseDouble(const char *source, int *index) const;
    string parseSymbol(const char *source, int *index) const;

public:
    explicit Parser(vector<string> symbols = Variable::getConstants()): symbols(std::move(symbols)){}
    BaseEntity *parseFromString(const string& str) const;
};

#endif //DERIVATIVES_PARSABLEENTITY_H
