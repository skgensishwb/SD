#pragma once

class MyString {
    private:
        int m_size;
        char* m_userString;
    public:
        char get(int i); // получение i-того элемента строки;
        void set(int i, char c); // установка i-того элемента строки;
        void setNewString(const char *str); // замена текущего содержимого на новое;
        void print(); // вывод строки на консоль;
        void readLine(); 
        /* 
            замена текущего содержимого строки на строку, считанную 
            с консоли (неопределенного размера).
        */

        char* getString();

        void clearString();

        void copyString(const char* newString);

        int len(const char* string);

        MyString();
        MyString(const char* stringCopy);
        MyString(const MyString& other);

        ~MyString();

};
