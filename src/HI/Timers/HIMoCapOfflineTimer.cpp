#include <string>
#include "HIMoCapOfflineTimer.h"

HIMoCapOfflineTimer::HIMoCapOfflineTimer(wxEvtHandler *owner, wxSlider* slider, wxStatusBar * status,int id): HIMoCapTimer(owner,status,id), _frame3d(0), _slider(slider), _gridPanel(0){
}

void HIMoCapOfflineTimer::setGridPanel(HIGridPanel* gridPanel){
  _gridPanel = gridPanel;
}

void HIMoCapOfflineTimer::setFrame3D(Frame3D* frame3d){
  _frame3d = frame3d;
}

void HIMoCapOfflineTimer::Notify(){
 try{

  vector<RotationInt> values = _fileMCD->getFrame(_slider->GetValue());
  if(this->IsOneShot()){
    _slider->SetValue(_slider->GetValue());
  }
  else{
  _slider->SetValue((_slider->GetValue()+1)%_slider->GetMax());
  }
  _status->SetStatusText(wxString::Format(_T("Frame\t%d/%d"), _slider->GetValue(),_slider->GetMax()-1),1);
  bool changeState = false;
  int dir = SensorsAttributes::VIRTUALJOINTS;
  vector<int> jointsIDs, sensorsIDs, sensorsRot;
  vector<int> valuesURad;
  vector<double> valuesDegree;
  vector<AxesRotations> jointsDirs;
//   DEBOUT(("frame size = %d\n",values.size()));
  for(unsigned int i=0; i<values.size();++i){
    try{

     sensorsIDs.push_back(values[i].id);
      sensorsRot.push_back(values[i].rot);
    //ricavo gli id del joint dagli id dei sensori
    jointsIDs.push_back(_sensSys->getAssociatedIDJoint(values[i].id));
    //ricavo le direzioni corrispondenti al joint
    jointsDirs.push_back( _sensSys->getJointAxes(jointsIDs[i],dir));
    valuesDegree.push_back(VALUETODEGREE(values[i].rot));
    valuesURad.push_back(static_cast<int>(VALUETOURADIANTS(values[i].rot)));
    // corrispondenza tra jointsIDs[i] e values[i].id
    //muovo i joints nel frame
    changeState =(_frame3d->getObject3D()->rotatePartAngle(jointsIDs[i],
			      valuesDegree[i],
			      jointsDirs[i])||changeState);

     
//       DEBOUT(("joint %d: %.2f x (%d,%d,%d)\n",jointsIDs[i],valuesDegree[i],jointsDirs[i].X,jointsDirs[i].Y,jointsDirs[i].Z));
      }//end try
    catch(runtime_error e) {
//       DEBOUT(("%s\n",e.what()));
    }

  } //end for(unsigned int i=0; i<value.size();++i)
//aggiorno il frame
  _frame3d->changeState(changeState);
//   if(_frame3d->IsShown() && _frame3d->isStateChanged()){
//     _frame3d->Render();
//   }
  
  _gridPanel->setColText(HIGridPanel::ID_COLUMN,sensorsIDs);
  _gridPanel->setColText(HIGridPanel::JOINTID_COLUMN,jointsIDs);
  _gridPanel->setColText(HIGridPanel::CLEANEDVALUE_COLUMN,sensorsRot);
  _gridPanel->setColText(HIGridPanel::DEGREEVALUE_COLUMN,valuesDegree);
  _gridPanel->setColText(HIGridPanel::URADIANTSVALUE_COLUMN,valuesURad);
  }//end try
  catch(runtime_error e) {
	DEBOUT(("Exception %s\n",e.what()));
  }
  
}//end Notify()
