/*

*/

#include <PPMnavigate.h>


ppmNavigate::ppmNavigate( int steeringInPin, int throttleInPin, int steeringOutPin,  int enablePinM1, int M1pinA, int M1pinB,int enablePinM2, int M2pinA, int M2pinB): Receiver(steeringInPin, throttleInPin), motorControl(enablePinM1,enablePinM2,M1pinA,M1pinB,M2pinA,M2pinB), Servo(){
    _throttleInPin = throttleInPin;
    _steeringInPin = steeringInPin;
    _steeringOutPin = steeringOutPin;

    pinMode(_throttleInPin, INPUT);
    pinMode(_steeringInPin, INPUT);
    pinMode(_steeringOutPin, OUTPUT);


};

void ppmNavigate::Update(){

    int steering = Channel1(Angle);
    attach(_steeringOutPin);
    write(steering);
    delay(15);
    
    int throttle = Channel2(Percent);   
    throttle = map(throttle,6,96,-100,100);
    
    if(throttle > 2){
        setDirection(RIGHT,RIGHT);
        setSpeed(throttle,throttle);
    }
    else if(throttle < -2){
        setDirection(LEFT,LEFT);
        setSpeed(throttle,throttle);
    }
    else{
        setDirection(NONE);
    }
};