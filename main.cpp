#include <iostream>
#include<sstream>
#include"windows.h"
#include<math.h>
#include"book.h"
#include"adminaccount.h"
#include"useraccount.h"
#include<list>
#include<vector>

using namespace std;



//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                         GLOBAL VARIABLES                          |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
list<Book> books;
list<Book>::iterator bookIndex;

list<UserAccount> users;
list<UserAccount>::iterator userIndex;

vector<AdminAccount> administrators;

// initialise the counter for the accounts
int AdminAccount::ID_counter = 1000;

/*enum
{
    GUEST,
    USER,
    ADMINISTRATOR
};*/

//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                            FUNCTIONS                              |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void printBookDetails(const Book &b);
void printUserDetails(const UserAccount &u);

void printWarning(string s);
bool criticalConfirmation(string s);
int printCountedBookList(list<Book> b, bool printNumbers = true);

void guestMenu();

void userMenu(UserAccount &user);
void checkOutBook(Book b, UserAccount &u);
void checkInBook(UserAccount &user);

void adminMenu(AdminAccount &admin);
void editUserAccounts(AdminAccount &adminName);
void addBookToLibrary();
void addNewUser();
void deleteBook(Book b);
void deleteUser(UserAccount u);
void setNumberOfCopies(Book b);

bool adminLoginCheck(string username, string password, int n);
bool userLoginCheck(string username, string password, int n);

bool isbnFound(uint64_t i);
bool validInteger(string n);
int extractInteger(string n);
uint64_t extractInteger_64(string n);
void printMenuTitle(string title);
int printCountedUserList(list<UserAccount> usersFound);

string askUser(string question);
string setLowerCase(string line);

list<Book> bookSearch(string &comment);
list<UserAccount> userSearch(string &comment);



//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                               MAIN                                |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main()
{
    administrators.push_back(AdminAccount("thomas", "1234"));
    administrators.push_back(AdminAccount("richard", "5678"));
    administrators.push_back(AdminAccount("henry", "9101"));


    books.push_back(Book("mastering machine code on your zx spectrum", "toni baker", 907563236, 1));
    books.push_back(Book("i hate everyone... starting with me", "joan rivers", 9780425255896, 1));
    books.push_back(Book("the hobbit", "jrr tolkien", 261103288, 5));
    books.push_back(Book("the silmarillion", "jrr tolkien", 261102737, 1));
    books.push_back(Book("unfinished tales", "jrr tolkien", 261102168, 2));
    books.push_back(Book("surviving hitler", "adam lebor roger boyes", 671022636, 0));
    books.push_back(Book("kama sutra", "kamini thomas kirk thomas", 9780007229765, 1));

    users.push_back(UserAccount("nom", "password"));//1004
    users.push_back(UserAccount("noman", "god#1"));//1005

    //  -------------------------- testing ------------------------------
    /*
    userIndex = users.begin();
    userIndex++;

    (*userIndex).checkOutBook(*bookIndex);
    bookIndex++;
    (*userIndex).checkOutBook(*bookIndex);

    printUserDetails(*userIndex);
    userIndex--;
    printUserDetails(*userIndex);
    //*/
    //  ------------------------ testing end ----------------------------

    while (true)
    {
        system("color 1f");
        system("cls");

        string userName = "";
        string password = "";
        string id = "";
        int idNumber = 0;

        printMenuTitle("LOGIN MENU");
        cout << "ENTER LOGIN DETAILS:";

        userName = askUser("\n\nUser Name: ");
        password = askUser("Password: ");
        id = askUser("ID#: ");


        // test for a valid login and if true go to that menu
        if (validInteger(id))
        {
            idNumber = extractInteger(id);
        }

        if (userName.compare("guest") == 0)
        {
            guestMenu();
        }
        else if (idNumber != 0 && adminLoginCheck(userName, password, idNumber))
        {
            // nothing to do in here. i was going to return here and then do a search to find
            // the admin account to pass onto the adminMenu(). i thought it more efficient to move
            // directly to the adminMenu() rather than search a second time.
            // i need a true/false catch so that when the program counter returns
            // here it will not print a warning if a valid login took place
        }
        else if (idNumber != 0 && userLoginCheck(userName, password, idNumber))
        {
            // nothing to do in here. i was going to return here and then do a search to find
            // the user account to pass onto the userMenu(). i thought it more efficient to move
            // directly to the userMenu() rather than search a second time.
            // i need a true/false catch so that when the program counter returns
            // here it will not print a warning if a valid login took place
        }
        else
        {
            printWarning("DETAILS INCORRECT!");
        }
    }



    return 0;
}


