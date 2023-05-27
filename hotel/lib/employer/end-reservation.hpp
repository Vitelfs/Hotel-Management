#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"


void endReservation(){

    std::fstream fileRoom("lib/hotel/room.json");
    nlohmann::json jsonData;
    bool clientFinded = false;
    if (fileRoom.is_open()) {
        fileRoom >> jsonData;
        for (const auto& category : jsonData["category"].items()) {
            std::cout << "Category: " << category.key() << std::endl;
            std::cout << "--------------------------" << std::endl;
            for (const auto& room : category.value()) {
                if(room["occupied"]){
                std::cout << "Room number: " << room["number"] << std::endl;
                std::cout << "Occupied by: " << room["occupiedBy"] << std::endl;
                std::cout << std::endl;
                }
            }
        }

        std::string clientName;

        std::cout << "Please enter the Cliente name to end his Revervation or type 'e' to exit:\n";
        std::getline(std::cin >> std::ws,clientName);

        for(int i = 0;i < clientName.size();i++){
            clientName[i] = tolower(clientName[i]);
        }
        if(clientName == "e"){
            system("cls");
            system("pause");
            return;
        }
        for (const auto& category : jsonData["category"].items()) {
            for (auto& room : category.value()) {
                if(room["occupiedBy"] == clientName){
                    room.erase("occupiedBy");
                    room.erase("start_date");
                    room.erase("end_date");
                    room["occupied"] = false;
                    clientFinded = true;
                    std::cout << clientName << "'s reservation closed!\n";
                    break;
                }
            }
        }
        if(!clientFinded){
            std::cout << "Client dont exist!\n";
            system("pause");
            return;
        }
        fileRoom.seekp(0);

        fileRoom << std::setw(4) << jsonData << std::endl;

        fileRoom.close();
    } else {
        std::cout << "Failed to open room.json" << std::endl;
    }
    system("pause");
    system("cls");
}
