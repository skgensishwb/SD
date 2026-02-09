#include <iostream>

#include "mystring.hpp"

using namespace std;

char MyString::get(int i) { 
    if (i < len(this->string)) {
        return string[i];
    }
    throw runtime_error("Array out of bounds");
}

void MyString::set(int i, char c) {
    int lenght = len(this->string);
    if (i < lenght) {
        string[i] = c;
    }
    else if (i == lenght) {
        int newSize = size + 1;

        char* newString = new char[newSize];
        for (int j = 0; j < newSize; j++) {
                newString[j] = string[j];
            }
        newString[i] = c;

        delete[] string;
        string = newString;
    }
    else {
        throw runtime_error("Array out of bounds");
    }
}

void MyString::set_new_string(const char *str) { // расширение массива
    copyString(str);
}

void MyString::print() {
    if (string == nullptr) {
        throw runtime_error("Nullptr was passed!");
    }

    int lenght = len(this->string);

    for (int i=0; i< lenght; i++) {
        cout << this->string[i];
    }

    cout << endl;
}

void MyString::read_line() {
    clearString();

    cout << "Input a line: ";

    char c;
    int newSize = size;
    int capacity = 0;

    while (cin.get(c) && c != '\n') {
        if (capacity + 1 >= newSize) {
            newSize *= 2;

            char* newString = new char[newSize];

            for (int i = 0; i < capacity; i++) {
                newString[i] = string[i];
            }

            delete[] string;
            string = newString;
        }
        string[capacity++] = c;
    }

    string[capacity] = '\0';
    size = newSize;
}

void MyString::clearString() {
    size = 0;

    char* newString = new char[size + 1];
    newString[0] = '\0';

    delete[] string;

    string = newString;
    size += 1;
}

void MyString::copyString(const char* newString) {
    clearString();
    
    int newSize = this->size;
    int sizeOfNewStr = len(newString);

    while(newSize < sizeOfNewStr + 1) {
        newSize += 10;
    }

    char* buffer = new char[newSize];
    for (int i=0; i<sizeOfNewStr; i++) {
        buffer[i] = newString[i];
    }
    buffer[sizeOfNewStr] = '\0';

    delete[] string;
    size = newSize;
    string = buffer;
}

int MyString::len(const char* string) {
    int length = 0;
    while (string[length] != '\0') {
        ++length;
    }
    return length;
}

MyString::MyString() {
    clearString();
}

MyString::MyString(const char* stringCopy) {
    if (stringCopy == nullptr) {
        throw runtime_error("Nullptr was passed!");
    }

    clearString();

    copyString(stringCopy);
}

MyString::MyString(const MyString& other) {
    if (other.string == nullptr) {
        throw runtime_error("Nullptr was passed!");
    }

    clearString();

    copyString(other.string);
}

MyString::~MyString() {
    delete [] string;
}