#ifndef FILTEREDREADSENSORS_H
#define FILTEREDREADSENSORS_H

#include<Headers/Exceptions.h>

#include "ReadSensors.h"
#include "Filter.h"

/**
La classe definisce 
*/
class FilteredReadSensors : public ReadSensors {
public:
  FilteredReadSensors(SensorsSystem* sensSystem) throw (ExceptionSensorNoInterface);
  FilteredReadSensors(SensorsSystem* sensSystem, Filter* filterSensors) throw (ExceptionSensorNoInterface);
  virtual ~FilteredReadSensors();
  virtual int getSensorValue(int id) throw (ExceptionIdOutOfRange); 
  void setFilter(Filter* fil);
protected:
  Filter* _filterSensors;
};
#endif
