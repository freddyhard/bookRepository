#include"useraccount.h"


UserAccount::UserAccount(string name, string pass) : AdminAccount(name, pass)
{

}


UserAccount::~UserAccount()
{

}



int UserAccount::booksCheckedOut() const
{
    return booksOnLoan.size();
}


list<Book> UserAccount::getBookList() const
{
    return booksOnLoan;
}


void UserAccount::checkOutBook(Book b)
{
    b.setQuantity(1);
    booksOnLoan.push_back(b);
}


void UserAccount::returnBook(int bookNumber)
{
    bookIndex = booksOnLoan.begin();

    for (int f = 0; f < bookNumber -1; f++)
    {
        bookIndex++;
    }

    booksOnLoan.erase(bookIndex);
}
