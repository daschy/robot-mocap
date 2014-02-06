#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <Headers/MACROS.h>
#include "ObjectMoCap.h"
#include <math.h>


static double white[3]={1.0,1.0,1.0};
static double fancy[3]={0.7,0.2,1.0};

ObjectMoCap::ObjectMoCap(Point3D root):Object3D(){

    //Distanze dei sensori dal centro di rotazione corrispondente del corpo
  _distances[SHOULDERZ]=Point3D(0.0,0.0,/*-*/7.5);
  _distances[SHOULDERY]=Point3D(/*-*/7.5,1.0,/*-*/2.0);
  _distances[SHOULDERX]=Point3D(/*-*/8.5,0.0,0.0);
  _distances[ELBOWX]=Point3D(/*-*/8.80/*6.0*/,/*9.50*/0.0,0.0); 
  _distances[ELBOWY]=Point3D(/*-*//*6.5*/9.80,0.0,/*-*/2.5);
  _distances[WRISTX]=Point3D(/*-*//*4.5*/13.80,0.0,0.0);
  _distances[KNUCKLEX]=Point3D(/*-*//*1.0*/11.80,1.0,/*-*/4.0);

 
    _moCapMeasuresRight[SHOULDERZ] = Point3D(root.X-20.0,root.Y,root.Z);

    _moCapMeasuresRight[SHOULDERY] = Point3D(_moCapMeasuresRight[SHOULDERZ].X-7.0,
                                _moCapMeasuresRight[SHOULDERZ].Y+1.0,
                                _moCapMeasuresRight[SHOULDERZ].Z+6.0);

    _moCapMeasuresRight[SHOULDERX] = Point3D(_moCapMeasuresRight[SHOULDERY].X-1.2,
                                _moCapMeasuresRight[SHOULDERY].Y-1.0,
                                _moCapMeasuresRight[SHOULDERY].Z+2.0);

    _moCapMeasuresRight[UPPERARMMOCAP]= Point3D(0.3/*1.0*/,24.0,0.3/*1.0*/);

    _moCapMeasuresRight[ELBOWX] = Point3D(_moCapMeasuresRight[SHOULDERX].X-_moCapMeasuresRight[UPPERARMMOCAP].X/*-5.0*/,
                             _moCapMeasuresRight[SHOULDERX].Y-_moCapMeasuresRight[UPPERARMMOCAP].Y,
                             _moCapMeasuresRight[SHOULDERX].Z-_moCapMeasuresRight[UPPERARMMOCAP].Z);
    
    _moCapMeasuresRight[ELBOWY] = Point3D(_moCapMeasuresRight[ELBOWX].X-1.0,
                             _moCapMeasuresRight[ELBOWX].Y-1.5/*7.0*/,
                             _moCapMeasuresRight[ELBOWX].Z-2.0);
    
    _moCapMeasuresRight[LOWERARMMOCAP]= Point3D(0.3/*1.0*/,24.0,0.3/*1.0*/);

    _moCapMeasuresRight[WRISTX] =  Point3D(_moCapMeasuresRight[ELBOWY].X-4.0,
                              _moCapMeasuresRight[ELBOWY].Y-_moCapMeasuresRight[LOWERARMMOCAP].Y,  _moCapMeasuresRight[ELBOWY].Z+2.0);

    _moCapMeasuresRight[HANDMOCAP] = Point3D(5.0/*9.0*/,3.0/*8.0*/,1.0/*6.0*/);

    _moCapMeasuresRight[KNUCKLEX] = Point3D(_moCapMeasuresRight[WRISTX].X,
                               _moCapMeasuresRight[WRISTX].Y-_moCapMeasuresRight[HANDMOCAP].Y,
                               _moCapMeasuresRight[WRISTX].Z-4.0);

     _moCapMeasuresRight[FINGERMOCAP] = Point3D(2.0,5.0,0.1);



   _armMeasuresRight[SHOULDER]=Point3D(_moCapMeasuresRight[SHOULDERX].X+_distances[SHOULDERX].X,
                          _moCapMeasuresRight[SHOULDERY].Y-_distances[SHOULDERY].Y,
                          _moCapMeasuresRight[SHOULDERZ].Z+_distances[SHOULDERZ].Z);

   _armMeasuresRight[ELBOW] = Point3D(_moCapMeasuresRight[ELBOWX].X+_distances[ELBOWX].X,
                         _moCapMeasuresRight[ELBOWY].Y+_distances[ELBOWY].Y,
                         _moCapMeasuresRight[ELBOWX].Z);

  _armMeasuresRight[WRIST] = Point3D( /*_armMeasures[ELBOW].X*/_moCapMeasuresRight[WRISTX].X+_distances[WRISTX].X,
                         _moCapMeasuresRight[WRISTX].Y,
                         _moCapMeasuresRight[WRISTX].Z);

  _armMeasuresRight[KNUCKLE] = Point3D(/*_armMeasures[WRIST].X-3.0*/_moCapMeasuresRight[KNUCKLEX].X+_distances[KNUCKLEX].X,
                         _moCapMeasuresRight[KNUCKLEX].Y-_distances[KNUCKLEX].Y,
                          _moCapMeasuresRight[KNUCKLEX].Z+_distances[KNUCKLEX].Z);


//LEFT ARM

    _moCapMeasuresLeft[SHOULDERZ] = Point3D(root.X+20.0,root.Y,root.Z);

    _moCapMeasuresLeft[SHOULDERY] = Point3D(_moCapMeasuresLeft[SHOULDERZ].X+7.0,
                                _moCapMeasuresLeft[SHOULDERZ].Y+1.0,
                                _moCapMeasuresLeft[SHOULDERZ].Z+6.0);

    _moCapMeasuresLeft[SHOULDERX] = Point3D(_moCapMeasuresLeft[SHOULDERY].X+1.2,
                                _moCapMeasuresLeft[SHOULDERY].Y-1.0,
                                _moCapMeasuresLeft[SHOULDERY].Z+2.0);

    _moCapMeasuresLeft[UPPERARMMOCAP]= Point3D(0.3/*1.0*/,24.0,0.3/*1.0*/);

    _moCapMeasuresLeft[ELBOWX] = Point3D(_moCapMeasuresLeft[SHOULDERX].X+_moCapMeasuresLeft[UPPERARMMOCAP].X/*-5.0*/,
                             _moCapMeasuresLeft[SHOULDERX].Y-_moCapMeasuresLeft[UPPERARMMOCAP].Y,
                             _moCapMeasuresLeft[SHOULDERX].Z-_moCapMeasuresLeft[UPPERARMMOCAP].Z);
    
    _moCapMeasuresLeft[ELBOWY] = Point3D(_moCapMeasuresLeft[ELBOWX].X+1.0,
                             _moCapMeasuresLeft[ELBOWX].Y-1.5/*7.0*/,
                             _moCapMeasuresLeft[ELBOWX].Z-2.0);
    
    _moCapMeasuresLeft[LOWERARMMOCAP]= Point3D(0.3/*1.0*/,24.0,0.3/*1.0*/);

    _moCapMeasuresLeft[WRISTX] =  Point3D(_moCapMeasuresLeft[ELBOWY].X+4.0,
                              _moCapMeasuresLeft[ELBOWY].Y-_moCapMeasuresLeft[LOWERARMMOCAP].Y,  _moCapMeasuresLeft[ELBOWY].Z+2.0);

    _moCapMeasuresLeft[HANDMOCAP] = Point3D(5.0/*9.0*/,3.0/*8.0*/,1.0/*6.0*/);

    _moCapMeasuresLeft[KNUCKLEX] = Point3D(_moCapMeasuresLeft[WRISTX].X,
                               _moCapMeasuresLeft[WRISTX].Y-_moCapMeasuresLeft[HANDMOCAP].Y,
                               _moCapMeasuresLeft[WRISTX].Z-4.0);

    _moCapMeasuresLeft[FINGERMOCAP] = Point3D(2.0,5.0,0.1);
 
  
   _armMeasuresLeft[SHOULDER]=Point3D(_moCapMeasuresLeft[SHOULDERX].X-_distances[SHOULDERX].X,
                          _moCapMeasuresLeft[SHOULDERY].Y-_distances[SHOULDERY].Y,
                          _moCapMeasuresLeft[SHOULDERZ].Z+_distances[SHOULDERZ].Z);

   _armMeasuresLeft[ELBOW] = Point3D(_moCapMeasuresLeft[ELBOWX].X-_distances[ELBOWX].X,
                         _moCapMeasuresLeft[ELBOWY].Y+_distances[ELBOWY].Y,
                         _moCapMeasuresLeft[ELBOWX].Z);

  _armMeasuresLeft[WRIST] = Point3D( /*_armMeasuresLeft[ELBOW].X*/_moCapMeasuresLeft[WRISTX].X-_distances[WRISTX].X,
                         _moCapMeasuresLeft[WRISTX].Y,
                         _moCapMeasuresLeft[WRISTX].Z);

  _armMeasuresLeft[KNUCKLE] = Point3D(/*_armMeasures[WRIST].X-3.0*/_moCapMeasuresLeft[KNUCKLEX].X-_distances[KNUCKLEX].X,
                          _moCapMeasuresLeft[KNUCKLEX].Y-_distances[KNUCKLEX].Y,
                          _moCapMeasuresLeft[KNUCKLEX].Z+_distances[KNUCKLEX].Z);

  //end LEFT ARM


//RIGHT ARM
   vector<vtkActor*> actorsRightMoCap = makeMocap(_moCapMeasuresRight);

   vector<vtkAssembly*> assembliesRightMoCap;  

   assemblyMoCapActors(actorsRightMoCap,assembliesRightMoCap,_moCapMeasuresRight, _armMeasuresRight);

   vector<vtkActor*> actorsRightArm = makeArm(_armMeasuresRight);
   vector<vtkAssembly*> assembliesRightArm;
   assemblyArmActors(actorsRightArm,assembliesRightArm,_armMeasuresRight);

   


//LEFT ARM
   vector<vtkActor*> actorsLeftMoCap = makeMocap(_moCapMeasuresLeft);
   vector<vtkAssembly*> assembliesLeftMoCap;  
   assemblyMoCapActors(actorsLeftMoCap,assembliesLeftMoCap,_moCapMeasuresLeft,_armMeasuresLeft);

   vector<vtkActor*> actorsLeftArm = makeArm(_armMeasuresLeft);
   vector<vtkAssembly*> assembliesLeftArm;
   assemblyArmActors(actorsLeftArm,assembliesLeftArm,_armMeasuresLeft);   

DEBOUT(("Prova 5\n"));
  addNodes(assembliesRightMoCap,assembliesRightArm,assembliesLeftMoCap,assembliesLeftArm);
DEBOUT(("Prova 6\n"));

   makeRoot();
DEBOUT(("Prova 7\n"));
}


