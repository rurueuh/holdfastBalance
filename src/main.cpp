#include "Balance.hpp"

int main(void)
{
    Balance balance;

    balance.init();
    balance.calculate();
    balance.sort();
    balance.display();
    return 0;
}