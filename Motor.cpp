/////////////////////////////////////////////////////////////////////////////
// Motor.cpp
//
//Implementation file for the Motor class.
//
//Author - Anind Duttaroy
////////////////////////////////////////////////////////////////////////////

#include "Motor.h"

Motor::Motor()
    : stop_command(""),
    initial_position(0),
    prev_position(0),
    curr_position(0),
    curr_velocity(0),
    prev_tick_count(0),
    curr_tick_count(0),
    elapsed(0),
    run_motor_state(false),
    start_toggle(false)
{
}


Motor::Motor(const Motor& mtr)
    : stop_command(mtr.stop_command),
    initial_position(mtr.initial_position),
    prev_position(mtr.prev_position),
    curr_position(mtr.curr_position),
    curr_velocity(mtr.curr_velocity),
    prev_tick_count(mtr.prev_tick_count),
    curr_tick_count(mtr.curr_tick_count),
    initial_start_time(mtr.initial_start_time),
    end_time(mtr.end_time),
    elapsed(mtr.elapsed),
    run_motor_state(mtr.run_motor_state),
    start_toggle(mtr.start_toggle)
{
}

Motor& Motor::operator=(const Motor& mtr)
{
    stop_command = mtr.stop_command;
    initial_position = mtr.initial_position;
    prev_position = mtr.prev_position;
    curr_position = mtr.curr_position;
    curr_velocity = mtr.curr_velocity;
    prev_tick_count = mtr.prev_tick_count;
    curr_tick_count = mtr.curr_tick_count;
    initial_start_time = mtr.initial_start_time;
    end_time = mtr.end_time;
    elapsed = mtr.elapsed;
    run_motor_state = mtr.run_motor_state;
    start_toggle = mtr.start_toggle;
    return *this;
}

Motor::~Motor()
{
}

void Motor::setVelocity(float velocity)
{
    curr_velocity = velocity;
    run_motor_state = true;
    if (!start_toggle)
    {
        start_toggle = true;
        initial_start_time = std::chrono::system_clock::now();
    }
    runMotor();
}

void Motor::runMotor()
{
    if (!run_motor_state)
    {
        curr_velocity = stopVelocity;
        return;
    }
    end_time = std::chrono::system_clock::now();
    elapsed = end_time - initial_start_time;
    curr_tick_count = elapsed.count();
    curr_position = prev_position + (curr_velocity * (curr_tick_count - prev_tick_count));
    prev_position = curr_position;
    prev_tick_count = curr_tick_count;
    if (curr_position >= maxPosition)
    {
        curr_velocity = stopVelocity;
        curr_position = maxPosition;
    }
    else if (curr_position <= minPosition)
    {
        curr_velocity = stopVelocity;
        curr_position = minPosition;
    }
}

float Motor::getCurrentPosition()
{
    runMotor();
    return curr_position;
}

float Motor::getCurrentVelocity()
{
    runMotor();
    return curr_velocity;
}

void Motor::stopMotor()
{
    curr_velocity = stopVelocity;
    prev_tick_count = 0;
    run_motor_state = false;
    start_toggle = false;
    runMotor();
}
