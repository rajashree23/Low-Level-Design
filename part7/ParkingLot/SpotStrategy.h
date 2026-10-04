#pragma once

#include <vector>

#include "ParkingSpot.h"
#include "ParkingFloor.h"
#include"Vehicle.h"

class SpotStrategy
{
public:
    virtual ParkingSpot* findSpot(std::vector<ParkingFloor> &pf, Vehicle v) = 0;

    virtual ~SpotStrategy() = default;
};