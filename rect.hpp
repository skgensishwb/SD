class Rect {
    private:
        int m_leftBorder;
        int m_rightBorder;
        int m_topBorder;
        int m_bottomBorder;

    public:
        inline int get_left() { return m_leftBorder; }
        inline int get_right() { return m_rightBorder; }
        inline int get_top() { return m_topBorder; }
        inline int get_bottom() { return m_bottomBorder; }

        int get_width();
        int get_height();

        int get_square();

        void set_width(int amount);
        void set_height(int amount);
        
        void set_all(int left, int right, int top, int bottom);

        void inflate(int amount);
        // отодвигает каждую из сторон от центра прямоугольника на величину `amount`
        void inflate(int dw, int dh);
        // отодвигает верхнюю и нижнюю сторону на `dh`, а левую и правую - на `dw`
        void inflate(int d_left, int d_right, int d_top, int d_bottom);
        // аналогично, но для каждой стороны отдельно

        void move(int moveX=0, int moveY=0);
        // перемещает прямоугольник на moveX по X и на moveY по Y
        
        void showLRTB();
        // Выводит все значения

        Rect(int m_leftBorder, int m_rightBorder, int m_topBorder, int m_bottomBorder);
        Rect();
        Rect(const Rect& other);

        ~Rect();
};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);
int mod(int number);

inline int max(int firstNumber, int secondNumber) {
    if (firstNumber > secondNumber) { return firstNumber; }
    return secondNumber;
}

inline int min(int firstNumber, int secondNumber) {
    if (firstNumber < secondNumber) { return firstNumber; }
    return secondNumber;
}