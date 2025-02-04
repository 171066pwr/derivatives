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
        cout << e.getGraphicIndicator() << endl;
        cout << e.what() << endl;
        return nullptr;
    }
}

void BasicMenu::displayMenu() {
    char *str = new char[100];
    Parser parser = Parser(Variable::getConstants());
    BaseEntity *entity = nullptr;

    while (entity == nullptr) {
        cout << "Podaj: " << endl;
        if (fgets(str,100, stdin) == NULL || strcmp(str, "\n") == 0)
            continue;
        entity = parse(str, parser);
    }

    cout << endl << endl << entity->toString() << endl;

    system("pause");
}
