#ifndef HIREADSENSORSTIMER_H
#define HIREADSENSORSTIMER_H

#include <wx/wx.h>
#include <Sensors/ReadSensors.h>
#include <Sensors/SensorsSystem.h>
#include <WXVTKInterface/Frame3D.h>
#include "../Panels/HIGridPanel.h"


class HIReadSensorsTimer : public wxTimer{
public: 
  HIReadSensorsTimer(wxEvtHandler *owner, HIGridPanel* gridPanel, Frame3D* frame3d,int id = -1);
  
  inline void setReadSensors(ReadSensors* rS){_rS = rS;};
  inline void setSensorsSystem(SensorsSystem* sensSys){_sensSys = sensSys;};

private:
  void Notify();
  ReadSensors* _rS;
  SensorsSystem* _sensSys;
private:
  HIGridPanel* _gridPanel;
  Frame3D* _frame3d;
};
#endif
