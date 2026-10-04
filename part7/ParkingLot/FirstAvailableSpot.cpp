#include "FirstAvailableSpot.h"

ParkingSpot *FirstAvailableSpot::findSpot(std::vector<ParkingFloor> &pf, Vehicle v)
{
    for (auto &pf : pf)
    {
        for (auto &ps : pf.getSpots())
        {
            if (ps->getType() != v.getType())
            {
                continue;
            }
            if (ps->assignSpot())
            {
                return ps.get();
            }
        }
    }
    return nullptr;
}