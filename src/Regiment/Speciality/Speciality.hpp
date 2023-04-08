#pragma once

#include <bits/stdc++.h>

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
