class Matrix {
    private:
        int m{}; // число строк
        int n{}; // число столбцов

        double** data;

    public:
        void zeroMatrix(int m, int n);

        double get(int i, int j); // получить значение элемента
        void set(int i, int j, double value); // установить значение элемента
        int get_height();
        int get_width(); // получить высоту и ширину соответственно
        void negate(); // операция `-A` для матрицы
        void add_in_place(Matrix& other); // операция `this += other` для матрицы;
        Matrix multiply(Matrix& other); // возвращает результат матричного умножения.

        Matrix(int n);
        Matrix(int m, int n, double fill_value = 0);

        Matrix(const Matrix& other);

        ~Matrix();
};