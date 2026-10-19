# Parking Lot — LLD

```text
// ═══════════════════════════════════════════════════════════════════════════
// REQUIREMENTS
//
// Example (Tic Tac Toe):
//   1. Two players alternate placing X and O on a 3x3 grid.
//   2. A player wins by completing a row, column, or diagonal.
//   Out of Scope: UI, AI opponent, networking
// ═══════════════════════════════════════════════════════════════════════════
```

## REQUIREMENTS

1. Parking Lot allows different types of vehicle parking: motorcycle, car, large vehicle.
2. It will be a single-floor parking lot.
3. We will have a single entry and a single exit.
4. On entry, we will check whether a parking spot is available for the vehicle type.
5. If available, give a ticket to the vehicle with timestamp, vehicle number, and ID.
6. On exit, fees are calculated, paid, and the parking spot is released.
7. If a spot is not available, reject vehicle parking.
8. When initializing vehicle types, we can assign the number of spots for each vehicle type and an hourly cost for each vehicle type. Keep the same cost for all spots of a type. Less than one hour will also be charged on an hourly basis; basically, it will be rounded up.
9. On exit, if the ticket has any issue, such as vehicle number mismatch or a used ticket, report an error.
10. If all is good, calculate cost: timestamp → convert to hours × cost.

### Out of Scope

- Multiple floors
- Multiple exits/entries
- UI
- Different parking spot cost
- Payment failure

---

## ENTITIES & RELATIONSHIPS

```text
// ═══════════════════════════════════════════════════════════════════════════
// ENTITIES & RELATIONSHIPS
//
// Example (Tic Tac Toe):
//   Game, Board, Player
// ═══════════════════════════════════════════════════════════════════════════
```

1. `ParkingLot` is the orchestrator.
2. `ParkingSpot`
3. `Vehicle`
4. `Ticket`
5. Enum → `VehicleType`
6. `PaymentProcessor`
7. `PriceCalculator`

### Relationships

```text
ParkingLot -> list of ParkingSpots
```

- `ParkingSpot` will have a vehicle type, whether it is empty or not, and cost.
- `Ticket` will be created when a spot is assigned. We will keep the spot ID and not the whole `ParkingSpot` object.
- `Vehicle` will have the `VehicleType` enum.
- `PaymentProcessor` can have simple if/else logic for now, supporting card and UPI payments.
- `PriceCalculator` will take timestamp and cost.

---

## CLASS DESIGN

```text
// ═══════════════════════════════════════════════════════════════════════════
// CLASS DESIGN
//
// Example (Tic Tac Toe):
//   class Game:
//     - board: Board
//     - currentPlayer: Player
//     + makeMove(row, col) -> bool
// ═══════════════════════════════════════════════════════════════════════════
```

```cpp
class ParkingLot {
    - parkingSpots: ParkingSpot[]
    - activeTickets: unordered_map<string, Ticket> // vehicleNo -> Ticket

    + checkParkingSpotAvailable(Vehicle v): ParkingSpot | null
    + generateTicket(vehicle: Vehicle, spotId: string): Ticket
    + assignSpot(Vehicle v): Ticket | null
    + addParkingSpots(parkingSpot: ParkingSpot): void
    + unassignSpot(ticket: Ticket): bool
    + findSpotById(id: string): ParkingSpot
    + calculateFees(ticket: Ticket, parkingSpot: ParkingSpot): double // delegates to PriceCalculator
    + processPayment(amount: double, paymentType: PaymentType): bool // delegates to PaymentProcessor
}

enum class VehicleType {
    motorcycle,
    car,
    large_vehicle
}

class Vehicle {
    - vehicleNo: string
    - type: VehicleType

    + getType(): VehicleType
}

class ParkingSpot {
    - id: string
    - type: VehicleType
    - isEmpty: bool
    - cost: double

    + isEmpty(): bool
    + assignSpot(): bool
    + unassignSpot(): bool
}

enum TicketStatus {
    Processed,
    Active
}

class Ticket {
    - id: string
    - spotId: string
    - timestamp: date
    - vehicle: Vehicle
    - status: TicketStatus

    // getters that are public
}

enum PaymentType {
    UPI,
    Card
}

class PaymentProcessor {
    + process(amount: double, paymentType: PaymentType): bool
}

enum TypeOfCalculator {
    Hourly
}

class PriceCalculator {
    - typeOfCalculator: TypeOfCalculator

    + calculate(timestamp: date, cost: double): double
}
```

---

## IMPLEMENTATION

```cpp
Ticket | null assignSpot(Vehicle v) {
    auto parkingSpot = checkParkingSpotAvailable(v);

    if (parkingSpot == NULL) {
        cout << "Not available";
        return null;
    }

    bool isSuccess = parkingSpot.assignSpot();

    if (!isSuccess) {
        cout << "Some error happened";
        return null;
    }

    Ticket t = generateTicket(v, parkingSpot.getSpotId());

    if (t == null) {
        parkingSpot.unassignSpot();
        cout << "Some error happened";
        return null;
    }

    activeTickets[v.getVehicleNo()] = t;
    return t;
}

bool unassignSpot(Ticket t, PaymentType paymentType, Vehicle v) {
    string vehicleNo = t.getVehicle().getVehicleNo();

    if (t.getStatus() == Processed) {
        cout << "not valid ticket";
        return false;
    }

    if (!activeTickets.count(vehicleNo)) {
        cout << "not valid ticket";
        return false;
    }

    if (v.getVehicleNo() != vehicleNo) {
        cout << "not valid ticket";
        return false;
    }

    auto PS = findSpotById(t.getSpotId());
    auto amt = calculateFees(t, PS);
    auto process = processPayment(amt, paymentType);

    if (!process) {
        cout << "Some error happened";
        return false;
    }

    bool isSuccess = PS.unassignSpot();

    if (!isSuccess) {
        cout << "Some error happened";
        return false;
    }

    t.status = Processed;
    activeTickets.erase(vehicleNo);

    return true;
}
```