//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                               GUEST                               |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void guestMenu()
{
    list<Book> booksFound;
    list<Book>::iterator bookIndex;
    string m = "Please select an option:\n\n";

    string menu = m + "1:\tLogin Menu\n"
                    + "2:\tSearch for a book\n\n";

    string bookSearchComment = "";

    while (true)
    {
        string userInput = "";

        system("cls");
        system("color 70");

        cout << bookSearchComment << "\n\n";
        // false means do not print a number for each book in the list
        printCountedBookList(booksFound, false);

        printMenuTitle("GUEST OPTIONS");

        userInput = askUser(menu);

        if (validInteger(userInput))
        {
            int choice = extractInteger(userInput);
            if (choice < 1 || choice > 2)
            {
                printWarning("INVALID CHOICE!");
            }
            else if (choice == 2)
            {
                booksFound = bookSearch(bookSearchComment);
                //menu = "\tPlease select an option:\n\n1:\tLogin Menu\n2:\tSearch for another book\n\n";
            }
            else
            {
                return;
            }
        }
        else
        {
            printWarning("NOT A VALID INPUT!");
        }
    }

}





//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                           ADMININSTRATOR                          |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void adminMenu(AdminAccount &admin)
{
    list<Book> booksFound;
    string menu = admin.getUserName() + " please select an option\n\n"
                                             + "1:\tLogout\n"
                                             + "2:\tSearch for a book\n"
                                             + "3:\tAdd a new Title to the Library\n"
                                             + "4:\tRemove a Title from the Library\n"
                                             + "5:\tSet the number of copies for a Title\n"
                                             + "6:\tEdit User Accounts\n\n";
    string bookSearchComment = "";

    while (true)
    {
        system("cls");
        system("color 61");

        cout << bookSearchComment << "\n\n";

        // print a numbered list for the user to view
        int bookSearchCount = printCountedBookList(booksFound);

        printMenuTitle("ADMINISTRATOR OPTIONS");

        string userInput = askUser(menu);

        if (validInteger(userInput))
        {
            int choice = extractInteger(userInput);
            if (choice < 1 || choice > 6)
            {
                printWarning("INVALID CHOICE!");
            }
            else if (choice == 2)
            {
                booksFound = bookSearch(bookSearchComment);
                /*menu = "\t" + admin.getUserName() + " please select an option\n\n1:\tLogout\n2:\tSearch for another book\n"
                                                  + "3:\tAdd a new Title to the Library\n4:\tRemove a Title from the Library\n"
                                                  + "5:\tSet the number of copies for a Title\n6:\tEdit User Accounts\n\n";*/
            }
            else if (choice == 3)
            {
                addBookToLibrary();
            }
            else if (bookSearchCount == 0 && (choice == 4 || choice == 5))
            {
                printWarning("DO A SEARCH FIRST!");
            }
            else if (choice == 4 || choice == 5)
            {
                userInput = askUser("Select a number for a book in the list above: ");

                if (validInteger(userInput))
                {
                    int bookNum = extractInteger(userInput);
                    if (bookNum < 1 || bookNum > bookSearchCount)
                    {
                        printWarning("INVALID CHOICE!");
                    }
                    else
                    {
                        bookIndex = booksFound.begin();
                        for (int f = 0; f < bookNum - 1; f++)
                        {
                            bookIndex++;
                        }
                        if (choice == 4)
                        {
                            deleteBook(*bookIndex);
                        }
                        else
                        {
                            setNumberOfCopies(*bookIndex);
                        }
                        booksFound.clear();
                        bookSearchComment = "";
                    }
                }
                else
                {
                    printWarning("NOT A VALID INPUT!");
                }
            }
            else if (choice == 6)
            {
                editUserAccounts(admin);
            }
            else
            {
                // go back to the login menu
                return;
            }
        }
        else
        {
            printWarning("NOT A VALID INPUT!");
        }
    }
}


