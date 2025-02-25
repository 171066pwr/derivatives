#ifndef ENTITYTEST_H
#define ENTITYTEST_H

#include "../utils/Logger.h"
#include "../entities/BaseEntity.h"
#include "../entities/Scalar.h"
#include "../entities/Variable.h"
#include "../utils/NumberUtils.h"

class EntityTest {
public:
    virtual void runTest(const string &title){
        Logger::log("\n------------\t" + title + "        ------------");
    };

    template <typename T>
    void testType(BaseEntity *testEntity, const string &successMsg, const string &failMsg){
        testCondition((bool) dynamic_cast<T *>(testEntity), successMsg, failMsg);
    }

    void testCondition(bool condition, const string &successMsg, const string &failMsg) {
        if(condition)
            Logger::success(successMsg);
        else
            Logger::warn(failMsg);
    }

    void testValue(BaseEntity* testSubject, BaseEntity* expected) {
        if(*testSubject == *expected)
            Logger::success("correct");
        else
            Logger::warn("should be " + expected->toString());
    }

    BaseEntity *printAndEvaluateFunction(BaseEntity *&e, string comment = "") {
        BaseEntity *result;
        cout << (comment.empty() ? "" : comment + ":\n") << e->toString();
        cout << "   =    " << (result = e->evaluateFunction())->toString() << endl;
        if (e != result) {
            delete e;
            e = nullptr;
        }
        return result;
    }

    BaseEntity *printAndEvaluateValue(BaseEntity *&e, double x, string comment = "", const string &variable = "x") {
        BaseEntity *result;
        cout << (comment.empty() ? "" : comment + ":\n") << "[" + variable + " == " + NumberUtils::toString(x) + "]   " << e->toString();
        cout << "   =   " << (result = e->evaluateValue(x, variable))->toString() << endl;
        return result;
    }

    BaseEntity *printAndEvaluateDerivative(BaseEntity *&e, string comment = "", const string &variable = "x") {
        BaseEntity *result;
        cout << (comment.empty() ? "" : comment + ":\n") << "[d" + variable +"]   " << e->toString();
        cout << "   =   " << (result = e->evaluateDerivative(variable))->toString() << endl;
        return result;
    }

    void printComparison(BaseEntity *e1, BaseEntity *e2, string comment = "") {
        cout << (comment.empty() ? "" : comment + ":\n") << e1->toString();
        cout << "   =    " << e2->toString() << endl;
    }

    BaseEntity *replace(BaseEntity *&old, BaseEntity *current) {
        if(old != current) {
            delete old;
            old = nullptr;
        }
        return old = current;
    }

    void deleteMultiple(initializer_list<BaseEntity *> list) {
        for (auto e: list)
            delete e;
    }
};

#endif //ENTITYTEST_H
