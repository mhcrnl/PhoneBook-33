#include "menu.h"
#include "PhoneBook.h"
#include "PhoneBookItem.h"
#include <iostream>


using namespace std;


int main()
{

    PhoneBookItem test("Alpha",99,"99");



    PhoneBook yellowPages;

    cout << "Inserting: " << endl;
    yellowPages.Insert("Mr. Mead",10,"911");
    yellowPages.Insert("Alpha",10,"112");
    yellowPages.Insert("Saxton Hale",40,"1-888-222-2222");
    yellowPages.Insert("Gabe Newell",40,"1-444-444-4444");
    yellowPages.Insert("Pyro",29,"1-234-567-8901");

    cout << "Original list: " << endl;
    cout << yellowPages << endl;

    //Test copy ctor

    PhoneBook blueBook(yellowPages);
    cout << "List after copy ctor: " << endl;
    cout << blueBook << endl;

    //Test operator =
    PhoneBook whiteBook;
    whiteBook = yellowPages;

    cout << "List after operator=: " << endl;
    cout << whiteBook << endl;


    //Pause
    cin.get();

    Menu menu(&yellowPages);
    int choice;
    bool done = false;
    while(!done){
        cout << "Select an option: \n";
        cout << "[1] Add a person\n";
        cout << "[2] Lookup a person\n";
        cout << "[3] Delete a person\n";
        cout << "[4] Get # of persons in phonebook\n";
        cout << "[5] Exit\n";
        cin >> choice;
        cin.ignore(50,'\n');

        switch(choice){

        case 1:
            menu.Add();
            break;
        case 2:
            menu.LookUp();
            break;
        case 3:
            menu.Delete();
            break;
        case 4:
            menu.GetLength();
            break;
        case 5:{
            done = true;
            break;
        }
        default:
            break;
        }

    }

    return 0;
}




//EXTRA


//    cout << "Max Age: " << yellowPages.GetMaxAge() << endl;

//    cout << "Getting all with max Age" << endl;
//    PhoneBook lol = yellowPages.GetAllPeopleWithMaxAge();

//    cout << lol << endl;
