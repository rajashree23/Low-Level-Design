#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <atomic>

#include "ParkingSpot.h"
#include "Ticket.h"
#include "Vehicle.h"
#include "PaymentProcessor.h"
#include "ParkingFloor.h"
#include "SpotStrategy.h"

class ParkingLot
{
private:
    //    std::vector<std::unique_ptr<ParkingSpot>> parkingSpots;
    std::vector<ParkingFloor> parkingFloors;
    std::unordered_map<std::string, std::unique_ptr<Ticket>> activeTickets;

   std::atomic<int> ticketId{1};

    std::mutex parkingLotMutex;
    std::mutex ticketMutex;

    std::unique_ptr<Ticket> generateTicket(Vehicle vehicle, std::string spotId);

    ParkingSpot* findSpotById(std::string id);

    double calculateFees(Ticket *ticket, ParkingSpot *parkingSpot);

    bool processPayment(double amount, PaymentType type);

public:
    ParkingSpot *getEmptyParkingSpot(Vehicle v, SpotStrategy *s);

    bool assignSpot(Vehicle v, SpotStrategy *s);

    // void addParkingSpots(std::unique_ptr<ParkingSpot> parkingSpot);
    void addParkingFloor(ParkingFloor fl);

    bool unassignSpot(Vehicle v, PaymentType type);
};