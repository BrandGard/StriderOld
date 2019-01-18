//
//  AtlasSensor.cpp
//  
//
//  Created by Rakesh Joshi on 9/23/16.
//
//




#include <Arduino.h>
#include <Wire.h>
#include <AtlasSensor.h>

AtlasSensor::AtlasSensor()
{
    data[20] = NULL;
   
    in_char = 0;
    sensor_float = 0;
    address = 0;
}

AtlasSensor::AtlasSensor(int add)
{
    data[20] = NULL;
   
    char in_char = 0;
    sensor_float = 0;
    address = add;
}


char* AtlasSensor::read()
{
    char code = 0;
    char in_char;
    int i = 0;
    
    Wire.beginTransmission(address);
    Wire.write('R');
    Wire.endTransmission();
    delay(1000);
    Wire.requestFrom(address,20,1);
    code = Wire.read();
    
    while(Wire.available())
    {
        in_char = Wire.read();
        data[i] = in_char;
        i+=1;
        if(in_char == 0)
        {
            i=0;
            Wire.endTransmission();
            break;
        }
    }

    sensor_float=atof(data);
    return(data);
}