vector<vtkActor*> 
ObjectMoCap::makeArm(map<int, Point3D>& armMeasures){
  vector<vtkPolyDataAlgorithm*> objects;
  vector<vtkActor*> actors;
  vector<vtkPolyDataMapper *> mappers;
  vector<vtkAssembly*> assemblies;
  
  double shoulderX = armMeasures[SHOULDER].X, shoulderY=armMeasures[SHOULDER].Y, shoulderZ =armMeasures[SHOULDER].Z;
  double elbowX = armMeasures[ELBOW].X, elbowY = armMeasures[ELBOW].Y, elbowZ = armMeasures[ELBOW].Z;
  double wristX = armMeasures[WRIST].X, wristY = armMeasures[WRIST].Y, wristZ =armMeasures[WRIST].Z;
  double knuckleX = armMeasures[KNUCKLE].X, knuckleY =armMeasures[KNUCKLE].Y, knuckleZ =armMeasures[KNUCKLE].Z;

  double FingerXLength = 2,FingerYLength=4, FingerZLength=0.1;
  double HandXLength = 6, HandYLength= fabs(knuckleY-wristY), HandZLength=0.1;
  double LowerArmXLength=2, LowerArmYLength = fabs(elbowY-wristY)-jointRadius, LowerArmZLength=0.1;
  double UpperArmXLength= 2, UpperArmYLength= fabs(shoulderY-elbowY)-jointRadius, UpperArmZLength=0.1;

  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[FINGERMOCAP])->SetXLength(FingerXLength);
  static_cast<vtkCubeSource*>(objects[FINGERMOCAP])->SetYLength(FingerYLength);
  static_cast<vtkCubeSource*>(objects[FINGERMOCAP])->SetZLength(FingerZLength);
  mappers[FINGERMOCAP]->SetInput(objects[FINGERMOCAP]->GetOutput());
  actors[FINGERMOCAP]->SetMapper(mappers[FINGERMOCAP]);
  actors[FINGERMOCAP]->SetPosition(knuckleX,knuckleY-jointRadius-FingerYLength/2,knuckleZ);
  actors[FINGERMOCAP]->SetOrigin(knuckleX,knuckleY-jointRadius,knuckleZ);
  actors[FINGERMOCAP]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
   DEBOUT(("Actor FINGER %d (%.2f,%.2f,%.2f)\n",FINGERMOCAP,(actors[FINGERMOCAP]->GetPosition())[0],(actors[FINGERMOCAP]->GetPosition())[1],(actors[FINGERMOCAP]->GetPosition())[2]));

  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetRadius(jointRadius);
  mappers[KNUCKLE]->SetInput(objects[KNUCKLEX]->GetOutput());
  actors[KNUCKLEX]->SetMapper(mappers[KNUCKLEX]);
  actors[KNUCKLEX]->SetPosition(knuckleX,knuckleY,knuckleZ);
  actors[KNUCKLEX]->SetOrigin(knuckleX,knuckleY,knuckleZ);
  actors[KNUCKLEX]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor KNUCKLE %d (%.2f,%.2f,%.2f)\n",KNUCKLE,(actors[KNUCKLEX]->GetPosition())[0],(actors[KNUCKLEX]->GetPosition())[1],(actors[KNUCKLEX]->GetPosition())[2]));

  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[HANDMOCAP])->SetXLength(HandXLength);
  static_cast<vtkCubeSource*>(objects[HANDMOCAP])->SetYLength(HandYLength);
  static_cast<vtkCubeSource*>(objects[HANDMOCAP])->SetZLength(HandZLength);
  mappers[HANDMOCAP]->SetInput(objects[HANDMOCAP]->GetOutput());
  actors[HANDMOCAP]->SetMapper(mappers[HANDMOCAP]);
  actors[HANDMOCAP]->SetPosition(wristX,wristY-jointRadius-HandYLength/2,wristZ);
  actors[HANDMOCAP]->SetOrigin(wristX,wristY-jointRadius,wristZ);
 actors[HANDMOCAP]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
   DEBOUT(("Actor HAND %d (%.2f,%.2f,%.2f)\n",HANDMOCAP,(actors[HANDMOCAP]->GetPosition())[0],(actors[HANDMOCAP]->GetPosition())[1],(actors[HANDMOCAP]->GetPosition())[2]));


  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetRadius(jointRadius);
  mappers[WRISTX]->SetInput(objects[WRISTX]->GetOutput());
  actors[WRISTX]->SetMapper(mappers[WRISTX]);
  actors[WRISTX]->SetPosition(wristX,wristY,wristZ);
  actors[WRISTX]->SetOrigin(wristX,wristY,wristZ);
  actors[WRISTX]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
   DEBOUT(("Actor WRIST %d (%.2f,%.2f,%.2f)\n",WRISTX,(actors[WRISTX]->GetPosition())[0],(actors[WRISTX]->GetPosition())[1],(actors[WRISTX]->GetPosition())[2]));

  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[LOWERARMMOCAP])->SetXLength(LowerArmXLength);
  static_cast<vtkCubeSource*>(objects[LOWERARMMOCAP])->SetYLength(LowerArmYLength);
  static_cast<vtkCubeSource*>(objects[LOWERARMMOCAP])->SetZLength(LowerArmZLength);
  mappers[LOWERARMMOCAP]->SetInput(objects[LOWERARMMOCAP]->GetOutput());
  actors[LOWERARMMOCAP]->SetMapper(mappers[LOWERARMMOCAP]);
  actors[LOWERARMMOCAP]->SetPosition(elbowX,elbowY-jointRadius-LowerArmYLength/2,elbowZ);
  actors[LOWERARMMOCAP]->SetOrigin(elbowX, elbowY-jointRadius, elbowZ);
  actors[LOWERARMMOCAP]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
   DEBOUT(("Actor LOWERARM %d (%.2f,%.2f,%.2f)\n",LOWERARMMOCAP,(actors[LOWERARMMOCAP]->GetPosition())[0],(actors[LOWERARMMOCAP]->GetPosition())[1],(actors[LOWERARMMOCAP]->GetPosition())[2]));

