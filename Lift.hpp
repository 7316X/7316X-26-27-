// #pragma once

// #include "EZ-Template/api.hpp"
// #include "api.h"
// #include "subsystems.hpp"

// /* Winch movement functions */

// inline ez::PID LiftPID{0.45, 0, 0, 0, "Lift"}; /*PID for Lift Movement*/


// void set_Lift(int input) { /*Function for Lift Movement*/
//   Lift_1.move(input);
//   Lift_2.move(input);
// }

// const int Alliance_Cup1 = 20;
// const int Alliance_Cup2 = 40;
// const int Alliance_Cup3 = 60;
// const int Alliance_Cup4 = 80;
// const int Alliance_Cup5 = 100;

// const int Neutral_Cup1 = 30;
// const int Neutral_Cup2 = 50;
// const int Neutral_Cup3 = 70;
// const int Neutral_Cup4 = 90;
// const int Neutral_Cup5 = 110;


//  void Lift_task() {
//   pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
//   while (true) {
//     set_Lift(LiftPID.compute(((Lift_1.get_position()) + (Lift_2.get_position())) / 2));

//     pros::delay(ez::util::DELAY_TIME);
//   }
// }
// // pros::Task Lift_Task(Lift_task);  // Create the task, this will cause the function to start running

//  void Lift_auto(double target){
//     LiftPID.target_set(target);
//     ez::exit_output exit= ez::RUNNING;
//     while(LiftPID.exit_condition({Lift_1, Lift_2}, true)== ez::RUNNING){
//         double output = LiftPID.compute(((Lift_1.get_position())+(Lift_2.get_position()))/2);
//         set_Lift(output);
//     pros::delay(ez::util::DELAY_TIME);
//     }
//     set_Lift(0);
// }

// void Lift_wait() {
//   while (LiftPID.exit_condition({Lift_1, Lift_2}, true) == ez::RUNNING) {
//     pros::delay(ez::util::DELAY_TIME);
//   }
// }