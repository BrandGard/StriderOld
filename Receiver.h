/*

*/

#ifndef Receiver_h
#define Receiver_h

#include <Arduino.h>
#include <math.h>

typedef enum {MicroSeconds,Percent,Angle,Bool,ThreeState} format;

class Receiver{
    public:
        Receiver(int);
        Receiver(int,int);
        Receiver(int,int,int,int);
        int Channel1(format);
        int Channel2(format);
        int Channel3(format);
        int Channel4(format);

    private:
        int _channel1Pin;
        int _channel2Pin;
        int _channel3Pin;
        int _channel4Pin;
};

#endif