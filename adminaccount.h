#ifndef ADMINACCOUNT_H_INCLUDED
#define ADMINACCOUNT_H_INCLUDED
#include<iostream>

using namespace std;

class AdminAccount
{
private:
    string userName;
    string password;
    static int ID_counter;
    int ID;


public:
    AdminAccount(){};
    AdminAccount(string name, string pass);
    ~AdminAccount();
    string getUserName() const;
    string getPassword() const;
    int getID() const;
    //int getStaticCounter() const;
};


#endif // ADMINACCOUNT_H_INCLUDED
