#ifndef READSENSORS_H
#define READSENSORS_H

#include <vector>
#include <string>

#include <SharedSensorArray.h>

#include <MyShared.h>
#include <GlobalComunication.h>

#include<Headers/Exceptions.h>

#include "SensorsSystem.h"

using namespace std;

/**
La classe definisce il modulo di lettura dei sensori.
*/
class ReadSensors {
public:
  ReadSensors(SensorsSystem* sensSystem) throw (ExceptionSensorNoInterface);
  ReadSensors(ReadSensors& rS) throw(ExceptionSensorNoInterface);
  virtual ~ReadSensors();
  
  virtual int getSensorValue(int id) throw (ExceptionIdOutOfRange) = 0;
  virtual int getCalibratedSensorValue(int id) throw (ExceptionIdOutOfRange);
  SharedSensorArray::sensorState getSensorState(int id) throw (ExceptionIdOutOfRange);
  
  virtual int getCleanedSensorValue(int& id) throw (ExceptionIdOutOfRange);

  SharedSensorArray* getSharedSensorArray(){return _sharedArray;};
  SensorsSystem* getSensorsSystem();
  void setSensorsSystem(SensorsSystem* sS) throw (ExceptionIdOutOfRange);
  vector<int> getSensorHistoryValue(int id) throw(ExceptionIdOutOfRange);
  
  string printHistory(int id) throw(ExceptionIdOutOfRange);

  friend ostream& operator<<(ostream& os, ReadSensors* rS) throw (ExceptionIdOutOfRange);

protected:
  
  inline int getSensorLastValue(int id) throw(ExceptionIdOutOfRange){return _sharedArray->getSensorHistoryValue(id)[1];};

  SharedSensorArray* _sharedArray;
  MyShared* _sharedMemory;
  SensorsSystem* _sensSystem;
  
};
#endif
