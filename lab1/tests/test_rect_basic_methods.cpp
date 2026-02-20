#include <cassert>
#include <iostream>

#include "../src/rect.hpp"

int main() {
    // Тест конструктора по умолчанию
    {
        Rect r;
        assert(r.get_left() == 0);
        assert(r.get_right() == 0);
        assert(r.get_top() == 0);
        assert(r.get_bottom() == 0);
    }

    // Тест конструктора с параметрами
    {
        Rect r(1, 10, 20, 5);
        assert(r.get_left() == 1);
        assert(r.get_right() == 10);
        assert(r.get_top() == 20);
        assert(r.get_bottom() == 5);
    }

    // Тест конструктора копирования
    {
        Rect r1(3, 7, 15, 2);
        Rect r2(r1);
        assert(r2.get_left() == 3);
        assert(r2.get_right() == 7);
        assert(r2.get_top() == 15);
        assert(r2.get_bottom() == 2);
    }

    // Тест set_all
    {
        Rect r;
        r.set_all(5, 20, 30, 10);
        assert(r.get_left() == 5);
        assert(r.get_right() == 20);
        assert(r.get_top() == 30);
        assert(r.get_bottom() == 10);
    }

    // Тест set_all с отрицательными координатами
    {
        Rect r;
        r.set_all(-10, -1, 5, -5);
        assert(r.get_left() == -10);
        assert(r.get_right() == -1);
        assert(r.get_top() == 5);
        assert(r.get_bottom() == -5);
    }

    std::cout << "test_rect_basic_methods: ALL PASSED" << std::endl;
    return 0;
}
