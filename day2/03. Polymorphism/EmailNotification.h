#pragma once

#include "Notification.h"
#include<string>

class EmailNotification : public Notification
{
public:
    void send(std::string message);
};