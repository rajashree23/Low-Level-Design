#pragma once

enum class PaymentType{
    UPI, CARD
};

class PaymentProcessor{
    public:
    bool process(double amount, PaymentType type);
};