#ifndef DERIVATIVES_SUMENTITY_H
#define DERIVATIVES_SUMENTITY_H

#include "BaseEntity.h"
#include "../utils/Logger.h"

class SumEntity: public BaseEntity {
public:
    std::string toString();

    bool addElement(BaseEntity * element) override;

    bool addElements(std::initializer_list<BaseEntity*> list);
    };

#endif //DERIVATIVES_SUMENTITY_H
