#include<iostream>
#include <time.h>
#include <signal.h>
#include"FilteredReadSensors.h"
#include"SensorsSystem.h"


bool exitFlag=false;
int calibrate=2;

void signalTerminatingHandler(int sig){
  if(calibrate==0){
    exitFlag=true;
  }
  
  if(calibrate==1){
    calibrate--;
  }
  if(calibrate==2){
    calibrate--;
  }
  
}


int main(){
  SensorsSystem* _sensSys = new SensorsSystem();
  ReadSensors* _rS = new FilteredReadSensors(_sensSys);


  signal(SIGINT,  signalTerminatingHandler);
  signal(SIGHUP,  signalTerminatingHandler);
  signal(SIGKILL, signalTerminatingHandler);
  signal(SIGQUIT , signalTerminatingHandler);
 
  long refresh=100;
  long refSec=refresh / 1000;
  long refNSec=(refresh * 1000000) % 1000000000;
  struct timespec pollTime;
  struct timespec remTime;
  int id=0;
  while(!exitFlag)
  {
    
    system("clear");
    cout<<"calibrate = "<<calibrate<<endl;
    if(calibrate==2){
      cout<<"Not Calibrating"<<endl;
    }

    if(calibrate==1){
	cout<<"Calibrating..."<<endl;
	for(int i=0; i<static_cast<int>(_sensSys->getSensorsIDs().size());i++){
	  id =_sensSys->getIDSensor(i);
	  _sensSys->setSensorCalibrateMin(id,_rS->getSensorValue(id));
	  _sensSys->setSensorCalibrateMax(id,_rS->getSensorValue(id));
      }
    }
    if(calibrate==0){
      cout<<"Stop calibrating"<<endl;
    }
    cout<<_rS<<endl;
   
    pollTime.tv_sec=refSec;
    pollTime.tv_nsec=refNSec;
    while(nanosleep(&pollTime, &remTime) == -1)
      pollTime=remTime;
  }
};
