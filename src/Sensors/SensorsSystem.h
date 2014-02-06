#ifndef SENSORSSYST_H_DEFINED
#define SENSORSSYST_H_DEFINED

#include <vector>
#include <string>
#include <iostream>
#include<Headers/Exceptions.h>
#include<Headers/MACROS.h>
#include<Headers/IOTypes.h>
#include<Headers/SensorsTypes.h>

using namespace std;


class SensorsSystem{
public:
       SensorsSystem() throw (ExceptionIdOutOfRange);
	
	SensorsSystem(SensorsSystem & sS) throw (ExceptionIdOutOfRange);
	~SensorsSystem();
        void setSensorsSystemName(string name){ _sensorsSystemName = name;};
	
	string getSensorsSystemName(){ return _sensorsSystemName;};
	
	
	void addSensor(int id){_sensorsMap[id];};
        void addSensor(SensorsAttributes attributes) throw (ExceptionSensors);
        
        
	void resetCalibration();
	inline int getNumSensors(){return static_cast<int>(_sensorsMap.size());};
	
	void setSensorCalibrateMax(int id, int value) throw (ExceptionIdOutOfRange);
	void setSensorCalibrateMin(int id, int value) throw (ExceptionIdOutOfRange);
	inline void setBoundingBoxMin(AxesRotations in){_boundingBox[min]=in;};
	inline void setBoundingBoxMax(AxesRotations in){_boundingBox[MAX]=in;};
	void setSensorMean(int id, double value) throw (ExceptionIdOutOfRange);
	void setSensorVariance(int id, double value) throw (ExceptionIdOutOfRange);
	void setSensorName(int id, string name) throw (ExceptionIdOutOfRange);
	void setInitValue(int id, int init) throw (ExceptionIdOutOfRange);
	
	vector<int> getSensorsCalibrateMax();
        int getSensorCalibrateMax(int id) throw (ExceptionIdOutOfRange);
        
	vector<int> getSensorsCalibrateMin();
        int getSensorCalibrateMin(int id) throw (ExceptionIdOutOfRange);
	
	vector<int> getSensorsInitValues();
        int getSensorInitValue(int id) throw (ExceptionIdOutOfRange);
	
	vector<int> getSensorsIDs();
	vector<string> getSensorsNames();
        string getSensorName(int id)throw (ExceptionIdOutOfRange);
	int getIDSensor(int index) throw (ExceptionIdOutOfRange);
        	
	void associateJointToSensor(int jointID, int sensorID) throw (ExceptionIdOutOfRange);
        vector<int> getJointsIDs();
	int getIDJoint(int index);
  
	int getAssociatedIDJoint(int sensorID);
	
	AxesRotations& getJointAxes(const int& jointID, const int& dir);
	
	vector<AxesRotations> getSensorJoints(int id) throw (ExceptionIdOutOfRange);
	vector<AxesRotations> getSensorsJoint(int jointDirs) throw (ExceptionIdOutOfRange);
	vector<vector<AxesRotations> > getSensorsJoints();
	
	inline map<int, SensorsAttributes> getSensorsMap(){return _sensorsMap;};
	inline AxesRotations getBoundingBoxMin(){return _boundingBox[min];};
	inline AxesRotations getBoundingBoxMax(){return _boundingBox[MAX];};
	
        string print();
        string printSensor(int id) throw (ExceptionIdOutOfRange);
        
  protected:
    enum DefaultValues{
    INIT=-1
    };

	
protected:
        enum{
	 min=0,
	 MAX=1 
	};
  
	string _sensorsSystemName;
	map<int, SensorsAttributes> _sensorsMap;
	vector<AxesRotations> _boundingBox;
};

/*
Aggiungi qui la dichiarazione del nuovo sistema di sensori (es:SistemaDiSensori) e crea il file in cui lo implementi (es:SistemaDiSensori.cpp).
*/

#endif
