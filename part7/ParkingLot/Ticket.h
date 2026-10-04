
#pragma once

#include <string>
#include <ctime>

#include "Vehicle.h"
#include "TicketStatus.h"


class Ticket
{
private:
    std::string id;
    std::string spotId;
    time_t timestamp;

    Vehicle vehicle;
    TicketStatus status;

    public:
    Ticket(std::string id, std::string spotId, time_t timestamp, Vehicle v);

    TicketStatus getStatus() const;
    Vehicle getVehicle() const;
    
    std::string getSpotId() const;
    time_t getTimeStamp() const;
    std::string getTicketId() const;

    void setStatus(TicketStatus s);
};
