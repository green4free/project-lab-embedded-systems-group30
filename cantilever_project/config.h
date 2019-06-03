#pragma once

//Motor data
#define STEPS_PER_TURN 200
#define TURNS_PER_MM 1


//Behavioral dat
#define MOVE_SIZE 5 //In mm
#define ZERO_DEFELCTION_POINT 5 //In steps, can be changed, don't know whats best.. Current value to not make the "calibration" take so long time, will be corrected when we have a real setup


//Sensor data
#define SENS_LENGTH 0.17
#define SENS_WIDTH 0.03
#define SENS_THICKNSSS 0.0014
