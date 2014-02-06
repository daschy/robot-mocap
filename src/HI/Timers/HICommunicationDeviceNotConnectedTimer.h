#ifndef HICOMMUNICATIODEVICENOTCONNECTEDTIMER_H
#define HICOMMUNICATIODEVICENOTCONNECTEDTIMER_H

#include <wx/wx.h>

#include "HICommunicationTimer.h"

class HICommunicationDeviceNotConnectedTimer: public HICommunicationTimer{
  public:
    HICommunicationDeviceNotConnectedTimer(wxEvtHandler *owner, wxSlider* slider, int id = -1,  messageType mvJointsType = MVJOINTUWTIME, int mvJointsParameter=100);

    inline void setIOMCD (IOMCD* fileMCD){_fileMCD = fileMCD;};
    
  private:
    void Notify();
  
  private:
    wxSlider* _slider;
   

    IOMCD* _fileMCD;
};
#endif
