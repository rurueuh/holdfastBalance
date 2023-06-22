#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Printer.hpp"


class Speciality {
    public:
        Speciality(bool arty = false, bool cav = false, bool skirm = false) : arty(arty), cav(cav), skirm(skirm) {};
        ~Speciality();

        bool arty = false;
        bool cav = false;
        bool skirm = false;

    protected:
    private:
};