//    int ELBOWYARM=5, ELBOWXARM=6,SHOULDERXARM=8, SHOULDERYARM=9,SHOULDERZARM=10;

  //ELBOW


   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetRadius(jointRadius);
  mappers[ELBOWY]->SetInput(objects[ELBOWY]->GetOutput());
  actors[ELBOWY]->SetMapper(mappers[ELBOWY]);
  actors[ELBOWY]->SetPosition(elbowX,elbowY,elbowZ);
  actors[ELBOWY]->SetOrigin(elbowX,elbowY,elbowZ);
  actors[ELBOWY]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor ELBOW %d (%.2f,%.2f,%.2f)\n",ELBOWY,(actors[ELBOWY]->GetPosition())[0],(actors[ELBOWY]->GetPosition())[1],(actors[ELBOWY]->GetPosition())[2]));
// 
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetRadius(jointRadius);
  mappers[ELBOWX]->SetInput(objects[ELBOWX]->GetOutput());
  actors[ELBOWX]->SetMapper(mappers[ELBOWX]);
  actors[ELBOWX]->SetPosition(elbowX,elbowY,elbowZ);
  actors[ELBOWX]->SetOrigin(elbowX,elbowY,elbowZ);
  actors[ELBOWX]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor ELBOW %d (%.2f,%.2f,%.2f)\n",ELBOWX,(actors[ELBOWX]->GetPosition())[0],(actors[ELBOWX]->GetPosition())[1],(actors[ELBOWX]->GetPosition())[2]));
   
  //UPPERARM
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[UPPERARMMOCAP])->SetXLength(UpperArmXLength);
  static_cast<vtkCubeSource*>(objects[UPPERARMMOCAP])->SetYLength(UpperArmYLength);
  static_cast<vtkCubeSource*>(objects[UPPERARMMOCAP])->SetZLength(UpperArmZLength);
  mappers[UPPERARMMOCAP]->SetInput(objects[UPPERARMMOCAP]->GetOutput());
  actors[UPPERARMMOCAP]->SetMapper(mappers[UPPERARMMOCAP]);
  actors[UPPERARMMOCAP]->SetPosition(shoulderX, shoulderY-jointRadius-UpperArmYLength/2, shoulderZ);
  actors[UPPERARMMOCAP]->SetOrigin(shoulderX, shoulderY-jointRadius, shoulderZ);
  actors[UPPERARMMOCAP]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor UPPERARM %d (%.2f,%.2f,%.2f)\n",UPPERARMMOCAP,(actors[UPPERARMMOCAP]->GetPosition())[0],(actors[UPPERARMMOCAP]->GetPosition())[1],(actors[UPPERARMMOCAP]->GetPosition())[2]));  
 
  //SHOULDER

   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetPhiResolution(25);
  mappers[SHOULDERX]->SetInput(objects[SHOULDERX]->GetOutput());
  actors[SHOULDERX]->SetMapper(mappers[SHOULDERX]);
  actors[SHOULDERX]->SetPosition(shoulderX, shoulderY, shoulderZ);
  actors[SHOULDERX]->SetOrigin(shoulderX, shoulderY, shoulderZ);
  actors[SHOULDERX]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor SHOULDER %d (%.2f,%.2f,%.2f)\n",SHOULDERX,(actors[SHOULDERX]->GetPosition())[0],(actors[SHOULDERX]->GetPosition())[1],(actors[SHOULDERX]->GetPosition())[2]));
