#ifndef HICOMMUNICATIODEVICETIMER_H
#define HICOMMUNICATIODEVICETIMER_H


#include <vector.h>
#include <wx/wx.h>
#include<debug.h>
#include <Sensors/ReadSensors.h>
#include <Sensors/SensorsSystem.h>
#include<Communication/CommInterface.h>
#include <IO/IOMCD.h>


class HICommunicationTimer:public wxTimer {
  public:

    HICommunicationTimer(wxEvtHandler *owner, int id = -1, messageType mvJointsType = MVJOINTUWTIME, int mvJointsParameter=100);
    
    inline void setSensorsSystem(SensorsSystem* sensSys) {_sensSys = sensSys;};

    inline void setCommunicationInterface(CommInterface * commInt){_commInt = commInt;};
    
    inline void setMvJointsType(messageType mvJointsType){ _mvJointsType = mvJointsType;};

    inline void setMvJointsParameter(int mvJointsParameter){_jointsParameter=mvJointsParameter;};

     static const int MAXREADINGFAILED =200;
  protected:
    virtual void Notify() = 0;
    
    
  protected:
    SensorsSystem* _sensSys;
    CommInterface *_commInt;
    string _stringToSend;
    
    messageType _mvJointsType;
    
    int _jointsParameter;
    int _numReadingFailed;
};
#endif
