#ifndef DERIVATIVES_SUMENTITY_H
#define DERIVATIVES_SUMENTITY_H

#include "BaseEntity.h"
#include "../utils/Logger.h"

class SumEntity: public BaseEntity {
    void mergeSums();
    void mergeScalars();
    void mergeVariables();
    void applyMultiplier();
public:
    SumEntity(double multiplier = 1): BaseEntity(multiplier) {};
    std::string toString();
    bool addElement(BaseEntity * element) override;
    bool addElements(std::initializer_list<BaseEntity*> list);
    BaseEntity* evaluateFunction() override ;
    BaseEntity* evaluateValue(double x) override;
    };

#endif //DERIVATIVES_SUMENTITY_H
