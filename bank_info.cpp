#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
#include "bank_info.h"

using namespace std;

void bank_info::changeBanknotes(int* tempAmount){
    for (int i = 0; i < banknotesValuesAmount;i++){
        money_amount[i] = tempAmount[i];
    }

    ofstream bankChange("banknotes.txt");

    for (int i = 0; i < banknotesValuesAmount ; i++){
        bankChange << tempAmount[i] << " ";
    }
    bankChange << "\n";
    bankChange.close();
}

void bank_info::getBankInfo(int* tempAmount){
    fstream bank("banknotes.txt");

    for (int i = 0; i < 7; i++){
        bank >> money_amount[i];
        tempAmount[i] = money_amount[i];
    }

    bank.close();
}
