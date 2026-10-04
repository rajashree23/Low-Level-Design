#include <iostream>

#include "PaymentProcessor.h"

bool PaymentProcessor::process(double amount, PaymentType type)
{
    if (type == PaymentType::CARD)
    {
        std::cout << "Card payment processed for: "<<amount<<" "<< std::endl;
        return true;
    }
    if (type == PaymentType::UPI)
    {
        std::cout << "UPI payment processed for: "<<amount<<" "<< std::endl;
        return true;
    }

    std::cout << "Payment payment not supported" << std::endl;
    return false;
}