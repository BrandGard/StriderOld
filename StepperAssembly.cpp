/*

*/

#include <StepperAssembly.h>

stepperAssembly::stepperAssembly(int enA,int enB,int in1,int in2, int in3, int in4, int res, int RPM, int indexes, int indexRes):stepperControl(enA,enB,in1,in2,in3,in4,res,RPM){
    //Serial.begin(9600);
    
    _index = 0;
    _indexes = indexes;
    for(int i = 0 ; i < indexes ; i++){
        _cal[i] = i*indexRes;
    }
};
void stepperAssembly::indexCal(int indexNum, int indexRes){
    _cal[indexNum] = indexRes;
};
void stepperAssembly::moveTo(int target){
    /*for(int i = 0; 0 < _indexes; i++){
        Serial.print(_cal[i]);Serial.print("\n");
    }*/

    Step(target);
    if(target > _index){
        Step(-(_cal[target] - _cal[_index]));
    }
    if(target < _index){
        Step(-(_cal[target] - _cal[_index]));
    }
    _index = target;


};
//void stepperAssembly::radioTest(int,int,int,int){};