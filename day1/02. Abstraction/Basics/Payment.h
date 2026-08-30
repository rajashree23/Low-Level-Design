#pragma once

enum class PaymentMethod
{
    UPI,
    CREDIT_CARD
};

class Payment
{
public:
    void process(PaymentMethod method, double amount);
};