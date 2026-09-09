#include <iostream>
#include <memory>
using namespace std;

class OldPayment {
public:
    void makePayment() {
        cout << "Making old payment" << "\n";
    }
};

class Payment {
public:
    virtual void pay() = 0;
    virtual ~Payment() = default;
};

class Adapter : public Payment {
private:
    OldPayment p;

public:
    void pay() override {
        p.makePayment();
    }
};

int main() {
    auto p = make_unique<Adapter>();
    p->pay();

    return 0;
}