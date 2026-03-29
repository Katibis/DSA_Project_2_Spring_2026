#include <iostream>
#include "search.cpp"


int main(){
    std::cout << "Welcome to Gem search. Since this is the first time running the program, please wait a few seconds for the functions to initialize." << std::endl;
    std::string query;
    Search s = Search();
    s.loadData();
    std::vector<string> results;
    std::vector<double> percentages;
    while(true){
        std::cout << "Please enter your search query (Enter Exit to exit the program): ";
        getline(cin, query);
        if(query == "Exit"){
            break;
        }
        std::cout << "Please wait..." << std::endl;
        // Convert query into lowercase
        for(int i = 0; i < query.length(); i++){
            query[i] = tolower(query[i]);
        }
        results = s.getTopSites_Block(query);
        percentages = s.getTopScores_Block(query);
        std::cout << "Results:  Name:            Percentage Match with query:" << std::endl;
        for(int j = 0; j < 10; j++){
            std::cout << results[j] << " ----------- " << percentages[j] << "%" << std::endl;
        }
        
    }
    return 0;
}