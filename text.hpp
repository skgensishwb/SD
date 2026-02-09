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
        // Text(char* input, int len=40);

        //реализовать отдельный метод который разбирает строку на слова

        ~Text();

    private:
        void addWord(char* word, int len);

        void clear();

        void printLine();

};