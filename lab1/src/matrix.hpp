#pragma once

class Matrix {
    private:
        int m_m{}; // Число строк
        int m_n{}; // Число столбцов

        double** data;

    public:
        void zeroMatrix(int m, int n);

        double get(int i, int j); // Получить значение элемента
        void set(int i, int j, double value); // Установить значение элемента
        int getHeight();
        int getWidth(); // Получить высоту и ширину соответственно
        void negate(); // Операция `-A` для матрицы
        void addInPlace(Matrix& other); // Операция `this += other` для матрицы;
        Matrix multiply(Matrix& other); // возвращает результат матричного умножения.

        Matrix(int n);
        Matrix(int m, int n, double fillValue = 0);

        Matrix(const Matrix& other);

        ~Matrix();
};