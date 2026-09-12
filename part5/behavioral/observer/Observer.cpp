#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(int price, string ticker) = 0;
};

class Subject
{
public:
    virtual ~Subject() = default;
    virtual void add(Observer *o) = 0;
    virtual void remove(Observer *o) = 0;
    virtual void notify() = 0;
};

class Stock : public Subject
{
private:
    int price;
    string ticker;
    vector<Observer *> listOfObservers;

public:
    Stock(string t) : ticker(t), price(0) {}

    void add(Observer *o) override
    {
        listOfObservers.push_back(o);
    }

    void remove(Observer *o) override
    {
        listOfObservers.erase(
            std::remove(listOfObservers.begin(), listOfObservers.end(), o),
            listOfObservers.end());
    }

    void notify()
    {
        for (auto o : listOfObservers)
        {
            o->update(price, ticker);
        }
    }

    void setPrice(int price)
    {
        this->price = price;
        notify();
    }
};

class PriceInfo : public Observer
{
public:
    void update(int price, string ticker) override
    {
        std::cout << "Price update for " << ticker << " is " << price << "\n";
    }
};

class PriceAlert : public Observer
{
private:
    int threshold = 100;

public:
    void update(int price, string ticker) override
    {
        if (price > threshold)
            std::cout << "Price is above your threshold for " << ticker << " is " << price << "\n";
    }
};

int main()
{
    Stock s("AAPL-US");
    PriceInfo p1;
    PriceAlert p2;

    s.add(&p1);
    s.add(&p2);

    s.setPrice(200);

    s.remove(&p2);
    s.setPrice(300);
    return 0;
}