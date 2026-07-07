#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"

/* Winch movement functions */

inline ez::PID winchPID{0.45, 0, 0, 0, "Winch"}; /*PID for Winch Movement*/


inline void set_winch(int input) { /*Function for Winch Movement*/
  L_Winch.move(input);
  R_Winch.move(input);
}

const int Alliance_Cup1 = 20;
const int Alliance_Cup2 = 40;
const int Alliance_Cup3 = 60;
const int Alliance_Cup4 = 80;
const int Alliance_Cup5 = 100;

const int Neutral_Cup1 = 30;
const int Neutral_Cup2 = 50;
const int Neutral_Cup3 = 70;
const int Neutral_Cup4 = 90;
const int Neutral_Cup5 = 110;


void winch_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    set_winch(winchPID.compute((L_Winch.get_position() + R_Winch.get_position()) / 2));

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task Winch_Task(winch_task);  // Create the task, this will cause the function to start running

void winch_auto(double target){
    winchPID.target_set(target);
    ez::exit_output exit= ez::RUNNING;
    while(winchPID.exit_condition({L_Winch, R_Winch}, true)== ez::RUNNING){
        double output = winchPID.compute((L_Winch.get_position()+R_Winch.get_position())/2);
        set_winch(output);
    pros::delay(ez::util::DELAY_TIME);
    }
    set_winch(0);
}

void winch_wait() {
  while (winchPID.exit_condition({L_Winch, R_Winch}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}