#include <ctime>

#include "PriceCalculator.h"

double PriceCalculator::calculate(double cost, time_t timestamp)
{
    auto curr = time(nullptr);
    auto duration = curr - timestamp;

    if (duration == 0)
    {
        return cost;
    }

    auto hours = (duration + 3599) / 3600;

    return cost * hours;
}