#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"


void seeReservs(std::string clientName){

    std::ifstream clientRoomData("lib/hotel/room.json");
    nlohmann::json jsonData;

    if(clientRoomData.is_open()){
        clientRoomData >> jsonData;
        bool reservFind = false;

        for (auto& category : jsonData["category"].items()) {
            
            for (auto& room : category.value()) {
                if(room["occupiedBy"] == clientName){
                    reservFind = true;
                    std::cout << "Category: " << category.key() << std::endl;
                    std::cout << "Room number: " << room["number"] << std::endl;
                    std::cout << "Start date:" << room["start_date"] << std::endl;
                    std::cout << "End date: " << room["end_date"] << std::endl;
                    std::cout << std::endl;
                }
            }
        }
        if(!reservFind){
            std::cout << "You have no reservs\n";
        }
    }
    system("pause");
    system("cls");
}