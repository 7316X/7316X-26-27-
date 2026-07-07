#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"


/*PTO Functions*/

bool is_extended = true;

void claw() {
    is_extended = !is_extended;
    
      PTO_piston.set(is_extended);
}