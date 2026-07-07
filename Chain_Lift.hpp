#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"



/* Winch movement functions */

inline ez::PID LiftPID{0.45, 0, 0, 0, "Lift"}; /*PID for Lift Movement*/


inline void set_lift(int input) { /*Function for Lift Movement*/
   L_Lift.move(input);
   R_Lift.move(input);
 }

  const int Load = 0;  /* Variable for Winch Movement, "0" is the position the robot will define as the loading position */
  const int score = 180;/* Variable for Winch Movement, "180" is the position the robot will define as the scoring position */
  const int Match_Load= 250; /* Variable for Winch Movement, "250" is the position the robot will define as the match loading position */


void lift_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    set_lift(LiftPID.compute((L_Lift.get_position() + R_Lift.get_position()) / 2));

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task Lift_Task(lift_task);  // Create the task, this will cause the function to start running

void lift_auto(double target){
    LiftPID.target_set(target);
    ez::exit_output exit= ez::RUNNING;
    while(LiftPID.exit_condition({L_Lift, R_Lift}, true)== ez::RUNNING){
        double output = LiftPID.compute((L_Lift.get_position() + R_Lift.get_position()) / 2);
        set_lift(output);
    pros::delay(ez::util::DELAY_TIME);
    }
    set_lift(0);
}

void lift_wait() {
  while (LiftPID.exit_condition({L_Lift, R_Lift}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}