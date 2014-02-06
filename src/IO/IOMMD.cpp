#include"IOMMD.h"
#include<vector>
#include<Headers/Exceptions.h>
#include <MyConfigParser/MyConfigParser.h>


using namespace std;

IOMMD::IOMMD()
{
}


IOMMD::~IOMMD()
{
    DEBOUT(("IOMMD::~IOMMD()\n"));
}

bool IOMMD::writeString(string str, string filename, bool append)
{
   return writeString(str.c_str(), filename.c_str(), append);
}

bool IOMMD::writeString(const char *str, const char * filename, bool append)
{
  FILE* file;
    //aprire il file in modalit�append
    if (append) {
	file = fopen(filename, "a+b");
    }
    //altrimenti
    else {
	file = fopen(filename, "wb");
    }
    //se il file �aperto allora prosegui
    if (file) {
	// cout<<"IOMMD::writeString() Writing "<<str<<endl;
	fprintf(file, "%s", str);
	fclose(file);
	return true;
    }
    //altrimenti ritorna false
    else {
	return false;
    }
}


bool IOMMD::writeData(SensorsSystem* sensSys, const char* path, const char* filename)
{
  try{
    vector<int> sensors = sensSys->getSensorsIDs();
    
    string temp="";
    if(sensors.size()<=1){
      temp+=sensSys->print();
    }
    else{
      temp+="sec sensorcollection\n";
      char tempChr[128]="";
      sprintf(tempChr,"numsensors: %d\n",sensors.size());
      
      temp+=string(tempChr);
      for(unsigned int i=0; i<sensors.size();++i){
	this->writeString(sensSys->printSensor(sensors[i]),string(path)+sensSys->getSensorName(sensors[i])+string(".cfg"),false);
  
	sprintf(tempChr,"sensor%d: %s%s\n",i,sensSys->getSensorName(sensors[i]).c_str(),".cfg");
	temp+=string(tempChr);
      }
      temp+="endsec\n";
    }

    if (writeString(temp.c_str(), string(path)+string(filename), false))
	return true;
    else
	return false;
    }//end try

    catch(runtime_error e){
      DEBOUT(("%s",e.what()));
    }
  return false;
}

bool 
    IOMMD::writeData(SensorsSystem* sensSys, string path, string filename) {
  return writeData(sensSys, path.c_str(),filename.c_str());
}


 SensorsSystem *IOMMD::importData(const char *path,const char* filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error){
   
     MyConfigParser par;
     par=MyConfigParser(string(path)+string(filename));
     vector<SensorsAttributes> sensors;
     //seleziona la prima sezione, quindi il primo sensore
     bool simpleSensors= false;
    try{ 
      par.selectFirstSection("sensor");
     simpleSensors= true;
    }
    catch(runtime_error e){
      simpleSensors = false;
    }
    

    if(simpleSensors){
      sensors = (this->importSensors(path,filename));
    }
    else{
      //Se nn lancia eccezioni
       sensors=( this->importSensorCollection(path,filename));
    }

    SensorsSystem* sensSys=new SensorsSystem();
    sensSys->setSensorsSystemName(filename);
    for(unsigned int i=0; i<sensors.size();++i){
      sensSys->addSensor(sensors[i]);
    }
    return sensSys;
}

