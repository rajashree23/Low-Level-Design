#include "Vehicle.h"

Vehicle::Vehicle(std::string no, VehicleType t) : vehicleNo(no), type(t) {}

std::string Vehicle::getVehicleNo() const
{
    return vehicleNo;
}

VehicleType Vehicle::getType() const
{
    return type;
}