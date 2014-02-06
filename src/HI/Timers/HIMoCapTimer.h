#ifndef HIMOCAPTIMER_H
#define HIMOCAPTIMER_H

#include <vector.h>
#include <wx/wx.h>
#include<debug.h>

#include <IO/IOMCD.h>
#include <Sensors/SensorsSystem.h>



class HIMoCapTimer : public wxTimer{
    
public:
    HIMoCapTimer(wxEvtHandler *owner,  wxStatusBar * status,int id = -1);
 
    void setIOMCD (IOMCD* fileMCD);
   
    void setSensorsSystem(SensorsSystem* sensSys);

protected:
     virtual void Notify();

protected:
    
    
    SensorsSystem* _sensSys;

    IOMCD* _fileMCD;
    
    wxStatusBar * _status;
    
};

#endif
