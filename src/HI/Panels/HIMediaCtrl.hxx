#ifndef HIMEDIACTRL_H
#define HIMEDIACTRL_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <Headers/Exceptions.h>


using namespace std;

class HIMediaCtrl : public wxPanel{
  public:
    HIMediaCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = _T("himediacrtl_panel"));

  void do_layout();

    wxButton* _play;
    wxButton* _stop;
    wxButton* _beginPosition;
    wxButton* _endPosition;
    wxButton* _loop;
    wxSlider* _slider;

     enum WIDGETS{ 
      PLAYBUTTON_ID = 0,
      STOPBUTTON_ID,
      BEGINBUTTON_ID,
      ENDBUTTON_ID,
      LOOPBUTTON_ID,
      SLIDER_ID
    };

   void OnPlay(wxCommandEvent &event);
    void OnStop(wxCommandEvent &event);
    void OnBegin(wxCommandEvent &event);
    void OnEnd(wxCommandEvent &event);
    void OnLoop(wxCommandEvent &event);
    void OnSlider(wxCommandEvent &event);
    void OnResize (wxSizeEvent &event);
    void OnCloseWindow(wxCloseEvent & event);




};
#endif
