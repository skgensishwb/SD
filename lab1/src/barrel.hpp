#pragma once

class Barrel {
    private:
        int m_liters;
        float m_concentration;

    private:
        float countConcentration(float thisConcentration, float secondConcentration, int secondVpreviously, int secondVnew);
        /* Считает концентрацию вещества по формуле */
    public:
        Barrel(int liters, float concentration);
        Barrel();

    public:
        float get_concentarion();

        void pourOverFromTo(Barrel& r2);
        /*
            r1.method(r2) <==> from r1 to r2
            Уменьшает/увеличивает объем при переливе
            и изменяет концентрациб вещества 2 (r2)
        */
};