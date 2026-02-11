#include <iostream>

#include "rect.hpp"

using namespace std;

Rect bounding_rect(Rect r1, Rect r2) {
    Rect r3;
    r3.set_all(
        ( min( r1.get_left(), r2.get_left() ) ),
        ( max( r1.get_right(), r2.get_right() ) ),
        ( min( r1.get_bottom(), r2.get_bottom() ) ),
        ( max( r1.get_top(), r2.get_top() ) )
    );
    return r3;
}

void print_rect(Rect &r) {
    int width = r.get_width();
    int height = r.get_height();

    int widthWithOutBorders = 0;
    int heightWithOutBorders = 0;
    if (width > 1 && height > 1) { 
        widthWithOutBorders = width-1; 
        heightWithOutBorders = height-2;
    }
    else {
        cout << "Something strange.." << endl;
        return;
    }

    for (int i=0; i<width; i++) {
        cout << "\xe2\x80\x94";
    }

    cout << endl;

    for (int i=0; i<heightWithOutBorders; i++) {
        cout << '|';
        for (int j=0; j< widthWithOutBorders; j++) {
            cout << ' ';
        }
        cout << '|' << endl;
    }

    for (int i=0; i<width; i++) {
        cout << "\xe2\x80\x94";
    }

    cout << endl;
}

int mod(int number) {
    if (number<0) { return (-number); }
    return number;
}

// Старая реализация:
// int Rect::get_width() {
//     return mod( (get_right() - get_left()) );
// }
// int Rect::get_height() {
//     return mod( (get_top() - get_bottom()) );
// }

// Новая реализация:
int Rect::get_width() {
    return mod(m_width);
}

int Rect::get_height() {
    return mod(m_height);
}

int Rect::get_square() {
    return ( get_width() * get_height() );
}

// Старая реализация:
// void Rect::set_width(int amount) {
//     m_rightBorder = m_leftBorder + amount;
// }
// void Rect::set_height(int amount) {
//     m_topBorder = m_bottomBorder + amount;
// }

// Новая реализация:
void Rect::set_width(int amount) {
    m_width = amount;
}

void Rect::set_height(int amount) {
    m_height = amount;
}

// Старая реализация:
// void Rect::set_all(int left, int right, int top, int bottom) {
//     m_leftBorder = left;
//     m_rightBorder = right;
//     m_topBorder = top;
//     m_bottomBorder = bottom;
// }

// Новая реализация:
void Rect::set_all(int left, int right, int top, int bottom) {
    m_x = left;
    m_y = bottom;
    m_width = right - left;
    m_height = top - bottom;
}

void Rect::inflate(int amount) {
    set_all(
        (get_left() + amount),
        (get_right() + amount),
        (get_top() + amount),
        (get_bottom() + amount)
    );
}

void Rect::inflate(int dw, int dh) {
    set_all(
        (get_left() + dw),
        (get_right() + dw),
        (get_top() + dh),
        (get_bottom() + dh)
    );
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    set_all(
        (get_left() + d_left),
        (get_right() + d_right),
        (get_top() + d_top),
        (get_bottom() + d_bottom)
    );
}

void Rect::move(int moveX, int moveY) {
    // Старая реализация пересчитывала все 4 границы через set_all.
    // Новая — просто сдвигает точку:
    m_x += moveX;
    m_y += moveY;
}

void Rect::showLRTB() {
    cout << "Left: " << get_left() << endl;
    cout << "Right: " << get_right() << endl;
    cout << "Top: " << get_top() << endl;
    cout << "Bottom: " << get_bottom() << endl;
}

// Старая реализация:
// Rect::Rect(int m_leftBorder, int m_rightBorder, int m_topBorder, int m_bottomBorder) {
//     this->m_leftBorder = m_leftBorder;
//     this->m_rightBorder = m_rightBorder;
//     this->m_topBorder = m_topBorder;
//     this->m_bottomBorder = m_bottomBorder;
// }

// Новая реализация:
Rect::Rect(int left, int right, int top, int bottom)
    : m_x(left),
      m_y(bottom),
      m_width(right - left),
      m_height(top - bottom)
{
    #ifndef NDEBUG
        cout << "The constructor with parameters is called: " << this << endl;
    #endif
}

// Старая реализация:
// Rect::Rect() {
//     m_leftBorder = 0; m_rightBorder = 0;
//     m_topBorder = 0;  m_bottomBorder = 0;
// }

// Новая реализация:
Rect::Rect()
    : m_x(0), m_y(0), m_width(0), m_height(0)
{
    #ifndef NDEBUG
        cout << "Explicit default constructor called: " << this << endl;
    #endif
}

// Старая реализация:
// Rect::Rect(const Rect& other)
//     : m_leftBorder(other.m_leftBorder),
//       m_rightBorder(other.m_rightBorder),
//       m_topBorder(other.m_topBorder),
//       m_bottomBorder(other.m_bottomBorder) {}

// Новая реализация:
Rect::Rect(const Rect& other)
    : m_x(other.m_x),
      m_y(other.m_y),
      m_width(other.m_width),
      m_height(other.m_height)
{
    #ifndef NDEBUG
        cout << "Copy constructor 'called by the compiler': " << this << endl;
    #endif
}

Rect::~Rect() {
    #ifndef NDEBUG
        cout << "The destructor has been called" << endl;
    #endif
}
