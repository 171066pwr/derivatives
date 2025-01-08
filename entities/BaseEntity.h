#ifndef DERIVATIVES_BASEENTITY_H
#define DERIVATIVES_BASEENTITY_H

#include <string>
#include <vector>

using namespace std;

class BaseEntity {
private:
    std::string raw;

protected:
    vector<BaseEntity*> elements;

public:
    BaseEntity();
    ~BaseEntity();

    std::string getRaw() {
        return raw;
    };

    /* some functions accept only 1 element (sin/ln, if something else is added then it's added to their sum/multiplication single element)
     * grouping of elements can take place when adding on the rules of the function (i.e. scalars, variable of equal power, possible further)
     * it is even better that we won't have it all in one huge class but distributed across responsible classes
     */
    virtual bool addElement(BaseEntity* element);
    virtual std::string toString();
    virtual BaseEntity* evaluateFunction();
    virtual BaseEntity* evaluateValue(double x);
    virtual BaseEntity* evaluateDerivative();

    void evaluateValue(double x, BaseEntity* entity);
    void evaluateFunction(BaseEntity* entity);
};


#endif //DERIVATIVES_BASEENTITY_H
