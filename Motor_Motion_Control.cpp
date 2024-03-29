/////////////////////////////////////////////////////////////////////////////
// Motor_Motion_Control.cpp
//
//Program to start, stop and run the motor.
//
//Author - Anind Duttaroy
////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Motor.h"


int main()
{
    std::string input;
    std::string output;
    std::string temp;
    float curr_pos = 0;
    float curr_vel = 0;
    float velocity = 0;
    Motor motor;

    while (true)
    {
        std::cin >> input;
        if (input == get_position_command)
        {
            curr_pos = motor.getCurrentPosition();
            temp = std::to_string(curr_pos);
            output = return_position_string;
            output += temp;
            std::cout << output << std::endl;
            std::cout << "Enter q to quit. " << std::endl;
        }
        else if (input == get_velocity_command)
        {
            curr_vel = motor.getCurrentVelocity();
            temp = std::to_string(curr_vel);
            output = return_velocity_string;
            output += temp;
            std::cout << output << std::endl;
            std::cout << "Enter q to quit. " << std::endl;
        }
        else if (input.substr(0, 2) == set_velocity_command)
        {
            int size = input.size();
            temp = input.substr(2, size - 1);
            const char* temp_vel = temp.c_str();
            velocity = std::strtof(temp_vel, nullptr);
            motor.setVelocity(velocity);
            std::cout << "Enter q to quit. " << std::endl;
        }
        else if (input == stop_command)
        {
            motor.stopMotor();
            std::cout << "Enter q to quit. " << std::endl;
        }
        else if (input == quit_command)
        {
            return 0;
        }
        else
        {
            std::cout << unknown_command << std::endl;
        }
    }

    return 0;
    
}

