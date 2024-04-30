#ifndef MOTOR_H
#define MOTOR_H

void initMotors(void);
void setLeftPWMForward(float);
void setRightPWMForward(float);

void setLeftPWMBackward(float);
void setRightPWMBackward(float);

void pulseLeftMotor(void);
void pulseRightMotor(void);

#endif

