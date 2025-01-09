#include "Logger.h"

void Logger::warn(string s) {
    //TODO red console color (I just hope CLion console supports it) or other graphic distinction like *** ### ~~~ etc.
    cout << s << endl;
}

void Logger::important(string s) {
    //TODO yellow console color
    cout << s << endl;
}

void Logger::success(string s) {
    //TODO green console color
    cout << s << endl;
}
