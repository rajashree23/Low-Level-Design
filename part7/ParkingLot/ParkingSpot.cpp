#include <iostream>

#include "ParkingSpot.h"

ParkingSpot::ParkingSpot(std::string id, VehicleType t, double cost) : id(id), type(t), empty(true), cost(cost) {}

bool ParkingSpot::isEmpty() const
{
    return empty;
}

bool ParkingSpot::assignSpot()
{
    std::lock_guard<std::mutex> lock(spotMutex);
    if (empty)
    {
        empty = false;
        std::cout << "Parking Spot assigned" << std::endl;
        return true;
    }
    std::cout << "Parking Spot is not empty" << std::endl;
    return false;
}

bool ParkingSpot::unassignSpot()
{
    if (!empty)
    {
        empty = true;
        return true;
    }
    std::cout << "Parking Spot could not be vacated" << std::endl;
    return false;
}

/**
 * Getters
 */
double ParkingSpot::getCost() const
{
    return cost;
}

std::string ParkingSpot::getId() const
{
    return id;
}

VehicleType ParkingSpot::getType() const
{
    return type;
}