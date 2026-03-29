#include <iostream>
#include "search.cpp"


int main(){
    std::cout << "Welcome to Gem search. Please enter your search query (Enter Exit to exit the program):" << std::endl;
    std::string query;
    while(true){
        std::cout << "Query: ";
        std::cin >> query;
        if(query == "Exit"){
            break;
        }
        std::cout << "Echo: " << query << std::endl;
    }
    return 0;
}