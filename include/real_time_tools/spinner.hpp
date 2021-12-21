/**
 * @file spinner.hpp
 * @author Maximilien Naveau (maximilien.naveau@gmail.com)
 * license License BSD-3-Clause
 * @copyright Copyright (c) 2019, New York University and Max Planck
 * Gesellschaft.
 * @date 2019-05-22
 *
 * @brief Tools for maintaining the timing on a while loop.
 */

#ifndef SPINNER_HPP
#define SPINNER_HPP

#include <unistd.h>
#include <chrono>
#include "real_time_tools/timespec.h"

namespace real_time_tools
{
/**
 * @brief Class to have threads / loops running at a desired frequency
 */
class Spinner
{
public:
    // create a spinner for the desired frequency
    Spinner();

    /**
     * @brief set_period sets the period of the loop in !!seconds!!
     * @param period in seconds.
     */
    void set_period(double period)
    {
      period_timespec_ = timespec_from_double( period);
    }

    /**
     * @brief Set the frequency of the loop [Hz]
     *
     * @param frequency
     */
    void set_frequency(double frequency)
    {
      period_timespec_ = timespec_from_double(1.0 / frequency);
    }

    /**
     * @brief To be called at the beginning of the loop if the spinner is not
     * created just before.
     */
    void initialize();

    /**
     * @brief spin waits for the time such that successive calls to spin
     * will result in spin being called at the desired frequency
     */
    void spin();

    /**
     * @brief Predict the time the current thread is going to sleep.
     */
    double predict_sleeping_time();

   /**
    * @brief Predict the time the current thread is going to sleep.
    */
  float predict_sleeping_time_micro();

 protected:
    /**
     * @brief period_timespec_ is the period of the loop in seconds
     */
    timespec period_timespec_;

    /**
     * @brief next_date_timespec_ is the date when the loop needs to wake up.
     */
    timespec next_date_timespec_;
};

}  // namespace real_time_tools

#endif  // SPINNER_HPP
