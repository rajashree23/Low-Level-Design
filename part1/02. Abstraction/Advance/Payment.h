#pragma once

class PaymentMethod
{
public:
    virtual ~PaymentMethod() = default;

    // Pure virtual function → defines the interface
    virtual void process(double amount) = 0;
};