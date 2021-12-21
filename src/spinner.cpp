/**
 * @file spinner.cpp
 * @author Maximilien Naveau (maximilien.naveau@gmail.com)
 * license License BSD-3-Clause
 * @copyright Copyright (c) 2019, New York University and Max Planck
 * Gesellschaft.
 * @date 2019-05-22
 *
 * @brief This file implements a spinner to time a loop
 */

#include <pthread.h>
#include <iostream>
#include <real_time_tools/spinner.hpp>
#include <real_time_tools/timer.hpp>

namespace real_time_tools
{
Spinner::Spinner()
{
    next_date_timespec_ = timespec_add(Timer::get_current_time(), period_timespec_);
}

void Spinner::initialize()
{
    next_date_timespec_ = timespec_add(Timer::get_current_time(), period_timespec_);
}

void Spinner::spin()
{
    Timer::sleep_until_timespec(next_date_timespec_);
    next_date_timespec_ = timespec_add(Timer::get_current_time(), period_timespec_);
}

double Spinner::predict_sleeping_time()
{
    return timespec_to_double(timespec_sub(next_date_timespec_, Timer::get_current_time()));
}

float Spinner::predict_sleeping_time_micro()
{
  return timespec_to_micros_float(timespec_sub(next_date_timespec_, Timer::get_current_time()));
}

}  // namespace real_time_tools
