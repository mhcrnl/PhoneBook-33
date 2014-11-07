#include "PhoneBook.h"
#include "PhoneBookItem.h"
#include "algorithm"
#include <strings.h>

PhoneBook::PhoneBook(){
    m_head = new PhoneBookItem("",-99,"");
    m_num = 0;
}

PhoneBook::PhoneBook(const PhoneBook& pb){
    m_head = new PhoneBookItem("",-99,"");
    m_num = 0;
    Copy(pb);
}

PhoneBook::~PhoneBook(){
    Clear();
}

ostream& operator<<(ostream& os, const PhoneBookItem& item){
    //Overloaded ostream operator.

    os << "Name: " << item.m_name << " Age: " << item.m_age << " Number: " << item.m_phone;
    return os;
}

ostream& operator<<(ostream& os, const PhoneBook& pb){

    PhoneBookItem* current;
    current = pb.m_head->m_next;

    while(current != nullptr){
        os << *current << endl;
        current = current->m_next;

    }

        return os;
}

PhoneBook& PhoneBook::operator =(const PhoneBook& pb){  // pb1 = pb2;
    //Precondition: Does not refer to itself.
    //Overloaded assignment operater.
    //Calls PhoneBook::Copy which deals with the implementation.


    if(this != &pb){ //Does not share same address.
        Clear();
        Copy(pb);
    }
    return *this;
}


void PhoneBook::Copy(const PhoneBook& pb){
    //Precondition: Has valid Phonebook parameter.
    //Postcondition: Creates a new Phonebook on the heap.
    //Fills it with contents from calling Phonebook.

    PhoneBookItem *temp, *newNode, *newLoc;
    temp = pb.m_head->m_next;
    newLoc = m_head;


    while(temp != NULL){

        newNode = new PhoneBookItem(temp->m_name,temp->m_age,temp->m_phone);
        newLoc->m_next = newNode;
        newLoc = newLoc->m_next;
        temp = temp->m_next;
    }

}


bool PhoneBook::Insert(const string &name, int age, const string &phone){
    //Precondition: User has specified name, age and phone number.
    //Postcondition: Person is inserted into phonebook in alphabetical order.


    PhoneBookItem *temp = new PhoneBookItem(name,age,phone);
    PhoneBookItem *previous;
    PhoneBookItem *current;
    int compare;


    previous = m_head;
    current = m_head->m_next;


    while(true){

        if(current == nullptr)
            break;
        compare = current->m_name.compare(name);
        if(compare == 0){
            break;

        }
        if(compare < 0){
            previous = current;
            current = current->m_next;
            //Name is greater than current, place before
        }
        else if(compare > 0)
            break;
        //Name is less than current, place after
    }

    temp->m_name = name;

    if(previous == nullptr){
        temp->m_next = current;
    }
    else{
        temp->m_next = current;
        previous->m_next = temp;
    }

    length++;


    return true;
}

bool PhoneBook::Delete(const string &name){
    //Precondition: User has specified name.
    //Postcondition: Person entry is deleted from phonebook.

    PhoneBookItem* previous;
    PhoneBookItem* current;
    PhoneBookItem* temp;

    current = m_head->m_next;

    if(strcasecmp(current->m_name.c_str(),name.c_str()) == 0){ /*current->m_name == name*/
        temp = current;
        m_head->m_next = current->m_next;

        delete temp;
        length--;
        return true;
    }
    else
    {

        while(strcasecmp(current->m_next->m_name.c_str(),name.c_str()) != 0 ){ /*current->m_next->m_name != name*/
            previous = current;
            current = current->m_next;
            if(current->m_next == nullptr)
                return false;
        }

        temp = current->m_next;
        current->m_next = current->m_next->m_next;

        delete temp;
        length--;
        return true;

    }


    return false;
}

bool PhoneBook::Lookup(const string &name, int &age, string &phone) const{
    //Precondition: User has specified name.
    //Postcondition: Person is found. Age and Phone are filled with found values.

    string name_ = name;
    std::transform(name_.begin(),name_.end(),name_.begin(),::tolower);

    PhoneBookItem* current;

    current = m_head->m_next;

    //Use strcasecmp (C lib.) to ignore case.
    while(/*current->m_name != name*/ strcasecmp(current->m_name.c_str(),name.c_str()) != 0){
        if(current->m_next != nullptr) //we've reached the end!
            current = current->m_next;
        else
            return false;
    }

    age = current->m_age;
    phone = current->m_phone;
    return true;

}


void PhoneBook::Output(){
    //Precondition: None.
    //Postcondition: Prints out Phonebook contents.
    //Loops through using pointer current. If current points to nullptr next,
    //then we have reached the last person.

    PhoneBookItem* current;

    current = m_head;

    while(current->m_next != nullptr){
        current = current->m_next;
        cout << *current << endl;
    }

}


void PhoneBook::Clear(){
    //Precondition: None.
    //Postcondition: Clears out Phonebook.
    //Loops through phonebook starting from m_head->m_next.
    //Uses head to point to previous node.
    //Uses temp to hold leading node to delete it.

    PhoneBookItem* head;
    PhoneBookItem* current;
    PhoneBookItem* temp;

    current = m_head->m_next;
    head = m_head;


    while(current != nullptr){

        temp = current;             //Save location of current.
        current = current->m_next;  //Set current to point to next element after the one we are deleting.
        head->m_next = current;     //set head next to point to current.
        delete temp;                //Now delete temp. Rinse and repeat.
    }
    delete m_head;                  //We DUUNN. Delete m_head.
}


int PhoneBook::Size() const {
    //Returns length value

    return length;
}



//EXTRA

//int PhoneBook::GetMaxAge(){
//    //Loops through each linked list element.
//    //If age is bigger than maxAge, set maxAge to age.

//    int maxAge = 0;
//    PhoneBookItem* current;
//    current = m_head->m_next;

//    while(current != nullptr){
//        if(current->m_age > maxAge){
//            maxAge = current->m_age;
//        }

//        current = current->m_next;

//    }

//    return maxAge;

//}

//PhoneBook PhoneBook::GetPeopleWithGivenAge(int age){

//    PhoneBook newPb;
//    PhoneBookItem *current;
//    current = m_head->m_next;

//    while(current != nullptr){
//        if(current->m_age == age){
//            newPb.Insert(current->m_name,current->m_age,current->m_phone);
//        }
//        current = current->m_next;
//    }

//    return newPb;
//}


//PhoneBook PhoneBook::GetAllPeopleWithMaxAge(){

//    int maxAge = this->GetMaxAge();
//    PhoneBook newPb;
//    PhoneBookItem *current;
//    current = m_head->m_next;

//    while(current != nullptr){
//        if(current->m_age == maxAge){
//            newPb.Insert(current->m_name,current->m_age,current->m_phone);
//        }
//        current = current->m_next;
//    }

//    return newPb;
//}
