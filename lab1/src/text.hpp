#pragma once

#include "mystring.hpp"

class Text {
    private:
        int m_lenOfString;
        int m_arrayWordCount;
        int m_arrayWordCapacity;
        
        int* m_lenOfWords;
        char** m_arrayOfWords;

    public:
        void readLine();

        Text();
        Text(const char* input, int len=40);
        Text(MyString& input, int len);

        ~Text();

    private:
        void addWord(char* word, int len);

        void splitStringIntoWords(const char* string, int maxWidth);

        void clear();

        void printLine();

};