#include"Actuators.h"

Actuators::Actuators(){
  _delay=-1;
}


void Actuators::activeChannel(ActuatorType::CHANNELS ch) throw (ExceptionChannelNotPresent){
   map<ActuatorType::CHANNELS, Frame3D*>::iterator itV = _virtualChannels.find(ch);
   map<ActuatorType::CHANNELS, CommInterface*>::iterator itP =  _physicalChannels.find(ch);
   if(itV!= _virtualChannels.end() || itP!= _physicalChannels.end()) {
     _activeChannels.push_back(ch);
   }
   else {
     throw ExceptionChannelNotPresent(DEBPOS"This channel not Exists ");
   }
}
 
 void Actuators::deactiveChannel(ActuatorType::CHANNELS ch) throw (ExceptionChannelNotPresent){
   vector<ActuatorType::CHANNELS>::iterator it = find(_activeChannels.begin(),_activeChannels.end(),ch);
   if(it!= _activeChannels.end()) {
     _activeChannels.erase(it,it);
   }
   else {
     throw ExceptionChannelNotPresent(DEBPOS"This channel not Exists ");
   }
 }
 
 
 void Actuators::addChannel(ActuatorType::CHANNELS ch,Frame3D* obj) throw (ExceptionChannel){
   map<ActuatorType::CHANNELS, Frame3D*>::iterator it = _virtualChannels.find(ch);
   
   if(it!=_virtualChannels.end()) {
    
//      throw ExceptionChannel(DEBPOS"This Virtual Channel Already Exists");
    
   }
  else{
    _virtualChannels[ch] = obj;
    
  }
 }

 void Actuators::addChannel(ActuatorType::CHANNELS ch,CommInterface* commInterface, int delay) throw (ExceptionChannel){
  map<ActuatorType::CHANNELS, CommInterface*>::iterator it =  _physicalChannels.find(ch);
   
   if(it!= _physicalChannels.end()) {
    
//      throw ExceptionChannel(DEBPOS"This Phisical Channel Already Exists");
    
   }
   else{
     _physicalChannels[ch] = commInterface;
     _delay=delay;
   }
 }
 
 
 void 
Actuators::setSensorsSystem(SensorsSystem* sensSys){
   _sensSys = sensSys;
}
 
 
 
 bool Actuators::isActive(ActuatorType::CHANNELS ch){
   vector<ActuatorType::CHANNELS>::iterator it = find(_activeChannels.begin(),_activeChannels.end(),ch);
   if(it!= _activeChannels.end()) {
     return true;
   }
   else {
    return false;
   }
 }
 
bool Actuators::isPresent(ActuatorType::CHANNELS ch){
   map<ActuatorType::CHANNELS, Frame3D*>::iterator itV = _virtualChannels.find(ch);
   map<ActuatorType::CHANNELS, CommInterface*>::iterator itP =  _physicalChannels.find(ch);
   if(itV!= _virtualChannels.end() || itP!= _physicalChannels.end()) {
    return true; 
   }
   else {
     return false;
   }
 }
 
 
 void Actuators::setAxesRotations(ActuatorType::CHANNELS ch, vector<AxesRotations> axes) throw (ExceptionChannelNotPresent){
   if(this->isPresent(ch)){
//      _axes[ch];
     _axes[ch] = axes;
//      map<ActuatorType::CHANNELS, vector<AxesRotations> >::iterator it = _axes.find(ch);
//      for(unsigned int i=0;i<axes.size();++i){
//        DEBOUT(("%i (%d,%d,%d) (%d,%d,%d)\n",i,
// 	       axes[i].X,axes[i].Y,axes[i].Z,
// 	       _axes[ch][i].X,_axes[ch][i].Y,_axes[ch][i].Z
// 	      )); 
//      }
   }
   else {
     throw ExceptionChannelNotPresent(DEBPOS"This channel not Exists ");
   }
  
}
 

 void Actuators::setActuatorValue(vector<RotationInt>& values) throw (ExceptionIdOutOfRange,ExceptionConnectionInvalid,ExceptionChannelNotPresent){
   for(unsigned int i=0; i<_activeChannels.size(); ++i){
     
     switch(_activeChannels[i]){
       case(ActuatorType::VIRTUALSTICKJOINTS):
       {
	 bool changeState = false;
	 for(unsigned int id = 0; id<values.size();++id){
	   changeState =  (_virtualChannels[_activeChannels[i]]->getObject3D()->rotatePartAngle(values[id].id, 
	   VALUETODEGREE(values[id].rot),
	   _axes[_activeChannels[i]][id])|| changeState);
	   
	  
	   
// 	   	   DEBOUT(("jointid=%d value=%d (%d,%d,%d)*(%.2f,%.2f,%.2f)\n",values[id].id,values[id].rot,
// 		   (_axes[_activeChannels[i]][id].X),
// 		   (_axes[_activeChannels[i]][id].Y),
// 		   (_axes[_activeChannels[i]][id].Z),
// 		   VALUETODEGREE(_axes[_activeChannels[i]][id].X*values[id].rot),
// 		   VALUETODEGREE(_axes[_activeChannels[i]][id].Y*values[id].rot),
// 		   VALUETODEGREE(_axes[_activeChannels[i]][id].Z*values[id].rot)
// 		  ));
	 }
	 _virtualChannels[_activeChannels[i]]->changeState(changeState);
// 	 DEBOUT(("Stato %d\n",changeState));
       }
	  break;
       case(ActuatorType::NAISJOINTS):
       {
	 string stringToSend;
// 	 DEBOUT(("Prova1\n"));
	  setActuatorValueCommInterface(values, stringToSend);
	  if(_physicalChannels.find(_activeChannels[i])==_physicalChannels.end()){
	   DEBOUT(("Not Valid\n"));
	  }
	 
	  else {
// // 	    DEBOUT(("Send %s\n\n",stringToSend.c_str()));
	    (_physicalChannels[_activeChannels[i]])->sendData(stringToSend);
	  }
	  
// 	  DEBOUT(("Prova6\n"));
// 	  DEBOUT(("Send %s\n\n",stringToSend.c_str()));
       }
          break;

       default:
	 
	 break;
     }
   }
 }
 
void Actuators::setActuatorValueCommInterface(vector<RotationInt>& values, string& stringToSend){
  unsigned int numSensors = values.size();
  
  vector<int> servos;
  vector<int> uradPositions;
  vector<int> utimes(numSensors,
		     static_cast <int >((1.0 / static_cast < double >(this->_delay))*1000000.0)*30);
//   DEBOUT(("Prova2\n"));
  int tempAngle=0;
  map<ActuatorType::CHANNELS, vector<AxesRotations> >::iterator it = _axes.find(ActuatorType::NAISJOINTS);
//   DEBOUT(("Prova3\n"));
  for (unsigned int row = 0; row < numSensors; ++row){
    
    servos.push_back(values[row].id);
    
    tempAngle = (((it->second)[row]).X+
	(it->second)[row].Y+
	(it->second)[row].Z)*values[row].rot;
    
    uradPositions.push_back(static_cast<int>(DEGREETOURADIANTS(tempAngle)));
  }//end for
//   DEBOUT(("Prova4\n"));
  stringToSend="";
    CommInterface::cgMessageMvJointWTimeFactory(servos,uradPositions,utimes,stringToSend);
//     DEBOUT(("Prova5\n"));
//       DEBOUT(("Send %s\n\n",_stringToSend.c_str()));

}
