#ifndef DERIVATIVES_SUMENTITY_H
#define DERIVATIVES_SUMENTITY_H

#include "BaseEntity.h"
#include "../utils/Logger.h"

class SumEntity: public BaseEntity {
private:
    void mergeSums();
    void mergeScalars();
    void mergeVariables();
    void applyMultiplier();
public:
    SumEntity(double multiplier = 1): BaseEntity(multiplier) {};
    SumEntity(double multiplier, initializer_list<BaseEntity*> list): BaseEntity(multiplier, list) {};
    BaseEntity* copy();
    bool equals(const BaseEntity* entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    bool operator==(const BaseEntity* entity) override {
        return equals(entity);
    }

    std::string toString();
    bool addElement(BaseEntity * element) override;
    BaseEntity* evaluateFunction() override ;
    BaseEntity* evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;
};

#endif //DERIVATIVES_SUMENTITY_H
