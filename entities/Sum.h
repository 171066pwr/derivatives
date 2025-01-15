#ifndef DERIVATIVES_SUMENTITY_H
#define DERIVATIVES_SUMENTITY_H

#include "BaseEntity.h"
#include "../utils/Logger.h"

class Sum: public BaseEntity {
private:
    void mergeSums();
    void mergeScalars();
    void mergeVariables();
    void mergeMultiplications();
    void mergeMultiplier();
public:
    Sum(double multiplier = 1.0): BaseEntity(multiplier) {};
    Sum(double multiplier, initializer_list<BaseEntity *> list): BaseEntity(multiplier, list) {};
    BaseEntity *copy();
    bool equals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString();
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;
};

#endif //DERIVATIVES_SUMENTITY_H
