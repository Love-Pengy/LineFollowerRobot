#ifndef MOTOR_H
#define MOTOR_H

void initMotors(void);
void setLeftPWM(float);
void setRightPWM(float);

void pulseLeftMotor(void);
void pulseRightMotor(void);

#endif

