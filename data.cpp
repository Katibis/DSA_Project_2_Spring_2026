#include <iostream>
#include <string>
#include <sstream>
#include <vector>



// Function for generating the name of a website. Need to combine multiple words to created 2^32 combinations.
std::string getName(){
    

};

int main(){
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
    return 0;
}