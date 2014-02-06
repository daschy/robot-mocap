#include "HIMoCapTimer.h"


HIMoCapTimer::HIMoCapTimer(wxEvtHandler *owner,  wxStatusBar * status, int id) :wxTimer(owner,id), _sensSys(0), _fileMCD(0),_status(status){

} 

void HIMoCapTimer::setIOMCD (IOMCD* fileMCD){
  _fileMCD = fileMCD;
}
   
void HIMoCapTimer::setSensorsSystem(SensorsSystem* sensSys){
  _sensSys = sensSys;
}


void  HIMoCapTimer::Notify(){
}
