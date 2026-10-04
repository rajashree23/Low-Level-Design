#include"ParkingFloor.h"

ParkingFloor::ParkingFloor(std::string id):id(id){}

void ParkingFloor::addParkingSpots(std::unique_ptr<ParkingSpot> parkingSpot)
{
    parkingSpots.push_back(std::move(parkingSpot));
}

const std::vector<std::unique_ptr<ParkingSpot>>& ParkingFloor::getSpots() const
{
    return parkingSpots;
}