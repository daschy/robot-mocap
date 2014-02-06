#include "FilteredReadSensors.h"

FilteredReadSensors::FilteredReadSensors(SensorsSystem* sensSystem) throw (ExceptionSensorNoInterface): ReadSensors(sensSystem) {
  _filterSensors = new FilterMedian();
  DEBOUT(("FilteredReadSensors::FilteredReadSensors(SensorsSystem* )\n"));
}


FilteredReadSensors::FilteredReadSensors(SensorsSystem* sensSystem, Filter* filterSensors) throw (ExceptionSensorNoInterface): ReadSensors(sensSystem), _filterSensors(filterSensors){
  DEBOUT(("FilteredReadSensors::FilteredReadSensors(SensorsSystem* sensSystem, Filter*)\n"));
}

FilteredReadSensors::~FilteredReadSensors(){
  delete(_filterSensors);
  DEBOUT(("FilteredReadSensors::~FilteredReadSensors()\n"));
}

int 
FilteredReadSensors::getSensorValue(int id) throw (ExceptionIdOutOfRange){
      vector<int> vecTemp = this->getSensorHistoryValue(id);
      return _filterSensors->getValue(vecTemp);
} 




void
FilteredReadSensors::setFilter(Filter* fil){
  delete(_filterSensors);
  _filterSensors = fil;
}
