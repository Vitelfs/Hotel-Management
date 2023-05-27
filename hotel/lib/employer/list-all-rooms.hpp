#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

void listAllRooms() {
    std::ifstream fileRoom("lib/hotel/room.json");
    nlohmann::json jsonData;
    if (fileRoom.is_open()) {
        fileRoom >> jsonData;
        for (const auto& category : jsonData["category"].items()) {
            std::cout << "Category: " << category.key() << std::endl;
            std::cout << "--------------------------" << std::endl;
            for (const auto& room : category.value()) {
                std::cout << "Room number: " << room["number"] << std::endl;
                std::cout << "Status Occupied: " << room["occupied"] << std::endl;
                std::cout << "Price: " << room["price"] << std::endl;
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "Failed to open room.json" << std::endl;
    }
    system("pause");
    system("cls");
}