class Text {
    private:
        int stringLen;
        int countOfWords;

        char* word;
        char** arrayOfWords;
    public:
        void read_line();

        void clearString();

        Text();


};