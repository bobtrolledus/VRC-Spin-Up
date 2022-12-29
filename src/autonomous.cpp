#include <cmath>
#include <vex.h>
#include <mecanumDrivetrain.h>

const int  drivePCT_AUTO = 50;
const float wheelCirc = 4.125 * 3.1416;
const float gearRatio = 0.5;
const float turningDiameter = 19.0;


namespace colours 
{
const int red = 1;
const int blue = 2;
const int miss = 3;
} 


// sensors 
pros::Distance indexerSensor(2);
pros::Optical rollerSensor(3);
pros::IMU imu_sensor(1);


// define OPTICAL_PORT 1
void initialize() 
{
  public vex::optical::optical(int32_t index, bool enableGesture=false)
}


// gets roller colour from optical sensor
int getColourRoller()
{
    if(rollerSensor.get_proximity()<200)
    {
        return 0;
    }

// determines the colour of the roller
    double hue = rollerSensor.get_hue();
    if (hue > 0 && hue < 20) 
    {
        return 1;                           // recognizes its red
        } 
        else if (hue > 220 && hue < 250) 
        {
            return 2;                       // recognizes its blue
        } 
        else 
        {
            return 3;                       // didn’t recognize
        }
        return 0;
}


// turns the roller to blue
void setBlueRoller()
{
    int rollerTime = pros::millis();
    roller.move_velocity(100);

    while(pros::millis() - rollerTime < 1250 && getColourRoller() != 1)
    {
        pros::delay(5);
    }

    // need to add further functions
}

// turns the roller red
void setRedRoller() 
{
	int rollerTime = pros::millis();
	roller.move_velocity(100);
    
	while (pros::millis() - rollerTime < 1250 && getColourRoller() != 2) 
    {
		pros::delay(5);
	}

	// need to add further functions
}



// need to add further functions


void auton()
{
    // neg value indicates red
    // pos value indicates blue
}

