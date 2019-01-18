/*

*/

#ifndef PPMnavigate_h
#define PPMnavigate_h

#include <Receiver.h>
#include <L298N.h>

#include <Servo.h>

class ppmNavigate:Receiver,motorControl,Servo{
    public:
        ppmNavigate(int,int,int,int,int,int,int,int,int);
        void Update();
    private:
        int _throttleInPin, _steeringInPin;
        int _steeringOutPin;
};       

#endif