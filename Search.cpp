/**
 * Source file for functions defined in Search.h
 */

#include "Search.h"
#include <regex>
using namespace std;

/**
 * Loads sites from data.txt into vector
 */
void Search::loadData() {
    regex reg ("[A-Z a-z]+"); // ensure string only contains letters and/or spaces
    ifstream inputFile("data.txt"); // data.txt must be in source directory
    while (!inputFile.eof()) {
        string line, ip, name, temp;
        getline(inputFile, line);
        istringstream ss(line);
        ss >> ip;
        getline(ss, temp, '"');
        getline(ss, name, '"');
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (regex_match(name, reg))
            this->data.emplace_back(ip, name);
    }
    inputFile.close();
}

int main() {

    return 0;
}