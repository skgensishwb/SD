#pragma once

class Rect {
    private:
        // Старое представление:
        // int m_leftBorder;
        // int m_rightBorder;
        // int m_topBorder;
        // int m_bottomBorder;

        // Новое представление: левая нижняя точка + размеры
        int m_x; // координата X левой нижней точки (left)
        int m_y; // координата Y левой нижней точки (bottom)
        int m_width;
        int m_height;

    public:
        inline int get_left()   { return m_x; }
        inline int get_right()  { return m_x + m_width; }
        inline int get_top()    { return m_y + m_height; }
        inline int get_bottom() { return m_y; }

        int get_width();
        int get_height();

        int get_square();

        void set_width(int amount);
        void set_height(int amount);
        
        void set_all(int left, int right, int top, int bottom);

        void inflate(int amount);
        void inflate(int dw, int dh);
        void inflate(int d_left, int d_right, int d_top, int d_bottom);

        void move(int moveX=0, int moveY=0);
        
        void showLRTB();

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
