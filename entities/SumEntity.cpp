#include <memory>
#include "SumEntity.h"
#include "VariableEntity.h"

std::string SumEntity::toString() {
    string result = "(";
    for(auto element: elements) {
        result += element -> toString();
        if(element != elements.back())
            result += " + ";
    }
    result += ")";
    return result;
}

bool SumEntity::addElement(BaseEntity * element) {
    if(!BaseEntity::addElement(element)){
        Logger::log("Failed to add element: " + element -> toString());
        return false;
    }
    return true;
}

bool SumEntity::addElements(std::initializer_list<BaseEntity*> list) {
    for(BaseEntity * entity: list) {
        if(!addElement(entity))
            return false;
    }
    return true;
}

BaseEntity* SumEntity::evaluateFunction() {
    BaseEntity::evaluateFunction();

    for(vector<BaseEntity*>::iterator iter = elements.begin(); iter != elements.end(); iter++) {
        //if subelement is also sum, we can merge them.
        /*
        if(SumEntity* s = dynamic_cast<SumEntity*>(*iter)) {
            //elements.insert(this->elements.end(), s->elements.begin(), s->elements.end());
            //elements.erase(iter);
            //s->toString();
        }

        else if(VariableEntity* v = dynamic_pointer_cast<VariableEntity*>(*iter)) {
            elements.insert(this->elements.end(), s->elements.begin(), s->elements.end());
            elements.erase(iter);
         }
        else if(ScalarEntity* s = dynamic_pointer_cast<ScalarEntity*>(*iter)) {
            elements.insert(this->elements.end(), s->elements.begin(), s->elements.end());
            elements.erase(iter);
        }
        */
    }
}

BaseEntity* SumEntity::evaluateValue(double x) {
    BaseEntity* evaluated = new SumEntity();
    BaseEntity::evaluateValue(x, evaluated);

    return evaluated;
}