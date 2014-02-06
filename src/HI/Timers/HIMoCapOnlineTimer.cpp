#include "HIMoCapOnlineTimer.h"

HIMoCapOnlineTimer::HIMoCapOnlineTimer(wxEvtHandler *owner,wxStatusBar * status, int id) : HIMoCapTimer(owner,status,id), _rS(0){


}

void HIMoCapOnlineTimer::setReadSensors(ReadSensors* rS){
  _rS = rS;
}

//Il metodo scrive su file i movimenti acquisiti dalla mocap
void  HIMoCapOnlineTimer::Notify(){
  try{

//     DEBOUT(("HIMoCapOnlineTimer::Notify() 2\n"));
    vector<int> sensorsIDs = _sensSys->getSensorsIDs();
//     DEBOUT(("HIMoCapOnlineTimer::Notify() 3\n"));
    vector<RotationInt> frame;
    RotationInt data;
    for(int i=0; i<_sensSys->getNumSensors(); ++i){
      data.id = sensorsIDs[i];
      data.rot = _rS->getCleanedSensorValue(sensorsIDs[i]);
      frame.push_back(data);
      DEBOUT(("add <%d,%d>\n",data.id,data.rot));
    }
    DEBOUT(("frame size %d\n",frame.size()));
//     DEBOUT(("HIMoCapOnlineTimer::Notify() 4\n"));
    _fileMCD->addFrame(frame);
     _status->SetStatusText(wxString::Format(_T("Frame\t%d/%d"),_fileMCD->getNumFrames()-1 ,0),1);
  }
  catch(runtime_error e) {
//     this->Stop();
//     wxLogError(wxString(e.what(), wxConvUTF8));
	DEBOUT(("%s\n",e.what()));
  }
}
