#pragma once

#include<string>

#include"VehicleType.h"

class Vehicle{
    private:
    std::string vehicleNo;
    VehicleType type;
    
    public:
    Vehicle(std::string no, VehicleType t);

    std::string getVehicleNo() const;
    VehicleType getType() const;
};