void editUserAccounts(AdminAccount &admin)
{
    // this will offer a search for a user by name and/or ID number
    // will print list of users found with a list of books checked out
    // an option will be offered to delete a User Account from the searched list with CRITICAL CONFIRMATION ASKED!
    // an option will be offered to add an account, by taking a user name and password
    // the user account ID will be automatically generated and will be displayed for the admin
    // with CRITICAL CONFIRMATION ASKED! before adding the user to the list

    list<UserAccount> usersFound;
    // use a local iterator to erase a user should the administrator do this
    list<UserAccount>::iterator userIndex;
    string menu = admin.getUserName() + " please select an option:\n\n"
                                   + "1:\tReturn to main menu\n"
                                   + "2:\tSearch for a User\n"
                                   + "3:\tDelete an Account\n"
                                   + "4:\tCreate a new Account\n";
    string usersFoundComment = "";

    while (true)
    {
        system("cls");
        system("color 61");
        cout << usersFoundComment << "\n\n";
        int userSearchCount = printCountedUserList(usersFound);
        printMenuTitle("EDIT USER ACCOUNTS");

        string userInput = askUser(menu);

        if (validInteger(userInput))
        {
            int choice = extractInteger(userInput);
            if (choice < 1 || choice > 4)
            {
                printWarning("INVALID CHOICE!");
            }
            else if (choice == 2)
            {
                usersFound = userSearch(usersFoundComment);
            }
            else if (userSearchCount == 0 && choice == 3)
            {
                printWarning("DO A USER SEARCH FIRST!");
            }
            else if (choice == 3)
            {
                userInput = askUser("Select a number for a user in the above list: ");

                if (validInteger(userInput))
                {
                    int userNum = extractInteger(userInput);
                    if (userNum < 1 || userNum > userSearchCount)
                    {
                        printWarning("INVALID CHOICE!");
                    }
                    else
                    {
                        userIndex = usersFound.begin();
                        for (int f = 0; f < userNum - 1; f++)
                        {
                            userIndex++;
                        }
                        deleteUser(*userIndex);
                        usersFound.clear();
                        usersFoundComment = "";
                    }
                }
                else
                {
                    printWarning("NOT A VALID INPUT!");
                }
            }
            else if (choice == 4)
            {
                addNewUser();
            }
            else
            {
                // return to main menu
                return;
            }
        }
        else
        {
            printWarning("NOT A VALID INPUT!");
        }
    }
}

void addNewUser()
{
    while (true)
    {
        system("cls");
        system("color 1a");
        printMenuTitle("ADD A NEW USER");

        string finished = askUser("Press ENTER to continue or 'r' to return: ");

        if (finished.compare("r") == 0)
        {
            return;
        }

        string newName = askUser("Enter user name: ");
        string newPassword = askUser("Enter password: ");

        if (newName.length() > 0 && newPassword.length() > 0)
        {
            users.push_back(UserAccount(newName, newPassword));
            userIndex = users.end();
            userIndex--;
            system("cls");
            printUserDetails(*userIndex);
            printWarning("NEW USER ADDED!");
        }
        else
        {
            printWarning("NO FIELDS CAN BE BLANK!");
        }
    }
}


void addBookToLibrary()
{
    // this will receive a title, author and ISBN from admin.
    // check that ISBN does not already exist, if not then add it to Books

    while (true)
    {
        system("cls");
        system("color 61");
        printMenuTitle("ADD A NEW TITLE TO THE LIBRARY");

        string finished = askUser("Press ENTER to continue or 'r' to return: ");

        if (finished.compare("r") == 0)
        {
            return;
        }

        string newTitle = askUser("Enter Title: ");
        string newAuthor = askUser("Enter Author: ");
        string newIsbn = askUser("Enter ISBN#: ");
        string newQuantity = askUser("Enter quantity: ");

        if (validInteger(newIsbn) && validInteger(newQuantity))
        {
            uint64_t isbnNum = extractInteger_64(newIsbn);
            int quantityNum = extractInteger(newQuantity);
            if (newTitle.length() == 0 || newAuthor.length() == 0 || isbnNum == 0)
            {
                printWarning("NO FIELDS CAN BE BLANK!");
            }
            else if (isbnFound(isbnNum))
            {
                printWarning("THAT ISBN NUMBER ALREADY EXISTS!");
            }
            else
            {
                books.push_back(Book(newTitle, newAuthor, isbnNum, quantityNum));
                printWarning("Book added to the Library!");
            }
        }
        else
        {
            printWarning("ONLY NUMBERS ACCEPTED FOR ISBN AND QUANTITIES!");
        }
    }
}



