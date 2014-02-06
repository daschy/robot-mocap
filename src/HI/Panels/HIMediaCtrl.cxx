#include "HIMediaCtrl.h"


 
HIMediaCtrl::HIMediaCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent,id ,pos,size,style,name){


_beginPosition = new wxButton(this, BEGINBUTTON_ID, wxT("|<"), wxDefaultPosition, wxDefaultSize, 0 );
   _play = new wxButton(this, PLAYBUTTON_ID, wxT(">"), wxDefaultPosition, wxDefaultSize, 0 );
  _stop = new wxButton(this, STOPBUTTON_ID, wxT("[]"), wxDefaultPosition, wxDefaultSize, 0 );
  
  _endPosition = new wxButton(this, ENDBUTTON_ID, wxT(">|"), wxDefaultPosition, wxDefaultSize, 0 );
  _loop = new wxButton(this, LOOPBUTTON_ID, wxT("<=/=>"), wxDefaultPosition, wxDefaultSize, 0 );

     _slider = new wxSlider(this, SLIDER_ID, 0,0,100, wxDefaultPosition, wxSize(size.GetWidth(),(_play->GetSize()).GetHeight()),wxSL_AUTOTICKS|wxSL_HORIZONTAL);
}

void 
HIMediaCtrl::do_layout(){
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* sizer_bar = new  wxBoxSizer(wxHORIZONTAL);
//   wxBoxSizer* sizer_slider=new wxBoxSizer(wxVERTICAL);
  
  this->SetSizer(sizer);
  
  sizer->Add(sizer_bar,  0,wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
  
  sizer_bar->Add(_beginPosition,  0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
  sizer_bar->Add(_play,  0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
//   sizer_bar->Add(_stop,  0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
//   sizer_bar->Add(_loop,  0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
//   sizer_bar->Add(_endPosition,  0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
//   
//   

 
//   sizer->Add(_slider, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);




//   SetAutoLayout(true);
//   Layout();
}


void 
HIMediaCtrl::OnPlay(wxCommandEvent &event){
  try{
   
  
  }//end try
  catch(runtime_error e){
    wxLogError(wxString (e.what(), wxConvUTF8));
  }
}

void 
HIMediaCtrl::OnStop(wxCommandEvent &event){
  try{
   
  }//end try
  catch(runtime_error e){
    wxLogError(wxString (e.what(), wxConvUTF8));
  }
}

void 
HIMediaCtrl::OnBegin(wxCommandEvent &event){
  try{
    
  }//end try
  catch(runtime_error e){
    wxLogError(wxString (e.what(), wxConvUTF8));
  }
}

void 
HIMediaCtrl::OnEnd(wxCommandEvent &event){
  try{
    
  }//end try
  catch(runtime_error e){
    wxLogError(wxString (e.what(), wxConvUTF8));
  }
}
    
void 
HIMediaCtrl::OnLoop(wxCommandEvent &event){
  try{
   
  
  }//end try
  catch(runtime_error e){
    wxLogError(wxString (e.what(), wxConvUTF8));
  }
}

void 
HIMediaCtrl::OnSlider(wxCommandEvent &event){
  try{
    
  //DEBOUT(("Slider value = %d\n",_slider->GetValue()));
  }//end try
  catch(runtime_error e){
    wxLogError(wxString (e.what(), wxConvUTF8));
  }
}