SensorsSystem* IOMMD::importData(string path, string filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error)
{
  return importData(path.c_str(),filename.c_str());
}

 vector<SensorsAttributes> IOMMD::importSensors(const char *path,const char* filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error){
 try{
     MyConfigParser par;
     par=MyConfigParser(string(path)+string(filename));

     //Se nn lancia eccezioni
    vector<SensorsAttributes> sensors;
     //seleziona la prima sezione, quindi il primo sensore
     par.selectFirstSection("sensor");
     
     string sensorName = par.getValueInCurrentSection("name");
     int id = atoi(par.getValueInCurrentSection("id").c_str());
     int index = atoi(par.getValueInCurrentSection("index").c_str());
     int jointID = atoi(par.getValueInCurrentSection("jointID").c_str());
     int max = atoi(par.getValueInCurrentSection("MAX").c_str());
     int min = atoi(par.getValueInCurrentSection("min").c_str());
     int initValue = atoi(par.getValueInCurrentSection("initValue").c_str());
     int numJoints = atoi(par.getValueInCurrentSection("numJoints").c_str());
     
     int x=0, y=0, z=0;
     char tempChr[128];
     vector<AxesRotations> jointsAxes;
     for(int i=0; i<numJoints; ++i){
      sprintf(tempChr,"dir%d",i);
      sscanf(par.getValueInCurrentSection(tempChr).c_str(),"%d %d %d",&x,&y,&z);
      jointsAxes.push_back(AxesRotations(x,y,z));
     }
     double mean = atof(par.getValueInCurrentSection("mean").c_str());
     double variance = atof(par.getValueInCurrentSection("variance").c_str());
   
     
     sensors.push_back(SensorsAttributes(sensorName,id,index,jointID,max,min,initValue,jointsAxes,mean,variance));
//      DEBOUT(("Added %s\n",sensorName.c_str()));
     
     while(par.selectNextSection("sensor")){
       
       
       string sensorName = par.getValueInCurrentSection("name");
       id = atoi(par.getValueInCurrentSection("id").c_str());
       index = atoi(par.getValueInCurrentSection("index").c_str());
       jointID = atoi(par.getValueInCurrentSection("jointID").c_str());
       max = atoi(par.getValueInCurrentSection("MAX").c_str());
       min = atoi(par.getValueInCurrentSection("min").c_str());
       initValue = atoi(par.getValueInCurrentSection("initValue").c_str());
       numJoints = atoi(par.getValueInCurrentSection("numJoints").c_str());
       x=0; y=0; z=0;
       jointsAxes.clear();
       for(int i=0; i<numJoints; ++i){
	 sprintf(tempChr,"dir%d",i);
	 sscanf(par.getValueInCurrentSection(tempChr).c_str(),"%d %d %d",&x,&y,&z);
	 jointsAxes.push_back(AxesRotations(x,y,z));
       }
       mean = atof(par.getValueInCurrentSection("mean").c_str());
       variance = atof(par.getValueInCurrentSection("variance").c_str());
       sensors.push_back(SensorsAttributes(sensorName,id,index,jointID,max,min,initValue,jointsAxes,mean,variance));
//        DEBOUT(("Added %s\n",sensorName.c_str()));
     }
     return sensors;
   }//end try
   catch(ExceptionSensors& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionSensors(buffer);
    }
   catch(MyConfigParser::ExceptionValueNotFound& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionValueNotFound(buffer);
   }
   catch(MyConfigParser::ExceptionSectionNotFound& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionSectionNotFound(buffer);
   }
   catch(MyConfigParser::ExceptionParseError& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionParseError(buffer);
   }
   catch(MyConfigParser::ExceptionErrorOpeningFile& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionErrorOpeningFile(buffer);
   }
   catch (runtime_error& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "IO Error");
     throw runtime_error(buffer);
   }
}

vector<SensorsAttributes> IOMMD::importSensorCollection(const char *path,const char* filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error){
  try{
    MyConfigParser par;
     par=MyConfigParser(string(path)+string(filename));
     //Se nn lancia eccezioni
    vector<SensorsAttributes> sensors;
    vector<SensorsAttributes> sensorsTemp;
     //seleziona la prima sezione, quindi il primo sensore
     par.selectFirstSection("sensorcollection");
     int numSensors = atoi(par.getValueInCurrentSection("numsensors").c_str());
     string sensorFilename;
     char temp[64]="";
    for(int i=0;i<numSensors;++i){
      sprintf(temp,"sensor%d",i);
      sensorFilename = par.getValueInCurrentSection(temp).c_str();

      sensorsTemp = (this->importSensors(path,sensorFilename.c_str()));
      //Aggiunge tutti i sensori trovati 
      for(unsigned int i=0; i<sensorsTemp.size();++i){
          sensors.push_back(sensorsTemp[i]);
        }
    }
    return sensors;
  }
  catch(ExceptionSensors& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionSensors(buffer);
    }
   catch(MyConfigParser::ExceptionValueNotFound& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionValueNotFound(buffer);
   }
   catch(MyConfigParser::ExceptionSectionNotFound& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionSectionNotFound(buffer);
   }
   catch(MyConfigParser::ExceptionParseError& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionParseError(buffer);
   }
   catch(MyConfigParser::ExceptionErrorOpeningFile& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "%s",e.what());
     throw ExceptionErrorOpeningFile(buffer);
   }
   catch (runtime_error& e){
     char buffer[128];
     sprintf(buffer, DEBPOS "IO Error");
     throw runtime_error(buffer);
   }
}