bool adminLoginCheck(string username, string password, int id)
{
    // if login details match an account continue to adminMenu() then
    // return true to confirm a login did happen
    for (unsigned int f = 0; f < administrators.size(); f++)
    {
        if (username.compare(administrators[f].getUserName()) == 0 &&
            password.compare(administrators[f].getPassword()) == 0 && id == administrators[f].getID())
        {
            adminMenu(administrators[f]);
            return true;
        }
    }
    return false;
}

void deleteUser(UserAccount u)
{
    if (criticalConfirmation("ARE YOU SURE YOU WAN TO DELETE THIS USER? (y/n): "))
    {
        for (userIndex = users.begin(); userIndex != users.end(); userIndex++)
        {
            if (u.getID() == (*userIndex).getID())
            {
                users.erase(userIndex);
                return;
            }
        }
    }
}


void deleteBook(Book b)
{
    if (criticalConfirmation("ARE YOU SURE YOU WANT TO DELETE THIS BOOK? (y/n): "))
    {
        for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++)
        {
            if (b.getIsbn() == (*bookIndex).getIsbn())
            {
                books.erase(bookIndex);
                return;
            }
        }
    }
}


void setNumberOfCopies(Book b)
{
    string userInput = askUser("Enter a number to set the quantity: ");

    if (validInteger(userInput))
    {
        int quantity = extractInteger(userInput);

        for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++)
        {
            if (b.getIsbn() == (*bookIndex).getIsbn())
            {
                (*bookIndex).setQuantity(quantity);
                return;
            }
        }
    }
    else
    {
        printWarning("NOT A VALID NUMBER!");
    }
}



bool isbnFound(uint64_t i)
{
    for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++)
    {
        if ((*bookIndex).getIsbn() == i)
        {
            return true;
        }
    }
    return false;
}


int printCountedUserList(list<UserAccount> usersFound)
{
    int counter = 0;
    for (userIndex = usersFound.begin(); userIndex != usersFound.end(); userIndex++)
    {
        counter++;
        cout << counter << ":\n";
        printUserDetails(*userIndex);
    }

    return counter;
}

list<UserAccount> userSearch(string &comment)
{
    list<UserAccount> userSearch;

    while (true)
    {
        system("cls");
        system("color 61");

        printMenuTitle("SEARCH FOR A USER");
        cout << "SEARCH FOR A USER:\n(inputs can be blank)\n";

        string nameInput = askUser("Enter user name: ");
        string passwordInput = askUser("Enter user password: ");
        string idInput = askUser("Enter user ID#: ");

        if (validInteger(idInput))
        {
            int idSearch = extractInteger(idInput);
            // assume no users are found
            comment = "NO USERS MATCH THE SEARCH!";

            for (userIndex = users.begin(); userIndex != users.end(); userIndex++)
            {
                if ((nameInput.length() == 0 || nameInput == (*userIndex).getUserName()) &&
                    (passwordInput.length() == 0 || passwordInput == (*userIndex).getPassword()) &&
                    (idSearch == 0 || idSearch == (*userIndex).getID()))
                {
                    userSearch.push_back(*userIndex);
                    // a user matched the search, so change the comment
                    comment = "USERS FOUND THAT MATCH THE SEARCH";
                }
            }
            return userSearch;
        }
        else
        {
            printWarning("NOT A VALID ID NUMBER!");
        }
    }
}


