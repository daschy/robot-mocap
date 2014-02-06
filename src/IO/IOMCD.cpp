#include "IOMCD.h"
#include <sstream>
#include<Headers/Exceptions.h>
#include<debug.h>

using namespace std;
IOMCD::IOMCD(string path, int numMarkers, int frameRate)throw(ExceptionErrorOpeningFile): _filename(path){
  _currentFrame=0;
  _numFrames=0;
  _numMarkers=numMarkers;
  _frameRate=frameRate;
  _bufferData=0;
  _pattern.push_back("frames = %d\tmarkers = %d\tHz = %d\n");
  _pattern.push_back("%d %d\n");
}

IOMCD::~IOMCD(){
  //if(_file) fclose(_file);
  DEBOUT(("IOMCD::~IOMCD()\n"));
}


bool 
IOMCD::writeString(string str, bool append){
    if(append){
      _file = fopen((_filename).c_str(), "a+b");
    }
    else{
      _file = fopen((_filename).c_str(), "wb");
    }
  if(_file){
   // cout<<"IOMCD::writeString() Writing "<<str<<endl;
    fprintf(_file,"%s",str.c_str());
    fclose(_file);
    return true;
    }
  else {
    return false;
  }
}

bool 
IOMCD::writeString(const char* str, bool append){
    if(append){
      _file = fopen((_filename).c_str(), "a+b");
    }
    else{
      _file = fopen((_filename).c_str(), "wb");
    }
  if(_file){
   // cout<<"IOMCD::writeString() Writing "<<str<<endl;
    fprintf(_file,"%s",str);
    fclose(_file);
    return true;
  }
  else {
    return false;
  }
}

bool
IOMCD::writeData(string path){
  char tempChar[128];
  string tempStr="";
  vector<RotationInt>::iterator itData;
  map<int, vector<RotationInt> >::iterator itFrames;
  //se non devo riscrivere tutto il file
  //DEBOUT(("Start Writing..\n"));
  
  
    sprintf(tempChar,_pattern[HEAD].c_str(),_numFrames, _numMarkers, _frameRate);
    tempStr+=tempChar;
  
  for(int i=0; i<static_cast<int>(_numFrames);++i){
    itFrames=_data.find(i);
    for(itData=(itFrames->second).begin(); itData!=(itFrames->second).end(); ++itData){
      sprintf(tempChar,_pattern[FRAMES].c_str(),itData->id,itData->rot);
      tempStr+=tempChar;
      //DEBOUT(("%d %d %d\t%s\n",itData->X,itData->Y,itData->Z, tempStr.c_str()));
    }
  }
  DEBOUT(("End Writing\n"));
  this->setPath(path);
  return writeString(tempStr);
}

void 
IOMCD::addFrame(vector<RotationInt> data)throw (ExceptionMCDFile){
//   if(static_cast<int>(data.size())!=_numMarkers) throw ExceptionMCDFile(DEBPOS"Frame dimension not valid");
  //aggiorna il numero di frames
  _numFrames=_numFrames+1;
  for(unsigned int i=0; i<data.size(); ++i){
  //aggiungi  il frame nell'ultima posizione
    _data[_numFrames-1].push_back(data[i]);
//     DEBOUT(("Added <%d,%d> datasize = %d\n", _data[_numFrames-1][i].id,_data[_numFrames-1][i].rot,data.size()));
  }
}

bool
IOMCD::importData(string filename)throw(ExceptionParseError){
  this->setPath(filename);
  _file = fopen(_filename.c_str(),"rb"); 
  _frameRate=-1;
  _numFrames=0;
  _numMarkers=-1;
  int temp=0;
  //se l'apertura del file �andata a buon fine.
  if(_file){
    char buffer[64];
    //leggi la riga di header
    if(fscanf(_file,_pattern[HEAD].c_str(),&temp, &_numMarkers, &_frameRate)!=3){
      sprintf(buffer, "Parse Error at header");
      throw ExceptionParseError(buffer);
    }//fine if(fscanf())
    int tempID=0,tempValue=0;
    vector<RotationInt> tempFrame;
    //leggi le altre righe
    for(int i=0;!(feof(_file)); ++i){
      for(int j=0; j<_numMarkers;++j){
	if(fscanf(_file,_pattern[FRAMES].c_str(),&tempID, &tempValue)!=2){
	  sprintf(buffer, "Parse Error at frame: %d", i);
	  throw ExceptionParseError(buffer);
	}
	tempFrame.push_back(RotationInt(tempID,tempValue));
      }
      addFrame(tempFrame);
      tempFrame.clear();
    }//fine for()
    fclose(_file);
    return true;
  }//fine if(_file)
   //altrimenti
  else return false;
}

void 
IOMCD::eraseData(){
  _data.clear();
  _numFrames=0;
  _numMarkers=0;
  _frameRate=0;
  DEBOUT(("IOMCD::eraseData()\n"));
}

vector<RotationInt>
IOMCD::getFrame(int frame)throw(ExceptionMCDFile){
  if(_data.find(frame)!= _data.end()){
    return ((_data.find(frame))->second);
  }
  else throw ExceptionMCDFile(DEBPOS"Frame out of range");
}

vector<RotationInt>
IOMCD::getFrame(){
  return ((_data.find(_currentFrame))->second);
}

RotationInt 
IOMCD::getValue(int frame, int marker)throw(ExceptionMCDFile){
  if(_data.find(frame)!= _data.end()){
    if(static_cast<int>(((_data.find(frame))->second).size())<marker) {
      return ((_data.find(frame))->second)[marker];
    }
    else throw ExceptionMCDFile(DEBPOS"Marker out of range");
  }
  else throw ExceptionMCDFile(DEBPOS"Frame out of range");
}

RotationInt 
IOMCD::getValue(int marker)throw(ExceptionMCDFile){
  return ((_data.find(_currentFrame))->second)[marker];
}
