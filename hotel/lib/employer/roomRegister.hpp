#include <iostream>
#include <fstream>
#include "../nlohmann/json.hpp"

class Room{
private:
    std::string number;
    float price;
public:
    Room (std::string roomNumber, int roomPrice) : number(roomNumber), price(roomPrice){};
    std::string getNumber(){
        return number;
    }
    void setNumber(std::string roomNumber){
        number = roomNumber;
    }   
    int getPrice(){
        return price;
    }
    void setPrice(int roomPrice){
        price = roomPrice;
    }
};
void roomRegister(){
    std::fstream roomFile("lib/hotel/room.json");
    nlohmann::json jsonData;

    if(roomFile.is_open()){
        roomFile >> jsonData;
        std::string category,roomNumber;
        bool numberValid;

        std::cout << "Which room you will add? 'Basic' - 'Lux - 'SuperLux'\n";
        do{
            std::getline(std::cin >> std::ws,category);
            for(int i = 0;i < category.size();i++){
                category[i] = tolower(category[i]);
            }
            if(category != "basic" && category != "lux" && category != "superlux"){
                std::cout << "Invalid room's category, enter a valid one:\n";
            }
        }while(category != "basic" && category != "lux" && category != "superlux");
        std::cout << "Enter a room number:\n";

        do{ 
            std::cin >> roomNumber;
            numberValid = true;
             for (const auto& category : jsonData["category"].items()) {
                for (const auto& room : category.value()) {
                    if(room["number"] == roomNumber){
                        std::cout << "This number its already registred! Enter another\n";
                        numberValid = false;
                    }
                }
            }
        }while(!numberValid);

        nlohmann::json roomData;
        if(category == "basic"){
            Room registrateRoom(roomNumber,50);
            roomData["number"] = registrateRoom.getNumber();
            roomData["price"] = registrateRoom.getPrice();
            roomData["occupied"] = false;
        }
        else if(category == "lux"){
            Room registrateRoom(roomNumber,100);
            roomData["number"] = registrateRoom.getNumber();
            roomData["price"] = registrateRoom.getPrice();
            roomData["occupied"] = false;
        }
        else{
            Room registrateRoom(roomNumber,150);
            roomData["number"] = registrateRoom.getNumber();
            roomData["price"] = registrateRoom.getPrice();
            roomData["occupied"] = false;
        }
        jsonData["category"][category].push_back(roomData);
        roomFile.seekp(0);

        roomFile << std::setw(4) << jsonData << std::endl;

        roomFile.close();
    }
}