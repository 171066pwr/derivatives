#ifndef DERIVATIVES_PARSABLEENTITY_H
#define DERIVATIVES_PARSABLEENTITY_H

#include <string>
#include <utility>
#include <vector>
#include "../entities/BaseEntity.h"

using namespace std;

class Parser {
    vector<string> symbols;
    BaseEntity *parse(const char *source, int index = 0) const;
public:
    explicit Parser(vector<string> symbols): symbols(std::move(symbols)){}
    BaseEntity *parseFromString(const string& str) const;
};

#endif //DERIVATIVES_PARSABLEENTITY_H
