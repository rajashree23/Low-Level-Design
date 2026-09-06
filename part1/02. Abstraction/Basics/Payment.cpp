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
        // handle authorisation
        // handle key etc
        // not to be handled by other service/ caller that isn't responsible for maintaining it.
        cout << "UPI processed";
        return;
    }

    if (method == PaymentMethod::CREDIT_CARD)
    {
        // handle authorisation
        // handle key etc
        // not to be handled by other service/ caller that isn't responsible for maintaining it.
        cout << "Credit card processed";
        return;
    }

   cout<<"Declined";
}
