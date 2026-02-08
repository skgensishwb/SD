class MyString {
    private:
        int size;
        char* string;
    public:
        char get(int i); // получение i-того элемента строки;
        void set(int i, char c); // установка i-того элемента строки;
        void set_new_string(const char *str); // замена текущего содержимого на новое;
        void print(); // вывод строки на консоль;
        void read_line(); 
        /* 
            замена текущего содержимого строки на строку, считанную 
            с консоли (неопределенного размера).
        */

        char* copyString(const char* newString);

        int len(const char* string);

        MyString();
        MyString(const char* stringCopy);

};
