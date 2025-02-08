#ifndef BASICMENU_H
#define BASICMENU_H

#include <map>
#include <utility>
#include <conio.h>

#include "ParseException.h"

class Parser;
class BaseEntity;

class BasicMenu {
    struct WorkingEntity;

    WorkingEntity *entity = nullptr;
    const int limit;
    BaseEntity *parse(const std::string& input, const Parser& parser);
    bool loadEntity();

    struct WorkingEntity {
        BaseEntity* entity;
        BaseEntity* derivative;
        string diffBase;
    };

public:
    explicit BasicMenu(int limit): limit(limit) {}

    static void cls();
    static void clearCIN();

    void display();
};

struct StringBuffer {
    string buffer;

    explicit StringBuffer(const string& input): buffer(input) {}

    string append(string input) {
        buffer += input;
        return input;
    }

    string appendln(string input) {
        buffer += "\n" + input;
        return input;
    }

    void reset() {
        buffer.clear();
    }

    void print() const {
        printf("%s\n", buffer.c_str());
    }
};

struct ChoiceMenu {
    map<int, string> choices;
    string overheadText;
    int position;

    explicit ChoiceMenu(string overhead): position(0), overheadText(std::move(overhead)) {}

    int getAndResetPosition() {
        int result = position;
        position = 0;
        return result;
    }

    void resetText(string overhead) {
        overheadText = std::move(overhead);
        position = 0;
    }

    void addPosition(string position) {
        choices[(int)choices.size()] = std::move(position);
    }

    void printOverhead() {
        printf("%s\n", overheadText.c_str());
    }

    void displayMenu() {
        BasicMenu::cls();
        printOverhead();
        map<int, string>::iterator it;
        int i = 0;
        for (it = choices.begin(); it != choices.end(); it++, i++) {
            displayLine(it->second.c_str(), i == position);
        }
    }

    void displayLine(string description, bool isPosition) {
        if(isPosition) {
            printf("\033[92m->%s\033[0m\n", description.c_str());
        } else {
            printf("\033[93m%s\033[0m\n", description.c_str());
        }
    }

    int readInput() {
        char c;
        bool update = true;

        while (true) {
            if(update)
                displayMenu();
            update = false;
            switch ((c = _getch())) {
                case 72:
                    position = --position < 0 ? choices.size()-1 : position%choices.size();
                update = true;
                break;
                case 80:
                    position = (++position)%(choices.size());
                update = true;
                break;
                case 13:
                    BasicMenu::cls();
                    printOverhead();
                    return getAndResetPosition();
                default: break;
            }
        }
    }
};

#endif //BASICMENU_H
