#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "autons.hpp"

extern Drive chassis;

// declarations of motors, sensors, etc.

// pros:: Motor Auto_Lift1(-1);
// pros:: Motor Auto_Lift2(10);


inline pros::MotorGroup sixbar({-1, 10});  
inline pros::MotorGroup twobar({-4, 20});

inline pros::Motor Lift_1(20);
inline pros::Motor Lift_2(-20);
inline pros::Motor Lift_3(-20);

inline pros::Motor Claw(5);

inline pros::Motor Pivot(20);
inline ez::Piston Wing_L('A');
inline ez::Piston Wing_R('B');

inline ez::Piston forks('C');

