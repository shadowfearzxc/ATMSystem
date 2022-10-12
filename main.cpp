#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
#include "bank_info.h"
#include "clientInteraction.h"
#include "extraFunctions.h"

using namespace std;

int main()
{
    cout << "Welcome, this is the ATM of someBank!\n" << endl;

    int generalChoise;
    do{
        system("cls");
        cout << "kustanovich Bank ATM systems. All rights reserved\n";
        cout << "We care about you as ourselves \n\n";
        cout << "What do you prefer to do?" << endl;

        cout << generalFunctions();
        cout << "Your choice is: ";
        generalChoise = safeCin(generalChoise);

        switch(generalChoise){
            case 1:{
                int clientsNumber = clientsAmount();
                clientInteraction* clients = new clientInteraction[clientsNumber];

                setData(clients, clientsNumber);

                int possibleLogin;
                int clNum;

                cout << "Enter your login :";
                possibleLogin = safeCin(possibleLogin);

                if (!authorization(clients, clientsNumber, possibleLogin, clNum)){
                   cout << "Bad login error :-(" << endl;
                   Sleep(5000);
                }
                else {
                    int clientChoise;
                    do {
                        system("cls");

                        cout << "Welcome, " << clients[clNum].getFullname() << endl;
                        cout << "\nPlease, choose one of the next functions:\n";

                        cout << clientFunctions() << endl;

                        cout << "Your choice is: ";
                        clientChoise = safeCin(clientChoise);

                        switch(clientChoise){
                            case 1:{
                                if (clients[clNum].cashOut(clientsNumber, clNum)){
                                    cout << "Please, grab your money \n";
                                    Sleep(5000);
                                }
                                else{
                                    cout << "Try again later \n";
                                    Sleep(5000);
                                }
                                break;
                            }
                            case 2:{
                                clients[clNum].cashIn(clientsNumber,clNum);

                                cout << "\nOperation complete!\n";
                                Sleep(5000);
                                break;
                            }
                            case 3:{
                                cout << "Your actual balance: " << clients[clNum].getBalance() << " somevals.\n";
                                Sleep(4000);
                                break;
                            }
                            case 4:{
                                unsigned int transferLogin;
                                int transferNumber;

                                cout << "Enter the login to transfer\nOr press 0 to escape\nInput:";
                                transferLogin = safeCin(transferLogin);

                                if (transferLogin == 0){
                                    cout << "\nAs you wish so\n";
                                    Sleep(5000);
                                    break;
                                }

                                if (!transferLoginCheck(clients, transferLogin ,clientsNumber,clNum, transferNumber)){
                                    cout << "Bad login error.Try again later\n";
                                }
                                else{
                                    if (clients[clNum].transfer(clients[transferNumber],clientsNumber,clNum,transferNumber)){
                                        cout << "\nOperation complete\n";
                                    }
                                    else {
                                        cout << "\nTry again later\n";
                                    }
                                }
                                Sleep(5000);
                                break;
                            }
                            case 5:{
                                if (clients[clNum].payment(clientsNumber,clNum)){
                                    cout << "\nPayment succeed\n";
                                }
                                else {
                                    cout << "\nPayment failed\n";
                                }
                                Sleep(5000);
                                break;
                            }
                            case 6:{
                                cout << "\nLogging out...\n";
                                Sleep(3500);
                                break;
                            }
                            default:{
                                cout << "Error. There are no such functions. Try again\n\n" << endl;
                                Sleep(5000);
                                break;
                            }
                        }
                    }while(clientChoise != 6);
                }
                Sleep(2000);
                break;
            }
            case 2:{
                cout << "Todays exchange rates are\n";

                showRates();

                Sleep(5000);
                break;
            }
            case 3:{
                cout << "Thanks for being our client! We appreciate it." << endl;
                break;
            }
            default:{
                cout << "Error. There are no such functions. Try again\n\n" << endl;
                Sleep(3000);
                break;
            }
        }
    } while(generalChoise != 3);

    system("pause");
    return 0;
}
