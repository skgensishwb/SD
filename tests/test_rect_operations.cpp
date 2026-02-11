#include <cassert>
#include <iostream>

#include "../src/rect.hpp"

int main() {
    // Тест move
    {
        Rect r(0, 10, 20, 5);
        r.move(3, 7);
        assert(r.get_left() == 3);
        assert(r.get_right() == 13);
        assert(r.get_top() == 27);
        assert(r.get_bottom() == 12);
    }

    // Тест move с отрицательными значениями
    {
        Rect r(5, 15, 20, 10);
        r.move(-3, -5);
        assert(r.get_left() == 2);
        assert(r.get_right() == 12);
        assert(r.get_top() == 15);
        assert(r.get_bottom() == 5);
    }

    // Тест move с нулями (без перемещения)
    {
        Rect r(1, 2, 3, 4);
        r.move(0, 0);
        assert(r.get_left() == 1);
        assert(r.get_right() == 2);
        assert(r.get_top() == 3);
        assert(r.get_bottom() == 4);
    }

    // Тест inflate(int amount) — все стороны
    {
        Rect r(0, 10, 20, 5);
        r.inflate(2);
        assert(r.get_left() == 2);
        assert(r.get_right() == 12);
        assert(r.get_top() == 22);
        assert(r.get_bottom() == 7);
    }

    // Тест inflate(int dw, int dh)
    {
        Rect r(0, 10, 20, 5);
        r.inflate(3, 5);
        assert(r.get_left() == 3);
        assert(r.get_right() == 13);
        assert(r.get_top() == 25);
        assert(r.get_bottom() == 10);
    }

    // Тест inflate(int d_left, int d_right, int d_top, int d_bottom)
    {
        Rect r(0, 10, 20, 5);
        r.inflate(1, 2, 3, 4);
        assert(r.get_left() == 1);
        assert(r.get_right() == 12);
        assert(r.get_top() == 23);
        assert(r.get_bottom() == 9);
    }

    std::cout << "test_rect_operations: ALL PASSED" << std::endl;
    return 0;
}
