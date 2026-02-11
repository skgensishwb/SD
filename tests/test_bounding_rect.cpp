#include <cassert>
#include <iostream>

#include "../src/rect.hpp"

int main() {
    // Тест: обычный случай
    {
        Rect r1(0, 10, 20, 5);
        Rect r2(5, 15, 25, 0);
        Rect br = bounding_rect(r1, r2);
        assert(br.get_left() == 0);
        assert(br.get_right() == 15);
        assert(br.get_top() == 25);
        assert(br.get_bottom() == 0);
    }

    // Тест: один прямоугольник внутри другого
    {
        Rect r1(0, 20, 20, 0);
        Rect r2(5, 15, 15, 5);
        Rect br = bounding_rect(r1, r2);
        assert(br.get_left() == 0);
        assert(br.get_right() == 20);
        assert(br.get_top() == 20);
        assert(br.get_bottom() == 0);
    }

    // Тест: одинаковые прямоугольники
    {
        Rect r1(3, 7, 10, 2);
        Rect r2(3, 7, 10, 2);
        Rect br = bounding_rect(r1, r2);
        assert(br.get_left() == 3);
        assert(br.get_right() == 7);
        assert(br.get_top() == 10);
        assert(br.get_bottom() == 2);
    }

    // Тест: отрицательные координаты
    {
        Rect r1(-10, -1, 5, -5);
        Rect r2(-5, 10, 10, 0);
        Rect br = bounding_rect(r1, r2);
        assert(br.get_left() == -10);
        assert(br.get_right() == 10);
        assert(br.get_top() == 10);
        assert(br.get_bottom() == -5);
    }

    // Тест: перепутаны лево и право (left > right)
    {
        Rect r1(10, 0, 20, 5);   // left=10 > right=0
        Rect r2(0, 10, 20, 5);
        Rect br = bounding_rect(r1, r2);
        assert(br.get_left() == 0);
        assert(br.get_right() == 10);
    }

    // Тест: перепутаны верх и низ (top < bottom)
    {
        Rect r1(0, 10, 5, 20);   // top=5 < bottom=20
        Rect r2(0, 10, 20, 5);
        Rect br = bounding_rect(r1, r2);
        assert(br.get_top() == 20);
        assert(br.get_bottom() == 5);
    }

    std::cout << "test_bounding_rect: ALL PASSED" << std::endl;
    return 0;
}
