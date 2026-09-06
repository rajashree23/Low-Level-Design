#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>

class Notification
{
public:
    virtual ~Notification() = default;
    virtual void send(const std::string &message) = 0;
};

class Email : public Notification
{
public:
    void send(const std::string &message) override
    {
        std::cout << "Email sent " << message << std::endl;
    }
};

class SMS : public Notification
{
public:
    void send(const std::string &message) override
    {
        std::cout << "SMS sent " << message << std::endl;
    }
};

class NotificationFactory
{
public:
    static std::unique_ptr<Notification> create(const std::string &type)
    {
        if (type == "email")
        {
            return std::make_unique<Email>();
        }
        if (type == "sms")
        {
            return std::make_unique<SMS>();
        }
        throw std::invalid_argument("unknown");
    }
};

int main()
{
    auto notif = NotificationFactory::create("email");
    notif->send("hello");

    auto notif2 = NotificationFactory::create("sms");
    notif2->send("hello");
    return 0;
}