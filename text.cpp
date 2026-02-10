#include <iostream>

#include "text.hpp"

using namespace std;

void Text::readLine() {
    clear();
    cout << "\n\n\nInput a string: " << endl;

    char c;

    int inputLen = 0;
    int inputCap = 50;
    int newStrCap = 0;

    char* input = new char[inputCap];

    while (cin.get(c) && c != '\n') {
        if (inputLen >= inputCap) {
            newStrCap = inputCap * 2;
            char* newInput = new char[newStrCap];

            for (int i=0; i< inputLen; i++) {
                newInput[i] = input[i];
            }

            delete[] input;
            input = newInput;
            inputCap = newStrCap;
        }
        input[inputLen++] = c;
    }

    splitStringIntoWords(input, inputLen);

    delete[] input;
}

void Text::addWord(char* word, int len) {
    if (len == 0) {
        return;
    }

    if (arrayWordCount >= arrayWordCapacity) {
        int newCap = (arrayWordCapacity == 0) ? 4 : arrayWordCapacity * 2;

        char** newArrayOfWords = new char*[newCap];
        int* newLenOfWords = new int[newCap];

        for (int i=0; i<arrayWordCount ; i++) {
            newArrayOfWords[i] = arrayOfWords[i];
            newLenOfWords[i] = lenOfWords[i];
        }

        delete[] arrayOfWords;
        arrayOfWords = newArrayOfWords;

        delete[] lenOfWords;
        lenOfWords = newLenOfWords;

        arrayWordCapacity = newCap;

    }

    char* newWord = new char[len + 1];
    for (int i=0; i < len + 1; i++) {
        newWord[i] = word[i];
    }
    newWord[len] = '\0';

    lenOfWords[arrayWordCount] = len;
    arrayOfWords[arrayWordCount] = newWord;
    arrayWordCount++;
}

void Text::splitStringIntoWords(const char* string, int len) {
    clear();

    char c;
    
    int bufCap = 15;
    int bufLen = 0;
    char* buf = new char[bufCap];

    int newBufCap;

    while (cin.get(c) && c != '\n') {
        if (c == ' ') {
            if (bufLen > 0) {
                addWord(buf, bufLen);
                bufLen = 0;
            }
        } 
        else {
            if (bufLen >= bufCap) {
                newBufCap = bufCap * 2; 

                char* newBuf = new char[newBufCap];
                for (int i=0; i<bufLen ; i++) {
                    newBuf[i] = buf[i];
                }
                
                delete[] buf;
                buf = newBuf;
                bufCap = newBufCap;
            }
            buf[bufLen++] = c;
        }
    }

    if (bufLen > 0) {
        addWord(buf, bufLen);
    }

    delete[] buf;

    printLine();
}

void Text::clear() {
    for (int i=0; i < arrayWordCount; i++) {
        delete[] arrayOfWords[i];
    }

    delete[] lenOfWords;
    delete[] arrayOfWords;
    lenOfWords = nullptr;
    arrayOfWords = nullptr;
    arrayWordCount = 0 ;
    arrayWordCapacity = 0 ;
}

void Text::printLine() {
    int lenString = 0; 
    for (int i=0;  i< arrayWordCount; i++) {
        if (lenOfWords[i] > lenOfString) {
            if (lenString != 0) {
                cout << endl;
            }
            int pos = 0;
            while (pos < lenOfWords[i]) {
                int chunk = lenOfWords[i] - pos;
                if (chunk > lenOfString) chunk = lenOfString;
                for (int j = 0; j < chunk; j++) {
                    cout << arrayOfWords[i][pos + j];
                }
                pos += chunk;
                if (pos < lenOfWords[i]) cout << endl;
                lenString = chunk;
            }
        }
        else {
            if (lenString + lenOfWords[i] > lenOfString) {
                cout << endl;
                lenString = 0;
            }

            for (int j=0; j < lenOfWords[i]; j++) {
                cout <<  arrayOfWords[i][j];
                lenString++;
            }

            if (lenString < lenOfString) {
                cout << ' ';
                lenString ++;
            }
        }
    }

    cout << endl;
}

Text::Text() : arrayOfWords(nullptr), lenOfWords(nullptr),
               arrayWordCount(0), arrayWordCapacity(0), lenOfString(40) {}

Text::Text(const char* input, int len=40) {
    splitStringIntoWords(input, len);
}

Text::Text(MyString& input, int len) {
    splitStringIntoWords(input.getString(), len);
}

Text::~Text() {
    clear();
}