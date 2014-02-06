#include "HICommunicationDeviceNotConnectedTimer.h"
#include "../HIFrame.h"

HICommunicationDeviceNotConnectedTimer::HICommunicationDeviceNotConnectedTimer(wxEvtHandler *owner, wxSlider* slider, int id,  messageType mvJointsType, int mvJointsParameter): HICommunicationTimer(owner,id, mvJointsType, mvJointsParameter), _slider(slider){
}


void
HICommunicationDeviceNotConnectedTimer::Notify(){
  try{
   
    vector<RotationInt> values = _fileMCD->getFrame(_slider->GetValue());

  int dir = SensorsAttributes::NAISJOINTS;
  vector<int> jointsIDs, sensorsIDs, sensorsRot;
  vector<AxesRotations> jointsDirs;
  vector<int> uradPositions;
  int tempValueOriented=0;
  vector<int> parameters(values.size(),_jointsParameter);

  for(unsigned int i=0; i<values.size();++i){
    try{
      //ricavo gli id del joint dagli id dei sensori
      jointsIDs.push_back(_sensSys->getAssociatedIDJoint(values[i].id));
      //ricavo le direzioni corrispondenti al joint
      jointsDirs.push_back( _sensSys->getJointAxes(jointsIDs[i],dir));
      
      tempValueOriented = (jointsDirs[i].X+jointsDirs[i].Y+jointsDirs[i].Z)*(values[i].rot);

      uradPositions.push_back(static_cast<int>(VALUETOURADIANTS(tempValueOriented)));
      
     }//end try
    catch(runtime_error e) {
      
    }
  }

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
//       DEBOUT(("HICommunicationDeviceNotConnectedTimer Send %s\n\n",stringToSend.c_str()));
      
//      DEBOUT(("HICommunicationDeviceNotConnectedTimer Receive %s\n",_commInt->recvDataAsString().c_str()));
//       _commInt->recvDataAsString();

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
	DEBOUT(("%s\n",e.what()));
  }

}
