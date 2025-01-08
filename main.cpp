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
    SumEntity* sum = new SumEntity();
    SumEntity* subSum = new SumEntity();
    ScalarEntity* two = new ScalarEntity(2);
    ScalarEntity* twenty = new ScalarEntity(20.00002);
    VariableEntity* x = new VariableEntity(1);
    VariableEntity* xxx = new VariableEntity(3);
    VariableEntity* x2 = new VariableEntity(1, 2);
    VariableEntity* pi = new VariableEntity("pi", 1, 1);
    VariableEntity* twoPi2 = new VariableEntity("pi", 2, 2);
    VariableEntity* e0 = new VariableEntity("e", 1, 0);
    VariableEntity* zeroX = new VariableEntity(0, 10);

    /*
    Logger::log(two.toString());
    Logger::log(twenty.toString());
    Logger::log(xxx.toString());
    Logger::log(x2.toString());
     */
    subSum -> addElements({xxx, twoPi2, e0, zeroX});
    sum -> addElements({two, twenty, x, x2, pi, subSum});
    cout << sum -> toString() << endl;
    sum -> evaluateFunction();
    cout << sum -> toString() << endl;

    cout << sum -> evaluateValue(10) -> toString() << endl;;
}