// 
 
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetPhiResolution(25);
  mappers[SHOULDERY]->SetInput(objects[SHOULDERY]->GetOutput());
  actors[SHOULDERY]->SetMapper(mappers[SHOULDERY]);
  actors[SHOULDERY]->SetPosition(shoulderX, shoulderY, shoulderZ);
  actors[SHOULDERY]->SetOrigin(shoulderX, shoulderY, shoulderZ);
  actors[SHOULDERY]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor SHOULDER %d (%.2f,%.2f,%.2f)\n",SHOULDERY,(actors[SHOULDERY]->GetPosition())[0],(actors[SHOULDERY]->GetPosition())[1],(actors[SHOULDERY]->GetPosition())[2]));
// 
// 
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetPhiResolution(25);
  mappers[SHOULDERZ]->SetInput(objects[SHOULDERZ]->GetOutput());
  actors[SHOULDERZ]->SetMapper(mappers[SHOULDERZ]);
  actors[SHOULDERZ]->SetPosition(shoulderX, shoulderY, shoulderZ);
  actors[SHOULDERZ]->SetOrigin(shoulderX, shoulderY, shoulderZ);
  actors[SHOULDERZ]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
  DEBOUT(("Actor SHOULDER %d (%.2f,%.2f,%.2f)\n",SHOULDERZ,(actors[SHOULDERZ]->GetPosition())[0],(actors[SHOULDERZ]->GetPosition())[1],(actors[SHOULDERZ]->GetPosition())[2]));
//   
  return actors;
  
}

void 
ObjectMoCap::assemblyArmActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& assemblies, map<int, Point3D>& armMeasures){

  assemblies .push_back(vtkAssembly::New());
  assemblies[FINGERMOCAP]->AddPart(actors[FINGERMOCAP]);
  
  
  for(int i=1; i<static_cast<int>(actors.size()); ++i){
    assemblies .push_back(vtkAssembly::New());
    assemblies[i]->AddPart(assemblies[i-1]);
    assemblies[i]->AddPart(actors[i]);
  }
  
//    int ELBOWYARM=5, ELBOWXARM=6,SHOULDERXARM=8, SHOULDERYARM=9,SHOULDERZARM=10;

//   assemblies[FINGERMOCAP]->SetOrigin(armMeasures[KNUCKLE].X, 
//                                  armMeasures[KNUCKLE].Y, 
//                                  armMeasures[KNUCKLE].Z);

  assemblies[KNUCKLEX]->SetOrigin(armMeasures[KNUCKLE].X, 
                                 armMeasures[KNUCKLE].Y, 
                                 armMeasures[KNUCKLE].Z);

  assemblies[WRISTX]->SetOrigin(armMeasures[WRIST].X, 
                               armMeasures[WRIST].Y, 
                               armMeasures[WRIST].Z);

  assemblies[ELBOWY]->SetOrigin(armMeasures[ELBOW].X,
                                   armMeasures[ELBOW].Y,
                                   armMeasures[ELBOW].Z); 
  
  assemblies[ELBOWX]->SetOrigin(armMeasures[ELBOW].X, 
                                   armMeasures[ELBOW].Y,
                                   armMeasures[ELBOW].Z);
  
  assemblies[SHOULDERX]->SetOrigin(armMeasures[SHOULDER].X,
                                      armMeasures[SHOULDER].Y,
                                      armMeasures[SHOULDER].Z);
  
  assemblies[SHOULDERY]->SetOrigin(armMeasures[SHOULDER].X, 
                                      armMeasures[SHOULDER].Y, 
                                      armMeasures[SHOULDER].Z);
  
  assemblies[SHOULDERZ]->SetOrigin(armMeasures[SHOULDER].X, 
                                      armMeasures[SHOULDER].Y, 
                                      armMeasures[SHOULDER].Z);


//   assemblies[KNUCKLE]->SetOrigin(_moCapMeasures[KNUCKLEX].X, 
//                                  _moCapMeasures[KNUCKLEX].Y, 
//                                  _moCapMeasures[KNUCKLEX].Z);
// 
//   assemblies[WRIST]->SetOrigin(_moCapMeasures[WRISTX].X, 
//                                _moCapMeasures[WRISTX].Y, 
//                                _moCapMeasures[WRISTX].Z);
// 
//   assemblies[ELBOWYARM]->SetOrigin(_armMeasures[ELBOW].X,
//                                    _armMeasures[ELBOW].Y,
//                                    _armMeasures[ELBOW].Z); 
//   
//   assemblies[ELBOWXARM]->SetOrigin(_moCapMeasures[ELBOWX].X, 
//                                    _moCapMeasures[ELBOWX].Y,
//                                    _moCapMeasures[ELBOWX].Z);
//   
//   assemblies[SHOULDERXARM]->SetOrigin(_moCapMeasures[SHOULDERX].X,
//                                       _moCapMeasures[SHOULDERX].Y,
//                                       _moCapMeasures[SHOULDERX].Z);
//   
//   assemblies[SHOULDERYARM]->SetOrigin(_moCapMeasures[SHOULDERY].X, 
//                                       _moCapMeasures[SHOULDERY].Y, 
//                                       _moCapMeasures[SHOULDERY].Z);
//   
//   assemblies[SHOULDERZARM]->SetOrigin(_moCapMeasures[SHOULDERZ].X, 
//                                       _moCapMeasures[SHOULDERZ].Y, 
//                                       _moCapMeasures[SHOULDERZ].Z);

  return;
}