//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                               USER                                |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void userMenu(UserAccount &user)
{
    list<Book> booksFound;
    // use a local iterator to decrement the searched book list when a user checks it out
    list<Book>::iterator bookIndex;

    string menu = user.getUserName() + " please select an option:\n\n"
                                            + "1:\tLogout\n"
                                            + "2:\tSearch for a book\n"
                                            + "3:\tCheck out a book\n"
                                            + "4:\tReturn a book\n\n";
    string bookSearchComment = "";

    while (true)
    {
        system("cls");
        system("color 5a");

        cout << bookSearchComment << "\n\n";
        // print a numbered list for the user to view
        int bookSearchCount = printCountedBookList(booksFound);

        printMenuTitle("REGISTERED USER OPTIONS");

        string userInput = askUser(menu);

        if (validInteger(userInput))
        {
            int choice = extractInteger(userInput);
            if (choice < 1 || choice > 4)
            {
                printWarning("INVALID CHOICE!");
            }
            else if (choice == 2)
            {
                booksFound = bookSearch(bookSearchComment);
                /*menu = "\t" + user.getUserName() + " please select an option:\n\n1:\tLogout\n2:\tSearch for another book\n"
                                                 + "3:\tCheck out a book\n4:\tReturn a book\n\n";*/
            }
            else if (choice == 3 && bookSearchCount == 0)
            {
                printWarning("DO A SEARCH FIRST!");
            }
            else if (choice == 3)
            {
                userInput = askUser("Select a number for a book in the list above: ");

                if (validInteger(userInput))
                {
                    int bookNum = extractInteger(userInput);
                    if (bookNum < 1 || bookNum > bookSearchCount)
                    {
                        printWarning("INVALID CHOICE!");
                    }
                    else
                    {
                        bookIndex = booksFound.begin();
                        for (int f = 0; f < bookNum - 1; f++)
                        {
                            bookIndex++;
                        }
                        checkOutBook(*bookIndex, user);
                        (*bookIndex).decrementQuantity();
                    }
                }
                else
                {
                    printWarning("NOT A VALID INPUT!");
                }
            }
            else if (choice == 4)
            {
                checkInBook(user);
                booksFound.clear();
                bookSearchComment = "";
            }
            else
            {
                // go back to the login menu
                return;
            }
        }
        else
        {
            printWarning("NOT A VALID INPUT!");
        }

    }
}




bool userLoginCheck(string username, string password, int id)
{
    // if login details match an account continue to userMenu() then
    // return true to confirm a login did happen
    for (userIndex = users.begin(); userIndex != users.end(); userIndex++)
    {
        if (username.compare((*userIndex).getUserName()) == 0 &&
            password.compare((*userIndex).getPassword()) == 0 && id == (*userIndex).getID())
        {
            userMenu(*userIndex);
            return true;
        }
    }
    return false;
}



void checkOutBook(Book b, UserAccount &user)
{
    if (b.getQuantity() == 0)
    {
        printWarning("NO COPIES AVAILABLE!");
        return;
    }
    if (user.booksCheckedOut() > 0)
    {
        list<Book> currentUserList = user.getBookList();
        for (bookIndex = currentUserList.begin(); bookIndex != currentUserList.end(); bookIndex++)
        {
            if (b.getIsbn() == (*bookIndex).getIsbn())
            {
                printWarning("YOU ALREADY HAVE A COPY CHECKED OUT!");
                return;
            }
        }
    }

    user.checkOutBook(b);
    for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++)
    {
        if (b.getIsbn() == (*bookIndex).getIsbn())
        {
            (*bookIndex).decrementQuantity();
            return;
        }
    }
}


void checkInBook(UserAccount &user)
{
    if (user.booksCheckedOut() == 0)
    {
        cout << "\nYou do not have any books checked out!\n";
        system("pause");
        return;
    }

    while (true)
    {
        list<Book> currentList = user.getBookList();

        system("cls");
        system("color 5a");

        printMenuTitle("RETURN A BOOK");

        // print a numbered list for the user to view
        int bookCount = printCountedBookList(currentList);

        string userInput = askUser("Select a number for a book in the list above: ('q' to quit): ");

        if (validInteger(userInput))
        {
            int bookNumber = extractInteger(userInput);
            if (bookNumber < 1 || bookNumber > bookCount)
            {
                printWarning("NOT A VALID SELECTION!");
            }
            else
            {
                // remove this book from the users list
                user.returnBook(bookNumber);

                bookIndex = currentList.begin();
                for (int f = 0; f < bookNumber - 1; f++)
                {
                    bookIndex++;
                }
                Book returningBook = *bookIndex;

                for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++)
                {
                    if (returningBook.getIsbn() == (*bookIndex).getIsbn())
                    {
                        (*bookIndex).incrementQuantity();
                        break;
                    }
                }
            }
        }
        else if (userInput == "q")
        {
            return;
        }
        else
        {
            printWarning("NOT A VALID INPUT!");
        }


    }

}


//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  |                                                                   |
//  |                         COMMON FUNCTIONS                          |
//  |                                                                   |
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

