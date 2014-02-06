#include "CommInterface.h"
#include <Headers/Exceptions.h>
#include <Headers/MACROS.h>
#include<vector>
#include <string>
#include <debug.h>

#include<cgMessages.h>
#include<MyConfigParser/MyConfigParser.h>
#include<math.h>

#include <sys/time.h>
#include <unistd.h>

#include <cstdlib> 


using namespace std;

bool nextMove = false;
bool exitFlag = false;


void signalTerminatingHandler(int sig){
 nextMove =true;
  
}


/*
int main(){
  try{
    
   
    
    char * filename = "../Config/project.cfg";
    
    MyConfigParser par;
    par=MyConfigParser(filename);
     
     //seleziona la prima sezione, quindi il primo sensore
    par.selectFirstSection("general");
    
    
    
    CommInterface* cI = CommInterface::CommInterfaceFactory(35005, par.getValueInCurrentSection("NAISIP").c_str(),TCP);
    DEBOUT(("Receive Hello %s",(cI-> recvDataAsString()).c_str()));
    string str1 = "HELLO(13);";
    cI->sendData(str1);
    DEBOUT(("Receive %s\n",(cI-> recvDataAsString()).c_str()));
    
    
    signal(SIGINT,  signalTerminatingHandler);
    signal(SIGHUP,  signalTerminatingHandler);
    signal(SIGKILL, signalTerminatingHandler);
    signal(SIGQUIT , signalTerminatingHandler);
    
    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    char temp[128];
    unsigned int seed=tv.tv_usec, randomNumber;
    
    cgMessage* cgJointTime;
    string str;
    
    
    par=MyConfigParser("./moves.cfg");
    
    par.selectFirstSection("move");
    
    
    long refresh=100;
    long refSec=refresh / 1000;
    long refNSec=(refresh * 1000000) % 1000000000;
    struct timespec pollTime;
    struct timespec remTime;
    
    while(!exitFlag){
    
      if(nextMove==true){
        if(!par.selectNextSection("move")) exitFlag=true;
        else{
	  gettimeofday(&tv, NULL);
	  seed=tv.tv_usec;
          randomNumber = rand_r(&seed);
	  sprintf(temp, "MVJOINTWTIME(%d,%d,%d,%d);",randomNumber,atoi(par.getValueInCurrentSection("id").c_str()),static_cast<int>( DEGREETORADIANTS(atof(par.getValueInCurrentSection("angle").c_str()))*1000000),atoi( par.getValueInCurrentSection("speed").c_str()));
          str = temp;
      //DEBOUT(("Send %s\n",temp));
          cgJointTime = new cgMessageMvJointWTime(str);
	  DEBOUT(("Send MVJOINTWTIME(%d,%d,%.2f,%d);\n",randomNumber,atoi(par.getValueInCurrentSection("id").c_str()),atof(par.getValueInCurrentSection("angle").c_str()),atoi( par.getValueInCurrentSection("speed").c_str())));
          cI->sendData(cgJointTime);
          DEBOUT(("Receive %s\n",(cI-> recvDataAsString()).c_str()));
          delete(cgJointTime);
          
          nextMove=false;
          
        }
      }

    pollTime.tv_sec=refSec;
    pollTime.tv_nsec=refNSec;
    while(nanosleep(&pollTime, &remTime) == -1){
      pollTime=remTime;
    }
    }
    
    DEBOUT(("--------COMMUNICATION END--------\n"));
  }//end try
  
  catch(ExceptionCommunication e){
    DEBOUT(("ciao ciao1\n"));
    DEBOUT(("%s\n",e.what())); 
  }
  catch(runtime_error e){
    DEBOUT(("ciao ciao2 \n"));
    DEBOUT(("%s\n",e.what())); 
  }
}//end main*/


int main(int argc, char** argv){
  
  try{
  char * filename = "../Config/project.cfg";
    
  MyConfigParser par;
  par=MyConfigParser(filename);
     
     //seleziona la prima sezione, quindi il primo sensore
  par.selectFirstSection("general");

  CommInterface* cI = CommInterface::CommInterfaceFactory(atoi(par.getValueInCurrentSection("NAISPORT").c_str()), par.getValueInCurrentSection("NAISIP").c_str(),TCP);
  DEBOUT(("Receive Hello %s",(cI-> recvDataAsString()).c_str()));
  string str1 = "HELLO(13);";
  cI->sendData(str1);
  DEBOUT(("Receive %s\n",(cI-> recvDataAsString()).c_str()));
  
  
  cgMessage* cgJointTime;
  string str;
  char* movesName = "./moves.cfg";
//   DEBOUT(("num Input %d -%s-------%s-\n",argc,argv[0],argv[1]));
  if(argc>=2) movesName = argv[1];
  
  par=MyConfigParser(movesName);
    
  par.selectFirstSection("move");
  
  
  vector<int> servos, uradpositions, parameters;
  string temp;
  while(par.selectNextSection("move")){
    
    servos.push_back(atoi(par.getValueInCurrentSection("id").c_str()));
    uradpositions.push_back(static_cast<int>(DEGREETORADIANTS(atof(par.getValueInCurrentSection("angle").c_str()))*1000000));
    parameters.push_back(atoi( par.getValueInCurrentSection("parameter").c_str()));
    
    }//end while
    CommInterface::cgMessageMvJointUWTimeFactory(servos,uradpositions,parameters, temp);
    
    DEBOUT(("Mando %s\n",temp.c_str()));
    cI->sendData(temp);
    DEBOUT(("Receive %s\n",(cI-> recvDataAsString()).c_str()));
    cgMessageBye bye;
    cI->sendData(&bye);
    DEBOUT(("Receive BYE %s\n",(cI-> recvDataAsString()).c_str()));
    
  }//end try
  catch(runtime_error e){
    DEBOUT(("ciao ciao2 \n"));
    DEBOUT(("%s\n",e.what())); 
  }
  
}
