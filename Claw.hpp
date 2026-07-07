#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"


/*PTO Functions*/

bool is_extended = true;

void claw_flip() {
    is_extended = !is_extended;
    
      Flip1.set(is_extended);
      Flip2.set(!is_extended);
    }

    void Claw_Nuetral(){
        Flip1.set(false);
        Flip2.set(false);
    }

    

  

  
        