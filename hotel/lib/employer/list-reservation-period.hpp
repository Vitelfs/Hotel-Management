#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"
#include <sstream>
#include "../date/date.h"


void listReservationPerPeriod(){

    std::ifstream listRoom("lib/hotel/room.json");

    if(listRoom.is_open()){
        nlohmann::json jsonData;
        listRoom >> jsonData;
        bool reservFind = false;

        std::cout << "Set a start Date (Scruct: dd/mm/yyyy): ";
        std::string startDateStr;
        std::getline(std::cin >> std::ws, startDateStr);

        std::istringstream startDateStream(startDateStr);
        date::sys_time<std::chrono::milliseconds> startDate;
        startDateStream >> date::parse("%d/%m/%Y", startDate);

        std::cout << "Set a end Date (Scruct: dd/mm/yyyy): ";
        std::string endDateStr;
        std::getline(std::cin >> std::ws, endDateStr);
        
        std::istringstream endDateStream(endDateStr);
        date::sys_time<std::chrono::milliseconds> endDate;
        endDateStream >> date::parse("%d/%m/%Y", endDate);

        for (const auto& category : jsonData["category"].items()) {
            for (const auto& reservation : category.value()) {
                if (reservation.contains("start_date") && reservation.contains("end_date")){
                    std::string reservationStartDateStr = reservation["start_date"];
                    std::istringstream reservationStartDateStream(reservationStartDateStr);
                    date::sys_days reservationStartDate;
                    reservationStartDateStream >> date::parse("%d/%m/%Y", reservationStartDate);

                    std::string reservationEndDateStr = reservation["end_date"];
                    std::istringstream reservationEndDateStream(reservationEndDateStr);
                    date::sys_days reservationEndDate;
                    reservationEndDateStream >> date::parse("%d/%m/%Y", reservationEndDate);

                    if (reservationStartDate >= startDate && reservationEndDate <= endDate) {
                        std::cout << "Reservation details:" << std::endl;
                        std::cout << "Category: " << category.key() << std::endl;
                        std::cout << "Start date: " << reservationStartDateStr << std::endl;
                        std::cout << "End date: " << reservationEndDateStr << std::endl;
                        if (reservation.contains("occupiedBy")) {
                            std::cout << "Occupied By: " << reservation["occupiedBy"] << std::endl;
                        }
                        std::cout << "Room number: " << reservation["number"] << std::endl;
                        std::cout << std::endl;
                        reservFind = true;
                    }
                }
            }
        }
        if(!reservFind){
            std::cout << "There's no reserves at that period!\n";       
        }
    }
    system("pause");
    system("cls");  
}
