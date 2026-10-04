#include "Ticket.h"

Ticket::Ticket(std::string id, std::string spotId, time_t timestamp, Vehicle v) : id(id), spotId(spotId), timestamp(timestamp), vehicle(v), status(TicketStatus::Active) {}

TicketStatus Ticket::getStatus() const
{
    return status;
}

Vehicle Ticket::getVehicle() const
{
    return vehicle;
}

std::string Ticket::getSpotId() const
{
    return spotId;
}

time_t Ticket::getTimeStamp() const
{
    return timestamp;
}

std::string Ticket::getTicketId() const
{
    return id;
}


void Ticket::setStatus(TicketStatus s){
    status=s;
}