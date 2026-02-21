#include <iostream>

#include "matrix.hpp"

using namespace std;

void Matrix::zeroMatrix(int m, int n) {
    this->m_m = m;
    this->m_n = n;
    this->data = new double*[m];
    for (int i = 0; i < getHeight(); ++i) {
        this->data[i] = new double[n]();
    }
}

double Matrix::get(int i, int j) {
    return data[i][j];
}

void Matrix::set(int i, int j, double value) {
    data[i][j] = value;
}

int Matrix::getHeight(){
    return m_m;
}

int Matrix::getWidth(){
    return m_n;
}

void Matrix::negate(){
    for (int i=0; i<getHeight(); i++) {
            for (int j=0; j<getWidth(); j++) {
                if (get(i, j) != 0) {
                    set(i, j, -(get(i, j)));
                }
                else {
                    set(i, j, 0);
                }
            }
        }
}

void Matrix::addInPlace(Matrix& other){
    if (!((this->m_m == other.m_m) && (this->m_n == other.m_n))) {
        throw logic_error("Incorrect dimensions");
    }

    for (int i=0; i<getHeight(); i++) {
            for (int j=0; j<getWidth(); j++) {
                this->data[i][j] += other.data[i][j];
            }
        }
}

Matrix Matrix::multiply(Matrix& other){
    if (!(this->m_n == other.m_m)) {
        throw logic_error("Incorrect dimensions");
    }

    Matrix result(this->m_m, other.m_n, 0);

    double summ;
    for (int k=0; k<(this->getHeight()) ;k++) {
        for (int j=0; j<(other.getWidth()); j++) { 
            summ = 0;
            for (int i=0; i<(this->getWidth()); i++) {
                summ += ((this->get(k, i) ) * (other.get(i, j)));
            }
            result.set(k, j, summ);
        }
    }

    return result;
}



Matrix::Matrix(int n) {
    zeroMatrix(n, n);
    for (int i = 0; i < n; ++i) {
        this->data[i][i] = 1.0;
    }
}

Matrix::Matrix(int m, int n, double fillValue) {
    zeroMatrix(m, n);

    for (int i=0; i<getHeight(); i++) {
            for (int j=0; j<getWidth(); j++) {
                this->data[i][j] = fillValue;
            }
        }
}

Matrix::Matrix(const Matrix& other) : m_m(other.m_m), m_n(other.m_n) {
    for (int i=0; i<other.m_m; i++) {
            for (int j=0; j<other.m_n; j++) {
                this->data[i][j] = other.data[i][j];
            }
        }
}

Matrix::~Matrix() {
    for (int i=0; i<getHeight(); i++) {
            delete[] data[i];
        }
    delete[] data;
}
