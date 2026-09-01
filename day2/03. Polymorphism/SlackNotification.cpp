#include "SlackNotification.h"
#include<string>
#include<iostream>

void SlackNotification::send(std::string message){
    std::cout<<"Message from slack: "<<message<<std::endl;
}