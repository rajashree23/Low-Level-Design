#include <iostream>
#include "UPIPayment.h"
#include "CreditCardPayment.h"

int main()
{
    PaymentMethod* payment;

    UPIPayment upi;
    CreditCardPayment creditCard;

    payment = &upi;
    payment->process(1000);

    payment = &creditCard;
    payment->process(2000);

    return 0;
}