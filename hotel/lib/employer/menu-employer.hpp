#include <iostream>
#include <cctype>
#include "list-all-rooms.hpp"
#include "list-avaliable-rooms.hpp"
#include "list-all-clients.hpp"
#include "list-reservation-period.hpp"
#include "end-reservation.hpp"
#include "roomRegister.hpp"

void menuEmployer(){
    
    char decision_acc;
        do{      
            std::cout << "#####################\n";
            std::cout << "##  Employer Screen  ##\n";
            std::cout << "#####################\n";
            std::cout << "1-List All Rooms\n";
            std::cout << "2-List Avalible Rooms\n";
            std::cout << "3-Register a Room\n";
            std::cout << "4-List All Clients\n";
            std::cout << "5-List all reservations by period\n";
            std::cout << "6-End reservation\n";
            std::cout << "7-Exit\n";
            std::cin >> decision_acc;
            switch (decision_acc){
            case '1':
                system("cls");
                listAllRooms();
                break;
            case '2':
                system("cls");
                listAvaliableRooms();
                break;
            case '3':
                system("cls");
                roomRegister();
                break;
            case '4':
                system("cls");
                listAllClients();
                break;
            case '5':
                system("cls");
                listReservationPerPeriod();
                break;
            case '6':
                system("cls");
                endReservation();
                break;
            case '7':
                std::cout << "\nBye <3\n";
                system("pause");
                break;
            default:
                std::cout << "Invalid decision\n";
                break;
            }
    }while(decision_acc != '7');
    
}