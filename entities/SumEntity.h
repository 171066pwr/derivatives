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
    SumEntity(double multiplier, initializer_list<BaseEntity*> list): BaseEntity(multiplier, list) {};
    std::string toString();
    bool addElement(BaseEntity * element) override;
    BaseEntity* evaluateFunction() override ;
    BaseEntity* evaluateValue(double x) override;
    };

#endif //DERIVATIVES_SUMENTITY_H
