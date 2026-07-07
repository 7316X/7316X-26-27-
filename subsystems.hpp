#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// declarations of motors, sensors, etc.


inline pros::Motor L_Winch(-5);
inline pros::Motor R_Winch(6);

inline pros::Motor L_Lift(11);
inline pros::Motor R_Lift(-12);



inline ez::Piston PTO_piston('A');

inline ez::Piston Claw('B');
inline ez::Piston Flip1('C');
inline ez::Piston Flip2('D');


