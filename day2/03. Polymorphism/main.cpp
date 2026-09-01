#include <iostream>
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
    return 0;
}