vector<vtkActor*>
ObjectMoCap::makeMocap(map<int, Point3D>& moCapMeasures){
 
  vector<vtkPolyDataAlgorithm*> objects;
  vector<vtkActor*> actors;
  vector<vtkPolyDataMapper *> mappers;
  vector<vtkAssembly*> assemblies;
  
  double spallaZx = moCapMeasures[SHOULDERZ].X/*root.X+(_moCapMeasures[SHOULDERZ].X)*/, spallaZy=moCapMeasures[SHOULDERZ].Y/*root.Y+(_moCapMeasures[SHOULDERZ].Y)*/, spallaZz = moCapMeasures[SHOULDERZ].Z/* root.Z+(_moCapMeasures[SHOULDERZ].Z)*/;
  double spallaYx =moCapMeasures[SHOULDERY].X/*root.X+(_moCapMeasures[SHOULDERY].X)*/ ,spallaYy=moCapMeasures[SHOULDERY].Y/*root.Y+(_moCapMeasures[SHOULDERY].Y)*/,spallaYz=moCapMeasures[SHOULDERY].Z/*root.Z+(_moCapMeasures[SHOULDERY].Z)*/;
  double spallaXx=moCapMeasures[SHOULDERX].X/*root.X+(_moCapMeasures[SHOULDERX].X)*/,spallaXy=moCapMeasures[SHOULDERX].Y/*root.Y+(_moCapMeasures[SHOULDERX].Y)*/,spallaXz=/*root.Z+(_moCapMeasures[SHOULDERX].Z)*/moCapMeasures[SHOULDERX].Z;
   
  double elbowXx = /*root.X+_moCapMeasures[UPPERARMMOCAP].X+_moCapMeasures[ELBOWX].X*/moCapMeasures[ELBOWX].X, elbowXy = /*root.Y+_moCapMeasures[UPPERARMMOCAP].Y+_moCapMeasures[ELBOWX].Y*/moCapMeasures[ELBOWX].Y, elbowXz =/* root.Z+_moCapMeasures[UPPERARMMOCAP].Z+_moCapMeasures[ELBOWX].Z*/moCapMeasures[ELBOWX].Z;

  double elbowYx = moCapMeasures[ELBOWY].X/*root.X+_moCapMeasures[UPPERARMMOCAP].X+_moCapMeasures[ELBOWY].X*/, elbowYy =/* root.Y+_moCapMeasures[UPPERARMMOCAP].Y+_moCapMeasures[ELBOWY].Y*/moCapMeasures[ELBOWY].Y, elbowYz = /*root.Z+_moCapMeasures[UPPERARMMOCAP].Z+_moCapMeasures[ELBOWY].Z*/moCapMeasures[ELBOWY].Z;

  double wristXx = /*root.X + _moCapMeasures[UPPERARMMOCAP].X+_moCapMeasures[LOWERARMMOCAP].X+ _moCapMeasures[WRISTX].X*/moCapMeasures[WRISTX].X, wristXy = /*root.Y+_moCapMeasures[UPPERARMMOCAP].Y+_moCapMeasures[LOWERARMMOCAP].Y+ _moCapMeasures[WRISTX].Y*/moCapMeasures[WRISTX].Y, wristXz = /*root.Z+_moCapMeasures[UPPERARMMOCAP].Z+_moCapMeasures[LOWERARMMOCAP].Z+ _moCapMeasures[WRISTX].Z*/moCapMeasures[WRISTX].Z;

  double knuckleXx = /*root.X+_moCapMeasures[UPPERARMMOCAP].X+_moCapMeasures[LOWERARMMOCAP].X+_moCapMeasures[HANDMOCAP].X+_moCapMeasures[KNUCKLEX].X*/moCapMeasures[KNUCKLEX].X, knuckleXy = /*root.Y+_moCapMeasures[UPPERARMMOCAP].Y+_moCapMeasures[LOWERARMMOCAP].Y+_moCapMeasures[HANDMOCAP].Y+_moCapMeasures[KNUCKLEX].Y*/moCapMeasures[KNUCKLEX].Y, knuckleXz = /*root.Z+_moCapMeasures[UPPERARMMOCAP].Z+_moCapMeasures[LOWERARMMOCAP].Z+_moCapMeasures[HANDMOCAP].Z+_moCapMeasures[KNUCKLEX].Z*/moCapMeasures[KNUCKLEX].Z;

  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[FINGERMOCAP])->SetXLength(0.0);
  static_cast<vtkCubeSource*>(objects[FINGERMOCAP])->SetYLength(0.0);
  static_cast<vtkCubeSource*>(objects[FINGERMOCAP])->SetZLength(0.0);
  mappers[FINGERMOCAP]->SetInput(objects[FINGERMOCAP]->GetOutput());
  actors[FINGERMOCAP]->SetMapper(mappers[FINGERMOCAP]);
  actors[FINGERMOCAP]->GetProperty()->SetColor(1.0,1.0,1.0);
