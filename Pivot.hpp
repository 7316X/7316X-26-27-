#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "subsystems.hpp"

inline ez::PID PivotPID{25, 0, 0, 100, "Pivot"}; /*PID for Pivot Movement*/

inline void Pivot_set_0() {

Pivot.tare_position();
}

inline void set_Pivot(int position) { /*Function for Pivot Movement*/
  Pivot.move(position);

}

inline const int front = -3000;
inline const int back = 2000;



 inline void pivot_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    set_Pivot(PivotPID.compute(((Pivot.get_position()) )));

    pros::delay(ez::util::DELAY_TIME);
  }
}
inline pros::Task Pivot_Task(pivot_task);  // Create the task, this will cause the function to start running

 inline void Pivot_auto(double position){
    PivotPID.target_set(position);
    ez::exit_output exit= ez::RUNNING;
    while(PivotPID.exit_condition({Pivot}, true)== ez::RUNNING){
        double output = PivotPID.compute(((Pivot.get_position())));
        set_Pivot(output);
    pros::delay(ez::util::DELAY_TIME );
    }
    set_Pivot(0);
}

inline void Pivot_wait() {
  while (PivotPID.exit_condition({Pivot}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}

inline const int numStates=2; //States for the pivot, front and back
inline int states[numStates] = {front, back}; //Array for the states
inline int currState = 0; //Current state of the pivot, front or back
inline int target=0; //Target state of the pivot, front or back

inline void Pivot_Toggle(){
    currState +=1; //Increment the current state
    if(currState == numStates){ //If the current state is equal to the number of states, reset it to 0
        currState = 0;
    }
    target = states[currState]; //Set the target to the current state
    if(currState == 1){ //If the target is back, set the pivot to front
        Pivot.move(50);
        

    }
    if(currState == 0){ //If the target is front, set the pivot to back
        Pivot.move(-30);
      
    }
}



// void move_motor_with_timeout(int target_ticks, int timeout_ms) {
    


//     // 3. Track the start time and set an error threshold
//     uint32_t start_time = pros::millis();
//     int error_threshold = 500; // Allowed error in encoder ticks

//     // 4. Loop while the motor is far from the target AND time hasn't run out
//     while (std::abs(Pivot.get_target_position() - Pivot.get_position()) > error_threshold) {
        
//         // Check if the current time minus the start time exceeds the timeout
//         if ((pros::millis() - start_time) > timeout_ms) {
//             // Timeout reached! Break out of the loop.
//             break; 
//         }

//         // Delay to allow other tasks to run (crucial for V5 brain)
//         pros::delay(20); 
//     }

//     // 5. Explicitly stop the motor after exiting the loop
//     // Use E_MOTOR_BRAKE_HOLD to hold position, or E_MOTOR_BRAKE_COAST to let go
//     Pivot.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
//     Pivot.move_velocity(0); 
// }
