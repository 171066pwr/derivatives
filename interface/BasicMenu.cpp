#include "BasicMenu.h"
#include "Parser.h"
#include "../entities/Variable.h"

#include <iostream>
#include <cstdio>
using namespace std;

void BasicMenu::cls() {
    system("cls");
}

void BasicMenu::clearCIN() {
    std::cin.clear();
    std::cin.ignore(512, '\n');
}

BaseEntity *BasicMenu::parse(const std::string& input, const Parser& parser) {
    try{
        BaseEntity *entity = parser.parseFromString(input);
        return entity;
    } catch(const ParseException &e) {
        printf("\033[31m%s\033[0m\n%s\n", e.getGraphicIndicator(), e.what());
        return nullptr;
    }
}

bool BasicMenu::loadEntity() {
    char *str = new char[limit];
    string variable = "x";
    cout << "Wprowadz funkcje:\n";

    Parser parser = Parser();
    BaseEntity *entity = nullptr;
    while (entity == nullptr) {
        if (fgets(str,100, stdin) == NULL || strcmp(str, "\n") == 0)
            continue;
        entity = parse(str, parser);
    }
    StringBuffer buffer = StringBuffer(str);
    buffer.appendln("= " + entity->toString());
    BaseEntity::replace(entity, entity->evaluateFunction());
    buffer.appendln("= " + entity->toString());
    BaseEntity *derivative = entity->evaluateDerivative(variable);
    buffer.appendln("d" + variable + "\t:" + derivative->toString() + "\n");
    BaseEntity::replace(derivative, derivative->evaluateFunction());
    buffer.appendln("d" + variable + ":\t" + derivative->toString() + "\n");
    BaseEntity *value = nullptr;

    bool result = true;
    bool repeat = true;

    while (repeat && result) {
        ChoiceMenu choice(buffer.buffer);
        choice.addPosition("wylicz dla "  + variable + " =...");
        choice.addPosition("rozniczkuj po...");
        choice.addPosition("wprowadz nowa funkcje");
        choice.addPosition("wyjscie");

        int input = choice.readInput();
        double x;
        switch (input) {
            case 0:
                cout << variable << " = ";
                cin >> x;
                value = derivative->evaluateValue(x, variable);
                cout << buffer.appendln("[" + variable + " = " + NumberUtils::toString(x) + "]\t" + value->toString()) << endl;
                BaseEntity::deleteAndZero(value);
            break;
            case 1:
                cout << "rozniczkuj po... ";
                cin >> variable;
                buffer.appendln("zmienna rozniczkowania zmieniona na " + variable);
                BaseEntity::replace(derivative, entity->evaluateDerivative(variable));
                buffer.appendln("d" + variable + ":\t" + derivative->toString() + "\n");
                BaseEntity::replace(derivative, derivative->evaluateFunction());
                buffer.appendln("d" + variable + ":\t" + derivative->toString() + "\n");
            break;
            case 3:
                result = false;
            default:
                repeat = false;
        }
    }
    delete entity, delete derivative;
    return result;
}

void BasicMenu::display() {
    bool repeat = true;
    while (repeat) {
        cls();
        printf("Program liczy proste pochodne. Pozostalo do zaimplementowania:\n- funkcje trygonometryczne\n- logarytm\n");
        printf("- funkcja wykladnicza (mozna ja wprowadzic, ale wynikiem bedzie nieobliczona pochodna)\n");
        printf("- funkcja exp (sama stala 'e' jest rozpoznawana)\noraz zlozenie funkcji ogolem (bez w/w nie bylo potrzebne)\n\n");

        repeat = loadEntity();
    }
}
