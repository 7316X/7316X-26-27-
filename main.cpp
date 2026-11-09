#include "main.h"
#include "Winch.hpp"
#include "PTO.hpp"
#include "Pivot.hpp"
#include "EZ-Template/api.hpp"
#include "Claw.hpp"

int rM1 = 8; 
int rM2 = -9;
// int rM3 = 0;
int lM1 = 2; 
int lM2 = -3;
// int lM3 = 0;

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {lM1, lM2},     // Left Chassis Ports (negative port will reverse it!)
    {rM1, rM2},  // Right Chassis Ports (negative port will reverse it!)

    11,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM = cartridge * (motor gear / wheel gear)

// Uncomment the trackers you're using here!
// - `8` and `9` are smart ports (making these negative will reverse the sensor)
//  - you should get positive values on the encoders going FORWARD and RIGHT
// - `2.00` is the wheel diameter
// - `4.0` is the distance from the center of the wheel to the center of the robot
 ez::tracking_wheel horiz_tracker(6, 2.00, 4.0);  // This tracking wheel is perpendicular to the drive wheels
 ez::tracking_wheel vert_tracker(7, 2.00, 4.0);   // This tracking wheel is parallel to the drive wheels

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  //  - ignore this if you aren't using a horizontal tracker
  // chassis.odom_tracker_back_set(&horiz_tracker);
  // Look at your vertical tracking wheel and decide if it's to the left or right of the center of the robot
  //  - change `left` to `right` if the tracking wheel is to the right of the centerline
  //  - ignore this if you aren't using a vertical tracker
  // chassis.odom_tracker_left_set(&vert_tracker);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

//  Lift_task;

  

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
     { "Rightside", Rightside},
      { "Skills_Rightside", Skills_Rightside},


      // {"Drive\n\nDrive forward and come back", drive_example},
      // {"Turn\n\nTurn 3 times.", turn_example},
      // {"Drive and Turn\n\nDrive forward, turn, come back", drive_and_turn},
      // {"Drive and Turn\n\nSlow down during drive", wait_until_change_speed},
      // {"Swing Turn\n\nSwing in an 'S' curve", swing_example},
      // {"Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining},
      // {"Combine all 3 movements", combining_movements},
      // {"Interference\n\nAfter driving forward, robot performs differently if interfered or not", interfered_example},
      // {"Simple Odom\n\nThis is the same as the drive example, but it uses odom instead!", odom_drive_example},
      // {"Pure Pursuit\n\nGo to (0, 30) and pass through (6, 10) on the way.  Come back to (0, 0)", odom_pure_pursuit_example},
      {"Pure Pursuit Wait Until\n\nGo to (24, 24) but start running an intake once the robot passes (12, 24)", odom_pure_pursuit_wait_until_example},
      {"Boomerang\n\nGo to (0, 24, 45) then come back to (0, 0, 0)", odom_boomerang_example},
      {"Boomerang Pure Pursuit\n\nGo to (0, 24, 45) on the way to (24, 24) then come back to (0, 0, 0)", odom_boomerang_injected_pure_pursuit_example},
      {"Measure Offsets\n\nThis will turn the robot a bunch of times and calculate your offsets for your tracking wheels.", measure_offsets},
  });
 //tare the positions of the Chain lift and the Winch motors
   //Lift_1.tare_position();
   //Lift_2.tare_position();
  //Lift_set_0();
  Pivot_set_0();
 

  //winchPID.exit_condition_set(80, 50, 300, 150, 500, 500); /*Sets the exit conditions for the Winch PID*/
  LiftPID.exit_condition_set(80, 50, 300, 150, 500, 500); /*Sets the exit conditions for the Chain Lift PID*/


  //Once the code starts running, make the Flipper pistons in the starting position (retracted)
  

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

 Lift_Task.resume();
//  Pivot_Task.resume();
  /*
  Odometry and Pure Pursuit are not magic

  It is possible to get perfectly consistent results without tracking wheels,
  but it is also possible to have extremely inconsistent results without tracking wheels.
  When you don't use tracking wheels, you need to:
   - avoid wheel slip
   - avoid wheelies
   - avoid throwing momentum around (super harsh turns, like in the example below)
  You can do cool curved motions, but you have to give your robot the best chance
  to be consistent
  */

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}

