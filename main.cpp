#include<stdlib.h>
#include "entities/SumEntity.h"
#include "entities/ScalarEntity.h"
#include "entities/VariableEntity.h"

using namespace std;

void testInterfaces();

int main () {
    testInterfaces();
}

void testInterfaces() {
    SumEntity sum;
    ScalarEntity two = ScalarEntity(2);
    ScalarEntity twenty = ScalarEntity(20.00002);
    VariableEntity x = VariableEntity(1);
    VariableEntity xxx = VariableEntity(3);
    VariableEntity x2 = VariableEntity(1, 2);
    VariableEntity pi = VariableEntity("pi", 1, 1);
    VariableEntity twoPi2 = VariableEntity("pi", 2, 2);
    VariableEntity e0 = VariableEntity("e", 1, 0);
    VariableEntity zeroX = VariableEntity(0, 10);

    /*
    Logger::log(two.toString());
    Logger::log(twenty.toString());
    Logger::log(xxx.toString());
    Logger::log(x2.toString());
     */

    sum.addElements({&two, &twenty, &x, &xxx, &x2, &pi, &twoPi2, &e0, &zeroX});
    cout << sum.toString() << endl;
    sum.evaluateFunction();
    cout << sum.toString() << endl;

    cout << sum.evaluateValue(10)->toString() << endl;;
}