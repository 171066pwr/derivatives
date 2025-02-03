#define LIMIT 200
#include "interface/BasicMenu.h"

int main () {
    BasicMenu menu = BasicMenu(LIMIT);
    menu.displayMenu();

    system("pause");
}
