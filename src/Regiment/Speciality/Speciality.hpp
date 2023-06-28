#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Printer.hpp"


class Speciality {
    public:
        Speciality(bool arty = false, bool cav = false, bool skirm = false, bool mountedInfantry = false)
            : arty(arty), cav(cav), skirm(skirm), mountedInfantry(mountedInfantry) {};
        ~Speciality();

        bool arty = false;
        bool cav = false;
        bool skirm = false;
        bool mountedInfantry = false;

    protected:
    private:
};
