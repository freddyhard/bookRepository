#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include<iostream>

using namespace std;

class Book
{
private:
    string title;
    string author;
    uint64_t isbn;
    int quantity;
    Book(){};

public:
    Book(string t, string a, uint64_t i, int q);
    ~Book();
    string getTitle() const;
    string getAuthor() const;
    uint64_t getIsbn() const;
    int getQuantity() const;
    void decrementQuantity();
    void incrementQuantity();
    void setQuantity(int number);

};



#endif // BOOK_H_INCLUDED
