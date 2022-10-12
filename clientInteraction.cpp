#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
#include "clientInteraction.h"
#include "bank_info.h"
#include "extraFunctions.h"

using namespace std;

void clientInteraction::toClass(int tempLogin, int tempPassword, string tempSurname, string tempFirstname, double tempCash, bool tempIsValid){
    login = tempLogin;
    password = tempPassword;
    surname = tempSurname;
    firstname = tempFirstname;
    cash = tempCash;
    IsValid = tempIsValid;
}

bool clientInteraction::loginCheck(int possibleLogin,bool& chk){
    if ((possibleLogin == login) && (IsValid == 1)){
        return 1;
    }
    else if ((possibleLogin == login) && (IsValid == 0)){
        chk = 1;
        return 0;
    }
    return 0;
}

bool clientInteraction::passwordCheck(){
    int possiblePassword;
    for (int i = 0; i < 3; i++){
        cout << endl << 3 - i << " attempts available \nInput your password :";
        possiblePassword = safeCin(possiblePassword);
        if (possiblePassword == password){
            return 1;
        }
        cout << "\nWrong password!" << endl;
        Sleep(500);
    }
    return 0;
}

void clientInteraction::block(int clientsNumber, int clientBlockNumber){
    IsValid = 0;

    string newInfo = newInfoFunc(login,password,surname, firstname, cash, IsValid);

    dataChange("database.txt",newInfo,clientsNumber, clientBlockNumber);
}

bool clientInteraction::cashOut(int clientsNumber, int clNum){
    if (cash < 5){
        cout << "You do not have enough money to cash out\n";
        return 0;
    }
    else {
        int number;
        double Money = 0.0;
        int outMoney = 0;
        int tempAmount[7];
        bank_info bank;

        bank.getBankInfo(tempAmount);

        cout << "You have " << cash << " somevals \n";
        do{
            cout << "Enter the money you want to cash out: ";
            Money = safeCin(Money);
            if (Money > cash || Money < 5){
                cout << "Error. You entered the wrong money number\n";
            }
        } while (Money > cash || Money < 5);

        cout << "Our ATM could give:";

        for (int i = 0; i < bank.banknotesValuesAmount; i++){
            number = Money / bank.value[i];

            if (number > tempAmount[i]){
                number = tempAmount[i];
            }

            if (number == 0){
                continue;
            }

            cout << bank.value[i] << "x" << number << "  ";
            Money -= number * bank.value[i];

            tempAmount[i] -= number;

            outMoney += number * bank.value[i];
        }
        if (outMoney == 0){
            cout << "0 somevals" << endl;
            cout << "We are so sorry,but the ATM hasn't enough banknotes to withdraw your money\n\n";
            return 0;
        }

        cout << "\n\nIn total you'll get :" << outMoney << "somevals.\n\n";

        if (miniChoose()){
            cash -= outMoney;

            bank.changeBanknotes(tempAmount);

            string newInfo = newInfoFunc(login, password,surname, firstname, cash, IsValid);

            dataChange("database.txt",newInfo,clientsNumber,clNum);

            string info = "cash out. client:" + to_string(login) + " , sum:" + to_string(outMoney);
            transactionFixation(info);

            return 1;
        }
        else {
            cout << "As you wish so\n";
            return 0;
        }
    }
    return 1;
}

