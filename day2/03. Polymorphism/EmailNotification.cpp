#include "EmailNotification.h"
#include<string>
#include<iostream>

void EmailNotification::send(std::string message){
    std::cout<<"Message from email: "<<message<<std::endl;
}