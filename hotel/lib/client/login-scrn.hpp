#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "clientMenu.hpp"
#include "../nlohmann/json.hpp"

struct Login{
    std::string cpf;
    std::string password;
    bool login_sucess = false;
};
void login_scrn(){

    Login data;
    std::ifstream file("lib/client/clientData.json");
    nlohmann::json jsonData;

    if(file.is_open()){
        system("cls");
        std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        nlohmann::json jsonData = nlohmann::json::parse(jsonString);

        std::cout << "#######################\n";
        std::cout << "##   Login  Screen   ##\n";
        std::cout << "#######################\n";

        std::cout << "Enter your cpf:\n";
        std::cin >> data.cpf;
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
            std::string cpf_registred = registred_data["cpf"]; 
            std::string name = registred_data["name"];
            std::string password_registred = registred_data["password"];
            if (cpf_registred == data.cpf && password_registred == data.password) {
                data.login_sucess = true;
                if(data.login_sucess){
                std::cout << "\nLogin success!" << std::endl;
                std::cout << "Welcome Mr." << name << std::endl;
                file.close();
                Sleep(1500);
                system("cls"); 
                clientMenu(name);
                break;
                }
            }
        } 
        file.close();
        if(!data.login_sucess){
            std::cout << "\nSorry, this account dont exist." << std::endl;
            system("pause");
        } 
    }
}