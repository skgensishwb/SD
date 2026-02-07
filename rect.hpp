#include <iostream>

using namespace std;


class Rect {
    public:
        float m_leftBorder;
        float m_rightBorder;
        float m_upperBorder;
        float m_lowerBorder;

    public:
        Rect(float m_leftBorder, float m_rightBorder, float m_upperBorder, float m_lowerBorder) {
            
            cout << "The constructor with parameters is called: " << this << endl;

            this->m_leftBorder = m_leftBorder;
            this->m_rightBorder = m_rightBorder;
            this->m_upperBorder = m_upperBorder;
            this->m_lowerBorder = m_lowerBorder;
        }

        Rect() {

            cout << "Explicit default constructor called: " << this << endl;

            m_leftBorder = 0;
            m_rightBorder = 0;
            m_upperBorder = 0;
            m_lowerBorder = 0;
        }

        Rect(const Rect& other) {
            cout << "Copy constructor 'called by the compiler': " << this << endl;
        }

        ~Rect() {
            cout << "The destructor has been called" << endl;
        }
};