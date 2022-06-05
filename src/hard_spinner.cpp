/**
 * @file hard_spinner.cpp
 * @author Julian Viereck (jviereck@tuebingen.mpg.de)
 * license License BSD-3-Clause
 * @copyright Copyright (c) 2020, New York University and Max Planck
 * Gesellschaft.
 * @date 2020-11-26
 *
 * @brief This file implements a hard spinner to time a loop.
 */

#include <real_time_tools/hard_spinner.hpp>
#include <real_time_tools/timer.hpp>

namespace real_time_tools
{
HardSpinner::HardSpinner()
    : Spinner() { }

void HardSpinner::spin()
{
  if(predict_sleeping_time() > 0){
    Timer::sleep_until_timespec(next_date_timespec_);
    next_date_timespec_ = timespec_add(next_date_timespec_ ,period_timespec_);
  }else{
    next_date_timespec_ = timespec_add(Timer::get_current_time(), period_timespec_);
  }
}

}  // namespace real_time_tools