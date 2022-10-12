#ifndef CLIENTINTERACTION_H
#define CLIENTINTERACTION_H
using namespace std;

class clientInteraction{
public:
    void toClass(int, int, string, string, double, bool);
    bool loginCheck(int, bool&);
    bool passwordCheck();
    void block(int, int);
    bool cashOut(int, int);
    void cashIn(int,int);
    bool transfer(clientInteraction&,int,int,unsigned int);
    bool payment(int,int);
    void changeTransferClient(int, int, int);
    int getLogin();
    double getBalance();
    string getFullname();
private:
    int login;
    int password;
    string surname;
    string firstname;
    double cash;
    bool IsValid;
};
#endif // CLIENTINTERACTION_H
