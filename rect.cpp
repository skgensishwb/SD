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
    int width = mod( (r.get_right() - r.get_left()) );
    int hight = mod( (r.get_top() - r.get_bottom()) );

    int widthWithOutBorders = 0;
    int hightWithOutBorders = 0;
    if (width > 1 && hight > 1) { 
        widthWithOutBorders = width-1; 
        hightWithOutBorders = hight-2;
    }
    else {
        cout << "Something strange.." << endl;
        return;
    }

    for (int i=0; i<width; i++) {
        cout << "—";
    }

    cout << endl;

    for (int i=0; i<hightWithOutBorders; i++) {
        cout << '|';
        for (int j=0; j< widthWithOutBorders; j++) {
            cout << ' ';
        }
        cout << '|' << endl;
    }

    for (int i=0; i<width; i++) {
        cout << "—";
    }

    cout << endl;
}

int mod(int number) {
    if (number<0) { return (-number); }
    return number;
}

void Rect::set_all(int left, int right, int top, int bottom) {
            m_leftBorder = left;
            m_rightBorder = right;
            m_topBorder = top;
            m_bottomBorder = bottom;
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
    set_all(
        (get_left() + moveX),
        (get_right() + moveX),
        (get_top() + moveY),
        (get_bottom() + moveY)
    );
}

void Rect::showLRTB() {
        cout << "Left: " << m_leftBorder << endl;
        cout << "Right: " << m_rightBorder << endl;
        cout << "Top: " << m_topBorder << endl;
        cout << "Bottom: " << m_bottomBorder << endl;
    }

Rect::Rect(int m_leftBorder, int m_rightBorder, int m_topBorder, int m_bottomBorder) {
            
            #ifndef NDEBUG
                cout << "The constructor with parameters is called: " << this << endl;
            #endif

            this->m_leftBorder = m_leftBorder;
            this->m_rightBorder = m_rightBorder;
            this->m_topBorder = m_topBorder;
            this->m_bottomBorder = m_bottomBorder;
        }

Rect::Rect() {

            #ifndef NDEBUG
                cout << "Explicit default constructor called: " << this << endl;
            #endif

            m_leftBorder = 0;
            m_rightBorder = 0;
            m_topBorder = 0;
            m_bottomBorder = 0;
        }

Rect::Rect(const Rect& other) 
        : m_leftBorder(other.m_leftBorder),
            m_rightBorder(other.m_rightBorder),
            m_topBorder(other.m_topBorder),
            m_bottomBorder(other.m_bottomBorder)
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