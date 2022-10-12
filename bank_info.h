#ifndef BANK_INFO_H
#define BANK_INFO_H
class bank_info{
public:
    void getBankInfo(int*);
    void changeBanknotes(int*);
    const int value[7] = {500, 200, 100, 50, 20, 10, 5};
    const int banknotesValuesAmount = 7;
private:
    int money_amount[7];
};
#endif // BANK_INFO_H
