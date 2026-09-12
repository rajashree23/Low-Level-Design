#include <iostream>
#include<memory>

class PaymentMethod
{
public:
    virtual ~PaymentMethod() = default;
    virtual void makePayment() = 0;
};

class Credit : public PaymentMethod
{
public:
    void makePayment() override
    {
        std::cout << "Making card payment" << "\n";
    }
};
class UPI : public PaymentMethod
{
public:
    void makePayment() override
    {
        std::cout << "Making UPI payment" << "\n";
    }
};

class Order
{
public:
    Order(std::unique_ptr<PaymentMethod> p) : pm(std::move(p)) {}

    void processOrder()
    {
        std::cout<<"Processing order..."<<"\n";
        pm->makePayment();
    }

private:
    std::unique_ptr<PaymentMethod> pm;
};

int main(){
    auto c = std::make_unique<Credit>();

    Order o(std::move(c));

    o.processOrder();
    return 0;
}