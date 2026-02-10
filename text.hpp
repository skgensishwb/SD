#pragma once

#include "mystring.hpp"

class Text {
    private:
        int lenOfString;
        int arrayWordCount;
        int arrayWordCapacity;
        
        int* lenOfWords;
        char** arrayOfWords;

    public:
        void readLine();

        Text();
        Text(const char* input, int len=40);
        Text(MyString& input, int len=40);

        ~Text();

    private:
        void addWord(char* word, int len);

        void splitStringIntoWords(const char* string, int len);

        void clear();

        void printLine();

};