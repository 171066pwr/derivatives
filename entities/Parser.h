#ifndef DERIVATIVES_PARSABLEENTITY_H
#define DERIVATIVES_PARSABLEENTITY_H

#include <stdlib.h>
#include <string>
#include "BaseEntity.h"

using namespace std;

class Parser {
public:
    BaseEntity parse(string source);
};

#endif //DERIVATIVES_PARSABLEENTITY_H
