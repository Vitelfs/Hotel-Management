#include <iostream>
#include <string>
#include "lib/menu.hpp"



int main(){

    char decision;
    std::string validade_decision;

    do{
        system("cls");
        std::cout << "What you are? '1' Client - '2' Employer or '3' to exit\n";
        std::cin >> decision;
        while(decision != '1' && decision != '2' && decision != '3'){
            std::cout << "Invalid Decision" << std::endl;
            std::cin >> decision;
        }
        menu(decision);
    }while(decision != '3');
}