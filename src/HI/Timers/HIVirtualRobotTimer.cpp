#include "HIVirtualRobotTimer.h"
#include "../HIFrame.h"

HIVirtualRobotTimer::HIVirtualRobotTimer(wxEvtHandler *owner, int id):wxTimer(owner,id), _numReadingFailed(0){
 
}

 
void 
HIVirtualRobotTimer::setSensorsSystem(SensorsSystem* sensSys){
  _sensSys = sensSys;
}
 
void 
HIVirtualRobotTimer::setCommunicationInterface(CommInterface * commInt){
  _commInt = commInt;
}
 
void 
HIVirtualRobotTimer::setFrame3D(Frame3D * frame3d){
  _frame3d = frame3d;
}

void
HIVirtualRobotTimer::Notify(){
//   DEBOUT(("HIVirtualRobotTimer::Notify()\n")); 
    //la comunicazione è attiva, ma nessun sensore è attivo
 
    if(!_sensSys){
      //manda messaggi ping
      DEBOUT(("SensSys not Present\n"));
    }
    else{
      try{
      bool changeState = false;
      vector<AxesRotations> tempAxes;
      vector<int> servos;
      string receivedString;
     
// 	int numSensors = _sensSys->getNumSensors();
	
	servos = _sensSys->getJointsIDs();
	int dir = SensorsAttributes::VIRTUALROBOTJOINTS;
	tempAxes= _sensSys->getSensorsJoint(dir);
	string _stringToSend="";

	  CommInterface::cgMessageReqSensor(servos, _stringToSend);
//       DEBOUT(("VirtualRobot Send %s\n",_stringToSend.c_str()));
	 
	 _commInt->sendData(_stringToSend);
//         DEBOUT(("Sent string %s\n",_stringToSend.c_str()));
	
	if(_commInt->someActivities()){
        

	    receivedString = _commInt->recvDataAsString();
	    if(receivedString.size() ==0){
  //             DEBOUT(("Exception throw\n"));
	      throw ExceptionConnectionInvalid ("Connection Closed");
	  }
         DEBOUT(("Received string %s\n",receivedString.c_str()));
         (this->_numReadingFailed)=0;
        }
        else{ 
  //             DEBOUT(("Exception throw\n"));
              (this->_numReadingFailed)++;
              char buffer[24];
              sprintf(buffer,"%d",(this->_numReadingFailed));
	      throw ExceptionConnectionError (string("Can't read on socket ")+string(buffer));
	 }
        
	
	cgMessageSensor messSensor(receivedString);
	map<int,pair<int,int> > data = messSensor.getData();
	map<int,pair<int,int> >::iterator it;

	AxesRotations jointDir;
	
	for(it = data.begin(); it!=data.end(); it++){
	  if(it->second.first == 1){
	    
	    try{
	      jointDir = _sensSys->getJointAxes(it->first,dir);
	      changeState = (_frame3d->getObject3D()->rotatePartAngle(it->first,
			     URADIANTSTODEGREE(it->second.second),
			     jointDir)||changeState);
	      DEBOUT(("%d: %d -  (%d,%.2f)x(%d,%d,%d)\n",it->first,it->second.second,it->second.first,URADIANTSTODEGREE(it->second.second),jointDir.X,jointDir.Y,jointDir.Z));
	    }
	    catch(runtime_error e) {
	      DEBOUT(("%s\n",e.what()));
	    }
	    
	  } // end if(it->second.first == 1)
	  else{
	  }
	}
	_frame3d->changeState(true);
	if(_frame3d->IsShown() && _frame3d->isStateChanged()){
	  _frame3d->Render();
	}
	
      }
      catch(ExceptionConnectionInvalid e) {
          DEBOUT(("%s\n",e.what()));
            this->Stop();
            static_cast<HIFrame*>(m_owner)->connectionProblem(m_idTimer);
      } 
      catch(ExceptionConnectionError e) {
         if((this->_numReadingFailed)>=HIVirtualRobotTimer::MAXREADINGFAILED) {
            this->Stop();
            this->_numReadingFailed=0;
          //vedere wx/timer.h attributi protetti
            static_cast<HIFrame*>(m_owner)->connectionProblem(m_idTimer);
         }
          DEBOUT(("%s\n",e.what()));
      }
      catch(runtime_error e) {
//     this->Stop();
//     wxLogError(wxString(e.what(), wxConvUTF8));
	DEBOUT(("%s\n",e.what()));
      }
//       SEND--;
     }//end else
 
}