/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line

          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
      }
    }

    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

constexpr double SIX_GEAR   = 84.0 / 36.0;  // six-bar motor revs per arm rev
constexpr double TWO_GEAR   = 3.0;          // 2-bar motor revs per arm rev
constexpr double LIFT_RATIO = 1.65;         // 2-bar arm speed / six-bar arm speed
constexpr double ARM_RPM    = 38;           // six-bar ARM speed
constexpr double SLOW_FACTOR = 0.45;          // Y button speed as a fraction of ARM_RPM (0.4 = ~15rpm)
constexpr double TWO_DOWN_FACTOR = 0.90;   // 2-bar speed on the way down, as a fraction of its up speed (1.0 = same as up)
constexpr double VERY_SLOW_FACTOR = 0.2;   // (0.2 = ~7.6 rpm)



  // claw spin after R2 release, then lift pulse
  bool r2WasPressed = false;
  uint32_t clawHoldUntil = 0;
  constexpr uint32_t CLAW_HOLD_MS = 1000;
  uint32_t clawPulseStart = 0;
  uint32_t clawPulseEnd   = 0;
  constexpr uint32_t CLAW_LIFT_PULSE_MS     = 350;
  constexpr double   CLAW_LIFT_PULSE_FACTOR = 0.7;   // negative = down




bool upWasPressed = false;
uint32_t liftPulseUntil = 0;
constexpr uint32_t LIFT_PULSE_MS     = 150;  // how long the pulse lasts
constexpr double   LIFT_PULSE_FACTOR = 0.7;  // pulse speed as a fraction of ARM_RPM








void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  // Lift_Task.suspend();
  //  Pivot_Task.suspend();

  // Lift_1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  // Lift_2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
 //  Lift_Task.suspend();



 sixbar.set_gearing_all(pros::E_MOTOR_GEAR_GREEN);
  twobar.set_gearing_all(pros::E_MOTOR_GEAR_GREEN);
  sixbar.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
  twobar.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
  

  bool r2WasPressed = false;
  uint32_t clawHoldUntil = 0;
  constexpr uint32_t CLAW_HOLD_MS = 500;


  while (true) {
    // Gives you some extras to make EZ-Template ezier
    ez_template_extras();

    chassis.opcontrol_tank();  // Tank control
  
   Wing_L.button_toggle(DIGITAL_UP);
   Wing_R.button_toggle(DIGITAL_X);





    const bool up        = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    const bool down      = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    const bool chainUp = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
    const bool chainDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
    const bool slowDown  = master.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
    const bool verySlowDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);

    double sixArm = 0;   // wanted arm rpm, six-bar
    double twoArm = 0;   // wanted arm rpm, 2-bar

    if (upWasPressed && !up) {
  liftPulseUntil = pros::millis() + LIFT_PULSE_MS;   // L1 just released: start the pulse
  }
    upWasPressed = up;


    if (up && !down) {                              // both lifts up, synced
      sixArm =  ARM_RPM;
      twoArm =  ARM_RPM * LIFT_RATIO;
    } else if (down && !up) {                       // both lifts down, synced
      sixArm = -ARM_RPM;
      twoArm = -ARM_RPM * LIFT_RATIO;
    } else if (verySlowDown && !up && !down) {          // NEW: both lifts down, very slow, synced
      sixArm = -ARM_RPM * VERY_SLOW_FACTOR;
      twoArm = -ARM_RPM * VERY_SLOW_FACTOR * LIFT_RATIO * TWO_DOWN_FACTOR;
    } else if (slowDown && !up && !down) {          // both lifts down, slow, synced
      sixArm = -ARM_RPM * SLOW_FACTOR;
      twoArm = -ARM_RPM * SLOW_FACTOR * LIFT_RATIO;
    } else if (chainUp && !chainDown) {             // chain lift only, up
      twoArm =  ARM_RPM * LIFT_RATIO;
    } else if (chainDown && !chainUp) {             // chain only, down
      twoArm = -ARM_RPM * LIFT_RATIO * TWO_DOWN_FACTOR;
    } else if (pros::millis() < liftPulseUntil) {       // short down pulse after L1 release
      sixArm = -ARM_RPM * LIFT_PULSE_FACTOR;
      twoArm = -ARM_RPM * LIFT_PULSE_FACTOR * LIFT_RATIO;   // ratio only, no TWO_DOWN_FACTOR
    } else if (pros::millis() >= clawPulseStart && pros::millis() < clawPulseEnd) {
      sixArm = ARM_RPM * CLAW_LIFT_PULSE_FACTOR;
      twoArm = ARM_RPM * CLAW_LIFT_PULSE_FACTOR * LIFT_RATIO;
    }

    // if (twoArm < 0) twoArm *= TWO_DOWN_FACTOR;   // slows the 2-bar on any downward move


    if (sixArm == 0) sixbar.brake();
    else             sixbar.move_velocity(sixArm * SIX_GEAR);

    if (twoArm == 0) twobar.brake();
    else             twobar.move_velocity(twoArm * TWO_GEAR);
    

    pros::delay(10);





