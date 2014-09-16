#ifndef USERACCOUNT_H_INCLUDED
#define USERACCOUNT_H_INCLUDED

#include"book.h"
#include<list>
#include"adminaccount.h"


class UserAccount : public AdminAccount
{
private:
    list<Book> booksOnLoan;
    list<Book>::iterator bookIndex;
    UserAccount(){};

public:
    UserAccount(string name, string pass);
    ~UserAccount();
    int booksCheckedOut() const;
    list<Book> getBookList() const;
    void checkOutBook(Book b);
    void returnBook(int i);



};



#endif // USERACCOUNT_H_INCLUDED
