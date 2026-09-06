#pragma once
#include<string>

class Notification{
    public:
    virtual ~Notification() = default;
    virtual void send(std::string message) = 0;    
};