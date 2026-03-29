/*
 * RNG program to create a list of websites and export it as a text file,
 * via randomly-generated IP addresses and lists of nouns sourced from the internet.
 * Coded by Samy Katibi.
 */
// WARNING: DO NOT RUN THIS CODE UNLESS NECESSARY.
// IT WILL TAKE SOME TIME TO RUN THIS CODE AND CREATE THE DATA.TXT FILE.

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// Vector arrays of all the words that will be used to create website names.
std::vector<std::string> prefixes = {};
std::vector<std::string> subjects = {};
std::vector<std::string> suffixes = {""};


int count = 0;


// Function for generating the name of a website. Need to combine multiple words to created 2^32 combinations.
std::string getName(std::vector<std::string>::iterator first, std::vector<std::string>::iterator second, std::vector<std::string>::iterator third){
    count++;
    return *first + " " + *second + " " + *third;
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

    // Intialize iterators for use
    std::vector<std::string>::iterator first = prefixes.begin();
    std::vector<std::string>::iterator second = subjects.begin();
    std::vector<std::string>::iterator third = suffixes.begin();
    
    // Create file to write data
    std::ofstream out ("data.txt", std::ofstream::out);

    // Loop for creating IPv4 address.
    std::stringstream IP;
    for(int i = 0; i < 2; i++){ 
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 256; k++){
                for(int l = 0; l < 256; l++){
                    IP << i << '.' << j << '.' << k << '.' << l;
                    std::string str = IP.str();
                    // Turn all the information into one line of website data.
                    std::string output = str + " \"" + getName(first, second, third) + "\"\n";
                    // Write the data to the file.
                    out << output.c_str();
                    // For keeping track of progress.
                    std::cout << count << std::endl;
                    third++;
                    if(third == suffixes.end()){
                        third = suffixes.begin();
                        second++;
                    }
                    if(count % 120 == 0){
                        second+= 1;
                    }
                    if(second == subjects.end()){
                        second = subjects.begin();
                        first++;
                    }
                    if(count % 1234 == 0){
                        first++;
                    }
                    if(first == prefixes.end()){
                        first = prefixes.begin();
                    }
                    IP.str("");    
                }
            }
        }
    }
    
    
    
    return 0;
}