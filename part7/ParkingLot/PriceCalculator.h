#pragma once

#include <ctime>

class PriceCalculator{
    public:
    double calculate(double cost, time_t timestamp);
};