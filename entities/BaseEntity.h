#include <algorithm>

#include "../utils/NumberUtils.h"
#ifndef DERIVATIVES_BASEENTITY_H
#define DERIVATIVES_BASEENTITY_H

#include <string>
#include <vector>

using namespace std;

class BaseEntity {
protected:
    double multiplier = 1.0;
    bool isFunction = false;
    vector<BaseEntity *> elements;
    void deleteElement(BaseEntity *element);

    static BaseEntity *evaluateAndDelete(BaseEntity* entity);

public:
    BaseEntity(double multiplier = 1.0);
    BaseEntity(double multiplier, initializer_list<BaseEntity *> list);
    virtual ~BaseEntity();
    virtual BaseEntity *copy();
    virtual bool equals(const BaseEntity *entity);
    virtual bool equalsExceptMultiplier(const BaseEntity *entity);
    virtual bool contentsEquals(const BaseEntity *entity);

    virtual bool operator==(const BaseEntity& entity) {
        return equals(&entity);
    }

    virtual bool operator!=(const BaseEntity& entity) {
        return !(*this == entity);
    }

    /* some functions accept only 1 element (sin/ln, if something else is added then it's added to their sum/multiplication single element)
 * grouping of elements can take place when adding on the rules of the isFunction (i.e. scalars, variable of equal power, possible further)
 * it is even better that we won't have it all in one huge class but distributed across responsible classes
 */
    virtual bool addElement(BaseEntity *element);
    virtual bool addElements(initializer_list<BaseEntity *> list);
    /* todo - might be useful
     * virtual void sortElements();
     * */
    virtual std::string toString();
    virtual BaseEntity *evaluateFunction();
    virtual BaseEntity *evaluateValue(double x);
    virtual BaseEntity *evaluateDerivative();
    virtual bool updateAndGetIsFunction();

    template <typename T>
    static bool typeEquals(const BaseEntity *entity){
        const T *t = dynamic_cast<const T *>(entity);
        return t != nullptr;
    }

    template<typename T>
    static void deleteAndZero(T *&entity) {
        delete entity;
        entity = nullptr;
    }

    static BaseEntity *replace(BaseEntity *&old, BaseEntity *current) {
        if(old != current)
            delete old;
        return old = current;
    }

    void evaluateElementsValue(double x, BaseEntity *entity);

    double getMultiplier() const {
        return multiplier;
    }

    double getAndResetMultiplier() {
        double result = multiplier;
        multiplier = 1.0;
        return result;
    }

    bool isZero() {
        return NumberUtils::doubleEquals(multiplier, 0.0);
    }

    void multiplyByScalar(double scalar) {
        multiplier *= scalar;
    }

    void addToMultiplier(double scalar) {
        multiplier += scalar;
    }

    int getSize() {
        return elements.size();
    }

    bool getIsFunction() {
        return isFunction;
    }

    BaseEntity *getElement(int index) {
        return (index >= 0 && index < elements.size()) ? elements[index] : nullptr;
    }
};

#endif //DERIVATIVES_BASEENTITY_H
