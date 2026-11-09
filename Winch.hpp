#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"

/* Lift movement functions */

inline ez::PID LiftPID{15, 0, 0, 130, "Lift"}; /*PID for Lift Movement*/

inline void Lift_set_0(){
Lift_1.move(-127);
Lift_2.move(-127);
Lift_3.move(-127);
pros:: delay(1000);
Lift_1.tare_position();
Lift_2.tare_position();
Lift_3.tare_position();


}

inline void set_Lift(int position) { /*Function for Lift Movement*/
  Lift_1.move(position);
  Lift_2.move(position);
  Lift_3.move(position);
}

inline const int Alliance_Cup1 = 20;
inline const int Alliance_Cup2 = 40;
inline const int Alliance_Cup3 = 60;
inline const int Alliance_Cup4 = 80;
inline const int Alliance_Cup5 = 100;

inline const int Neutral_Cup1 = 30;
inline const int Neutral_Cup2 = 50;
inline const int Neutral_Cup3 = 70;
inline const int Neutral_Cup4 = 90;
inline const int Neutral_Cup5 = 110;


 inline void Lift_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    set_Lift(LiftPID.compute(((Lift_1.get_position()) + (Lift_2.get_position())) + (Lift_3.get_position())) / 3);

    pros::delay(ez::util::DELAY_TIME);
  }
}
inline pros::Task Lift_Task(Lift_task);  // Create the task, this will cause the function to start running

 inline void Lift_auto(double position){
    LiftPID.target_set(position);
    ez::exit_output exit= ez::RUNNING;
    while(LiftPID.exit_condition({Lift_1, Lift_2, Lift_3}, true)== ez::RUNNING){
        double output = LiftPID.compute(((Lift_1.get_position())+(Lift_2.get_position())+(Lift_3.get_position()))/3 );
        set_Lift(output);
    pros::delay(ez::util::DELAY_TIME);
    }
    set_Lift(0);
}

inline void Lift_wait() {
  while (LiftPID.exit_condition({Lift_1, Lift_2, Lift_3}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}