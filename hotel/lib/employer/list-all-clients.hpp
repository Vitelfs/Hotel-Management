#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

void listAllClients(){

    std::fstream clientsData("lib/client/clientData.json");
    nlohmann::json jsonData;
    int clientNum = 1;
    if(clientsData.is_open()){
        clientsData >> jsonData;

        if (jsonData.empty()) {
        std::cout << "The client list is empty!" << std::endl;
        system("pause");
        system("cls");
        return;
        }
        else{
            for(const auto& client : jsonData){
                std::cout << "Client "<< clientNum << ":" << client["name"] << std::endl;
                clientNum++;
                std::cout << std::endl;
            }
            clientsData.close();
        }
    } 
    else {
        std::cout << "Failed to open clientData.json." << std::endl;
    }

    system("pause");
    system("cls");
}