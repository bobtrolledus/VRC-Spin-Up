/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       mecanumDrivetrain.cpp                                     */
/*    Author:       Trubotics                                                 */
/*    Created:      2022-12-13, 10:55:45 p.m.                                 */
/*    Description:  A cool thing made to simplify the mecanum drive train     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <cmath>
#include <vex.h>
#include <mecanumDrivetrain.h>

using namespace vex;

MecanumDriveTrain::MecanumDriveTrain(int32_t leftFrontPort, int32_t leftBackPort, int32_t rightFrontPort, int32_t rightBackPort)
{
    leftFront = motor(leftFrontPort, ratio18_1, false);
    leftBack = motor(leftBackPort, ratio18_1, false);
    rightFront = motor(rightFrontPort, ratio18_1, false);
    rightBack = motor(rightBackPort, ratio18_1, false);

    // set brake modes
    leftFront.setStopping(vex::brakeType::hold);
    leftBack.setStopping(vex::brakeType::hold);
    rightFront.setStopping(vex::brakeType::hold);
    rightBack.setStopping(vex::brakeType::hold);
}

const double PI = atan(1) * 4;
void MecanumDriveTrain::convertMotorValues(int forward, int strafe, int turn, int motorValues[])
{
    // alternative more accurate version (if it works correctly), uncomment and test
    int x = strafe;      // unnecessary, can be directly put into atan and hypot
    int y = -forward;    // unnecessary, can be directly put into atan and hypot
    double theta = atan2(y, x);
    double power = hypot(x, y);
    
    double s = sin(theta - PI/4);
    double c = cos(theta - PI/4);
    
    double mx = fmax(fabs(s), fabs(c));
    motorValues[0] = power * c/mx + turn; // front left
    motorValues[1] = power * s/mx + turn; // back left
    motorValues[2] = power * s/mx - turn; // front right
    motorValues[3] = power * c/mx - turn; // back right
    
    if ((power + abs(turn)) > 127) { // unsure if 127 is max < it's -127 to 127
        for (int i=0;i<4;i++) {
            motorValues[i] /= power+turn;
        }
    }
    
    return;
}

void MecanumDriveTrain::drive(int forward, int strafe, int turn)
{
    int motorValues[4];
    convertMotorValues(forward, strafe, turn, motorValues);
    leftFront.spin(vex::forward, motorValues[0], vex::percent);
    leftBack.spin(vex::forward, motorValues[1], vex::percent);
    rightFront.spin(vex::forward, motorValues[2], vex::percent);
    rightBack.spin(vex::forward, motorValues[3], vex::percent);
    return;
}

// TODO: add more drive functions as needed (for autonomous period, etc.)
