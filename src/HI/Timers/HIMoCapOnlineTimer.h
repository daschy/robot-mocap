#ifndef HIMOCAPONLINETIMER_H
#define HIMOCAPONLINETIMER_H


#include <Sensors/ReadSensors.h>

#include "HIMoCapTimer.h"

class HIMoCapOnlineTimer : public HIMoCapTimer{

public:
   HIMoCapOnlineTimer(wxEvtHandler *owner, wxStatusBar * status,int id = -1);
   void setReadSensors(ReadSensors* rS);

private:
   void Notify();

private:
  ReadSensors* _rS;
};
#endif
