#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"



void Intake_control() {
  if (master.get_digital(DIGITAL_L1)) {
    L_winch.move(127);
    R_winch.move(127);
  } else if (master.get_digital(DIGITAL_L2)) {
    L_winch.move(-127);
    R_winch.move(-127);
  } else {
    L_winch.move(0);
    R_winch.move(0);
  }
}