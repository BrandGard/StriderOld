/*

*/

#ifndef StepperAssembly_h
#define StepperAssembly_h

#include <L298N.h>
#include <SoftwareSerial.h>


class stepperAssembly:public stepperControl{ 
    public:
        stepperAssembly(int,int,int,int,int,int,int,int,int,int);
        void indexCal(int,int);
        //int checkCal(int,int);
        void moveTo(int);
        //void radioTest(int,int,int,int);
    private:
        int _index;
        int _indexes;
        int _cal[30];

};

#endif