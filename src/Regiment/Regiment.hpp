#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Speciality/Speciality.hpp"
#include "Printer.hpp"


class Regiment {
    public:
        Regiment(const std::string &name, int nbPlayer, Speciality *wantedSpeciality);
        ~Regiment();

        std::string _name = "";
        int _nbPlayer = 0;
        Speciality *wantedSpeciality = nullptr;
        Speciality *currentSpeciality = nullptr;
        int _oldSpeCount = 0;

    protected:
    private:
};
