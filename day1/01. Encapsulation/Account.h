#pragma once

class Account
{
private:
    double balance=0;

public:
    double getBalance();
    void deposit(double amount);
    void setBalance(double amount); // bad setter method
};