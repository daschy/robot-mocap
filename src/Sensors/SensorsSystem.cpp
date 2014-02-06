#include "SensorsSystem.h"
#include<debug.h>

using namespace std;
//throw ExceptionIdOutOfRange("ID not found");
SensorsSystem::SensorsSystem() throw (ExceptionIdOutOfRange): _sensorsSystemName("Null"){
 _boundingBox.push_back(AxesRotations());
 _boundingBox.push_back(AxesRotations());
}

SensorsSystem::SensorsSystem(SensorsSystem & sS) throw (ExceptionIdOutOfRange){
  _sensorsMap=sS._sensorsMap;
  DEBOUT(("SensorsSystem::SensorsSystem(SensorsSystem & sS)\n"));
}

SensorsSystem::~SensorsSystem(){
  DEBOUT(("SensorsSystem::~SensorsSystem()\n"));
}

vector<string> 
SensorsSystem::getSensorsNames(){
  map<int, SensorsAttributes>::iterator it;
  vector<string> temp;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->second.name);
  }
  return temp;
}

string SensorsSystem::getSensorName(int id)throw (ExceptionIdOutOfRange){
   map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  string temp="";
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
        temp = it->second.name;
  }
  return temp;
}

vector<int>
SensorsSystem::getSensorsIDs(){
  map<int, SensorsAttributes>::iterator it;
  vector<int> temp;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->first);
  }
  return temp;
}	


void 
SensorsSystem::resetCalibration(){
  map<int, SensorsAttributes>::iterator it;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    (it->second).MAX=INIT;
    (it->second).min=INIT;
  }
}

void 
SensorsSystem::setSensorCalibrateMax(int id, int value) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
    if(it->second.MAX<value || it->second.MAX == INIT){
        it->second.MAX = value;
    }
  }
  return;
}


void 
SensorsSystem::setSensorCalibrateMin(int id, int value) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
    if(it->second.min>value || it->second.min == INIT){
        it->second.min = value;
    }
  }
  return;
}  



void 
SensorsSystem::setSensorMean(int id, double value) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
        it->second.mean = value;
  }
  return;
}

void 
SensorsSystem::setSensorVariance(int id, double value) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
        it->second.var = value;
  }
  return;
}

vector<int> 
SensorsSystem::getSensorsCalibrateMax(){
  map<int, SensorsAttributes>::iterator it;
  vector<int> temp;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->second.MAX);
  }
  return temp;
}

void 
SensorsSystem::setSensorName(int id, string name) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
        it->second.name = name;
  }
  return;
}

void 
SensorsSystem::setInitValue(int id, int init) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
        it->second.initValue = init;
  }
  return;
}


int 
SensorsSystem::getSensorCalibrateMax(int id) throw (ExceptionIdOutOfRange){
   map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
   int temp = INIT;
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
     temp =  it->second.MAX;
    }
  return temp;
}


vector<int> 
SensorsSystem::getSensorsCalibrateMin(){
  map<int, SensorsAttributes>::iterator it;
  vector<int> temp;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->second.min);
  }
  return temp;
}

int 
SensorsSystem::getSensorCalibrateMin(int id) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
   int temp = INIT;
//     DEBOUT(("getSensorCalibrateMin(int id) id = %d\n",id));
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
     temp =  it->second.min;
    }
  return temp;
}

vector<int> 
SensorsSystem::getSensorsInitValues(){
   map<int, SensorsAttributes>::iterator it;
  vector<int> temp;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->second.initValue);
  }
  return temp;
}

int 
SensorsSystem::getSensorInitValue(int id) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
   int temp = INIT;
//     DEBOUT(("getSensorCalibrateMin(int id) id = %d\n",id));
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
     temp =  it->second.initValue;
    }
  return temp;
}

void 
SensorsSystem::associateJointToSensor(int jointID, int sensorID) throw (ExceptionIdOutOfRange){
   map<int, SensorsAttributes>::iterator it = _sensorsMap.find(sensorID);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
     it->second.jointID = jointID;
    }
}

vector<int>
SensorsSystem::getJointsIDs(){
  map<int, SensorsAttributes>::iterator it;
  vector<int> temp;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->second.jointID);
  }
  return temp;
}

int 
SensorsSystem::getIDJoint(int index){
  map<int, SensorsAttributes>::iterator it;
  int temp = INIT;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    if(index == it->second.idx){
      temp = it->second.jointID;
    };
  }
  if(temp==INIT) throw ExceptionIdOutOfRange(string(DEBPOS)+string("Index out of range"));
  
  return temp;
}

int SensorsSystem::getAssociatedIDJoint(int sensorID){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(sensorID);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
  else {
    return it->second.jointID;
  }
}

AxesRotations& SensorsSystem::getJointAxes(const int& jointID, const int& dir){
  map<int, SensorsAttributes>::iterator it;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    if(jointID == it->second.jointID){
      return it->second.jointsDirs[dir];
    }
  }
  throw ExceptionIdOutOfRange(string(DEBPOS)+string("Index out of range"));
}


int 
SensorsSystem::getIDSensor(int index) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it;
  int temp = INIT;
  for(it= _sensorsMap.begin(); it!=_sensorsMap.end();it++){
    if(index == it->second.idx){
      temp = it->first;
    }
  }
  if(temp==INIT) throw ExceptionIdOutOfRange(string(DEBPOS)+string("Index out of range"));
  return temp;
}

