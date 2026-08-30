#pragma once

#include "Payment.h"

class CreditCardPayment : public PaymentMethod
{
public:
    void process(double amount) override;
};