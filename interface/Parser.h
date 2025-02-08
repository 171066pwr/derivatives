#ifndef DERIVATIVES_PARSABLEENTITY_H
#define DERIVATIVES_PARSABLEENTITY_H

#include <string>
#include <utility>
#include <vector>
#include "../entities/BaseEntity.h"
#include "../entities/Variable.h"

using namespace std;

class Parser {
    vector<string> symbols;
    BaseEntity *parse(const char *source, int *index) const;
    double parseDouble(const char *source, int *index) const;
    string parseSymbol(const char *source, int *index) const;

    enum LastParsed {
        NOTHING,
        SCALAR,
        SYMBOL,
        ENTITY,
        MULTIPLICATION
    };

    enum Operation {
        NONE,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE
    };
public:
    explicit Parser(vector<string> symbols = Variable::getConstants()): symbols(std::move(symbols)){}
    BaseEntity *parseFromString(const string& str) const;
};

#endif //DERIVATIVES_PARSABLEENTITY_H
