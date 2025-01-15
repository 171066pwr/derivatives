#ifndef ENTITYTEST_H
#define ENTITYTEST_H

#include "../utils/Logger.h"
#include "../entities/BaseEntity.h"
#include "../utils/NumberUtils.h"

class EntityTest {
public:
    virtual void runTest(string title){
        Logger::log("\n------------\t" + title + "        ------------");
    };

    template <typename T>
    void testType(BaseEntity *testEntity, string successMsg, string failMsg){
        testCondition((bool) dynamic_cast<T *>(testEntity), successMsg, failMsg);
    }

    void testCondition(bool condition, string successMsg, string failMsg) {
        if(condition)
            Logger::success(successMsg);
        else
            Logger::warn(failMsg);
    }

    BaseEntity *printAndEvaluateFunction(BaseEntity *&e, string comment = "") {
        BaseEntity *result;
        cout << (comment == "" ? "" : comment + ":\n") << e->toString();
        cout << "   =    " << (result = e->evaluateFunction())->toString() << endl;
        if (e != result) {
            delete e;
            e = nullptr;
        }
        return result;
    }

    BaseEntity *printAndEvaluateValue(BaseEntity *e, double x, string comment = "") {
        BaseEntity *result;
        cout << (comment == "" ? "" : comment + ":\n") << "[x == " + NumberUtils::toString(x) + "]   " << e->toString();
        cout << "   =   " << (result = e->evaluateValue(x))->toString() << endl;
        return result;
    }

    void printComparison(BaseEntity *e1, BaseEntity *e2, string comment = "") {
        cout << (comment == "" ? "" : comment + ":\n") << e1->toString();
        cout << "   =    " << e2->toString() << endl;
    }

    BaseEntity *replace(BaseEntity *&old, BaseEntity *current) {
        if(old != current)
            delete old;
        return old = current;
    }

    void deleteMultiple(initializer_list<BaseEntity *> list) {
        for (auto e: list)
            delete e;
    }
};

#endif //ENTITYTEST_H
