#pragma once

#include <string>
#include <mutex>

#include "VehicleType.h"

class ParkingSpot
{
private:
    std::string id;
    VehicleType type;
    bool empty;
    double cost;
    std::mutex spotMutex;

public:
    ParkingSpot(std::string id, VehicleType t, double cost);

    bool assignSpot();
    bool unassignSpot();

    bool isEmpty() const;
    double getCost() const;
    std::string getId() const;
    VehicleType getType() const;
};