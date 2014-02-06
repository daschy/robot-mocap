
#include <cgConnectionUnix.h>
#include <cgConnectionTCP.h>

#include"CommInterfaceNetwork.h"

using namespace std;

CommInterfaceNetwork::CommInterfaceNetwork(int socket,const char* ipAddress, PROTOCOL protocol) throw(ExceptionConnectionError) : _protocol(protocol) {
  try{
    if(protocol==TCP){
      _connectionNet = new cgConnectionTCP(socket, ipAddress);
    }
  }
  catch(cgConnection::ExceptionConnectionError e){
    throw ExceptionConnectionError(string(DEBPOS)+ string(e.what()));
  }
}


CommInterfaceNetwork::~CommInterfaceNetwork(){
  if(_connectionNet) delete(_connectionNet);
}


size_t 
CommInterfaceNetwork::sendData(const unsigned char* data, size_t sizeOfData) throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->sendData(data,sizeOfData);
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

size_t
CommInterfaceNetwork::sendData(string& str) throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->sendData(str);
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}
    
size_t
CommInterfaceNetwork::sendData(vector<unsigned char>& vec) throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->sendData(vec);
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

size_t 
CommInterfaceNetwork::sendData(cgMessage* msg) throw(ExceptionConnectionInvalid){
  try{
    messageType type = msg->getMessageType();
    
    switch(type){
      case INVALID: /**< Messaggio non valido.*/
	 {
	DEBOUT(("case INVALID\n"));
	}
	break;
      case BYE: /**< Messaggio di chiusura.*/
      {
	char tempChr[32];
	sprintf(tempChr,"BYE(%ld);",random());
	    
	string temp = tempChr;
	
	return sendData(temp);
      }
	break;
      case HELLO: /**< Messaggio di saluto*/
      {
	char tempChr[32];
	sprintf(tempChr,"HELLO(%ld);",random());
	string temp = tempChr;
	return sendData(temp);
      }
	break;
      case MODE: /**< Messaggio per il cambio di modalita'*/
      {
	cgMessageMode::modeType mode =((cgMessageMode*)msg)->getMode();
	char tempChr[128];
	string temp;
	
	sprintf(tempChr,"%d", static_cast<int>(msg->getMessageNumber()));
	temp ="CNGMODE(";
	temp+=tempChr;
	temp+=",";
	sprintf(tempChr,"%d", static_cast<int>(mode));
	temp+=tempChr;
	temp+=")";
      }
	break;
      case COMMAND: /**< Messaggio di comando'*/
	DEBOUT(("case COMMAND\n"));
	break;
      case REQSENSOR: /**< Messaggio di richiesta stato sensori*/
	DEBOUT(("case REQSENSOR\n"));
	break;
      case SENSOR: /**< Messaggio contenente lo stato dei sensori*/
	DEBOUT(("case SENSOR\n"));
	break;
      case REQSENSORHISTORY: /**< Messaggio di richiesta history del sensore*/
	DEBOUT(("case REQSENSORHISTORY\n"));
	break;
      case SENSORHISTORY: /**< Messaggioio contenente la history del sensore*/
	DEBOUT(("case SENSORHISTORY\n"));
	break;
      case REQCORESTATE: /**< Messaggio di richiesta dello stato della centralina di controllo*/
	DEBOUT(("case REQCORESTATE\n"));
	break;
      case CORESTATE: /**< Messaggio contenente lo stato della centralina di controllo*/
	DEBOUT(("case CORESTATE\n"));
	break;
	case MVJOINTWSPEED: /**< Messaggio per lo spostamento dei Joint specificando la velocita'.*/
      {
	std::vector< struct cgMessageMvJointWSpeed::JointValue> servos=((cgMessageMvJointWSpeed*)msg)->getData();
	char tempChr[128];
	sprintf(tempChr,"%d", static_cast<int>(msg->getMessageNumber()));
	string temp="MVJOINTWSPEED(";
	temp+=tempChr;
	for(int i=0; i<static_cast<int>(servos.size()); ++i){
	  sprintf(tempChr,",%d,%d,%d",static_cast<int>(servos[i].mJointId), static_cast<int>(servos[i].mJointPosition), static_cast<int>(servos[i].mJointParameter));
	  temp+=tempChr;
	}
	temp+=");";
	DEBOUT(("Send %s\n",temp.c_str()));
	return sendData(temp);
	
      }
	break;
      case MVJOINTWTIME: /**< Messaggio per lo spostamento dei Joint specificando la durata dello spostamento.*/
      {
	std::vector< struct cgMessageMvJointWTime::JointValue> servos=((cgMessageMvJointWTime*)msg)->getData();
	char tempChr[128];
	sprintf(tempChr,"%d", static_cast<int>(msg->getMessageNumber()));
	string temp="MVJOINTWTIME(";
	temp+=tempChr;
	for(int i=0; i<static_cast<int>(servos.size()); ++i){
	  sprintf(tempChr,",%d,%d,%d",static_cast<int>(servos[i].mJointId), static_cast<int>(servos[i].mJointPosition), static_cast<int>(servos[i].mJointParameter));
	  temp+=tempChr;
	}
	temp+=");";
	
// 	DEBOUT(("Send %s\n",((cgMessageMvJointWTime*)msg)->getAsString().c_str()));
	return sendData(temp);
	
      }
	break;
      default:
	DEBOUT(("INVALID MESSAGE\n"));
	break;
    }
    return 0;
  }

  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

vector<unsigned char> 
CommInterfaceNetwork::recvDataAsVector() throw(ExceptionReceiveError, ExceptionConnectionInvalid){
  try{
    return _connectionNet->recvDataAsVector();
  }
  
  catch(cgConnection::ExceptionReceiveError e){
    throw ExceptionReceiveError(string(DEBPOS)+ string(e.what()));
  }
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

string 
CommInterfaceNetwork::recvDataAsString() throw(ExceptionReceiveError, ExceptionConnectionInvalid){
  try{
    return _connectionNet->recvDataAsString();
  }
  
  catch(cgConnection::ExceptionReceiveError e){
    throw ExceptionReceiveError(string(DEBPOS)+ string(e.what()));
  }
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}
    
size_t 
CommInterfaceNetwork::recv(unsigned char* ptr, size_t maxSize)  throw(ExceptionReceiveError, ExceptionConnectionInvalid){
  try{
    return _connectionNet->recv(ptr,maxSize);
  }
  
  catch(cgConnection::ExceptionReceiveError e){
    throw ExceptionReceiveError(string(DEBPOS)+ string(e.what()));
  }
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
  
}

bool 
CommInterfaceNetwork::closeConnection() throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->closeConnection();
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

/** Fa un restart della connessione.*/
void 
CommInterfaceNetwork::restart() throw(ExceptionConnectionError){
  try{
    return _connectionNet->restart();
  }
  
  catch(cgConnection::ExceptionConnectionError e){
    throw ExceptionConnectionError(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

string 
CommInterfaceNetwork::getRemoteIpAdd() throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->getRemoteIpAdd();
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

int 
CommInterfaceNetwork::getPort() throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->getPort();
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

time_t 
CommInterfaceNetwork::getElapsedTime() throw(ExceptionConnectionInvalid){
  try{
    return _connectionNet->getElapsedTime();
  }
  
  catch(cgConnection::ExceptionConnectionInvalid e){
    throw ExceptionConnectionInvalid(string(DEBPOS)+ string(e.what()));
  }
  catch(runtime_error e){
    throw ExceptionCommunication(string(DEBPOS)+ string("Communication Error"));
  }
}

bool 
CommInterfaceNetwork::isValidConnection() {
  return _connectionNet->isValidConnection();
}

int 
CommInterfaceNetwork::getSocketFd() {
  return _connectionNet->getSocketFd();
}

