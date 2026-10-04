#include "ParkingSpot.h"
#include "VehicleType.h"
#include "ParkingLot.h"
#include "ParkingFloor.h"
#include "Vehicle.h"
#include "Ticket.h"
#include "FirstAvailableSpot.h"
#include <memory>

int main()
{
    ParkingLot pl;
    SpotStrategy* strategy=new FirstAvailableSpot();

    ParkingFloor floor1("F1");

    floor1.addParkingSpots(
        std::make_unique<ParkingSpot>("1", VehicleType::Motorcycle, 20));

    floor1.addParkingSpots(
        std::make_unique<ParkingSpot>("2", VehicleType::Car, 20));

    floor1.addParkingSpots(
        std::make_unique<ParkingSpot>("3", VehicleType::LargeVehicle, 20));

    pl.addParkingFloor(std::move(floor1));

    Vehicle v1("123", VehicleType::Motorcycle);
    Vehicle v2("124", VehicleType::Motorcycle);

    pl.assignSpot(v1, strategy);
    pl.assignSpot(v2, strategy);

    pl.unassignSpot(v1, PaymentType::UPI);
    // pl.unassignSpot(v2, PaymentType::CARD);
    delete strategy;
}