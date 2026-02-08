class Barrel {
    private:
        int m_liters;
        float m_concentration;

    private:
        float countConcentration(float firstConcentration, float secondConcentration, int secondVpreviously, int secondVnew);

    public:
        Barrel(int liters, float concentration);
        Barrel();

    public:
        float get_concentarion();

        void pourOverFromTo(Barrel& r2);
};