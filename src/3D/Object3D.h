#ifndef OBJECT3D_H
#define OBJECT3D_H

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

using namespace std;

/**
La classe rappresenta l'oggetto visualizzato in #Frame3D.
*/
class Object3D {
  public:
    static Object3D* Object3DFactory(const char* dir,const char* filename) throw( ExceptionFileNotFound);
    
    Object3D();
    virtual ~Object3D();
    vtkAssembly* getRoot();
    
    vtkAssembly* getAssembly(int& id) throw (ExceptionIdOutOfRange);
    
    virtual bool rotatePartAngle(int id, double angle, AxesRotations& axes) throw (ExceptionIdOutOfRange);
   
    virtual bool rotatePartAngles(int id, double angleX, double angleY, double angleZ) throw (ExceptionIdOutOfRange);
    
    
    vector<int> getIDs();
    
  protected:
    
   
    
    void setAxesRotations(int jointID, AxesRotations axes) throw (ExceptionIdOutOfRange);
    
    void setAxesRotations(vector<int> jointIDs, vector<AxesRotations> axesVec) throw (ExceptionIdOutOfRange);
    
    void addNode(vtkAssembly * item, int id, AxesRotations axRot);
    void addNode(vtkAssembly * item, int id, vtkAssembly * armPiece);
    void addNode(vtkAssembly * item, int id, vtkAssembly * armPiece0,vtkAssembly * armPiece1);
    void addNode (vtkAssembly *item, int id, int rot_axies, bool rot_direction);
    void addNode(vtkAssembly * item, int id);
    void makeRoot();
    
    vtkAssembly *genStruct(string directory, string genTxt);
    
  private:
     friend Object3D* Object3DFactory(const char* filename);
    struct list_dRobot {
	list_dRobot():id(0),initValue(0), rot_axies(), piece(0),armPiece0(0),armPiece1(0) {};
	list_dRobot(int idValue, AxesRotations axRot,vtkAssembly * pieceValue):
	     id(idValue),initValue(0),lastValue(initValue),rot_axies(axRot), piece(pieceValue),armPiece0(0),armPiece1(0){};
	int id;
	int initValue;
	int lastValue;
	AxesRotations rot_axies;
	vtkAssembly* piece;
        vtkAssembly* armPiece0;
        vtkAssembly* armPiece1;
    };

  protected:
    vtkAssembly * _root;
    map <int, list_dRobot > _robotList;
};



class Object3DRightArm : public Object3D{
  public:
  Object3DRightArm(Point3D root);
  
  private:
    void makeArm(Point3D root);
    void assemblyActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& assemblies);
    enum armParts{
    FINGER=0,
    KNUCKLEX,
    HAND,
    WRISTX,
    LOWERARM,
    ELBOWY, 
    ELBOWX,
    UPPERARM,
    SHOULDERX,
    SHOULDERY,
    SHOULDERZ
  };
  static const double jointRadius = 0.1;
 
};


class Object3DLeftArm : public Object3D{
  public:
  Object3DLeftArm(Point3D root);
  
  private:
    void makeArm(Point3D root);
    void assemblyActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& assemblies);
    enum armParts{
    FINGER=0,
    KNUCKLEX,
    HAND,
    WRISTX,
    LOWERARM,
    ELBOWY, 
    ELBOWX,
    UPPERARM,
    SHOULDERX,
    SHOULDERY,
    SHOULDERZ
  };
  static const double jointRadius = 0.1;
 
};


class Object3DHalfBody : public Object3D{
  public:
    Object3DHalfBody(Point3D root);
  
  private:
    
    void makeHalfBody(Point3D root);
    vector<vtkActor*> makeLeftArm(Point3D root);
    vector<vtkActor*> makeRightArm(Point3D root);
    
    
    void assemblyActors(vector<vtkActor*>& actors,vector<vtkActor*>& actorsLeftArm,
    vector<vtkActor*>& actorsRightArm);
    
    vector<Object3D*> _objs;
    
    
    
    enum halfBodyParts{
      BACHELOR=0,
      ROOT=1,
      //LeftArmParts
      FINGERSX=0,
      KNUCKLEXSX,
      HANDSX,
      WRISTXSX,
      LOWERARMSX,
      ELBOWYSX, 
      ELBOWXSX,
      UPPERARMSX,
      SHOULDERXSX,
      SHOULDERYSX,
      SHOULDERZSX,
      //RightArmParts
      FINGERDX=0,
      KNUCKLEXDX,
      HANDDX,
      WRISTXDX,
      LOWERARMDX,
      ELBOWYDX, 
      ELBOWXDX,
      UPPERARMDX,
      SHOULDERXDX,
      SHOULDERYDX,
      SHOULDERZDX,
    };
    static const double jointRadius = 0.1;
 
};





#endif
