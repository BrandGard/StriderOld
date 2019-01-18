/*
    l298n.h library for l298n stepper motor controller 
*/

#include <L298N.h>

stepperControl::stepperControl(int ENA ,int ENB ,int IN1,int IN2,int IN3,int IN4, int res, int RPM):Stepper(res,IN1,IN2,IN3,IN4){
    _enA = ENA; _enB = ENB;
    _in1 = IN1; _in2 = IN2; _in3 = IN3; _in4 = IN4;
    _res = res; _RPM = RPM; _pos = 0;
    
    pinMode(_enA,OUTPUT);
    pinMode(_enB,OUTPUT);
    pinMode(_in1,OUTPUT);
    pinMode(_in2,OUTPUT);
    pinMode(_in3,OUTPUT);
    pinMode(_in4,OUTPUT);

    setSpeed(_RPM);
    analogWrite(_enA,127);
    analogWrite(_enB,127);

};
void stepperControl::Step(int n){
    step(n);
    _pos = _pos + n;    
};

motorControl::motorControl(int EN,int INA,int INB){
    pinMode(EN, OUTPUT);
    pinMode(INA, OUTPUT);
    pinMode(INB, OUTPUT);

    _enA  = EN;
    _in1 = INA;
    _in2 = INB;
};

motorControl::motorControl(int enA,int enB, int in1, int in2, int in3, int in4){
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    _enA = enA;
    _in1 = in1;
    _in2 = in2;

    _enB = enB;
    _in3 = in3;
    _in4 = in4;
};

void motorControl::setSpeed(int percentage){
 
    percentage = constrain(percentage, 0, 100);

    _speedA = percentage * 2.55;
    analogWrite(_enA, _speedA);

};

void motorControl::setSpeed(int percentageA, int percentageB){
 
    percentageA = constrain(abs(percentageA), 0, 100);
    percentageB = constrain(abs(percentageB), 0, 100);

    _speedA = percentageA * 2.55;
    _speedB = percentageB * 2.55;

    analogWrite(_enA, _speedA);
    analogWrite(_enB, _speedB);

};

void motorControl::setDirection(direction d){
    switch (d)
    {
        case LEFT:
            digitalWrite(_in1, HIGH);
            digitalWrite(_in2, LOW);
            break;

        case RIGHT:
            digitalWrite(_in1, LOW);
            digitalWrite(_in2, HIGH);
            break;

        case NONE:
            stop();
            break;
    }

    _directionA = d;
};


void motorControl::setDirection(direction dA,direction dB){
    switch (dA)
    {
        case LEFT:
            digitalWrite(_in1, HIGH);
            digitalWrite(_in2, LOW);
            break;

        case RIGHT:
            digitalWrite(_in1, LOW);
            digitalWrite(_in2, HIGH);
            break;

        case NONE:
            stop();
            break;
    }

        switch (dB)
    {
        case LEFT:
            digitalWrite(_in3, HIGH);
            digitalWrite(_in4, LOW);
            break;

        case RIGHT:
            digitalWrite(_in3, LOW);
            digitalWrite(_in4, HIGH);
            break;

        case NONE:
            stop();
            break;
    }

    _directionA = dA;
    _directionB = dB;
};

void motorControl::stop(motor M)
{
    switch(M){
        case A:
            digitalWrite(_enA, LOW);
            digitalWrite(_in1, LOW);
            digitalWrite(_in2, LOW);
            _speedA = 0;
            _directionA = NONE;
            break;
        case B:
            digitalWrite(_enB, LOW);
            digitalWrite(_in3, LOW);
            digitalWrite(_in4, LOW);
            _speedB = 0;
            _directionB = NONE;
            break;
    }
};

void motorControl::stop()
{

        digitalWrite(_enA, LOW);
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, LOW);
        _speedA = 0;
        _directionA = NONE;

        digitalWrite(_enB, LOW);
        digitalWrite(_in3, LOW);
        digitalWrite(_in4, LOW);
        _speedB = 0;
        _directionB = NONE;
    
    
};



