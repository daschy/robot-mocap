#ifndef OBJECTMOCAP_H
#define OBJECTMOCAP_H

#include <vector>
#include <string>
// #include<vtkPolyDataSource.h>
#include<vtkPolyDataAlgorithm.h>
#include<vtkPolyDataMapper.h>
#include<vtkPoints.h>
#include<vtkAssembly.h>
#include<vtkActor.h>
#include<iostream>

#include<Headers/IOTypes.h>
#include<Headers/Exceptions.h>


#include "Object3D.h"

class ObjectMoCap : public Object3D{
  public: 
     ObjectMoCap(Point3D root);
   
    virtual bool rotatePartAngles(int id, double angleX, double angleY, double angleZ) throw (ExceptionIdOutOfRange);

  protected:
    vector<vtkActor*> makeArm(map<int, Point3D>& armMeasures);
    vector<vtkActor*> makeMocap(map<int, Point3D>& moCapMeasures);

     void assemblyArmActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& assemblies, map<int, Point3D>& armMeasures);
     void assemblyMoCapActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& moCapAssemblies, map<int, Point3D>& moCapMeasures, map<int, Point3D>& armMeasures);
    void addNodes(vector<vtkAssembly*>& moCapAssembliesRight, vector<vtkAssembly*>& armAssembliesRight,vector<vtkAssembly*>& moCapAssembliesLeft, vector<vtkAssembly*>& armAssembliesLeft);
 

    enum moCapParts{
     FINGERMOCAP=0,
    KNUCKLEX,
    HANDMOCAP,
    WRISTX,
    LOWERARMMOCAP,
    ELBOWY, 
    ELBOWX,
    UPPERARMMOCAP,
    SHOULDERX,
    SHOULDERY,
    SHOULDERZ
  };

   enum armParts{
//     FINGER=0,
    KNUCKLE,
//     HAND,
    WRIST,
//     LOWERARM,
    ELBOW,
//     UPPERARM,
    SHOULDER
  };

   map<int, Point3D> _distances;


    map<int, Point3D> _moCapMeasuresRight;
    map<int, Point3D> _armMeasuresRight;
    

    map<int, Point3D> _moCapMeasuresLeft;
    map<int, Point3D> _armMeasuresLeft;


    static const double jointRadius = 1;
    

};
#endif
