#ifndef SENSORSTYPES_DEFINED
#define SENSORSTYPES_DEFINED

#include "IOTypes.h"
#include <string>
#include <vector>

struct SensorsAttributes{
      SensorsAttributes():name(""), id(-1),idx(-1), jointID(-1),MAX(-1),min(-1),initValue(-1), jointsDirs(),/*servoDir(),*/ mean(sqrt(-1.0)), var(sqrt(-1.0)){};
      
      SensorsAttributes(std::string nameSensor,int idValue, int index, int associatedJoint, int maxValue, int minValue, int init,std::vector<AxesRotations> dirValues, /*AxesRotations dirServoValue,*/double meanValue,double varValue): name(nameSensor), id(idValue), idx(index), jointID(associatedJoint),MAX(maxValue),min(minValue), initValue(init),jointsDirs(dirValues), /*servoDir(dirServoValue),*/mean(meanValue), var(varValue){
      };
      std::string name;
      int id;
      int idx;
      int jointID;
      int MAX;
      int min;
      int initValue;
//       AxesRotations dir;
//       AxesRotations servoDir;
      std::vector<AxesRotations> jointsDirs;
      double mean;
      double var;
      
	static const int VIRTUALJOINTS=0;
	static const int NAISJOINTS=1;
	static const int VIRTUALROBOTJOINTS=2;

	static const int JOINTSTIME = 1000;

    };
#endif
