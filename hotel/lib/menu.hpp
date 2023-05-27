#include <iostream>
#include <cctype>
#include "client/login-scrn.hpp"
#include "client/register-scrn.hpp"
#include "employer/employer-login.hpp"


void menu(char decision){

    char decision_acc;

    if(decision == '1'){
        do{
            system("cls");
            std::cout << "#####################\n";
            std::cout << "##  Client Screen  ##\n";
            std::cout << "#####################\n";
            std::cout << "Do u have a account? (y/n) or 'e' to exit\n";
            do{
                std::cin >> decision_acc;
                decision_acc = toupper(decision_acc);
            }while(decision_acc != 'Y' && decision_acc != 'N' && decision_acc != 'E');
            
            switch (decision_acc){
            case 'Y':
                login_scrn();
                break;
            case 'N':
                register_scrn();
                break;
            case 'E':
                std::cout << "Bye\n";
                break;
            default:
                std::cout << "Invalid decision\n";
                break;
            }
        }while(decision_acc != 'E');
    }
    else if (decision == '2'){
        employer_login();
    }
}

