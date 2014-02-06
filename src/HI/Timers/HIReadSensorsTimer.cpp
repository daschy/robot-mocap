#include "HIReadSensorsTimer.h"

HIReadSensorsTimer::HIReadSensorsTimer(wxEvtHandler *owner, HIGridPanel* gridPanel,Frame3D* frame3d,int id): wxTimer(owner,id), _gridPanel(gridPanel), _frame3d(frame3d){
}

void HIReadSensorsTimer::Notify(){
  
try{

  vector<int> tempSensorsIDs = _sensSys->getSensorsIDs();
  vector<int> tempJointsIDs = _sensSys->getJointsIDs();
  vector<int> tempSensorsStates;
  vector<int> tempCurrentValues;
  vector<int> tempInitValues = _sensSys->getSensorsInitValues();
  vector<int> tempCleandValues;
  vector<double> tempCurrentAngleValues;
  vector<int> tempCurrentURadiantsValues;
  vector<int> tempMinValues = _sensSys->getSensorsCalibrateMin();
  vector<int> tempMaxValues = _sensSys->getSensorsCalibrateMax();

  bool changeState = false;

     for(int row = 0; row< _sensSys->getNumSensors();++row){
        tempSensorsStates.push_back(_rS->getSensorState(tempSensorsIDs[row]));
        tempCurrentValues.push_back(_rS->getCalibratedSensorValue(tempSensorsIDs[row]));
        tempCleandValues.push_back(_rS->getCleanedSensorValue(tempSensorsIDs[row]));
        tempCurrentAngleValues.push_back(VALUETODEGREE(tempCleandValues[row]));
        tempCurrentURadiantsValues.push_back(static_cast<int>(VALUETOURADIANTS(tempCleandValues[row])));
        try{
	  changeState = (_frame3d->getObject3D()->rotatePartAngle(tempJointsIDs[row],tempCurrentAngleValues[row],_sensSys->getJointAxes(tempJointsIDs[row],0/*SensorsAttributes::VIRTUALJOINTS*/))||changeState);
        }
        catch(ExceptionIdOutOfRange e) {
//           DEBOUT(("%s\n",e.what()));
// 	wxLogError(wxString(e.what(), wxConvUTF8));
        }
      }

      _frame3d->changeState(changeState);
   if(_gridPanel->IsShown()){ 
    _gridPanel->setColText(HIGridPanel::ID_COLUMN,tempSensorsIDs);
    _gridPanel->setColText(HIGridPanel::STATE_COLUMN,tempSensorsStates);
    _gridPanel->setColText(HIGridPanel::CURRVALUE_COLUMN,tempCurrentValues);
    _gridPanel->setColText(HIGridPanel::JOINTID_COLUMN,tempJointsIDs);
//     _gridPanel->setColText(HIGridPanel::JOINTVALUE_COLUMN,tempCurrentValues);
    _gridPanel->setColText(HIGridPanel::INITVALUE_COLUMN,tempInitValues);
    _gridPanel->setColText(HIGridPanel::CLEANEDVALUE_COLUMN,tempCleandValues);
    _gridPanel->setColText(HIGridPanel::DEGREEVALUE_COLUMN,tempCurrentAngleValues);
    _gridPanel->setColText(HIGridPanel::URADIANTSVALUE_COLUMN,tempCurrentURadiantsValues);
    _gridPanel->setColText(HIGridPanel::MINVALUE_COLUMN,tempMinValues);
    _gridPanel->setColText(HIGridPanel::MAXVALUE_COLUMN,tempMaxValues);
    }
  }//end try
  catch(runtime_error e) {
      DEBOUT(("%s\n",e.what()));
// 	wxLogError(wxString(e.what(), wxConvUTF8));
    }
   
  return;


}

