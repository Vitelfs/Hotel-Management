#include <iostream>
#include "deleteAcc.hpp"
#include "rentRoom.hpp"
#include "change-password.hpp"
#include "seeClientReservs.hpp"

void clientMenu(std::string clientName){

    int decision;
    
    do{
        std::cout << "#######################\n";
        std::cout << "##    CLIENT MENU    ##\n";
        std::cout << "#######################\n";

        std::cout << "1.Rent a room\n";
        std::cout << "2.Delete Account\n";
        std::cout << "3.See my Reservs\n";
        std::cout << "4.Change my password\n";
        std::cout << "5.Exit\n";
         std::cin >> decision;

        switch(decision){
            case 1:
                system("cls");
                rentRoom(clientName);
                break;
            case 2:
                system("cls");
                deleteAcc(clientName);
                system("pause");
                decision = 5;
                break;
            case 3:
                system("cls");
                seeReservs(clientName);
                break;
            case 4:
                system("cls");
                changePassword(clientName);
                break;
            default:
                std::cout << "Invalid Decision\n";
                break;
        }
    }while(decision != 5);
}