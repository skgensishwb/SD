#include <iostream>

#include "mystring.hpp"

using namespace std;
// очистить буфер где и как
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
    string = copyString(str);
}

void MyString::print() {
    int lenght = len(this->string);

    for (int i=0; i< lenght; i++) {
        cout << this->string[i];
    }
}

void MyString::read_line() {
    cout << "Input a line: ";

    char c;
    int newSize = size;
    int capacity = 0;

    while (cin.get(c) && c != '\n') {
        if (capacity + 1 >= newSize) {
            capacity *= 2;

            char* newString = new char[capacity];

            for (int i = 0; i < newSize; i++) {
                newString[i] = string[i];
            }

            delete[] string;
            string = newString;
        }
        string[capacity++] = c;
    }

    
}

char* MyString::copyString(const char* newString) {
    int size = this->size;
    int newSize = len(newString);
    while(size < newSize + 1) {
        size += 10;
    }

    char* string = new char[size];
    for (int i=0; i<newSize; i++) {
        string[i] = newString[i];
    }

    return string;
}

int MyString::len(const char* string) {
    int lenght = sizeof(*string) / sizeof(string[0]);
    return lenght;
}

MyString::MyString() {
    size = 50;
    char* string = new char[size];
}

MyString::MyString(const char* stringCopy) {
    if (stringCopy == nullptr) {
        throw runtime_error("Nullptr was passed!");
    }

    int lenght = len(stringCopy);

    char* string = new char[lenght];
    for (int i=0; i< lenght; i++) {
        string[i] = stringCopy[i];
    }
}