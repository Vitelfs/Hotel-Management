#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

void deleteAcc(std::string clientToDelete){


    std::cout << "Are u sure? '1' - yes | '2' - no\n";
    int decision;

    do{
        std::cin >> decision;
    }while(decision != 1 && decision != 2);

    if(decision == 1){
        std::ifstream deleteUser("lib/client/clientData.json");
        nlohmann::json jsonData;

        if(deleteUser.is_open()){
            deleteUser >> jsonData;

            for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
                if ((*it)["name"] == clientToDelete) {         
                    jsonData.erase(it);
                    break; 
                }
            }
        }
        deleteUser.close();
        
        std::ofstream updateData("lib/client/clientData.json");
        if (updateData.is_open()) {
            updateData << jsonData.dump(4);
            updateData.close();
            std::cout << "User deleted successfully." << std::endl;
        } 

        std::fstream roomFile("lib/hotel/room.json");
        nlohmann::json hotelDeleteUserData;

        if(roomFile.is_open()){
            roomFile >> hotelDeleteUserData;
            for (auto& category : hotelDeleteUserData["category"].items()) {
                for (auto& room : category.value()) {
                    if(room.contains("occupiedBy")){
                        if(room["occupiedBy"] == clientToDelete){
                            room.erase("occupiedBy");
                            room.erase("start_date");
                            room.erase("end_date");
                            room["occupied"] = false;
                            std::ofstream updateData("lib/hotel/room.json", std::ios::trunc);
                            if (updateData.is_open()) {
                                updateData << std::setw(4) << hotelDeleteUserData << std::endl;
                                updateData.close();
                                std::cout << clientToDelete << "'s reservation closed!\n";
                            }
                            break;
                        }
                    }
                }
            }
        }  
    }
}