//   actors[FINGERMOCAP]->SetPosition(knuckleX,knuckleY-jointRadius-FingerYLength/2,knuckleZ);
//   actors[FINGERMOCAP]->SetOrigin(knuckleX,knuckleY-jointRadius,knuckleZ);
//   actors[FINGERMOCAP]->GetProperty()->SetColor(/*1.0,1.0,1.0*/fancy);
//    DEBOUT(("Actor FINGER %d (%.2f,%.2f,%.2f)\n",FINGERMOCAP,(actors[FINGERMOCAP]->GetPosition())[0],(actors[FINGERMOCAP]->GetPosition())[1],(actors[FINGERMOCAP]->GetPosition())[2]));



   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetRadius(jointRadius);
  mappers[KNUCKLEX]->SetInput(objects[KNUCKLEX]->GetOutput());
  actors[KNUCKLEX]->SetMapper(mappers[KNUCKLEX]);
  actors[KNUCKLEX]->SetPosition(knuckleXx,knuckleXy,knuckleXz);
  actors[KNUCKLEX]->SetOrigin(knuckleXx,knuckleXy,knuckleXz);
  actors[KNUCKLEX]->GetProperty()->SetColor(1.0,1.0,1.0/*fancy*/);
   DEBOUT(("Actor MoCap KNUCKLEX %d (%.2f,%.2f,%.2f)\n",KNUCKLEX,(actors[KNUCKLEX]->GetPosition())[0],(actors[KNUCKLEX]->GetPosition())[1],(actors[KNUCKLEX]->GetPosition())[2]));
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[HANDMOCAP])->SetXLength(/*_moCapMeasures[HANDMOCAP].X*/0);
  static_cast<vtkCubeSource*>(objects[HANDMOCAP])->SetYLength(/*_moCapMeasures[HANDMOCAP].Y*/0);
  static_cast<vtkCubeSource*>(objects[HANDMOCAP])->SetZLength(/*_moCapMeasures[HANDMOCAP].Z*/0);
  mappers[HANDMOCAP]->SetInput(objects[HANDMOCAP]->GetOutput());
  actors[HANDMOCAP]->SetMapper(mappers[HANDMOCAP]);
  actors[HANDMOCAP]->GetProperty()->SetColor(1.0,1.0,1.0);
//   actors[HANDMOCAP]->SetPosition(_moCapMeasures[ELBOWY].X,_moCapMeasures[WRISTX].Y-jointRadius-_moCapMeasures[HANDMOCAP].Y/2,_moCapMeasures[WRISTX].Z);
//   actors[HANDMOCAP]->SetOrigin(_moCapMeasures[ELBOWY].X,_moCapMeasures[WRISTX].Y,_moCapMeasures[WRISTX].Z);

  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetRadius(jointRadius);
  mappers[WRISTX]->SetInput(objects[WRISTX]->GetOutput());
  actors[WRISTX]->SetMapper(mappers[WRISTX]);
  actors[WRISTX]->SetPosition( wristXx, wristXy, wristXz);
  actors[WRISTX]->SetOrigin(wristXx, wristXy, wristXz);
  actors[WRISTX]->GetProperty()->SetColor(1.0,1.0,1.0/*fancy*/);
  DEBOUT(("Actor MoCap WRISTX %d (%.2f,%.2f,%.2f)\n",WRISTX,(actors[WRISTX]->GetPosition())[0],(actors[WRISTX]->GetPosition())[1],(actors[WRISTX]->GetPosition())[2]));

    objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[LOWERARMMOCAP])->SetXLength(/*_moCapMeasures[LOWERARMMOCAP].X*/0);
  static_cast<vtkCubeSource*>(objects[LOWERARMMOCAP])->SetYLength(/*_moCapMeasures[LOWERARMMOCAP].Y*/0);
  static_cast<vtkCubeSource*>(objects[LOWERARMMOCAP])->SetZLength(/*_moCapMeasures[LOWERARMMOCAP].Z*/0);
  mappers[LOWERARMMOCAP]->SetInput(objects[LOWERARMMOCAP]->GetOutput());
  actors[LOWERARMMOCAP]->SetMapper(mappers[LOWERARMMOCAP]);
//   actors[LOWERARMMOCAP]-> SetPosition(_moCapMeasures[ELBOWY].X,_moCapMeasures[ELBOWY].Y-jointRadius-_moCapMeasures[LOWERARMMOCAP].Y/2,_moCapMeasures[ELBOWY].Z);
//   actors[LOWERARMMOCAP]->SetOrigin(_moCapMeasures[ELBOWY].X,_moCapMeasures[ELBOWY].Y-jointRadius-_moCapMeasures[LOWERARMMOCAP].Y,_moCapMeasures[ELBOWY].Z);

   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetRadius(jointRadius);
  mappers[ELBOWY]->SetInput(objects[ELBOWY]->GetOutput());
  actors[ELBOWY]->SetMapper(mappers[ELBOWY]);
  actors[ELBOWY]->SetPosition( elbowYx, elbowYy, elbowYz);
  actors[ELBOWY]->SetOrigin(elbowYx, elbowYy, elbowYz);
  actors[ELBOWY]->GetProperty()->SetColor(1.0,1.0,1.0/*fancy*/);
  DEBOUT(("Actor MoCap ELBOWY %d (%.2f,%.2f,%.2f)\n",ELBOWY,(actors[ELBOWY]->GetPosition())[0],(actors[ELBOWY]->GetPosition())[1],(actors[ELBOWY]->GetPosition())[2]));
  
     objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetRadius(jointRadius);
  mappers[ELBOWX]->SetInput(objects[ELBOWX]->GetOutput());
  actors[ELBOWX]->SetMapper(mappers[ELBOWX]);
  actors[ELBOWX]->SetPosition( elbowXx, elbowXy, elbowXz);
  actors[ELBOWX]->SetOrigin(elbowXx, elbowXy, elbowXz);
  actors[ELBOWX]->GetProperty()->SetColor(1.0,1.0,1.0/*fancy*/);
  DEBOUT(("Actor MoCap ELBOWX %d (%.2f,%.2f,%.2f)\n",ELBOWX,(actors[ELBOWX]->GetPosition())[0],(actors[ELBOWX]->GetPosition())[1],(actors[ELBOWX]->GetPosition())[2]));
  

   //UPPERARMMOCAP
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[UPPERARMMOCAP])->SetXLength(/*_moCapMeasures[UPPERARMMOCAP].X*/0);
  static_cast<vtkCubeSource*>(objects[UPPERARMMOCAP])->SetYLength(/*_moCapMeasures[UPPERARMMOCAP].Y*/0);
  static_cast<vtkCubeSource*>(objects[UPPERARMMOCAP])->SetZLength(/*_moCapMeasures[UPPERARMMOCAP].Z*/0);
  mappers[UPPERARMMOCAP]->SetInput(objects[UPPERARMMOCAP]->GetOutput());
  actors[UPPERARMMOCAP]->SetMapper(mappers[UPPERARMMOCAP]);
