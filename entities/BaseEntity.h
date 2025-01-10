#ifndef DERIVATIVES_BASEENTITY_H
#define DERIVATIVES_BASEENTITY_H

#include <string>
#include <vector>

using namespace std;

class BaseEntity {
private:
    //std::string raw;
protected:
    double multiplier = 1;
    vector<BaseEntity*> elements;
public:
    BaseEntity(double multiplier = 1);
    BaseEntity(double multiplier, initializer_list<BaseEntity*> list);
    ~BaseEntity();

    /* some functions accept only 1 element (sin/ln, if something else is added then it's added to their sum/multiplication single element)
     * grouping of elements can take place when adding on the rules of the function (i.e. scalars, variable of equal power, possible further)
     * it is even better that we won't have it all in one huge class but distributed across responsible classes
     */
    bool operator==(const BaseEntity& entity) {
        bool result = multiplier == entity.multiplier;
        result = result && elements.size() == entity.elements.size();
        if(result)
            for(int i = 0; i < elements.size(); i++) {
                result = result && elements[i] == entity.elements[i];
            }
        return result;
    }

    bool operator!=(const BaseEntity& entity) {
        return !(*this == entity);
    }

    virtual bool addElement(BaseEntity* element);
    virtual bool addElements(initializer_list<BaseEntity *> list);
    virtual std::string toString();
    virtual BaseEntity* evaluateFunction();
    virtual BaseEntity* evaluateValue(double x);
    virtual BaseEntity* evaluateDerivative();

    void evaluateElementsValue(double x, BaseEntity *entity);
    void evaluateFunction(BaseEntity* entity);

    /*
    std::string getRaw() {
        return raw;
    }
     */

    double getMultiplier() {
        return multiplier;
    }

    void multiplyByScalar(double scalar) {
        multiplier *= scalar;
    }

    void invertSign() {
        multiplier = -multiplier;
    }

    int getSize() {
        return elements.size();
    }

    BaseEntity getElement(int index) {
        return (index >= 0 && index < elements.size()) ? *elements[index] : NULL;
    }
};

#endif //DERIVATIVES_BASEENTITY_H
