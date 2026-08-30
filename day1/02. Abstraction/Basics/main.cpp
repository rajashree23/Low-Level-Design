#include <iostream>
#include "Payment.h"
using namespace std;

int main()
{
    double amount;
    cin >> amount;

    Payment payment;
    payment.process(PaymentMethod::UPI, amount);
    return 0;
}