#ifndef HICOMMUNICATIODEVICECONNECTEDTIMER_H
#define HICOMMUNICATIODEVICECONNECTEDTIMER_H


#include "HICommunicationTimer.h"

class HICommunicationDeviceConnectedTimer: public HICommunicationTimer{
  public:
     HICommunicationDeviceConnectedTimer(wxEvtHandler *owner, int id = -1, messageType mvJointsType = MVJOINTUWTIME, int mvJointsParameter=100);
     
     inline void setReadSensors(ReadSensors * rS){_rS = rS;};

  private:
    void Notify();

  private:
    
     ReadSensors* _rS;
};
#endif