list<Book> bookSearch(string &comment)
{
    list<Book> bookSearch;

    while (true)
    {
        system("cls");
        system("color 0f");

        cout << "SEARCH FOR A BOOK:\n(inputs can be blank)\n";

        string titleInput = askUser("Enter Title: ");
        string authorInput = askUser("Enter Author: ");
        string isbnInput = askUser("Enter ISBN#: ");

        if (validInteger(isbnInput))
        {
            uint64_t isbnSearch = extractInteger_64(isbnInput);
            // assume no books match the search
            comment = "NO BOOKS MATCH THE SEARCH!";

            for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++)
            {
                if ((titleInput.length() == 0 || titleInput == (*bookIndex).getTitle()) &&
                    (authorInput.length() == 0 || authorInput == (*bookIndex).getAuthor()) &&
                    (isbnSearch == 0 || isbnSearch == (*bookIndex).getIsbn()))
                {
                    bookSearch.push_back(*bookIndex);
                    // a book matched the search, so change the comment
                    comment = "BOOKS FOUND THAT MATCH THE SEARCH";
                }
            }
            return bookSearch;
        }
        else
        {
            printWarning("NOT A VALID ISBN NUMBER!");
        }


    }
}


void printBookDetails(const Book &b)
{
    cout << "TITLE:\t" << b.getTitle() << endl;
    cout << "AUTHOR:\t" << b.getAuthor() << endl;
    cout << "ISBN:\t" << b.getIsbn() << endl;

    if (b.getQuantity() > 0)
    {
        cout << "COPIES:\t" << b.getQuantity() << endl;
    }
    else
    {
        cout << "NOT AVAILABLE" << endl;
    }
    cout << "\n";
}




void printUserDetails(const UserAccount &u)
{
    cout << "NAME:\t\t" << u.getUserName() << endl;
    cout << "PASSWORD:\t" << u.getPassword() << endl;
    cout << "ID:\t\t" << u.getID() << endl;

    if (u.booksCheckedOut())
    {
        list<Book> booksOnLoan = u.getBookList();
        //list<Book>::iterator bookIndex;

        cout << "\nList of Books Checked Out:" << endl;

        for (bookIndex = booksOnLoan.begin(); bookIndex != booksOnLoan.end(); bookIndex++)
        {
            cout << "\n";
            printBookDetails(*bookIndex);
        }

    }
    else
    {
        cout << "\nNO BOOKS ON LOAN" << endl;
    }
    cout << "\n";
}



void printWarning(string message)
{
    cout << "\n" << message << endl;
    system("color fc");
    system("pause");
}


bool criticalConfirmation(string message)
{
    system("color 4f");

    string userInput = askUser(message);

    if (userInput.compare("y") == 0)
    {
        return true;
    }

    return false;
}



bool validInteger(string number)
{
    for (unsigned int f = 0; f < number.length(); f++)
    {
        if (int(number[f]) < 48 || int(number[f]) > 57)
        {
            return false;
        }
    }
    return true;
}


/** @brief this will convert a string of numbers to an int
 *
 * @param number is the number in string format to be converted
 * @return the converted string passed
 *
 */
int extractInteger(string number)
{
    double numExtract = 0;

    for (unsigned int f = 0; f < number.length(); f++)
    {
        int num = int(number[f]) - 48;

        double power = double(number.length() - f - 1);
        numExtract += num * pow(10.0, power);
    }
    return int(numExtract);
}



int printCountedBookList(list<Book> bookList, bool printNumbers)
{
    int counter = 0;
    for(bookIndex = bookList.begin(); bookIndex != bookList.end(); bookIndex++)
    {
        if (printNumbers)
        {
            counter++;
            cout << counter << ":\n";
        }
        printBookDetails(*bookIndex);
    }
    return counter;
}



uint64_t extractInteger_64(string number)
{
    double numExtract = 0;

    for (unsigned int f = 0; f < number.length(); f++)
    {
        int num = int(number[f]) - 48;

        double power = double(number.length() - f - 1);
        numExtract += num * pow(10.0, power);
    }
    return uint64_t(numExtract);
}



void printMenuTitle(string title)
{
    string bar = "";
    for (unsigned int f = 0; f < title.length() + 4; f++)
    {
        bar += "=";
    }
    cout << "\t" << bar << endl;
    cout << "\t| " << title << " |\n";
    cout << "\t" <<bar << endl;
}

string askUser(string question)
{
    string userIn = "";
    cout << question;
    getline(cin, userIn);
    userIn = setLowerCase(userIn);
    return userIn;
}


string setLowerCase(string line)
{
    string lineLowerCase = "";
    for (unsigned int f = 0; f < line.length(); f++)
    {
        if (int(line[f]) < 65 || int(line[f]) > 90)
        {
            lineLowerCase += line[f];
        }
        else
        {
            lineLowerCase += char(int(line[f]) + 32);
        }
    }
    return lineLowerCase;
}
