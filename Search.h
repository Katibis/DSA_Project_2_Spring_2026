/**
 * Search algorithms to process data for use by main
 */
#pragma once
#ifndef P2_SEARCH_H
#define P2_SEARCH_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Search {
private:
    string term;
    vector<pair<string, string>> data;
public:
    void loadData();
};



#endif //P2_SEARCH_H
