/*

*/

#include <Receiver.h>

Receiver::Receiver(int channel1Pin){

   _channel1Pin = channel1Pin;

   pinMode(channel1Pin,INPUT);
};

Receiver::Receiver(int channel1Pin, int channel2Pin){

   _channel1Pin = channel1Pin;
   _channel2Pin = channel2Pin;

   pinMode(_channel1Pin,INPUT);
   pinMode(_channel2Pin,INPUT);
};

Receiver::Receiver(int channel1Pin, int channel2Pin, int channel3Pin, int channel4Pin){

    _channel1Pin = channel1Pin;
    _channel2Pin = channel2Pin;
    _channel3Pin = channel3Pin;
    _channel4Pin = channel4Pin;

    pinMode(_channel1Pin,INPUT);
    pinMode(_channel2Pin,INPUT);
    pinMode(_channel1Pin,INPUT);
    pinMode(_channel2Pin,INPUT);
};

int Receiver::Channel1(format out){
    int output;
    output = pulseIn(_channel1Pin,HIGH);
    output = map(output,1150,1920,1000,2000);
    output = constrain(output,1000,2000);

    switch(out){
    case MicroSeconds:
        break;
    case Percent:
        output = map(output,1100,1900,0,100);
        output = constrain(output,0,100);
        break;
    case Angle:
        output = map(output,1000,2000,0,180);
        output = constrain(output,0,180);
        break;
    case Bool:
        if( output > 1500 ){
            output = 1;
            break;
        }
        if( output < 1500 ){
            output = 0;
            break;
        }
    case ThreeState:
        if( output < 1250){
            output = 1;
            break;
        }
        if( output < 1750){
            output = 2;
            break;
        }
        if( output < 2000){
            output = 3;
            break;
        }
    }


    return output;
};

int Receiver::Channel2(format out){
    int output;

    output = pulseIn(_channel2Pin,HIGH);
    output = map(output,1150,1950,1000,2000);
    output = constrain(output,1000,2000);

    switch(out){
    case MicroSeconds:
        break;
    case Percent:
        output = map(output,1100,1900,0,100);
        break;
    case Angle:
        output = map(output,1000,2000,0,180);
        break;
    case Bool:
        if( output > 1500 ){
            output = 1;
            break;
        }
        if( output < 1500 ){
            output = 0;
            break;
        }    
    case ThreeState:
        if( output < 1250){
            output = 1;
            break;
        }
        if( output < 1750){
            output = 2;
            break;
        }
        if( output < 2000){
            output = 3;
            break;
        }    
    }
    return output;
};

int Receiver::Channel3(format out){
    int output;

    output = pulseIn(_channel3Pin,HIGH);
    output = map(output,1150,1950,1000,2000);
    output = constrain(output,1000,2000);

    switch(out){
    case MicroSeconds:
        break;
    case Percent:
        output = map(output,1100,1900,0,100);
        break;
    case Angle:
        output = map(output,1000,2000,0,180);
        break;
    case Bool:
        if( output > 1500 ){
            output = 1;
            break;
        }
        if( output < 1500 ){
            output = 0;
            break;
        }
    case ThreeState:
        if( output < 1250){
            output = 1;
            break;
        }
        if( output < 1750){
            output = 2;
            break;
        }
        if( output < 2000){
            output = 3;
            break;
        }            
    }
    return output;
};

int Receiver::Channel4(format out){
    int output;

    output = pulseIn(_channel4Pin,HIGH);
    output = map(output,1150,1950,1000,2000);
    output = constrain(output,1000,2000);

    switch(out){
    case MicroSeconds:
        break;
    case Percent:
        output = map(output,1100,1900,0,100);
        break;
    case Angle:
        output = map(output,1000,2000,0,180);
        break;
    case Bool:
        if( output > 1500 ){
            output = 1;
            break;
        }
        if( output < 1500 ){
            output = 0;
            break;
        }    
    case ThreeState:
        if( output < 1250){
            output = 1;
            break;
        }
        if( output < 1750){
            output = 2;
            break;
        }
        if( output <= 2000){
            output = 3;
            break;
        }        
    }
    return output;
};
