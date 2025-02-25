#ifndef DERIVATIVES_SUMENTITY_H
#define DERIVATIVES_SUMENTITY_H

#include "BaseEntity.h"

class Sum: public BaseEntity {
private:
    void mergeSums();
    void mergeMultiplier();
    void mergeContents();
    void evaluateAndReplaceElement(BaseEntity *entity);

public:
    Sum(double multiplier = 1.0): BaseEntity(multiplier) {}
    Sum(double multiplier, initializer_list<BaseEntity *> list): BaseEntity(multiplier, list) {}
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString();
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x, string variable) override;
    BaseEntity *evaluateDerivative(string variable) override;
};

#endif //DERIVATIVES_SUMENTITY_H
