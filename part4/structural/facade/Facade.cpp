#include <iostream>
using namespace std;

class Inventory
{
public:
    void checkStock()
    {
        cout << "checking stock" << "\n";
    }
};

class Payment
{
public:
    void makePayment()
    {
        cout << "making payment" << "\n";
    }
};

class Shipping
{
public:
    void addToShip()
    {
        cout << "adding to shipping" << "\n";
    }
};

class Order
{
private:
    Inventory inventory;
    Payment payment;
    Shipping shipping;

public:
    void processOrder()
    {
        inventory.checkStock();
        payment.makePayment();
        shipping.addToShip();

        cout << "Order placed..\n";
    }
};

int main(){
    Inventory i;
    Payment p;
    Shipping s;

    Order o;
    o.processOrder();
    return 0;
}