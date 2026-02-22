#include <iostream>

#include "mystring.hpp"

const char* MyString::cStr() const {
    return m_userString ? m_userString : "";
}

char MyString::get(int i) { 
    if (i < len(this->m_userString)) {
        return m_userString[i];
    }
    std::cout << "\nArray out of bounds\n" << std::endl;
    return '\0';
}

void MyString::set(int i, char c) {
    int lenght = len(this->m_userString);
    if (i < lenght) {
        m_userString[i] = c;
    }
    else if (i == lenght) {
        int newSize = m_size + 1;

        char* newString = new char[newSize];
        for (int j = 0; j < m_size; j++) {
                newString[j] = m_userString[j];
            }
        newString[i] = c;
        newString[newSize] = '\0';

        delete[] m_userString;
        m_userString = newString;
    }
    else {
        std::cout << "\nArray out of bounds\n" << std::endl;
    }
}

void MyString::setNewString(const char *str) {
    copyString(str);
}

void MyString::print() {
    if (m_userString == nullptr) {
        std::cout << "\nNullptr\n" << std::endl;
    } else {
        int lenght = len(this->m_userString);

        for (int i=0; i< lenght; i++) {
            std::cout << this->m_userString[i];
        }

        std::cout << std::endl;
    }
}

void MyString::readLine() {
    clearString();

    std::cout << "Input a line: ";

    char c;
    int newSize = m_size;
    int capacity = 0;

    while (std::cin.get(c) && c != '\n') {
        if (capacity + 1 >= newSize) {
            newSize *= 2;

            char* newString = new char[newSize];

            for (int i = 0; i < capacity; i++) {
                newString[i] = m_userString[i];
            }

            delete[] m_userString;
            m_userString = newString;
        }
        m_userString[capacity++] = c;
    }

    m_userString[capacity] = '\0';
    m_size = newSize;
}

char* MyString::getString() {
    return m_userString;
}

void MyString::clearString() {
    delete[] m_userString;
    m_size = 1;
    m_userString = new char[m_size];
    m_userString[0] = '\0';
}

void MyString::copyString(const char* newString) {
    clearString();
    
    int newSize = this->m_size;
    int sizeOfNewStr = len(newString);

    while(newSize < sizeOfNewStr + 1) {
        newSize += 10;
    }

    char* buffer = new char[newSize];
    for (int i=0; i<sizeOfNewStr; i++) {
        buffer[i] = newString[i];
    }
    buffer[sizeOfNewStr] = '\0';

    delete[] m_userString;
    m_size = newSize;
    m_userString = buffer;
}

int MyString::len(const char* string) {
    int length = 0;
    while (string[length] != '\0') {
        ++length;
    }
    return length;
}

MyString::MyString() : m_size(0), m_userString(nullptr) {
    clearString();
}

MyString::MyString(const char* stringCopy) : m_size(0) {
    if (stringCopy == nullptr) {
        std::cout << "\nNullptr\n" << std::endl;
    } else {
        copyString(stringCopy);
    }
}

MyString::MyString(const MyString& other) : m_size(0) {
    if (other.m_userString == nullptr) {
        std::cout << "\nNullptr\n" << std::endl;
    } else {
        copyString(other.m_userString);
    }
}

MyString::~MyString() {
    delete [] m_userString;
}