#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <exception>
#include <string.h>
#include <string>

using namespace std;

class ParseException: public std::exception {
    char *message;
public:
    const char *cause;
    const int index;

    ParseException(int index, const char *cause, const char *message = "Syntax error at "): index(index), cause(cause) {
        string strIndex = message + to_string(index);
        this->message = (char*)malloc(strIndex.size()+1);
        strcpy(this->message, strIndex.c_str());
    }

    const char *what() const noexcept override {
        string msg(message);
        msg = msg + ": " + cause;
        char *result = new char[msg.size()+1];
        result = strcpy(result, msg.c_str());
        return result;
    }

    const char *getGraphicIndicator() const {
        char *result = (char *)malloc((index+2) * sizeof(char));
        memset(result,'-', index);
        result[index] = '^';
        result[index+1] = '\0';
        return result;
    }
};

#endif //PARSEEXCEPTION_H
