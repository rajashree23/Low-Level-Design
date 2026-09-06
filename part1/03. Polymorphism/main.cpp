#include <iostream>
#include <memory>
#include "EmailNotification.h"
#include "SlackNotification.h"
#include "Notification.h"

int main()
{
    Notification* notification;

    EmailNotification en;
    SlackNotification sn;

    notification = &en;
    notification->send("hello");

    notification = &sn;
    notification->send("hello");

    // delete notification;

    // new syntax
    auto newNotification = std::make_unique<EmailNotification>();
    newNotification->send("NEW syntax hello");
    return 0;
}