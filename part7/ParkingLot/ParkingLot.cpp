#include <memory>
#include <ctime>
#include <iostream>

#include "ParkingLot.h"
#include "PaymentProcessor.h"
#include "PriceCalculator.h"
#include "SpotStrategy.h"

std::unique_ptr<Ticket> ParkingLot::generateTicket(Vehicle vehicle, std::string spotId)
{
    int idNum = ticketId.fetch_add(1);
    std::string id = "T" + std::to_string(idNum);
    time_t timestamp = time(nullptr);

    auto t = std::make_unique<Ticket>(id, spotId, timestamp, vehicle);
    return t;
}

ParkingSpot *ParkingLot::findSpotById(std::string id)
{
    for (auto &pf : parkingFloors)
    {
        for (auto &ps : pf.getSpots())
        {
            if (ps->getId() == id)
            {
                return ps.get();
            }
        }
    }
    return nullptr;
}

double ParkingLot::calculateFees(Ticket *ticket, ParkingSpot *parkingSpot)
{
    PriceCalculator pc;
    return pc.calculate(parkingSpot->getCost(), ticket->getTimeStamp());
}

bool ParkingLot::processPayment(double amount, PaymentType type)
{
    PaymentProcessor pp;
    return pp.process(amount, type);
}

ParkingSpot *ParkingLot::getEmptyParkingSpot(Vehicle v, SpotStrategy *s)
{
    return s->findSpot(parkingFloors, v);
}

bool ParkingLot::assignSpot(Vehicle v, SpotStrategy *s)
{
    // std::lock_guard<std::mutex>lock(parkingLotMutex);
    ParkingSpot *ps = getEmptyParkingSpot(v, s);

    if (ps == nullptr)
    {
        return false;
    }

    // bool isSuccess = ps->assignSpot();

    // if (!isSuccess)
    // {
    //     std::cout << "Some error happened" << std::endl;
    //     return false;
    // }

    auto t = generateTicket(v, ps->getId());

    if (t == nullptr)
    {
        ps->unassignSpot();
        ;
        std::cout << "Ticket couldn't be assigned" << std::endl;
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(ticketMutex);
        activeTickets[v.getVehicleNo()] = std::move(t);
    }
    return true;
}

bool ParkingLot::unassignSpot(Vehicle v, PaymentType type)
{
    Ticket *ticket;

    // Get ticket safely from activeTickets
    {
        std::lock_guard<std::mutex> lock(ticketMutex);

        if (!activeTickets.count(v.getVehicleNo()))
        {
            std::cout << "Not valid ticket as vehicle number does not have any active Ticket" << std::endl;
            return false;
        }

        ticket = activeTickets[v.getVehicleNo()].get();

        // Validate ticket while protecting ticket state
        if (ticket->getStatus() == TicketStatus::Processed)
        {
            std::cout << "Not an active ticket" << std::endl;
            return false;
        }

        std::string vehicleNo = ticket->getVehicle().getVehicleNo();

        if (v.getVehicleNo() != vehicleNo)
        {
            std::cout << "Vehile number do no match" << std::endl;
            return false;
        }
    }

    auto PS = findSpotById(ticket->getSpotId());

    auto amt = calculateFees(ticket, PS);

    auto process = processPayment(amt, type);

    if (!process)
    {
        std::cout << "Some error happened" << std::endl;
        return false;
    }

    bool isSuccess = PS->unassignSpot();

    if (!isSuccess)
    {
        std::cout << "Some error happened" << std::endl;
        return false;
    }

    // Update ticket state and remove from activeTickets
    {
        std::lock_guard<std::mutex> lock(ticketMutex);

        ticket->setStatus(TicketStatus::Processed);
        activeTickets.erase(v.getVehicleNo());
    }

    return true;
}

void ParkingLot::addParkingFloor(ParkingFloor fl)
{
    parkingFloors.push_back(std::move(fl));
}