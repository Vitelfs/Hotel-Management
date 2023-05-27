#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "../nlohmann/json.hpp"

class Client{
private:
    std::string name;
    std::string cpf;
    std::string password;
public:
    Client (std::string client_name,std::string client_cpf, std::string client_password) : name(client_name), cpf(client_cpf), password(client_password){};
    std::string getName(){
        return name;
    };
    void setName(std::string client_name){
        name = client_name;
    }

    std::string getCpf(){
        return cpf;
    }
    void setCpf(std::string client_cpf){
        cpf = client_cpf;
    }

    std::string getPassword(){
        return password;
    }
    void setPassword(std::string client_password){
        password = client_password;
    }
};

void register_scrn() {
    system("cls");
    std::ifstream file("lib/client/clientData.json");
    nlohmann::json data;

    if (file.is_open()) {
        file >> data;
        file.close();
    }
    else {
        std::cout << "Failed to open the file\n";
        return;
    }

    std::string name, password,cpf;

    std::cout << "#######################\n";
    std::cout << "##  Register Screen  ##\n";
    std::cout << "#######################\n";

    std::cout << "Enter your full name:\n";
    std::getline(std::cin >> std::ws, name);

    for(int i = 0;i < name.size();i++){
        name[i] = tolower(name[i]);
    }

    std::cout << "Enter your cpf (Only numbers!): ";
    std::cin >> cpf;
    std::cout << "Enter your password:\n";
    std::cin >> password;

    Client registerClient(name, cpf, password);

    nlohmann::json clientData;
    clientData["name"] = registerClient.getName();
    clientData["cpf"] = registerClient.getCpf();
    clientData["password"] = registerClient.getPassword();

    data.push_back(clientData);

    std::ofstream outputFile("lib/client/clientData.json");
    if (outputFile.is_open()) {
        outputFile << data.dump(4) << std::endl;
        outputFile.close();
        std::cout << "Successfully Registered\n";
    }
    else {
        std::cout << "Failed to open the file for writing\n";
    }
}