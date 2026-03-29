/**
 * Source file for functions defined in Search.h
 */

#include "Search.h"
#include <fstream>
#include <regex>
#include <queue>
using namespace std;

/**
 * Loads sites from data.txt into vector.
 * All name strings are validated to confirm that they consist only of letters and spaces,
 * as well as converted to lowercase.
 */
void Search::loadData() {
    regex reg("[A-Za-z ]+"); // ensure site names comprise only letters and spaces
    ifstream inputFile("data.txt");

    while (!inputFile.eof()) {
        string line, ip, name, temp;
        getline(inputFile, line);
        istringstream ss(line);

        ss >> ip;
        getline(ss, temp, '"');
        getline(ss, name, '"');

        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (regex_match(name, reg)) {
            int index = data.size();
            data.emplace_back(ip, name);

            // Insert words into trie
            vector<string> words = splitWords(name);
            for (const string& w : words)
                insertWord(w, index);
        }
    }
    inputFile.close();
}

/**
 * Takes strings from data and splits them into component words.
 * @param s
 * @return Vector of strings separated from larger string
 */
vector<string> Search::splitWords(const string& s) const {
    vector<string> words;
    string word;

    for (char c : s) {
        if (isspace(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += tolower(c);
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

/**
 * Inserts word into trie.
 * @param word
 * @param index
 */
void Search::insertWord(const string& word, int index) {
    TrieNode* node = root;
    for (char c : word) {
        if (!node->children.count(&c))
            node->children[&c] = new TrieNode();
        node = node->children[&c];
    }
    node->websiteIndices.push_back(index);
}

vector<int> Search::lookup(const string& word) const {
    const TrieNode* node = root;
    for (char c : word) {
        if (!node->children.count(&c))
            return {};
        node = node->children.at(&c);
    }
    return node->websiteIndices;
}

/**
 * Searches trie (via min-heap) to get
 * @param query
 * @return Top 10 sites in the trie structure
 */
vector<string> Search::getTopSites_Trie(const string& query) {
    vector<string> qwords = splitWords(query);

    unordered_map<int,int> matchCount;  // website index → match score

    // Trie lookup for every query word
    for (const string& w : qwords) {
        vector<int> matches = lookup(w);
        for (int i : matches)
            matchCount[i]++;  // one point per matched word
    }

    // Min-heap for top 10
    priority_queue<
        pair<double,int>,
        vector<pair<double,int>>,
        greater<pair<double,int>>
    > pq;

    for (auto& p : matchCount) {
        int index = p.first;
        int hits = p.second;

        // convert to % score
        vector<string> siteWords = splitWords(data[index].second);
        double score = (double)hits / siteWords.size() * 100.0;

        if (pq.size() < 10)
            pq.emplace(score, index);
        else if (score > pq.top().first) {
            pq.pop();
            pq.emplace(score, index);
        }
    }

    // Extract in descending order
    vector<pair<double,int>> sorted;
    while (!pq.empty()) {
        sorted.push_back(pq.top());
        pq.pop();
    }
    sort(sorted.rbegin(), sorted.rend());

    vector<string> results;
    for (auto& p : sorted)
        results.push_back(data[p.second].second);

    return results;
}

/**
 * Similar to the above, but searches for similarity scores.
 * @param query
 * @return Top 10 sites most similar to the query, by percentage.
 */
vector<double> Search::getTopScores_Trie(const string& query) {
    vector<string> top = getTopSites_Trie(query);
    vector<double> scores;

    vector<string> qwords = splitWords(query);

    // Recompute scores (same as earlier)
    for (const string& siteName : top) {
        vector<string> siteWords = splitWords(siteName);

        int matches = 0;
        for (const string& w : qwords) {
            if (find(siteWords.begin(), siteWords.end(), w) != siteWords.end())
                matches++;
        }

        double score = (double)matches / siteWords.size() * 100.0;
        scores.push_back(score);
    }

    return scores;
}

/**
 * Calculates how similar a site's name is to the user's query.
 * @param query
 * @param site
 * @return Similarity score (as a percentage)
 */
double Search::computeSimilarity(const string& query, const string& site) const {
    vector<string> qwords = splitWords(query);
    vector<string> swords = splitWords(site);

    int hits = 0;
    for (const string& qw : qwords) {
        for (const string& sw : swords) {
            if (qw == sw) hits++;
        }
    }

    if (swords.empty()) return 0.0;
    return (double)hits / swords.size() * 100.0;
}

/**
 * Partitions data into blocks and searches each one, then compares the winners.
 * @param query
 * @return Top 10 sites as found by block search
 */
vector<string> Search::getTopSites_Block(const string& query) {
    const int BLOCK_SIZE = 10000;

    // Store pair of (score, index)
    vector<pair<double,int>> blockWinners;

    for (int start = 0; start < data.size(); start += BLOCK_SIZE) {
        int end = min(start + BLOCK_SIZE, (int)data.size());

        double bestScore = -1;
        int bestIndex = -1;

        // Linear search INSIDE the block only
        for (int i = start; i < end; i++) {
            double score = computeSimilarity(query, data[i].second);

            if (score > bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        }

        if (bestIndex != -1)
            blockWinners.emplace_back(bestScore, bestIndex);
    }

    // Sort block winners by best score
    sort(blockWinners.rbegin(), blockWinners.rend());

    // Extract top 10 sites
    vector<string> results;
    for (int i = 0; i < blockWinners.size() && i < 10; i++)
        results.push_back(data[blockWinners[i].second].second);

    return results;
}

/**
 *
 * @param query
 * @return Similar to getTopScores_Trie, but with the block search.
 */
vector<double> Search::getTopScores_Block(const string& query) {
    vector<string> topSites = getTopSites_Block(query);
    vector<double> scores;

    for (const string& site : topSites) {
        scores.push_back(computeSimilarity(query, site));
    }
    return scores;
}