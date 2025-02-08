#ifndef TESTREPORT_H
#define TESTREPORT_H
#include <map>
#include <string>
#include <vector>

using namespace std;

//TODO
class TestReport {
    struct ReportEntry {
        std::string name;
        vector<string> lines;
    };

    std::map<std::string, std::vector<std::string>> tests;

};



#endif //TESTREPORT_H
