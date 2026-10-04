#pragma once

#include <string>
#include <vector>
#include <memory>

#include "ParkingSpot.h"

class ParkingFloor
{
private:
    std::string id;
    std::vector<std::unique_ptr<ParkingSpot>> parkingSpots;

public:
    ParkingFloor(std::string id);

    void addParkingSpots(std::unique_ptr<ParkingSpot> parkingSpot);

    const std::vector<std::unique_ptr<ParkingSpot>> &getSpots() const;
};