const bool r1 = master.get_digital(DIGITAL_R1);
const bool r2 = master.get_digital(DIGITAL_R2);

if (r2WasPressed && !r2) {
  clawHoldUntil  = pros::millis() + CLAW_HOLD_MS;
  clawPulseStart = clawHoldUntil;
  clawPulseEnd   = clawPulseStart + CLAW_LIFT_PULSE_MS;
}
if (r1 || r2) { clawPulseStart = 0; clawPulseEnd = 0; }
r2WasPressed = r2;



if (r2) {
  Claw.move(-127);
} else if (r1) {
  Claw.move(127);
} else if (pros::millis() < clawHoldUntil) {
  Claw.move(127);                        // 1-second intake after releasing R2
} else {
  Claw.move(0);
}



forks.button_toggle(master.get_digital(DIGITAL_UP));






  }














   
  
  //   if(master.get_digital(DIGITAL_L1)){
  //     Lift_1.move(127);
  //     Lift_2.move(127); 
  //     Lift_3.move(127);
    
  //   }
  //   if(master.get_digital(DIGITAL_L2)){
  //     Lift_1.move(-127);
  //     Lift_2.move(-127); 
  //     Lift_3.move(-127);
  
  //   }
  //   if(master.get_digital(DIGITAL_Y)){
  //   Lift_1.move(-70);
  //   Lift_2.move(-70); 
  //   }
  //   if(!master.get_digital(DIGITAL_L1) && !master.get_digital(DIGITAL_L2) && !master.get_digital(DIGITAL_Y)){
  //     Lift_1.move(0);
  //     Lift_2.move(0); 
  //     Lift_3.move(0);
  //   }
     
  
    // if(master.get_digital(DIGITAL_X)){
    //   Pivot.move(127);
    // }
    
    // if(master.get_digital(DIGITAL_UP)){
    //   Pivot.move(-127);
    // }

    // if(!master.get_digital(DIGITAL_X) && !master.get_digital(DIGITAL_UP)){
    //   Pivot.move(0);
    // }

    // if(master.get_digital_new_press(DIGITAL_RIGHT)){
    //  Pivot_Toggle();
    //  pros::delay(10);
      
    // }

    

  //  uint32_t last_press_time = 0;
  //   const int double_press_threshold = 250; // milliseconds
  //   // 1. Detect if the button (e.g., Digital A) was just pressed
  //       if (master.get_digital_new_press(DIGITAL_R1)) {
  //           uint32_t current_time = pros::millis();

  //           // 2. Check if the time since the last press is within the threshold
  //           if (current_time - last_press_time < double_press_threshold) {
  //             // is the button is pressed 2 times within 250 milliseconds, it will retract both flippers to go into nuetral position
  //              Flip1.set(false);
  //              Flip2.set(false);
             
  //           } else {
  //               // Single press or first press action
  //                  if(is_extended){ // if the button is pressed 1 time and is extended, it will retract the flipper
  //                   Flip1.set(false);
  //                   Flip2.set(true);
  //                  }
  //                   if(!is_extended){ //if the button is pressed 1 time and is not extended, it will extend the flipper
  //                   Flip1.set(true);
  //                   Flip2.set(false);
  //                  }
  //            }
  //           // 3. Update the last press timestamp
  //           last_press_time = current_time;
  //      }
    
  pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  
  }


