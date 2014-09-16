#include"book.h"


Book::Book(string t, string a, uint64_t i, int q)
{
    title = t;
    author = a;
    isbn = i;
    quantity = q;

}


Book::~Book()
{

}

int Book::getQuantity() const
{
    return quantity;
}

uint64_t Book::getIsbn() const
{
    return isbn;
}


string Book::getAuthor() const
{
    return author;
}


string Book::getTitle() const
{
    return title;
}

void Book::decrementQuantity()
{
    quantity--;
}

void Book::incrementQuantity()
{
    quantity++;
}

void Book::setQuantity(int number)
{
    quantity = number;
}
