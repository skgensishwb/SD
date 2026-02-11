#include <cassert>
#include <iostream>

#include "../src/rect.hpp"

int main() {
    // Тест get_width и get_height
    {
        Rect r(0, 10, 20, 5);
        assert(r.get_width() == 10);
        assert(r.get_height() == 15);
    }

    // Тест get_square
    {
        Rect r(0, 10, 20, 5);
        assert(r.get_square() == 150);
    }

    // Тест с нулевыми размерами
    {
        Rect r;
        assert(r.get_width() == 0);
        assert(r.get_height() == 0);
        assert(r.get_square() == 0);
    }

    // Тест set_width
    {
        Rect r(5, 10, 20, 0);
        r.set_width(30);
        assert(r.get_left() == 5);
        assert(r.get_right() == 35);  // left + 30
        assert(r.get_width() == 30);
    }

    // Тест set_height
    {
        Rect r(0, 10, 20, 5);
        r.set_height(50);
        assert(r.get_bottom() == 5);
        assert(r.get_top() == 55);  // bottom + 50
        assert(r.get_height() == 50);
    }

    // Тест: width/height при перепутанных координатах (left > right)
    {
        Rect r(10, 0, 5, 20);
        assert(r.get_width() == 10);   // mod(0 - 10) = 10
        assert(r.get_height() == 15);  // mod(5 - 20) = 15
    }

    std::cout << "test_rect_properties: ALL PASSED" << std::endl;
    return 0;
}
