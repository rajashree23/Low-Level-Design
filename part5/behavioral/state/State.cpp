#include <iostream>
#include <memory>

class VendingMachine;


class State
{
public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine &vm) = 0;
    virtual void selectItem(VendingMachine &vm) = 0;
    virtual void dispense(VendingMachine &vm) = 0;
};

class NoCoinState : public State
{
public:
    void insertCoin(VendingMachine &vm) override;

    void selectItem(VendingMachine &vm) override
    {
        std::cout << "Insert coin first" << "\n";
    }

    void dispense(VendingMachine &vm) override
    {
        std::cout << "Insert coin first" << "\n";
    }
};

class ProcessState : public State
{
public:
    void insertCoin(VendingMachine &vm) override
    {
        std::cout << "Insert coin first" << "\n";
    }
    void selectItem(VendingMachine &vm) override;

    void dispense(VendingMachine &vm) override
    {
        std::cout << "Insert coin first" << "\n";
    }
};

class DispenseState : public State
{
public:
    void insertCoin(VendingMachine &vm) override
    {
        std::cout << "Insert coin first" << "\n";
    }
    void selectItem(VendingMachine &vm) override
    {
        std::cout << "Insert coin first" << "\n";
    }

    void dispense(VendingMachine &vm) override;
};

class VendingMachine
{
private:
    std::unique_ptr<State> state;
    int coins;

public:
    VendingMachine() : state(std::make_unique<NoCoinState>()) {}

    void insertCoin(int coins)
    {
        this->coins = coins;
        state->insertCoin(*this);
    }

    void selectItem()
    {
        state->selectItem(*this);
    }

    void dispense()
    {
        state->dispense(*this);
        this->coins = 0;
    }

    void setState(std::unique_ptr<State> st)
    {
        this->state = std::move(st);
    }
};

void NoCoinState::insertCoin(VendingMachine &vm)
{

    std::cout << "Coin inserted..." << "\n";
    vm.setState(std::make_unique<ProcessState>());
}

void ProcessState::selectItem(VendingMachine &vm)
{
    std::cout << "Select item..." << "\n";
    vm.setState(std::make_unique<DispenseState>());
}

void DispenseState::dispense(VendingMachine &vm)
{
    std::cout << "Dispensing item..." << "\n";
    vm.setState(std::make_unique<NoCoinState>());
}

int main()
{
    VendingMachine vm;

    vm.insertCoin(100);
    vm.selectItem();
    vm.dispense();

    return 0;
}