#include "ReadSensors.h"
#include <vector>
#include <iostream>
#include <sstream>

ReadSensors::ReadSensors(SensorsSystem* sensSystem) throw (ExceptionSensorNoInterface){
  _sensSystem = sensSystem;
_sharedMemory=new MyShared(GC_PECSM_SHARED_KEY,GC_PECSM_DEFAULT_MEM_DIM, true);
  bool valid = false;
 
  if(!_sharedMemory->isValid())
    { //se non valida riprova
      for(int j=0; j< 7 && !valid; j++)
	{
	  DEBOUT(("Number of times that I'm trying to connect to Pecsm...%d\n",j));
	  usleep(2000);
	  _sharedMemory=new MyShared(GC_PECSM_SHARED_KEY,GC_PECSM_DEFAULT_MEM_DIM, true);
	  if(_sharedMemory->isValid()){
	    valid=true;
	    DEBOUT(("Zona di memoria valida\n"));
	  }
	}
    }
    else{
    valid=true;
    }
  if(!valid)
    {
       //cout << "ReadSensors() Error attaching shared memory" << endl;
      throw ExceptionSensorNoInterface("Pecsm not Active");
      //exit(EXIT_FAILURE);
    }
  _sharedArray = new SharedSensorArray(_sharedMemory->getPointer(), GC_PECSM_SHARED_KEY);
  DEBOUT(("ReadSensors::ReadSensors(SensorsSystem* sensSystem)\n"));
}

ReadSensors::ReadSensors(ReadSensors& rS) throw (ExceptionSensorNoInterface){
  _sharedMemory=new MyShared(GC_PECSM_SHARED_KEY,GC_PECSM_DEFAULT_MEM_DIM, true);
  bool valid = false;
  if(!_sharedMemory->isValid())
    { //se non valida riprova
      for(int j=0; j< 7 && !valid; j++)
	{
	  cout<<"Number of times that I'm trying to connect to Pecsm..."<<j<<endl;
	  usleep(2000);
	  _sharedMemory=new MyShared(GC_PECSM_SHARED_KEY,GC_PECSM_DEFAULT_MEM_DIM, true);
	  if(_sharedMemory->isValid()){
	    valid=true;
	  cout<<"Zona di memoria valida"<<endl;
	  }
	}
    }
  else
    valid=true;
  if(!valid)
    {
      //cout << "ReadSensors() Error attaching shared memory" << endl;
      throw ExceptionSensorNoInterface("Pecsm not Active");
      //exit(EXIT_FAILURE);
    }
  _sensSystem = new SensorsSystem(*(rS._sensSystem));
  _sharedArray = new SharedSensorArray(*(rS._sharedArray));
  DEBOUT(("ReadSensors::ReadSensors(ReadSensors& rS)\n"));
}

ReadSensors::~ReadSensors(){
  //if(_sensSystem) delete(_sensSystem);
  delete(_sharedMemory);
  delete(_sharedArray);
  DEBOUT(("ReadSensors::~ReadSensors()\n"));
}


SensorsSystem* 
ReadSensors::getSensorsSystem(){
  return _sensSystem;
}

void 
ReadSensors::setSensorsSystem(SensorsSystem* sS) throw (ExceptionIdOutOfRange){
  //if(_sensSystem) delete(_sensSystem);
  _sensSystem = sS;//new SensorsSystem(*sS);
  return;
} 


int 
ReadSensors::getCleanedSensorValue(int& id) throw (ExceptionIdOutOfRange){
    return (this->getCalibratedSensorValue(id) - _sensSystem->getSensorInitValue(id));
}


int 
ReadSensors::getCalibratedSensorValue(int id) throw (ExceptionIdOutOfRange){
  int temp = this->getSensorValue(id);
  int tempMin = _sensSystem->getSensorCalibrateMin(id);
  int tempMax = _sensSystem->getSensorCalibrateMax(id);
  int outTemp;
  //cout<<_sensSystem<<endl;

  if(tempMax==-1 && tempMin==-1) outTemp=temp;
  else if(temp<tempMin)  outTemp=tempMin;
  else if (temp>tempMax) outTemp=tempMax;
  //tempMin<=temp<=tempMax
  else outTemp=temp;
 // DEBOUT(("%d : %d<%d<%d\n",id,tempMin,outTemp,tempMax));
return outTemp;
}


SharedSensorArray::sensorState
ReadSensors::getSensorState(int id) throw (ExceptionIdOutOfRange){
  return (_sharedArray->getSensorLatestValue(id).mState);
}

vector<int> 
ReadSensors::getSensorHistoryValue(int id) throw(ExceptionIdOutOfRange){
  SharedSensorArray::sensorState* sensState = &(_sharedArray->getSensorLatestValue(id).mState);
  return _sharedArray->getSensorHistoryValue(id, sensState);
}

string 
ReadSensors::printHistory(int id) throw(ExceptionIdOutOfRange){
  SharedSensorArray::sensorState* sensState = &(_sharedArray->getSensorLatestValue(id).mState);
  ostringstream oss;
  vector<int> temp = _sharedArray->getSensorHistoryValue(id, sensState);
  for(int i=0; i<static_cast<int>(temp.size()); i++){
    oss<<temp[i]<<" ";
  }
  return oss.str();
}

ostream& operator<<(ostream& os, ReadSensors* rS) throw (ExceptionIdOutOfRange){
  os<<"";
  vector<int> sensorsIDs = rS->getSensorsSystem()->getSensorsIDs();
  SensorsSystem* _sensSystem=rS->getSensorsSystem();
  vector<int> history;
  vector<int>::iterator itSensorID;
  vector<int>::iterator itVecHistory;
  
  for(itSensorID=sensorsIDs.begin();itSensorID!=sensorsIDs.end();itSensorID++){
    os << "Sensore: [" << *itSensorID << "] state(" << rS->getSensorState(*itSensorID) <<")"
	<< " value= " << rS->getSensorValue(*itSensorID)<<"\t"<<"CleanedValue="<<rS->getSensorValue(*itSensorID)-_sensSystem->getSensorInitValue(*itSensorID)<<"  "
	<<" degree = "<<VALUETODEGREE(rS->getSensorValue(*itSensorID))<<"\t"
	<<" min="<<_sensSystem->getSensorCalibrateMin(*itSensorID)
	<<" MAX="<<_sensSystem->getSensorCalibrateMax(*itSensorID)<<"\t";
//       history = rS -> getSensorHistoryValue(*itSensorID);
//       for(itVecHistory=history.begin();itVecHistory!=history.end();itVecHistory++){
//         os<<*(itVecHistory)<<" ";
//       }
      os << "\n";
      os.flush();
// 	      str+=string(buffer);

  }

  return os;
}
