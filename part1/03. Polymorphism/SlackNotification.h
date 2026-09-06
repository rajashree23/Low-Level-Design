#pragma once

#include "Notification.h"
#include<string>

class SlackNotification : public Notification
{
public:
    void send(std::string message);
};