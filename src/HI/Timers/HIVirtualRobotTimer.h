#ifndef HIVIRTUALROBOTTIMER_H
#define HIVIRTUALROBOTTIMER_H

#include <vector.h>
#include <wx/wx.h>
#include<debug.h>
#include <WXVTKInterface/Frame3D.h>
#include <Sensors/SensorsSystem.h>
#include<Communication/CommInterface.h>




/**
Il timer chiede lo stato del robot via rete e aggiorna il modello 3d del robot
*/
class HIVirtualRobotTimer : public wxTimer{
  public:
    HIVirtualRobotTimer(wxEvtHandler *owner, int id = -1);
    
    void setCommunicationInterface(CommInterface * commInt);
    void setSensorsSystem(SensorsSystem* sensSys);
    void setFrame3D(Frame3D*);
    
    static const int MAXREADINGFAILED =20;
  private:
    void Notify();

  private:
    CommInterface *_commInt;
    SensorsSystem* _sensSys;
    Frame3D* _frame3d;
    int _numReadingFailed;
};
#endif


