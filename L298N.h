/*
    l298n.h library for l298n stepper motor controller 
*/

#ifndef L298N_h
#define L298N_h

#include <Stepper.h>
#include <Arduino.h>

typedef enum {LEFT, RIGHT, NONE} direction;
typedef enum {A,B} motor;

class stepperControl: public Stepper{
    public:
        stepperControl(int ENA ,int ENB ,int IN1,int IN2,int IN3,int IN4, int res, int RPM);
        void Step(int step);
    private:
        int _enA, _enB;
        int _in1, _in2, _in3, _in4;
        int _res, _RPM, _pos; 
};

class motorControl{
    public:
        motorControl(int,int,int,int,int,int);
        motorControl(int,int,int);
        
        void setSpeed(int);
        void setSpeed(int,int);
        void setDirection(direction);
        void setDirection(direction, direction);
        void stop(motor);
        void stop();

    private:
        int _enA , _enB;
        int _in1, _in2, _in3, _in4;
        int _speedA, _speedB;
        direction _directionA, _directionB;

};

#endif