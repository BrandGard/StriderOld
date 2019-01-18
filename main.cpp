/*

*/
#include <L298N.h>
#include <Receiver.h>
#include <ppmNavigate.h>
#include <StepperAssembly.h>
#include <AtlasSensor.h>

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SD.h>
#include <Adafruit_GPS.h>

/* Steering and Throttle Pin Definitions */
        
    /* Channel 1 from radio receiver */
    //#define RUDDER 2   
    /* Servo PPM out */
    //#define STEERING 10
    

    /* Channel 3 from radio receiver */
    #define rTHROTTLE 6
    #define lTHROTTLE 7

    #define rMotorPWM 12
    #define lMotorPWM 11


/* Sampling pin definitions*/

    /* Channel 5 from radio receiver */
    #define TRIGGER 8
    /* Channel 8 from radio receiver */
    #define SELECT 9

    /* Table Definitions */
    #define tableENA 2 
    #define tableENB 3
    #define tableIN1 17
    #define tableIN2 16
    #define tableIN3 15
    #define tableIN4 14
    int tableIndex = 0;
    int tablePositions = 16;
    int tableCal[] = {0,320,660,1000,1340,1600,1750,2000,0,0,0,0,0,0,0,0};

    //4 5 25 24 23 22
    /* Winch Definitions */
    #define winchENA 4 
    #define winchENB 5
    #define winchIN1 25
    #define winchIN2 24
    #define winchIN3 23
    #define winchIN4 22
    int winchIndex = 0;
    int winchPositions = 3;
    int winchCal[] = {0,3000,6000,9000};

    /* Pumping Definitions */
    #define PUMP 13
    #define VALVE1 37
    #define VALVE2 38   
    unsigned int purgeTime = 3000;
    unsigned int sampleTime = 3000;
    unsigned long start;

/* declare navigation system object */
    //ppmNavigate Navigate(STEERING,THROTTLE,RUDDER,motorENA,motorIN1,motorIN2,motorENB,motorIN3,motorIN4);
    Receiver Trigger(TRIGGER,SELECT,lTHROTTLE,rTHROTTLE);

    //setPwmFrequency(4,490);
    stepperAssembly Table(tableENA,tableENB,tableIN1,tableIN2,tableIN3,tableIN4,200,90,tablePositions,295);
    stepperAssembly Winch(winchENA,winchENB,winchIN1,winchIN2,winchIN3,winchIN4,200,60,winchPositions,1000);

    Servo pump;

    Servo rMotor;
    Servo lMotor;

/* atlas sensor declarations */
    char *phData, *doData, *orpData; 
    char date[8];

    #define addressPH 99
    #define addressORP 97
    #define addressDO 98

    AtlasSensor ph = AtlasSensor(addressPH);
    AtlasSensor orp = AtlasSensor(addressORP);
    AtlasSensor DO = AtlasSensor(addressDO);


/* gps declarations */

/* sd card declarations */
#define cs_select_pin 53
#define HEADER "Lat,Long,ph,do,orp"

File logfile;
Adafruit_GPS GPS(&Serial1);
double latB10 = 0.0000, lonB10 = 0.0000;
bool SerialData = true;


/* function declarations */
void pumpAssembly(unsigned int time);

void initGPS(bool SerialFlag, int baud);
void getGPS_lat_lon(bool SerialFlag, bool gps_lock);
void getGPS_date(bool SerialFlag, bool gps_lock);
void getGPS_lock(bool SerialFlag, bool gps_lock);

void create_log_file(bool serialoutput);
void save_file(bool serialoutput);

void setup() {

    pinMode(rTHROTTLE,INPUT);
    pinMode(lTHROTTLE,INPUT);
    pinMode(TRIGGER,INPUT);
    pinMode(SELECT,INPUT);
    //pinMode(lMotorPWM,OUTPUT);
    //pinMode(rMotorPWM,OUTPUT);
    pinMode(tableENA,OUTPUT);
    pinMode(tableENB,OUTPUT);
    pinMode(tableIN1,OUTPUT);
    pinMode(tableIN2,OUTPUT);
    pinMode(tableIN3,OUTPUT);
    pinMode(tableIN4,OUTPUT);
    pinMode(winchENA,OUTPUT);
    pinMode(winchENB,OUTPUT);
    pinMode(winchIN1,OUTPUT);
    pinMode(winchIN2,OUTPUT);
    pinMode(winchIN2,OUTPUT);
    pinMode(winchIN3,OUTPUT);
    pinMode(winchIN4,OUTPUT);
    
    //pinMode(PUMP,OUTPUT);
    pinMode(VALVE1,OUTPUT);
    pinMode(VALVE2,OUTPUT);

    //Serial.begin(9600);
    //Wire.begin(9600);
    //initGPS(SerialData, 9600);
    //create_log_file(SerialData);
       
    for(int i = 0; i < tablePositions; i++){
        Table.indexCal(i,tableCal[i]);
    }
    for(int i = 0; i < winchPositions; i++){
        Winch.indexCal(i,winchCal[i]);        
    }
       
    pump.attach(PUMP);
    pump.writeMicroseconds(1500);
    digitalWrite(VALVE1,HIGH);
    digitalWrite(VALVE2,LOW);

    lMotor.attach(lMotorPWM);
    rMotor.attach(rMotorPWM);

    lMotor.writeMicroseconds(1500);
    rMotor.writeMicroseconds(1500);



}
void loop() {
    lMotor.writeMicroseconds(Trigger.Channel3(MicroSeconds));
    rMotor.writeMicroseconds(Trigger.Channel4(MicroSeconds));
    if(Trigger.Channel1(Bool) == 1 && tableIndex <= tablePositions){
        while(winchIndex <= winchPositions){
            tableIndex++;
            winchIndex++;
            //Winch.moveTo(winchIndex);
            //pumpAssembly(purgeTime);
            Table.moveTo(tableIndex);
            pumpAssembly(sampleTime);
            Table.moveTo(0);
            delay(500);
            /*
            //for(int i = 0; i < 5; i++){
            phData = ph.read();
            orpData = orp.read();
            doData = DO.read();
            //}

            //getGPS_lat_lon(SerialData, true); 
            save_file(SerialData);
            */
        }
        winchIndex = 0;
        delay(500);
        //Winch.moveTo(winchIndex);
    }
}

