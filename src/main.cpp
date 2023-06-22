#include "Balance.hpp"
#include "Printer.hpp"

std::ofstream Printer::file = std::ofstream("output.txt");

int main(void)
{
    Balance balance;

    balance.init();
    balance.calculate();
    balance.sort();
    balance.display();
    return 0;
}