//
//  Header.h
//  
//
//  Created by Rakesh Joshi on 6/2/16.
//
//
#include <Arduino.h>
#ifndef AtlasSensor_h
#define AtlasSensor_h


//#include "../../libraries/Wire.h"
class AtlasSensor
{
private:
    char data[20];
    
    char in_char;
    float sensor_float;
    int address;
    
public:
    AtlasSensor();
    AtlasSensor(int);
    char* read();
   
    
};

#endif
