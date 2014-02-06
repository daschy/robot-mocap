#include "HICommunicationDeviceConnectedTimer.h"
#include "../HIFrame.h"

HICommunicationDeviceConnectedTimer::HICommunicationDeviceConnectedTimer(wxEvtHandler *owner, int id, messageType mvJointsType, int mvJointsParameter): HICommunicationTimer(owner,id, mvJointsType, mvJointsParameter){

}

void
HICommunicationDeviceConnectedTimer::Notify(){
 try{
      int numSensors = _sensSys->getNumSensors();
      vector< RotationInt > tempAxesCleaned;
      vector<int> jointsIDs = _sensSys->getJointsIDs();
      vector<int> uradPositions;
      
      vector<int> parameters(numSensors,_jointsParameter);
      
      vector<AxesRotations> servosDir = _sensSys->getSensorsJoint(SensorsAttributes::NAISJOINTS);
      vector<int> tempIDs = _sensSys->getSensorsIDs();
      string stringToSend="";
      int tempValueOriented=0;
      for (int row = 0; row < numSensors; ++row){
	tempValueOriented = (servosDir[row].X+servosDir[row].Y+servosDir[row].Z)*
	    (_rS->getCalibratedSensorValue(tempIDs[row])-_sensSys->getSensorInitValue(tempIDs[row]));
	
	
	uradPositions.push_back(static_cast<int>(VALUETOURADIANTS(tempValueOriented)));
	
	
      }//end for
//       CommInterface::cgMessageMvJointWTimeFactory(jointsIDs,uradPositions,utimes,_stringToSend);
      CommInterface::cgMessageMvJointFactory(_mvJointsType,jointsIDs,uradPositions,parameters,_stringToSend);
	_commInt->sendData(_stringToSend);
      if(_commInt->someActivities()){
       
        (this->_numReadingFailed)=0;
      }
       else {
	(this->_numReadingFailed)++;
	char buffer[24];
	sprintf(buffer,"%d",(this->_numReadingFailed));
	throw ExceptionConnectionError (string("Can't read on socket ")+string(buffer));
      }

    }//end try
   catch(ExceptionConnectionError e) {
         if((this->_numReadingFailed)>=HICommunicationTimer::MAXREADINGFAILED) {
            this->Stop();
          this->_numReadingFailed=0;
          //vedere wx/timer.h attributi protetti
            static_cast<HIFrame*>(m_owner)->connectionProblem(m_idTimer);
         }
          DEBOUT(("%s\n",e.what()));
   }
  catch(runtime_error e) {
//          this->Stop();
// 	  wxLogError(wxString(e.what(), wxConvUTF8));
	  DEBOUT(("%s\n",e.what()));
  }
}
