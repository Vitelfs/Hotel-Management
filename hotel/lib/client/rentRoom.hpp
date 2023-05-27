#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "../nlohmann/json.hpp"
#include "../date/date.h"

void rentRoom(std::string clientName){

    std::fstream fileRoom("lib/hotel/room.json", std::ios::in | std::ios::out);
    nlohmann::json jsonData;

    if(fileRoom.is_open()){
        fileRoom >> jsonData;
        std::string category;

        std::cout << "Which room category do you want?" << std::endl;
        std::cout << "Basic: $50/day | Lux: $100/day | SuperLux: $150/day" << std::endl;
        
        do{
            std::getline(std::cin >> std::ws,category);  
            for(int i = 0;i < category.size();i++){
                category[i] = tolower(category[i]);
            }
            if(category != "basic" && category != "lux" && category != "superlux"){
                std::cout << "Invalid category!" << std::endl;
            }
        }while(category != "basic" && category != "lux" && category != "superlux");

        std::cout << "Set a start Date (Scruct: dd/mm/yyyy): ";
        std::string startDateStr;
        std::getline(std::cin, startDateStr);
        std::istringstream startDateStream(startDateStr);
        date::sys_time<std::chrono::milliseconds> startDate;
        startDateStream >> date::parse("%d/%m/%Y", startDate);

        std::cout << "How many days you will stay?" << std::endl;
        int days;
        std::cin >> days;

        auto endDate = startDate + date::days(days);
        nlohmann::json rooms = jsonData["category"][category];
        
        bool foundRoom = false;
        for (auto& room : rooms) {
            if (!room["occupied"]) {
                int roomPrice = room["price"].get<double>();
                int totalPrice = roomPrice * days;
                std::cout << "Your Room: " << room["number"] << std::endl;
                std::cout << "Total price for " << days << " days: $" << totalPrice << ",00" << std::endl;
                std::cout << "Start date: " << date::format("%d/%m/%Y", startDate) << std::endl;
                std::cout << "End date: " << date::format("%d/%m/%Y", endDate) << std::endl;
                foundRoom = true;
                room["occupied"] = true;
                room["start_date"] = date::format("%d/%m/%Y", startDate);
                room["end_date"] = date::format("%d/%m/%Y", endDate);
                room["occupiedBy"] = clientName;
                break;
            }
        }
        if (!foundRoom) {
            std::cout << "No available rooms in the selected category." << std::endl;
            return;
        }
        
        jsonData["category"][category] = rooms;
        
        fileRoom.seekp(0);

        fileRoom << std::setw(4) << jsonData << std::endl;

        fileRoom.close();

        system("pause");
        system("cls");
    }
}