void clientInteraction::cashIn(int clientsNumber,int clNum){
    int tempAmount[7];
    int banknoteChoose;
    const double Limit = 10000;
    double MoneyIn = 0.0;

    bank_info bank;

    bank.getBankInfo(tempAmount);

    cout << "Enter:\n0 -> 500   1 -> 200   2 -> 100   3 -> 50   4 -> 20   5 -> 10   6 -> 5 \n7 -> stop\n";

    cout << "Put your money\n";

    do {
        cout << "Your choice is: ";
        banknoteChoose = safeCin(banknoteChoose);

        switch(banknoteChoose){
            case 0: case 1: case 2: case 3: case 4: case 5: case 6:{
                MoneyIn += bank.value[banknoteChoose];
                if (cash + MoneyIn > Limit){
                    MoneyIn -= bank.value[banknoteChoose];
                    cout << "You can't put this banknote because of " << Limit << " limit\n";
                    cout << "Try again w\ lower banknote or press 7 to exit the function\n\n";
                    Sleep(2200);
                    break;
                }
                tempAmount[banknoteChoose]++;
                cout << "Banknote " << bank.value[banknoteChoose] << " putted\n";
                break;
            }
            case 7:{
                if (MoneyIn < 5){
                    cout << "\nYou haven't put any banknotes.Try again later\n";
                    break;
                }
                cout << "\nIn total you putted " << MoneyIn << " somevals.\n";

                cash += MoneyIn;

                string newInfo = newInfoFunc(login, password,surname, firstname, cash, IsValid);

                dataChange("database.txt",newInfo,clientsNumber,clNum);

                bank.changeBanknotes(tempAmount);

                string info = "cash in . client:" + to_string(login) +" , sum:" + to_string(MoneyIn);
                transactionFixation(info);

                cout << "\nHave a nice day! :-) \n";
                break;
            }
            default:{
                cout << "Wrong number! Try again\n";
                break;
            }
        }
    }while (banknoteChoose != 7);
}

bool clientInteraction::payment(int clientsNumber,int clNum){
    if (cash <= 0){
        cout << "You have not got money to pay anything\n";
        return 0;
    }

    int payNum;
    cout << "Enter the paynum: ";
    payNum = safeCin(payNum);

    double payMoney;
    do{
        cout << "\nEnter the money you want to spend:";
        payMoney = safeCin(payMoney);
        if (payMoney <= 0 || payMoney > cash){
            cout << "You have not got enough money to pay it\n";
        }
    }while (payMoney <= 0 || payMoney > cash);

    if(miniChoose()){
        cash -= payMoney;
        string newInfo = newInfoFunc(login,password,surname,firstname,cash,IsValid);
        dataChange("database.txt",newInfo,clientsNumber,clNum);

        string info = "payment . client:" + to_string(login) + " , payNum:" + to_string(payNum) + " , sum:" + to_string(payMoney);
        transactionFixation(info);

        return 1;
    }
    else {
        cout << "As you wish so\n";

        return 0;
    }
}

double clientInteraction::getBalance(){
    return cash;
}

string clientInteraction::getFullname(){
    return surname + " " + firstname;
}

bool clientInteraction::transfer(clientInteraction& transfClient,int clientsNumber,int clNum,unsigned int transferNum){
    if (cash <= 0   ){
        cout << "You have not got enough money to transfer\n";
        return 0;
    }

    const double Limit = 10000;

    if(transfClient.getBalance() == Limit){
        cout << "This client can't get transfer because of the reached limit\n";
        return 0;
    }

    double transferMoney ;

    do{
        cout << "Enter the money you want to transfer: ";
        transferMoney = safeCin(transferMoney);
        if (transferMoney > cash || transferMoney <= 0){
            cout << "Wrong number! Try again\n\n";
        }
        else if (transferMoney + transfClient.getBalance() > Limit){
            cout << "You can't transfer so much money, because this will break the 10000 limit\n\n";
        }
    }while((transferMoney > cash) || (transferMoney <= 0) || (transferMoney + transfClient.getBalance() > Limit));

    if (miniChoose()){
        cash -= transferMoney;

        string newInfo = newInfoFunc(login,password,surname,firstname,cash,IsValid);
        dataChange("database.txt",newInfo,clientsNumber,clNum);

        transfClient.changeTransferClient(transferMoney,clientsNumber, transferNum);

        string info = "transfer. from:" + to_string(login) + " , to:" + to_string(transfClient.getLogin()) + " ,sum: " + to_string(transferMoney);
        transactionFixation(info);

        return 1;
    }
    else {
        cout << "As you wish so\n\n";
        return 0;
    }
}

void clientInteraction::changeTransferClient(int transferMoney, int clientsNumber, int transferNum){
    cash += transferMoney;

    string newInfo = newInfoFunc(login,password,surname,firstname,cash,IsValid);

    dataChange("database.txt", newInfo, clientsNumber, transferNum);
}

int clientInteraction::getLogin(){
    return login;
}