//   actors[UPPERARMMOCAP]->SetPosition(_moCapMeasures[SHOULDERX].X, _moCapMeasures[SHOULDERX].Y-jointRadius-_moCapMeasures[UPPERARMMOCAP].Y/2, _moCapMeasures[SHOULDERX].Z);
//   actors[UPPERARMMOCAP]->SetOrigin(_moCapMeasures[SHOULDERX].X, _moCapMeasures[SHOULDERX].Y-jointRadius-_moCapMeasures[UPPERARMMOCAP].Y, _moCapMeasures[SHOULDERX].Z);

  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetPhiResolution(25);
  mappers[SHOULDERX]->SetInput(objects[SHOULDERX]->GetOutput());
  actors[SHOULDERX]->SetMapper(mappers[SHOULDERX]);
  actors[SHOULDERX]->SetPosition(spallaXx, spallaXy, spallaXz);
  actors[SHOULDERX]->SetOrigin(spallaXx, spallaXy, spallaXz);
  actors[SHOULDERX]->GetProperty()->SetColor(1.0,1.0,1.0/*fancy*/);
   DEBOUT(("Actor MoCap SHOULDERX %d (%.2f,%.2f,%.2f)\n",SHOULDERX,(actors[SHOULDERX]->GetPosition())[0],(actors[SHOULDERX]->GetPosition())[1],(actors[SHOULDERX]->GetPosition())[2]));



  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetPhiResolution(25);
  mappers[SHOULDERY]->SetInput(objects[SHOULDERY]->GetOutput());
  actors[SHOULDERY]->SetMapper(mappers[SHOULDERY]);
  actors[SHOULDERY]->SetPosition(spallaYx, spallaYy, spallaYz);
  actors[SHOULDERY]->SetOrigin(spallaYx, spallaYy, spallaYz);
  actors[SHOULDERY]->GetProperty()->SetColor(/*fancy*/1.0,1.0,1.0);
  DEBOUT(("Actor MoCap SHOULDERY %d (%.2f,%.2f,%.2f)\n",SHOULDERY,(actors[SHOULDERY]->GetPosition())[0],(actors[SHOULDERY]->GetPosition())[1],(actors[SHOULDERY]->GetPosition())[2]));


   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetPhiResolution(25);
  mappers[SHOULDERZ]->SetInput(objects[SHOULDERZ]->GetOutput());
  actors[SHOULDERZ]->SetMapper(mappers[SHOULDERZ]);
  actors[SHOULDERZ]->SetPosition(spallaZx, spallaZy, spallaZz);
  actors[SHOULDERZ]->SetOrigin(spallaZx, spallaZy, spallaZz);
actors[SHOULDERZ]->GetProperty()->SetColor(1.0,1.0,1.0);
  DEBOUT(("Actor MoCap SHOULDERZ %d (%.2f,%.2f,%.2f)\n",SHOULDERZ,(actors[SHOULDERZ]->GetPosition())[0],(actors[SHOULDERZ]->GetPosition())[1],(actors[SHOULDERZ]->GetPosition())[2]));

  

   
return actors;
}

void 
ObjectMoCap::assemblyMoCapActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& assemblies, map<int, Point3D>& moCapMeasures, map<int, Point3D>& armMeasures){

  assemblies .push_back(vtkAssembly::New());
  assemblies[FINGERMOCAP]->AddPart(actors[FINGERMOCAP]);

  for(int i=1; i<static_cast<int>(actors.size()); ++i){
    assemblies .push_back(vtkAssembly::New());
    assemblies[i]->AddPart(assemblies[i-1]);
    assemblies[i]->AddPart(actors[i]);
  }
  
  assemblies[FINGERMOCAP]->SetOrigin(moCapMeasures[KNUCKLEX].X, 
                                  moCapMeasures[KNUCKLEX].Y, 
                                  moCapMeasures[KNUCKLEX].Z);


  assemblies[KNUCKLEX]->SetOrigin(moCapMeasures[KNUCKLEX].X, 
                                  moCapMeasures[KNUCKLEX].Y, 
                                  moCapMeasures[KNUCKLEX].Z);

  assemblies[HANDMOCAP]->SetOrigin(moCapMeasures[WRISTX].X, 
                              moCapMeasures[WRISTX].Y, 
                              moCapMeasures[WRISTX].Z);

  assemblies[WRISTX]->SetOrigin(moCapMeasures[WRISTX].X, 
                                moCapMeasures[WRISTX].Y, 
                                moCapMeasures[WRISTX].Z);

  assemblies[LOWERARMMOCAP]->SetOrigin(moCapMeasures[ELBOWY].X,
                                  moCapMeasures[ELBOWY].Y,
                                  moCapMeasures[ELBOWY].Z);

  assemblies[ELBOWY]->SetOrigin(moCapMeasures[ELBOWY].X,
                                moCapMeasures[ELBOWY].Y,
                                moCapMeasures[ELBOWY].Z);

  assemblies[ELBOWX]->SetOrigin(moCapMeasures[ELBOWX].X, 
                                moCapMeasures[ELBOWX].Y,
                                moCapMeasures[ELBOWX].Z);

  assemblies[UPPERARMMOCAP]->SetOrigin(moCapMeasures[SHOULDERX].X,
                                  moCapMeasures[SHOULDERX].Y,
                                  moCapMeasures[SHOULDERX].Z);

  assemblies[SHOULDERX]->SetOrigin(moCapMeasures[SHOULDERX].X,
                                   moCapMeasures[SHOULDERX].Y,
                                   moCapMeasures[SHOULDERX].Z);

  assemblies[SHOULDERY]->SetOrigin(moCapMeasures[SHOULDERY].X, 
                                   //moCapMeasures[SHOULDERY].Y,
                                   //IMPORTANTE
                                   armMeasures[5/*i.e.SHOULDERYARM*/].Y, 
                                   moCapMeasures[SHOULDERY].Z);

  assemblies[SHOULDERZ]->SetOrigin(moCapMeasures[SHOULDERZ].X, 
                                   moCapMeasures[SHOULDERZ].Y, 
                                   moCapMeasures[SHOULDERZ].Z);
 
  return;
}


