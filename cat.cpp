#include <iostream>

#include "cat.hpp"

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

void Text::read_line() {
    clearString();

    char c;

    int newStringLen = stringLen;
    int capacityStr = 0;

    int newCountOfWords = countOfWords;
    int capacityWordArray = 0;

    while (cin.get(c) && c != '\n') { // нужно реализовать массив размеров
        if (c == ' ') {
            if (capacityWordArray + 1 >= newCountOfWords) {
                newCountOfWords *= 2;

                char** newArray = new char*[newCountOfWords];

                for (int i = 0; i < capacityWordArray; i++) {
                    for (int j=0; j < capacityStr; j++) {
                        newArray[i][j] = arrayOfWords[i][j];
                    }
                }

                delete[] arrayOfWords;
                arrayOfWords = newArray;
                countOfWords = capacityStr;
            }

            for (int i=0; i<capacityWordArray; i++) { // будет ли переполнение?
                arrayOfWords[capacityStr][i] = word[i];
            }
            
            слово сбросить (и размеры)
        }
        if (capacityStr + 1 >= newStringLen) {
            newStringLen *= 2;

            char* newString = new char[newStringLen];

            for (int i = 0; i < capacityStr; i++) {
                newString[i] = word[i];
            }

            delete[] word;
            word = newString;
        }
        word[capacityStr++] = c;
    }
}

void Text::clearString(ЧТО-ТО ПРИНИМАЕТ) {
    stringLen = 0;

    char* newString = new char[stringLen + 1];
    newString[0] = '\0';

    delete[] word;

    word = newString;
    stringLen += 1;
}

Text::Text() {
    stringLen = 40;
    countOfWords = 10;

    clearString();
}