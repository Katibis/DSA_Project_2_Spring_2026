/**
 * Search algorithms to process data for use by main
 */
#pragma once
#ifndef P2_SEARCH_H
#define P2_SEARCH_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Search {
private:
    string query;
    vector<pair<string, string>> data; //ip, site name
    struct TrieNode {
        unordered_map<string, TrieNode*> children;
        vector<int> websiteIndices;
    };
    TrieNode* root;
    vector<string> splitWords(const string& s) const;
    void insertWord(const string& word, int index);
    vector<int> lookup(const string& word) const;

public:
    Search() {root = new TrieNode();}
    void loadData();

    vector<string> getTopSites_Trie(const string& query);
    vector<double> getTopScores_Trie(const string& query);

    double computeSimilarity(const string& query, const string& site) const;
    vector<string> getTopSites_Block(const string& query);
    vector<double> getTopScores_Block(const string& query);
};



#endif //P2_SEARCH_H
