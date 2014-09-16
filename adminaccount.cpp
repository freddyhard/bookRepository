#include"adminaccount.h"


AdminAccount::AdminAccount(string name, string pass)
{
    userName = name;
    password = pass;
    ID_counter++;
    ID = ID_counter;
}


AdminAccount::~AdminAccount()
{

}


string AdminAccount::getPassword() const
{
    return password;
}


string AdminAccount::getUserName() const
{
    return userName;
}


int AdminAccount::getID() const
{
    return ID;
}
