#include "HIScene3DTimer.h"

HIScene3DTimer::HIScene3DTimer(wxEvtHandler *owner, Frame3D* frame3d, int id ): wxTimer(owner,id), _frame3d(frame3d){

}

void HIScene3DTimer::Notify(){
  if(_frame3d->IsShown() /*&& _frame3d->isStateChanged()*/){
       _frame3d->Render();
//        DEBOUT(("HIScene3DTimer::Notify() render\n"));
    }
  else {
    return;
  }
}