void pumpAssembly(unsigned int time){
    start = millis();                                
    while( (millis() - start) < time){                        // Take water sample.
        lMotor.writeMicroseconds(Trigger.Channel3(MicroSeconds));
        rMotor.writeMicroseconds(Trigger.Channel4(MicroSeconds));
        //Navigate.Update();
        pump.writeMicroseconds(2000);    
    }
    pump.writeMicroseconds(1500);
};

void initGPS(bool SerialFlag, int baud){
    //Configures the GPS Module To Ouput Correct Data
    if (SerialFlag == true){
        Serial.println("Initializing GPS Data Link");
    }
    GPS.begin(baud);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Request Both RMS & GGA NMEA Sentences
    GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ); //Update Rate = 1 Hz
    GPS.sendCommand(PGCMD_NOANTENNA); // NO Antenna Used
};

void getGPS_lat_lon(bool SerialFlag, bool gps_lock){
    //Gathers the GPS Lat and Long
    
    if(SerialFlag == true){
        Serial.println("Getting GPS Data - Longtitude, Latitude");
    }
    if (gps_lock == false){
        getGPS_lock(SerialFlag, gps_lock);
        Serial.print("gps lock \n");
        latB10 = GPS.latitude/100;
        lonB10 = GPS.longitude/100;
        double intPart, decPart;

        //Converts the Position in Minutes and Seconds of Division
        decPart = (modf(latB10, &intPart))/(0.60);
        latB10 = intPart + (decPart);
        decPart = (modf(lonB10, &intPart))/(0.60);
        lonB10 = intPart + (decPart);
        if(GPS.lat == 'S') latB10 = -latB10;
        if(GPS.lon == 'W') lonB10 = -lonB10;

       
    } 
};

void getGPS_date(bool SerialFlag, bool gps_lock){
    //Gets the GPS Dat
    if(SerialFlag == true) Serial.println("Getting GPS Data - Date");
    if (gps_lock == false){
        getGPS_lock(SerialFlag, gps_lock);
        int day = GPS.day;
        int month = GPS.month;
        int year = GPS.year;

        sprintf_P(date, (PGM_P)F("%02d%02d%04d"), month, day, year); // Creates a String For the Date - SD Card File Name is limited to 8 characters

    }
};

void getGPS_lock(bool SerialFlag, bool gps_lock){
    //Gathers a GPS Lock
    while(!gps_lock){
            GPS.read();
            if(GPS.newNMEAreceived()){
                if(SerialFlag == true){
                    Serial.println("Getting NMEA String");
                }
                if(!GPS.parse(GPS.lastNMEA())){
                    continue;
                }
                if(true && GPS.fix){
                    gps_lock = true;
                }
            }
        }    
};

void create_log_file(bool serialoutput){
    //Creates the Log File on the SD Card
    if(serialoutput == true){
        Serial.println("Create Log File");
    }
    if(!SD.begin(cs_select_pin)){
        // ERROR CODE
        if(serialoutput == true){  Serial.println("SD Card Not Present");}
    }
    getGPS_date(serialoutput, false);
    if(!SD.exists(date)){
        if(serialoutput == true){
            Serial.print(date);
            Serial.println(" Created");
        }
        logfile = SD.open(date, FILE_WRITE);
        logfile.write(HEADER);
        logfile.println("");
        logfile.flush();
    }
};

void save_file(bool serialoutput){
    //Saves Data to SD Card
    bool flag = true;
    if(logfile){
    logfile.print(latB10);
    logfile.print(",");
    logfile.print(lonB10);
    logfile.print(",");
    logfile.print(phData);
    logfile.print(",");
    logfile.print(doData);
    logfile.print(",");
    logfile.print(orpData);
    logfile.print("");
    logfile.flush();
    }
    else{
        if(serialoutput == true) {
            flag = false;
            Serial.println("Error opening file.");
        }
    }

    if(serialoutput == true && flag == true){
        Serial.print(phData);
        Serial.print(" ,");
        Serial.print(doData);
        Serial.print(" ,");
        Serial.println(orpData);
    }
};