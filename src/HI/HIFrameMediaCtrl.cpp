#include "HIFrame.h"

void HIFrame::OnPlay(wxCommandEvent &event){
  
//     _moCapTimer->delta = 
   if(_commTimer){
      int delayCommunicationTimer = static_cast <int >((1.0 / static_cast < double >(FPSSENDDATA))*1000.0);
      _commTimer->setMvJointsType(MVJOINTSTYPE);
      _commTimer->setMvJointsParameter(MVJOINTSPARAMETER);
      _commTimer->Start(delayCommunicationTimer,wxTIMER_CONTINUOUS);
    }

//     if(_moCapTimer){
     int delayMoCapOfflineTimer = static_cast <int >((1.0 / static_cast < double >(_fileMCD->getFramerate()))*1000.0);
    _moCapTimer->Start(delayMoCapOfflineTimer,wxTIMER_CONTINUOUS);
//     }
    
   int enableList[] = {STOPBUTTON_ID};
   int disableList[] = {BEGINBUTTON_ID,LOOPBUTTON_ID,ENDBUTTON_ID,SLIDER_ID, NEXTFRAMEBUTTON_ID,PREVIOUSFRAMEBUTTON_ID };
   enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
   enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
  
}

void HIFrame::OnStop(wxCommandEvent &event){
 
   if(_commTimer){
    _commTimer->Stop();
   }
  
    _moCapTimer->Stop();
 
   int enableList[] = {PLAYBUTTON_ID,BEGINBUTTON_ID,LOOPBUTTON_ID,ENDBUTTON_ID,SLIDER_ID,NEXTFRAMEBUTTON_ID,PREVIOUSFRAMEBUTTON_ID};
   int disableList[] = {};
  enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
  enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
}

void HIFrame::OnBegin(wxCommandEvent &event){
_slider->SetValue(0);
this->OnSlider(event);
}

void HIFrame::OnEnd(wxCommandEvent &event){
  _slider->SetValue(_slider->GetMax());
this->OnSlider(event);
}

void HIFrame::OnLoop(wxCommandEvent &event){
  
}

void HIFrame::OnSlider(wxCommandEvent &event){
   if(_commTimer){
    int delayCommunicationTimer = static_cast <int >((1.0 / static_cast < double >(FPSSENDDATA))*1000.0);
   _commTimer->Start(delayCommunicationTimer,wxTIMER_ONE_SHOT);
   }

  int delayMoCapOfflineTimer = /*(1.0/25.0)*1000.0;*/ static_cast <int >((1.0 / static_cast < double >(FPSMOCAP))*1000.0);
  _moCapTimer->Start(delayMoCapOfflineTimer,wxTIMER_ONE_SHOT);
}

void HIFrame::OnPreviousFrame(wxCommandEvent &event){
    if(_slider->GetValue()>=(_slider->GetMin()+1)){
      _slider->SetValue(_slider->GetValue()-1);
      this->OnSlider(event);
    }
    else return;
}

void HIFrame::OnNextFrame(wxCommandEvent &event){
    if(_slider->GetValue()<=(_slider->GetMax()-1)){
       _slider->SetValue(_slider->GetValue()+1);
      this->OnSlider(event);
    }
    else return;
}

