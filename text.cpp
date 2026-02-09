#include <iostream>

#include "text.hpp"

using namespace std;

/* Реализуйте следующую программу. Пользователь вводит строку (любого
     * размера), после чего пользователю выводится на консоль следующее
     * изображение, где его ввод помещен в "speech bubble":
     *
     *  _____________________________________
     * / Here user input is shown. This line \
     * \ must be at most 40 characters long. /
     *  ------------------------------------
     *     \
     *      \
     *        /\_/\  (
     *       ( ^.^ ) _)
     *         \"/  (
     *       ( | | )
     *      (__d b__)
     *
     *  При этом длина строки в "облачке" должна быть не более 40 символов, при
     *  этом слова должны переноситься аккуратно. Это означет, что не должно
     *  быть переносов в центре слова (если только это слово не больше 40
     *  символов).
     *
     *  Дизайн облачка и ASCII-арт допустимо поменять по усмотрению.
     *
     *  Подсказка: обратите внимание на конкатенацию строковых литералов в
     *  языке С, это позволит задавать подобные рисунки так, чтобы они
     *  адекватно выглядели в коде.
    */

void Text::readLine() {
    clear();
    cout << "\n\n\nInput a string: " << endl;

    char c;
    
    int bufCap = 8;
    int bufLen = 0;
    char* buf = new char[bufCap];

    int newBufCap;

    while (cin.get(c) && c != '\n') {
        if (c == ' ') { // все еще проблема начальных пробелов
            addWord(buf, bufLen);
            bufLen = 0;
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

    addWord(buf, bufLen);

    delete[] buf;
    
    printLine();
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

Text::~Text() {
    clear();
}