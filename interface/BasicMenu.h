#ifndef BASICMENU_H
#define BASICMENU_H


#include "ParseException.h"

class Parser;
class BaseEntity;

class BasicMenu {
    const int limit;
    void cls();
    void clearCIN();
    BaseEntity *parse(const std::string& input, const Parser& parser);

public:
    explicit BasicMenu(int limit): limit(limit) {}
    void displayMenu();
};

#endif //BASICMENU_H
