#include "Payment.h"
#include <iostream>
using namespace std;

void Payment::process(PaymentMethod method, double amount)
{
    if (amount <= 0)
    {
        cout << "Amount can not be 0";
        return;
    }

    if (method == PaymentMethod::UPI)
    {
        cout << "UPI processed";
        return;
    }

    if (method == PaymentMethod::CREDIT_CARD)
    {
        cout << "Credit card processed";
        return;
    }

   cout<<"Declined";
}