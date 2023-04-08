#pragma once

#include <bits/stdc++.h>
#include "Speciality/Speciality.hpp"

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
