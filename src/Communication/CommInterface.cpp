#include <cstdlib> 
#include <sys/time.h>
#include <unistd.h>
#include "CommInterface.h"
#include "CommInterfaceNetwork.h"


class CommInterfaceNetwork;

void 
CommInterface::cgMessageMvJointFactory(messageType& mvType, vector<int>& servos, vector<int>& uradPositions, vector<int>& parameters, string& temp){
   
  switch(mvType){
    case MVJOINTWSPEED:
       CommInterface::cgMessageMvJointWSpeedFactory(servos,uradPositions,parameters, temp);
    break;
     case MVJOINTWTIME:
        CommInterface::cgMessageMvJointWTimeFactory(servos,uradPositions,parameters, temp);
    break;
     case MVJOINTUWSPEED:
        CommInterface::cgMessageMvJointUWSpeedFactory(servos,uradPositions,parameters, temp);
    break;
     case MVJOINTUWTIME:
        CommInterface::cgMessageMvJointUWTimeFactory(servos,uradPositions,parameters, temp);
    break;
     default:
        CommInterface::cgMessageMvJointUWTimeFactory(servos,uradPositions,parameters, temp);
    break;
   }
}

CommInterface* 
CommInterface::CommInterfaceFactory(int port, const char* ip_address, PROTOCOL prot) throw(ExceptionConnectionError){
  
//   if(prot==SERIAL) return (new CommInterfaceSerial());
//   else{
    return (new CommInterfaceNetwork(port,ip_address,prot));
//   }
  
}

void
CommInterface::cgMessageMvJointWTimeFactory(int servo, int uradposition, int utime, string& temp){
	char tempChr[128];
// 	struct timeval tv;
// 	gettimeofday(&tv, NULL);
// 	unsigned int t1 = tv.tv_usec;
// 	unsigned int randomNumber = rand_r(&t1);
	temp="MVJOINTWTIME(";
	sprintf(tempChr,"%ld,%d,%d,%d",random(), servo, uradposition, utime);
	temp+=tempChr;
	temp+=");";
}

/*
 SINTASSI:<BR>
     MVJOINTWTIME(\<casuale\> [,\<servo ID\> ,\<new position\>, \<new time\> [,\<servo ID\> ,\<new position\>, \<new time\> ...] ])
     */
void
CommInterface::cgMessageMvJointWTimeFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& utime, string& temp){

  char tempChr[128];
//   struct timeval tv;
//   gettimeofday(&tv, NULL);
//   unsigned int t1 = tv.tv_usec;
//   unsigned int randomNumber = rand_r(&t1);
  temp="MVJOINTWTIME(";
  sprintf(tempChr,"%ld",random());
  temp+=tempChr;
  for(unsigned int i=0;i<servo.size();++i){
    sprintf(tempChr,",%d,%d,%d",servo[i], uradposition[i],utime[i]);
    temp+=tempChr;
  }
  temp+=");";
}



void 
CommInterface::cgMessageMvJointWSpeedFactory(int servo, int uradposition, int uspeed, string& temp){
	char tempChr[128];
	temp="MVJOINTWSPEED(";
	sprintf(tempChr,"%ld,%d,%d,%d", random(), servo, uradposition, uspeed);
	temp+=tempChr;
	temp+=");";
}


void
CommInterface::cgMessageMvJointWSpeedFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& uspeed, string& temp){

  char tempChr[128];
//   struct timeval tv;
//   gettimeofday(&tv, NULL);
//   unsigned int t1 = tv.tv_usec;
//   unsigned int randomNumber = rand_r(&t1);
  temp="MVJOINTWSPEED(";
  sprintf(tempChr,"%ld",random());
  temp+=tempChr;
  for(unsigned int i=0;i<servo.size();++i){
    sprintf(tempChr,",%d,%d,%d",servo[i], uradposition[i],uspeed[i]);
    temp+=tempChr;
  }
  temp+=");";
}


void CommInterface::cgMessageMvJointUWTimeFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& utime, string& temp){
   char tempChr[128];
//   struct timeval tv;
//   gettimeofday(&tv, NULL);
//   unsigned int t1 = tv.tv_usec;
//   unsigned int randomNumber = rand_r(&t1);
  temp="MVJOINTUWTIME(";
  sprintf(tempChr,"%ld",random());
  temp+=tempChr;
  for(unsigned int i=0;i<servo.size();++i){
    sprintf(tempChr,",%d,%d,%d",servo[i], uradposition[i],utime[i]);
    temp+=tempChr;
  } 
  temp+=");";
}


void CommInterface::cgMessageMvJointUWSpeedFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& uspeed, string& temp){
   char tempChr[128];
//   struct timeval tv;
//   gettimeofday(&tv, NULL);
//   unsigned int t1 = tv.tv_usec;
//   unsigned int randomNumber = rand_r(&t1);
  temp="MVJOINTUWSPEED(";
  sprintf(tempChr,"%ld",random());
  temp+=tempChr;
  for(unsigned int i=0;i<servo.size();++i){
    sprintf(tempChr,",%d,%d,%d",servo[i], uradposition[i],uspeed[i]);
    temp+=tempChr;
  }
  temp+=");";

}
    

void 
CommInterface::cgMessageReqSensor(int sensorID,string& temp){
  char tempChr[128];
  temp="REQSENSOR(";
  sprintf(tempChr,"%ld,%d", random(), sensorID);
  temp+=tempChr;
  temp+=");";
}


void
CommInterface::cgMessageReqSensor(vector<int>& sensorsID,string& temp){

  char tempChr[128];
//   struct timeval tv;
//   gettimeofday(&tv, NULL);
//   unsigned int t1 = tv.tv_usec;
//   unsigned int randomNumber = rand_r(&t1);
  temp="REQSENSOR(";
  sprintf(tempChr,"%ld",random());
  temp+=tempChr;
  for(unsigned int i=0;i<sensorsID.size();++i){
    sprintf(tempChr,",%d",sensorsID[i]);
    temp+=tempChr;
  }
  temp+=");";
}

void
CommInterface::cgMessageByeFactory(string& temp){
  	char tempChr[128];
	temp="BYE(";
	sprintf(tempChr,"%ld", random());
	temp+=tempChr;
	temp+=");";
}