void 
ObjectMoCap::addNodes(vector<vtkAssembly*>& moCapAssembliesRight, vector<vtkAssembly*>& armAssembliesRight,vector<vtkAssembly*>& moCapAssembliesLeft, vector<vtkAssembly*>& armAssembliesLeft){

  vtkAssembly* root = vtkAssembly::New();
//     int ELBOWYARM=5, ELBOWXARM=6,SHOULDERXARM=8, SHOULDERYARM=9,SHOULDERZARM=10;

  root->AddPart(moCapAssembliesRight[SHOULDERZ]);
  root->AddPart(armAssembliesRight[SHOULDERZ]);

  root->AddPart(moCapAssembliesLeft[SHOULDERZ]);
  root->AddPart(armAssembliesLeft[SHOULDERZ]);

//   root->AddPart(armAssemblies[SHOULDERYARM]);
//   root->AddPart(armAssemblies[SHOULDERXARM]);
//   root->AddPart(armAssemblies[ELBOWXARM]);
//   root->AddPart(armAssemblies[ELBOWYARM]);
//   root->AddPart(armAssemblies[WRIST]);
//   root->AddPart(armAssemblies[KNUCKLE]);

//   moCapAssemblies[SHOULDERZ]->AddPart(armAssemblies[SHOULDERZARM]);
//   moCapAssemblies[SHOULDERY]->AddPart(armAssemblies[SHOULDERYARM]);
//   moCapAssemblies[SHOULDERX]->AddPart(armAssemblies[SHOULDERXARM]);
// 
//   moCapAssemblies[ELBOWX]->AddPart(armAssemblies[ELBOWXARM]);
//   moCapAssemblies[ELBOWY]->AddPart(armAssemblies[ELBOWYARM]);
// 
//   moCapAssemblies[WRISTX]->AddPart(armAssemblies[WRIST]);
//    moCapAssemblies[KNUCKLEX]->AddPart(armAssemblies[KNUCKLE]);

  

  addNode(root,0);

  addNode(moCapAssembliesLeft[SHOULDERZ],5001,armAssembliesLeft[SHOULDERZ]);
  addNode(moCapAssembliesLeft[SHOULDERY],5002,armAssembliesLeft[SHOULDERY]);
  addNode(moCapAssembliesLeft[SHOULDERX],5000,armAssembliesLeft[SHOULDERX]);
//   
  addNode(moCapAssembliesLeft[ELBOWX],5003,armAssembliesLeft[ELBOWX]);
  addNode(moCapAssembliesLeft[ELBOWY],5004,armAssembliesLeft[ELBOWY]);
//   
  addNode(moCapAssembliesLeft[WRISTX],5005,armAssembliesLeft[WRISTX]);
  addNode(moCapAssembliesLeft[KNUCKLEX],5006,armAssembliesLeft[KNUCKLEX]);



  addNode(moCapAssembliesRight[SHOULDERZ],6001,armAssembliesRight[SHOULDERZ]);
  addNode(moCapAssembliesRight[SHOULDERY],6002,armAssembliesRight[SHOULDERY]);
  addNode(moCapAssembliesRight[SHOULDERX],6000,armAssembliesRight[SHOULDERX]);
//   
  addNode(moCapAssembliesRight[ELBOWX],6003,armAssembliesRight[ELBOWX]);
  addNode(moCapAssembliesRight[ELBOWY],6004,armAssembliesRight[ELBOWY]);
//   
  addNode(moCapAssembliesRight[WRISTX],6005,armAssembliesRight[WRISTX]);
  addNode(moCapAssembliesRight[KNUCKLEX],6006,armAssembliesRight[KNUCKLEX]);


}

// bool ObjectMoCap::rotatePartAngle(int id, double angle, AxesRotations& axes) throw (ExceptionIdOutOfRange){
//   Object3D::rotatePartAngle(id, angle, axes);
//    map<int,list_dRobot>::iterator it = _robotList.find(id);
//   if(it==_robotList.end()) {
//     char temp[128];
//     sprintf(temp,"%d",id);
//     throw ExceptionIdOutOfRange(string(DEBPOS)+string(temp)+string(" Part not found"));
//   }
//   
//   return this->rotatePartAngles(id,(axes.X)*angle,(axes.Y)*angle,(axes.Z)*angle);
// }

bool 
ObjectMoCap::rotatePartAngles(int id, double angleX, double angleY, double angleZ) throw (ExceptionIdOutOfRange){
  map<int,list_dRobot>::iterator it = _robotList.find(id);
  if(it==_robotList.end()) {
    char temp[128];
    sprintf(temp,"%d",id);
    throw ExceptionIdOutOfRange(string(DEBPOS)+string(temp)+string(" Part not found"));
  }
  //Solo angleX o angleY o angleZ è diverso da 0
  int currentValue = static_cast<int>(DEGREETOVALUE(angleX+angleY+angleZ));
//   DEBOUT(("%d : (%.2f,%.2f,%.2f) %d\n",id,angleX,angleY,angleZ,currentValue));
  if(/*currentValue!=it->second.lastValue*/true){
    (it->second.piece)->SetOrientation(angleX,angleY,angleZ);
    
    if((it->second.armPiece0)){
      (it->second.armPiece0)->SetOrientation(angleX,angleY,angleZ);
//       DEBOUT(("Orientation %d (%.2f,%.2f,%.2f)\n",id,it->second.piece->GetOrientation()[0]-it->second.armPiece0->GetOrientation()[0],it->second.piece->GetOrientation()[1]-it->second.armPiece0->GetOrientation()[1],it->second.piece->GetOrientation()[2]-it->second.armPiece0->GetOrientation()[3]));  
//       DEBOUT(("Angles ObjectMoCap %d (%f,%f,%f)\n",id,angleX,angleY,angleZ));
    }
    if((it->second.armPiece1)){
      (it->second.armPiece1)->SetOrientation(angleX,angleY,angleZ);
//       DEBOUT(("Angles Object3D %d (%f,%f,%f)\n",id,angleX,angleY,angleZ));
    }
    
    it->second.lastValue = currentValue;
//     DEBOUT(("Angles ObjectMoCap %d (%f,%f,%f)\n",id,angleX,angleY,angleZ));
    return true;
  } 
  else return false;
}
