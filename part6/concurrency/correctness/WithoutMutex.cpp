#include <unordered_map>
#include <string>
#include <iostream>
#include <thread>
#include<chrono>

class TicketBooking
{
private:
    std::unordered_map<std::string, std::string> seats;

public:
    void bookSeat(const std::string &seatId, const std::string &userId)
    {
        if (seats.find(seatId) != seats.end())
        {
            std::cout << "Seat is occupied" << "\n";
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        seats[seatId] = userId;
        std::cout << "Seat: " << seatId << " assigned successfully" << "\n";
    }
};

int main()
{
    TicketBooking tb;

    std::thread t1(
        &TicketBooking::bookSeat,
        &tb,
        "a1",
        "u1");

    std::thread t2(
        &TicketBooking::bookSeat,
        &tb,
        "a1",
        "u2");

    t1.join();
    t2.join();
}