#include "Account.h"

double Account::getBalance()
{
    return balance;
}

void Account::deposit(double amount)
{
    balance += amount;
}

void Account::setBalance(double amount)
{
    balance = amount;
}