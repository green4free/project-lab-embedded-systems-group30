#pragma once


//#define DEBUG

//Motor data
#define STEPS_PER_TURN 200
#define TURNS_PER_MM 2.3707


//Behavioral data
#define ZERO_DEFELCTION_POINT (13276 + 7112) //In steps, can be changed, don't know whats best.. Current value to not make the "calibration" take so long time, will be corrected when we have a real setup


//Sensor data
#define SENS_LENGTH 0.17
#define SENS_WIDTH 0.03
#define SENS_THICKNSSS 0.0014


//Standard values for sweep
#define STD_NR_STOPS 10
#define STD_START_POINT 0.0

//Stat
#define NUMBER_OF_SAMPLES 1000
#define MAXIMUM_Z_SCORE 2.0

//Constants for communication
#define SEND_PRECISION 4



//Sensor parameters
#define REFERENCE_RESISTANCE 9930.0
#define FACTOR_COEFICIEN_THING 2.06 //Find better name
