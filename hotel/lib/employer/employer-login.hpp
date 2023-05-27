#include <iostream>
#include <fstream>
#include "menu-employer.hpp"
#include "../nlohmann/json.hpp"


struct Employer{
    std::string username;
    std::string password;
    bool login_success = false;
};


void employer_login(){
    
    system("cls");
    std::ifstream file("lib/employer/employerData.json");
   
    if(file.is_open()){
        std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        nlohmann::json jsonData = nlohmann::json::parse(jsonString);
        Employer data;

        do{
            std::cout << "#######################\n";
            std::cout << "##   Login  Screen   ##\n";
            std::cout << "#######################\n";
            std::cout << "Username:" << std::endl;

            std::getline(std::cin >> std::ws,data.username);
            std::cout << "Enter your password:\n";
            
            char crypto;
            while ((crypto = _getch()) != '\r'){ 
                if (crypto == '\b') {
                    if (!data.password.empty()) {
                        data.password.pop_back();
                        std::cout << "\b \b";
                    }
                }else{
                    data.password.push_back(crypto);
                    std::cout << "*";
                }
            }

            for (const auto& registred_data : jsonData) {
                std::string username_registred = registred_data["username"];
                std::string password_registred = registred_data["password"];

                if (username_registred == data.username && password_registred == data.password) {
                    data.login_success = true;
                    break;
                }
            }
            if(data.login_success){
                std::cout << "\nLogin success!" << std::endl;
                Sleep(1500);
                file.close();
                system("cls");
                menuEmployer();
            }else{
                std::cout << "\nSorry, this account dont exist." << std::endl;
                data.username.clear();
                data.password.clear(); 
            }   
        system("cls");       
        }while(!data.login_success);
    }
}