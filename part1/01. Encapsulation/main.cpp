#include <iostream>
#include "Account.h"

int main()
{
    Account account;

    account.deposit(1000);

    std::cout << account.getBalance() << std::endl;

    // account.balance = 5000; // won't work now


    account.setBalance(-1000); // BAD DESIGN 
    std::cout << account.getBalance() << std::endl;

    return 0;
}