### Price Calculator

```cpp
// class PriceCalculator {
//     - typeOfCalculator: TypeOfCalculator
//
//     + calculate(timestamp: date, cost: double): double
// }

double calculateFees(Ticket t, ParkingSpot ps) {
    PriceCalculator pc;
    return pc.calculate(t.getTimeStamp(), ps.getCost(), Hourly);
}

double calculate(date timestamp, double cost, TypeOfCalculator type) {
    if (type == Hourly) {
        // Convert timestamp to seconds.
        // Get current timestamp in seconds.

        auto curr = /* some logic to get current timestamp */;
        auto stored = /* some logic to convert timestamp to seconds */;

        auto duration = curr - stored;

        if (duration == 0) {
            return cost;
        }

        auto hours = (duration + 3599) / 3600;

        return cost * hours;
    }

    return /* non-supported type error */;
}
```

---

## EXTENSIBILITY

```text
parkingfloor {
    floorId: number // denoting floor number
    parkingSpots[]

    findAvailableSpot(vehicleType, spotStrategy) {
        // ...
    }
}

parkinglot {
    parkingFloors: parkingFloor[] // array of floor numbers sorted by floorId

    /*
    [
        {
            floorId: 0
            parkingSpots: []
        },
        {
            floorId: 1
            parkingSpots: []
        }
    ]
    */

    // Now assignSpot will run through parking floors.
    assignSpot(vehicle, spotStrategy)
}
```

## Followup

### 1. How to handle double assignment in parking spot
For correctness, we can keep a mutex at the `ParkingLot` level and use coarse-grained locking.

The lock should cover the complete critical section: checking whether a spot is available, assigning the spot, and updating `activeTickets`. This makes sure that two concurrent requests cannot see the same spot as available and assign it at the same time.

This approach is simple and safe, but it reduces concurrency because the complete operation is serialized. As a starting point, I would choose this because it keeps the synchronization logic easy to understand and maintain. If profiling later shows that lock contention is affecting performance, we can move to finer-grained locking or use another concurrency approach.

Fine-grained locking solves the reduced-concurrency problem of coarse-grained locking.

Instead of locking the entire operation, I use separate locks for individual shared resources.

For example:

One lock for each parking spot.
A separate lock for activeTickets.
ticketId can be atomic variable.

This allows different threads to work on different parking spots concurrently, so the system can have better concurrency. The important part is that the check and assignment of a spot must happen atomically under the same spot lock.

The tradeoff is that fine-grained locking is more complex and has more synchronization overhead.

There is also a risk of deadlock if multiple locks are acquired in inconsistent order.

For example:

Thread A:
    locks Spot A
    wants Spot B

Thread B:
    locks Spot B
    wants Spot A

Now both threads are waiting for each other, so neither can proceed.

To avoid this, we need to be careful about lock ordering and minimize holding multiple locks at the same time.

### 2. how multiple floor and spot strategy change the design?

Instead of ParkingLot directly containing parking spots, ParkingLot will contain multiple ParkingFloor objects, and each ParkingFloor will contain its parking spots.

For spot selection, we can define a SpotStrategy interface with different implementations for different selection criteria.

The strategy can take the parking floors and the vehicle as input and decide which eligible parking spot to select.

For example, we can have strategies like FirstAvailableSpotStrategy or NearestSpotStrategy.

### 3. Remember how we can round minutes to hours?

 -> (curr-past+3599)/3600
I calculate the elapsed seconds and use ceiling division by 3600 so any partial hour is charged as a complete hour.

### 4. different pricing is added for spot then does design change?

If different parking spots have different costs, the existing ParkingSpot already has a cost property, so no major design change is required.

If pricing depends on factors such as weekends, holidays, time of day, or other pricing rules, I can introduce a PricingStrategy or extend the PriceCalculator to handle those rules.

The exit flow can then use the pricing component to calculate the final amount.

### 5. Multiple entry/exit gates

Since there are multiple entry gates, spot selection may depend on the gate through which the vehicle entered.

I would pass the entry gate, or its location, to the spot-selection strategy. A NearestSpotStrategy can then select the closest eligible parking spot relative to that gate.

The exit gate would be relevant for exit-related operations, but it is not required for selecting a spot based on the entry location.


### 6. Timestamp syntax

```cpp
#include <chrono>

auto currTime = std::chrono::system_clock::now();
```

```cpp
class Ticket {
private:
    int id;
    std::chrono::system_clock::time_point startTime;
};
```

```cpp
#include <chrono>
#include <cmath>

double calculateCost(
    std::chrono::system_clock::time_point entryTime,
    std::chrono::system_clock::time_point exitTime,
    int hourlyCost
) {
    auto duration = exitTime - entryTime;

    auto minutes =
        std::chrono::duration_cast<std::chrono::minutes>(duration).count();

    auto hours = (minutes + 59) / 60;

    return hours * hourlyCost;
}
```