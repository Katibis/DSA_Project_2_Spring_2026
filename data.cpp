#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// Vector arrays of all the words that will be used to create website names.
std::vector<std::string> prefixes = {};
std::vector<std::string> subjects = {};
std::vector<std::string> suffixes = {""};

// Function for generating the name of a website. Need to combine multiple words to created 2^32 combinations.
std::string getName(){
    
    return "";
};

int main(){
    // Loading nounslist.txt
    std::fstream inFS;
    inFS.open("./nounlist.txt");
    std::string x;
    // Adding nouns to suffixes vector.
    while(!inFS.eof()){
        std::getline(inFS, x, '\n');
        suffixes.push_back(x);
    }
    // Remove ghost suffix.
    suffixes.pop_back();
    // Closing nounslist.txt
    inFS.close();
    
    // Loading morenouns.txt
    inFS.open("./morenouns.txt");
    // Adding nouns to subjects vector.
    while(!inFS.eof()){
        std::getline(inFS, x, '\n');
        subjects.push_back(x);
    }
    // Removing ghost subject.
    subjects.pop_back();
    inFS.close();

    // Loading adjectives.txt
    inFS.open("./adjectives.txt");
    // Adding adjectives to prefixes vector.
    while(!inFS.eof()){
        std::getline(inFS, x, '\n');
        prefixes.push_back(x);
    }
    // Removing ghost prefix.
    prefixes.pop_back();
    inFS.close();

    
    // Loop for creating IPv4 address.
    std::stringstream IP;
    for(int i = 0; i < 9; i++){ 
        for(int j = 0; j < 9; j++){
            for(int k = 0; k < 9; k++){
                for(int l = 0; l < 25; l++){
                    IP << i << '.' << j << '.' << k << '.' << l;
                    std::string str = IP.str();
                    std::cout << str << " \"" << getName() << "\"" << std::endl;  
                    IP.str("");    
                }
            }
        }
    }
    
    return 0;
}