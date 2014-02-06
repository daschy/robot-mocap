#ifndef IOTYPES_DEFINED
#define IOTYPES_DEFINED

#include <math.h>

struct AxesRotations{
  AxesRotations(int x=0, int y=0, int z=0){X=x; Y=y; Z=z;};
  int X; //rollio
  int Y;//beccheggio
  int Z;//deriva
};

struct Point3D{
  Point3D(double x=0, double y=0, double z=0):X(x),Y(y),Z(z){};
  double X;
  double Y;
  double Z;
};

struct RotationInt{
  RotationInt(int idValue=0,int rotValue=0):id(idValue),rot(rotValue){};
  int id;
  int rot;
};

/**
La struct AveragesType descrive ciascun elemento della sezione \em STICKS_AVERAGE.
*/
struct AveragesType{
  AveragesType(double mean=sqrt(-1.0), double var=sqrt(-1.0)):MEAN(mean), VAR(var){};
  double MEAN;
  double VAR;
};
#endif
