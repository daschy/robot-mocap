#ifndef HISCENE3DTIMER_H
#define HISCENE3DTIMER_H

#include <vector.h>
#include <wx/wx.h>
#include <WXVTKInterface/Frame3D.h>

using namespace std;

class HIScene3DTimer : public wxTimer{
public:
  HIScene3DTimer(wxEvtHandler *owner, Frame3D* frame3d,int id = -1);
  void Notify();

private:
  Frame3D* _frame3d;
  
};
#endif
