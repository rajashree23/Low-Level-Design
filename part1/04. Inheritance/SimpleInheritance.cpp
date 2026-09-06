#include <iostream>
using namespace std;

class Animal
{
public:
    virtual void eats()
    {
        cout << "Animal eats";
    }
};

class Dog : public Animal
{
public:
    void eats() override
    {
        cout << "Dog eats bone"<<endl;;
    }
};

class Cat : public Animal
{
public:
    void eats() override
    {
        cout << "Cat eats fish"<<endl;
    }
};

int main()
{
    Animal *animal;
    Dog dog;
    animal =&dog;
    animal->eats();


    Cat cat;
    cat.eats();

    return 0;
}