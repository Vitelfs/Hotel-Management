#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"


void changePassword(std::string clientName){

    std::fstream clientData("lib/client/clientData.json");
    nlohmann::json jsonData;

    if(clientData.is_open()){
        
        clientData >> jsonData;

        for(auto& information : jsonData){
            if(information["name"] == clientName){
                std::cout << "Your actual password is: " << information["password"] << std::endl;
                std::cout << "You still want to change? (y/n)\n";
                char decision;

                do{
                    std::cin >> decision;
                }while(decision != 'y' && decision != 'n');

                if(decision == 'y'){
                    std::cout << "Enter your new password:\n";
                    std::string newPassword;
                    std::getline(std::cin >> std::ws,newPassword);
                    information["password"] = newPassword;

                    clientData.seekp(0);
                    clientData << std::setw(4) << jsonData << std::endl;
                    clientData.close();
                }
                else{
                    std::cout << "Okay! Bye <3\n";
                    return;
                }
            }
        }    
    }
}