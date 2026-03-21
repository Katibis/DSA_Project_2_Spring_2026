#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Vector arrays of all the words that will be used to create website names.
std::vector<std::string> prefixes = {"Best ", "Excellent", "Awesome", "Great", "Good", "Mediocre", "Poor", "Terrible", "Horrible"};
std::vector<std::string> subjects = {""};
std::vector<std::string> suffixes = {"", "for programmers", "for grandma", "for mom", "for dad", "for grandpa", "for when you're sad", "for when you're happy", "for cats", "for dogs"};

// Function for generating the name of a website. Need to combine multiple words to created 2^32 combinations.
std::string getName(){
    
    return "";
};

int main(){
    /*
    // Loop for creating IPv4 address.
    std::stringstream IP;
    for(int i = 0; i < 9; i++){ 
        for(int j = 0; j < 9; j++){
            for(int k = 0; k < 9; k++){
                for(int l = 0; l < 25; l++){
                    IP << i << '.' << j << '.' << k << '.' << l;
                    std::string str = IP.str();
                    std::cout << str << " " << getName() << std::endl;  
                    IP.str("");    
                }
            }
        }
    }
    */
    std::cout << "Number of prefixes: " << prefixes.size() << std::endl;
    std::cout << "Number of subjects: " << subjects.size() << std::endl;
    std::cout << "Number of suffixes: " << suffixes.size() << std::endl;
    std::cout << "Total number of combinations: " << prefixes.size() * subjects.size() * suffixes.size() << std::endl;
    return 0;
}