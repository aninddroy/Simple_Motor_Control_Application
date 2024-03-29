/////////////////////////////////////////////////////////////////////////////
//Motor.h
//
//Header file for the Motor class.
//
//Author - Anind Duttaroy
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <chrono>

const std::string get_position_command = "p?";
const std::string get_velocity_command = "v?";
const std::string set_velocity_command = "v=";
const std::string return_position_string = "p=";
const std::string return_velocity_string = "v=";
const std::string stop_command = "stop";
const std::string unknown_command = "Unknown command";
const std::string quit_command = "q";


const float maxPosition = 1000.0;
const float minPosition = 0.0;
const float stopVelocity = 0.0;
using tick_duration = std::chrono::duration<float, std::ratio<1, 10>>;

class Motor
{
public:
    Motor();
    Motor(const Motor& mtr);
    Motor& operator=(const Motor& mtr);
    ~Motor();

    void setVelocity(float velocity);
    float getCurrentPosition();
    float getCurrentVelocity();
    void stopMotor();

private:
    std::string stop_command;
    float initial_position;
    float prev_position;
    float curr_position;
    float curr_velocity;
    float prev_tick_count;
    float curr_tick_count;
    std::chrono::system_clock::time_point initial_start_time;
    std::chrono::system_clock::time_point end_time;
    tick_duration elapsed;
    bool run_motor_state;
    bool start_toggle;

    void runMotor();

};

