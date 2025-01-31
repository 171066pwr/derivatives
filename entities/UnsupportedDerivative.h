#ifndef UNSUPPORTEDDERIVATIVE_H
#define UNSUPPORTEDDERIVATIVE_H
#include "BaseEntity.h"

class UnsupportedDerivative: public BaseEntity {
public:
    UnsupportedDerivative(BaseEntity *base, double multiplier = 1.0): BaseEntity(multiplier, {base}) {};
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override;;
    bool equalsExceptMultiplier(const BaseEntity *entity) override;;
    bool contentsEquals(const BaseEntity *entity) override;;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    bool addElement(BaseEntity * element) override;
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;

    BaseEntity* getBase();
};

#endif //UNSUPPORTEDDERIVATIVE_H
