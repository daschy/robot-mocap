#ifndef HIFRAMEMOCAPOFFLINETIMER_H
#define HIFRAMEMOCAPOFFLINETIMER_H

#include <wx/wx.h>
#include <Communication/CommInterface.h>
#include "../Panels/HIGridPanel.h"
#include <WXVTKInterface/Frame3D.h>
#include "HIMoCapTimer.h"

using namespace std;

class HIMoCapOfflineTimer : public HIMoCapTimer{

public:
  HIMoCapOfflineTimer(wxEvtHandler *owner, wxSlider* slider,wxStatusBar * status, int id = -1);

  void setFrame3D(Frame3D*);

  void setGridPanel(HIGridPanel* gridPanel);

private:
   void Notify();

private:
  Frame3D* _frame3d;
  wxSlider* _slider;
  HIGridPanel* _gridPanel;
};
#endif
