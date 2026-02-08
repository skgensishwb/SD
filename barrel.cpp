#include <iostream>

#include "barrel.hpp"

using namespace std;

float Barrel::get_concentarion() {
    return (this->m_concentration);
}


void Barrel::pourOverFromTo(Barrel& r2) {

    // r1.method(r2)
    
    r2.m_liters += 1;
    this->m_liters -=1;

    r2.m_concentration = countConcentration(
        this->m_concentration,
        r2.m_concentration,
        (r2.m_liters - 1),
        r2.m_liters
    );
}

float Barrel::countConcentration(
    float firstConcentration,
    float secondConcentration,
    int secondVpreviously,
    int secondVnew
) {

    float concentration;
    concentration = ((1 - firstConcentration) + secondVpreviously*secondConcentration) / (float)secondVnew;
    return concentration;
}

Barrel::Barrel(int liters, float concentration) {
            m_liters = liters;
            m_concentration = concentration;
        };

Barrel::Barrel() {
            m_liters = 20;
            m_concentration = 1.f;
        };