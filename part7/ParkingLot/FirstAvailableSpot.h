#pragma once

#include <vector>

#include "ParkingSpot.h"
#include "ParkingFloor.h"
#include "SpotStrategy.h"

class FirstAvailableSpot : public SpotStrategy
{
public:
    ParkingSpot *findSpot(std::vector<ParkingFloor> &pf, Vehicle v) override;
};