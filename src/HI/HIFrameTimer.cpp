#include "HIFrame.h"


/*
void 
HIFrame::OnTimer(wxTimerEvent& event){
try{
  
}
 catch(runtime_error e) {
	wxLogError(wxString(e.what(), wxConvUTF8));
    }
//   event.GetInterval()
  return;
}*/

bool HIFrame::startCalibrate() throw(ExceptionIdOutOfRange, ExceptionSensorNoInterface, ExceptionNoSensorsSystem)
{
  //Da framerate a delay
    int _delay =
	static_cast <
	int >((1.0 / static_cast < double >(FPSREADING)) *1000.0);
    if (!_rS) {
	throw ExceptionSensorNoInterface(DEBPOS "No Interface");
	return false;
    }
    if (!_rS->getSensorsSystem()) {
	throw ExceptionNoSensorsSystem(DEBPOS "No SensorsSystem");
	return false;
    }
//     _isCalibrating = true;
    return _readSensorsTimer->Start(_delay, wxTIMER_CONTINUOUS);
}

void HIFrame::stopCalibrate(){
//     _isCalibrating = false;
}

bool HIFrame::startMoCap(int numMarkers)
{
    //prepara la lettura e scrittura sul file
    _fileMCD->eraseData();
    _fileMCD->setNumMarkers(numMarkers);
    _fileMCD->setFramerate(static_cast <
		     int >((1.0 / static_cast < double >(FPSMOCAP))
			   *1000.0));
    int _delay =
	static_cast <
	int >((1.0 / static_cast < double >(FPSMOCAP)) *1000.0);
    
    //crea e setta il timer che cattura i movimenti
    _moCapTimer = new HIMoCapOnlineTimer(this,HIFrame_statusbar,TIMERMOCAP_ID);
    static_cast<HIMoCapOnlineTimer*>(_moCapTimer)->setReadSensors(_rS);
    _moCapTimer->setSensorsSystem(_currentSensSys);
    _moCapTimer->setIOMCD(_fileMCD);
    
//     _isCapturing = true;
    DEBOUT(("HITimer::startMoCap()\n"));
    return (/*_readSensorsTimer->Start(_delay, wxTIMER_CONTINUOUS) &&*/ _moCapTimer->Start(_delay, wxTIMER_CONTINUOUS));
}

void HIFrame::stopMoCap(){
//     _isCapturing = false;
    //ferma il timer
    _moCapTimer->Stop();
    delete(_moCapTimer);
    _moCapTimer=0;
    
//     _readSensorsTimer->Stop();
    DEBOUT(("HITimer::stopMoCap()\n"));
    return;
}


bool HIFrame::startReadSensors(){
 
  int delayReadSensors = static_cast <int >((1.0 / static_cast < double >(FPSREADING))*1000.0);
  _readSensorsTimer->setReadSensors(_rS);
    
  _readSensorsTimer->setSensorsSystem(_currentSensSys);
    
   _virtualStick->defaultPosition();
   _virtualRobot->defaultPosition();
   return  (_readSensorsTimer->Start(delayReadSensors,wxTIMER_CONTINUOUS) /*&& _scene3DTimer->Start(delayScene3DTimer,wxTIMER_CONTINUOUS)*/);
}

void HIFrame::stopReadSensors(){
  _readSensorsTimer->Stop();
  
}

bool HIFrame::startSimulation(){
  
 _virtualStick->defaultPosition();
 _virtualRobot->defaultPosition();
    //Creo il timer
//    int delayMoCapOfflineTimer = /*(1.0/25.0)*1000.0;*/ static_cast <int >((1.0 / static_cast < double >(_fileMCD->getFramerate()))*1000.0);

  _moCapTimer = new HIMoCapOfflineTimer(this,_slider,HIFrame_statusbar,TIMERMOCAP_ID);
  _moCapTimer->setSensorsSystem(_currentSensSys);
  static_cast<HIMoCapOfflineTimer*>(_moCapTimer)->setFrame3D(_virtualStick);
  _moCapTimer->setIOMCD(_fileMCD);
   static_cast<HIMoCapOfflineTimer*>(_moCapTimer)->setGridPanel(_gridPanel);
 
  _slider->SetValue(0);
  _slider->SetRange(0,_fileMCD->getNumFrames()-1);
  
  return true;
}

void HIFrame::stopSimulation(){
  _gridPanel->initAll(-1);
  _moCapTimer->Stop();
  
  delete(_moCapTimer);
  _moCapTimer=0;
}
