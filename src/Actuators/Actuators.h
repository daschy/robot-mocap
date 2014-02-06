#ifndef ACTUATORS_H
#define ACTUATORS_H

#include<vector>
#include<string>
#include<debug.h>
#include<Sensors/SensorsSystem.h>
#include<WXVTKInterface/Frame3D.h>
#include<3D/Object3D.h>
#include<WXVTKInterface/wxVTKRenderWindowInteractor.h>
#include<Communication/CommInterface.h>
#include<Headers/ActuatorsTypes.h>
#include<Headers/IOTypes.h>
#include<Headers/Exceptions.h>

using namespace std;

class Actuators{
  
  public:
      Actuators();
      void activeChannel(ActuatorType::CHANNELS ch) throw (ExceptionChannelNotPresent); 
      void deactiveChannel(ActuatorType::CHANNELS ch) throw (ExceptionChannelNotPresent); 
      bool isActive(ActuatorType::CHANNELS ch);
      bool isPresent(ActuatorType::CHANNELS ch);
      void setActuatorValue(vector<RotationInt>& values) throw (ExceptionIdOutOfRange,ExceptionConnectionInvalid, ExceptionChannelNotPresent);
      
      void addChannel(ActuatorType::CHANNELS ch,Frame3D* obj) throw (ExceptionChannel);
      void addChannel(ActuatorType::CHANNELS ch,CommInterface* commInterface, int delay=0) throw (ExceptionChannel);
      
      void setAxesRotations(ActuatorType::CHANNELS ch,  vector<AxesRotations> axes) throw (ExceptionChannelNotPresent);
      void setSensorsSystem(SensorsSystem* sensSys);
      
  private:
    void setActuatorValueCommInterface(vector<RotationInt>& values, string& stringToSend);
    
    
  private:
    
    vector<ActuatorType::CHANNELS> _activeChannels;
    map<ActuatorType::CHANNELS,CommInterface*>  _physicalChannels;
    int _delay;
    map<ActuatorType::CHANNELS,Frame3D*> _virtualChannels;
    
    map<ActuatorType::CHANNELS,vector<AxesRotations> > _axes;
    SensorsSystem* _sensSys;
};
#endif