vector<AxesRotations>
SensorsSystem::getSensorJoints(int id) throw(ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  AxesRotations temp;
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("Sensor ID not found"));
  }
  else {
    return it->second.jointsDirs;
  }
}

vector<AxesRotations>
SensorsSystem::getSensorsJoint(int jointDirs) throw (ExceptionIdOutOfRange){
  map<int, SensorsAttributes>::iterator it;
  vector<AxesRotations> temp;
  for(it=_sensorsMap.begin(); it!=_sensorsMap.end();it++){
    if(jointDirs>=static_cast<int>(it->second.jointsDirs.size())) {
      throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
    }
    else {
      temp.push_back(it->second.jointsDirs[jointDirs]);
    }
  }
  return temp;
}

vector< vector<AxesRotations> >
SensorsSystem::getSensorsJoints(){
  map<int, SensorsAttributes>::iterator it;
  vector<vector<AxesRotations> > temp;
  for(it=_sensorsMap.begin(); it!=_sensorsMap.end();it++){
    temp.push_back(it->second.jointsDirs);
  }
  return temp;
}

void 
SensorsSystem::addSensor(SensorsAttributes attributes) throw (ExceptionSensors){
  map<int, SensorsAttributes>::iterator it = _sensorsMap.find(attributes.id);
  
//   DEBOUT(("Inserting %d it==_sensorsMap.end()?%s\n",attributes.id,it==_sensorsMap.end()?"YES":"NO"));
  //Se NON c'è il sensore allora aggiungilo
  if(it!=_sensorsMap.end()) {
    
    throw ExceptionSensors(DEBPOS"Sensor Already Exist");
    
  }
  else {
    
    _sensorsMap[attributes.id] =attributes ;
  }
}

string 
SensorsSystem::print(){
  
  string temp = "";
  char tempChr[32];
  map<int, SensorsAttributes>::iterator it;
  
  for(it=_sensorsMap.begin(); it!=_sensorsMap.end();it++){
   
   temp+= "\nsec sensor\n";
   
   temp+="name: ";
   temp+=it->second.name;
   temp+="\n";
   
   temp+="id: ";
   sprintf(tempChr,"%d",it->second.id);
   temp+=string(tempChr);
   temp+="\n";
    
   temp+="index: ";
   sprintf(tempChr,"%d",it->second.idx);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="jointID: ";
   sprintf(tempChr,"%d",it->second.jointID);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="MAX: ";
   sprintf(tempChr,"%d",it->second.MAX);
   temp+=string(tempChr);
   temp+="\n";
   
   
   temp+="min: ";
   sprintf(tempChr,"%d",it->second.min);
   temp+=string(tempChr);
   temp+="\n";
   
   
   temp+="initValue: ";
   sprintf(tempChr,"%d",it->second.initValue);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="numJoints: ";
   sprintf(tempChr,"%d",it->second.jointsDirs.size());
   temp+=string(tempChr);
   temp+="\n";
   
   for(unsigned int i=0; i<it->second.jointsDirs.size(); ++i){
    sprintf(tempChr,"dir%d: ",i);
    temp+=string(tempChr);
    sprintf(tempChr,"%d %d %d",it->second.jointsDirs[i].X, it->second.jointsDirs[i].Y, it->second.jointsDirs[i].Z);
    temp+=string(tempChr);
    temp+="\n";
   }
   
   temp+="mean: ";
   sprintf(tempChr,"%.3f",it->second.mean);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="variance: ";
   sprintf(tempChr,"%.3f",it->second.var);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+= "endsec\n";

  }
  
  
  return temp;
  
}

string 
SensorsSystem::printSensor(int id) throw (ExceptionIdOutOfRange){
   map<int, SensorsAttributes>::iterator it = _sensorsMap.find(id);
  if(it==_sensorsMap.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("ID not found"));
  }
    string temp = "";
  char tempChr[32];

    temp+= "\nsec sensor\n";
   
   temp+="name: ";
   temp+=it->second.name;
   temp+="\n";
   
   temp+="id: ";
   sprintf(tempChr,"%d",it->second.id);
   temp+=string(tempChr);
   temp+="\n";
    
   temp+="index: ";
   sprintf(tempChr,"%d",it->second.idx);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="jointID: ";
   sprintf(tempChr,"%d",it->second.jointID);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="MAX: ";
   sprintf(tempChr,"%d",it->second.MAX);
   temp+=string(tempChr);
   temp+="\n";
   
   
   temp+="min: ";
   sprintf(tempChr,"%d",it->second.min);
   temp+=string(tempChr);
   temp+="\n";
   
   
   temp+="initValue: ";
   sprintf(tempChr,"%d",it->second.initValue);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="numJoints: ";
   sprintf(tempChr,"%d",it->second.jointsDirs.size());
   temp+=string(tempChr);
   temp+="\n";
   
   for(unsigned int i=0; i<it->second.jointsDirs.size(); ++i){
    sprintf(tempChr,"dir%d: ",i);
    temp+=string(tempChr);
    sprintf(tempChr,"%d %d %d",it->second.jointsDirs[i].X, it->second.jointsDirs[i].Y, it->second.jointsDirs[i].Z);
    temp+=string(tempChr);
    temp+="\n";
   }
   
   temp+="mean: ";
   sprintf(tempChr,"%.3f",it->second.mean);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+="variance: ";
   sprintf(tempChr,"%.3f",it->second.var);
   temp+=string(tempChr);
   temp+="\n";
   
   temp+= "endsec\n";

  return temp;


}



