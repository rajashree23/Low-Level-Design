#pragma once

#include "Payment.h"

class UPIPayment : public PaymentMethod
{
public:
    void process(double amount) override;
};