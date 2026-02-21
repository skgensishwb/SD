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

    if (m_arrayWordCount >= m_arrayWordCapacity) {
        int newCap = (m_arrayWordCapacity == 0) ? 4 : m_arrayWordCapacity * 2;

        char** newArrayOfWords = new char*[newCap];
        int* newLenOfWords = new int[newCap];

        for (int i=0; i<m_arrayWordCount ; i++) {
            newArrayOfWords[i] = m_arrayOfWords[i];
            newLenOfWords[i] = m_lenOfWords[i];
        }

        delete[] m_arrayOfWords;
        m_arrayOfWords = newArrayOfWords;

        delete[] m_lenOfWords;
        m_lenOfWords = newLenOfWords;

        m_arrayWordCapacity = newCap;

    }

    char* newWord = new char[len + 1];
    for (int i=0; i < len; i++) {
        newWord[i] = word[i];
    }
    newWord[len] = '\0';

    m_lenOfWords[m_arrayWordCount] = len;
    m_arrayOfWords[m_arrayWordCount] = newWord;
    m_arrayWordCount++;
}

void Text::splitStringIntoWords(const char* stringToSplit, int len) {
    clear();

    int bufCap = 15;
    int bufLen = 0;
    char* buf = new char[bufCap];

    int newBufCap;

    for (int j=0; j<len; j++) {
        if (stringToSplit[j] == ' ') {
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
            buf[bufLen++] = stringToSplit[j];
        }
    }

    if (bufLen > 0) {
        addWord(buf, bufLen);
    }

    delete[] buf;

    printLine();
}

void Text::clear() {
    for (int i=0; i < m_arrayWordCount; i++) {
        delete[] m_arrayOfWords[i];
    }

    delete[] m_lenOfWords;
    delete[] m_arrayOfWords;
    m_lenOfWords = nullptr;
    m_arrayOfWords = nullptr;
    m_arrayWordCount = 0 ;
    m_arrayWordCapacity = 0 ;
}

void Text::printLine() {
    cout << endl;

    int lenString = 0; 
    for (int i=0;  i< m_arrayWordCount; i++) {
        if (m_lenOfWords[i] > m_lenOfString) {
            if (lenString != 0) {
                cout << endl;
            }
            int pos = 0;
            while (pos < m_lenOfWords[i]) {
                int chunk = m_lenOfWords[i] - pos;
                if (chunk > m_lenOfString) chunk = m_lenOfString;
                for (int j = 0; j < chunk; j++) {
                    cout << m_arrayOfWords[i][pos + j];
                }
                pos += chunk;
                if (pos < m_lenOfWords[i]) cout << endl;
                lenString = chunk;
            }
        }
        else {
            if (lenString + m_lenOfWords[i] > m_lenOfString) {
                cout << endl;
                lenString = 0;
            }

            for (int j=0; j < m_lenOfWords[i]; j++) {
                cout <<  m_arrayOfWords[i][j];
                lenString++;
            }

            if (lenString < m_lenOfString) {
                cout << ' ';
                lenString ++;
            }
        }
    }

    cout << endl;
}

Text::Text()
    : m_lenOfString(40),
      m_arrayWordCount(0),
      m_arrayWordCapacity(0),
      m_lenOfWords(nullptr),
      m_arrayOfWords(nullptr) {}

Text::Text(const char* input, int maxWidth)
    : m_lenOfString(maxWidth),
      m_arrayWordCount(0),
      m_arrayWordCapacity(0),
      m_lenOfWords(nullptr),
      m_arrayOfWords(nullptr)
{
    int inputLen = 0;
    while (input[inputLen] != '\0') inputLen++;
    splitStringIntoWords(input, inputLen);
}

Text::Text(MyString& input, int len)
    : m_lenOfString(len),
      m_arrayWordCount(0),
      m_arrayWordCapacity(0),
      m_lenOfWords(nullptr),
      m_arrayOfWords(nullptr)
{
    char* str = input.getString();
    int inputLen = 0;
    while (str[inputLen] != '\0') inputLen++;
    splitStringIntoWords(str, inputLen);
}

Text::~Text() {
    clear();
}