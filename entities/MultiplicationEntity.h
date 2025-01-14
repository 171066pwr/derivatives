#ifndef MULTIPLICATIONENTITY_H
#define MULTIPLICATIONENTITY_H


#include "BaseEntity.h"

class MultiplicationEntity: public BaseEntity {
private:
    void mergeMultiplications();
    void mergeVariables();
    double mergeMultipliers();
public:
    MultiplicationEntity(double multiplier = 1.0): BaseEntity(multiplier) {};
    MultiplicationEntity(double multiplier, initializer_list<BaseEntity*> list): BaseEntity(multiplier, list) {};
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

#endif //MULTIPLICATIONENTITY_H
