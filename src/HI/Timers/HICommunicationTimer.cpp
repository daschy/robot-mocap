#include "HICommunicationTimer.h"

HICommunicationTimer::HICommunicationTimer(wxEvtHandler *owner, int id, messageType mvJointsType, int mvJointsParameter):wxTimer(owner,id), _stringToSend(""),_mvJointsType(mvJointsType), _jointsParameter(mvJointsParameter),_numReadingFailed(0){

}
