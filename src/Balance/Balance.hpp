#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include "Printer.hpp"

#include "Regiment.hpp"
#include "Game.hpp"


class Balance {
    public:
        Balance();
        ~Balance();

        void init();
        void calculate();
        void sort();
        void display();

        std::vector<Regiment *> _regiments = {};
        std::vector<Game *> _games = {};

    protected:
    private:
        constexpr static auto FILEPATHINPUT = "./input.txt";
        void input();
};
