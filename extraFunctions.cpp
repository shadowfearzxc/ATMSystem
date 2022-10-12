#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
#include "extraFunctions.h"
#include "clientInteraction.h"

using namespace std;

bool authorization(clientInteraction* cl, int clientsNumber, int possibleLogin, int& clNum) {
    bool block_checker = 0;
	for (int i = 0; i < clientsNumber; i++) {
		if (cl[i].loginCheck(possibleLogin,block_checker)) {
            if (cl[i].passwordCheck()){
                clNum = i;
                return 1;
            }
            else {
                cl[i].block(clientsNumber, i);
                cout << "Dear " << cl[i].getFullname() << ". We blocked your account due to fails." << endl;
                cout << "Please contact your local office to resolve the problem" << endl;
                return 0;
            }
		}
		else if(block_checker){
            cout << "Dear " << cl[i].getFullname() << ". Your account is blocked." << endl;
            cout << "Please contact your local office to resolve the problem" << endl;
            break;
		}
	}
	return 0;
}

bool transferLoginCheck(clientInteraction* cl, int transferLogin, int clientsNumber, int clNum, int& transferNumber){
    bool block_checker = 0;
    for(int i = 0; i < clientsNumber; i++){
        if (cl[i].loginCheck(transferLogin,block_checker)){
            if (transferLogin != cl[clNum].getLogin()){
                transferNumber = i;
                return 1;
            }
            else {
                cout << "You can't transfer to yourself.\n";
                break;
            }
        }
        else if(block_checker){
            cout << "This client is blocked right now\n";
            break;
        }
    }
    return 0;
}

void dataChange(string file, string info,int dataNumbers, int dataChangeNumber){
    ifstream indata(file);
    string buffer[dataNumbers];

    for (int i = 0; i < dataNumbers ; i++){
        getline(indata, buffer[i]);
    }
    indata.close();

    buffer[dataChangeNumber] = info;

    ofstream outdata(file);
    for (int i = 0; i < dataNumbers; i++){
        outdata << buffer[i] << "\n";
    }
    outdata.close();
}

int clientsAmount(){
	int clientsAmount = 0;
	char buffer;

	fstream data_check("database.txt");

	while (data_check.get(buffer)) {
        if (buffer =='\n'){
            clientsAmount++;
        }
	}
	data_check.close();

	return clientsAmount;
}

void setData(clientInteraction* cl,int n) {
    int tLogin,tPassword;
    double tCash;
    string tSurname,tFirstname;
    bool tIsValid;

    ifstream fin("database.txt");

    for (int i = 0; i < n; i++){
        fin >> tLogin;
        fin >> tPassword;
        fin >> tSurname;
        fin >> tFirstname;
        fin >> tCash;
        fin >> tIsValid;
        cl[i].toClass(tLogin,tPassword,tSurname,tFirstname,tCash,tIsValid);
    }
}

bool miniChoose(){
    bool choice = 0;
    cout << "Do you confirm the transaction?\n";
    cout << "Press: 1 - to agree\n";
    cout << "       0 - to disagree\n";
    choice = safeCin(choice);
    if (choice){
        return 1;
    }
    return 0;
}

void showRates(){
    ifstream rates("exchangeRates.txt");
    string buffer;

    while(getline(rates, buffer)){
        cout << buffer << "\n";
    }

    rates.close();
}

void transactionFixation(string info){
    fstream fixation;

    fixation.open("transactions.txt", ios::app);

    fixation << info << "\n";

    fixation.close();
}

string generalFunctions(){
    return "1) Log in \n2) Exchange Rates \n3) Exit \n\n";
}

string clientFunctions(){
    return "1) Cash out\n2) Recharge the balance\n3) Show Balance\n4) Transfer the money to another client\n5) Pay the services\n6) Log Out\n\n";
}

string newInfoFunc(int login, int password, string surname, string firstname, double cash, bool IsValid){
    return to_string(login) + " " + to_string(password) + " " + surname
              + " " + firstname + " " + to_string(cash) + " " + to_string(IsValid);
}
