#ifndef EXTRAFUNCTIONS_H
#define EXTRAFUNCTIONS_H
#include "clientInteraction.h"

bool miniChoose();
void setData(clientInteraction*,int);
int clientsAmount();
bool authorization(clientInteraction*, int, int, int&);
void dataChange(string, string, int, int);
bool transferLoginCheck(clientInteraction*, int, int,int, int&);
void transactionFixation(string);
void showRates();
string generalFunctions();
string clientFunctions();
string newInfoFunc(int, int ,string ,string ,double ,bool);

template <typename Type>
Type safeCin(Type variable){
    while (true)
    {
        cin >> variable;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(999999999,'\n');
            cout << "That value is invalid. Please try again\n";
            cout << "Input valid value: ";
        }
        else{
            cout << endl;
            return variable;
        }
    }
}

#endif // EXTRAFUNCTIONS_H
