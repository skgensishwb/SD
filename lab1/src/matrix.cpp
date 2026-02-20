#include <iostream>

#include "matrix.hpp"

using namespace std;

void Matrix::zeroMatrix(int m, int n) {
    this->m = m;
    this->n = n;
    this->data = new double*[m];
    for (int i = 0; i < get_height(); ++i) {
        this->data[i] = new double[n]();
    }
}

double Matrix::get(int i, int j) {
    return data[i][j];
}

void Matrix::set(int i, int j, double value) {
    data[i][j] = value;
}

int Matrix::get_height(){
    return m;
}

int Matrix::get_width(){
    return n;
}

void Matrix::negate(){
    for (int i=0; i<get_height(); i++) {
            for (int j=0; j<get_width(); j++) {
                if (get(i, j) != 0) {
                    set(i, j, -(get(i, j)));
                }
                else {
                    set(i, j, 0);
                }
            }
        }
}

void Matrix::add_in_place(Matrix& other){
    if (!((this->m == other.m) && (this->n == other.n))) {
        throw logic_error("Incorrect dimensions");
    }

    for (int i=0; i<get_height(); i++) {
            for (int j=0; j<get_width(); j++) {
                this->data[i][j] += other.data[i][j];
            }
        }
}

Matrix Matrix::multiply(Matrix& other){
    if (!(this->n == other.m)) {
        throw logic_error("Incorrect dimensions");
    }

    Matrix result(this->m, other.n, 0);

    double summ;
    for (int k=0; k<(this->get_height()) ;k++) {
        for (int j=0; j<(other.get_width()); j++) { 
            summ = 0;
            for (int i=0; i<(this->get_width()); i++) {
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

Matrix::Matrix(int m, int n, double fill_value) {
    zeroMatrix(m, n);

    for (int i=0; i<get_height(); i++) {
            for (int j=0; j<get_width(); j++) {
                this->data[i][j] = fill_value;
            }
        }
}

Matrix::Matrix(const Matrix& other) : m(other.m), n(other.n) {
    for (int i=0; i<other.m; i++) {
            for (int j=0; j<other.n; j++) {
                this->data[i][j] = other.data[i][j];
            }
        }
}

Matrix::~Matrix() {
    for (int i=0; i<get_height(); i++) {
            delete[] data[i];
        }
    delete[] data;
}
