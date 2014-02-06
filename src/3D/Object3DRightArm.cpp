#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include "Object3D.h"

Object3DRightArm::Object3DRightArm(Point3D root){
  
  makeArm(root);

  makeRoot();
}

void
Object3DRightArm::makeArm(Point3D root){
  
  vector<vtkPolyDataAlgorithm*> objects;
  vector<vtkActor*> actors;
  vector<vtkPolyDataMapper *> mappers;
  vector<vtkAssembly*> assemblies;
  
  double ShoulderXCenter=root.X , ShoulderYCenter=root.Y, ShoulderZCenter=root.Z;
  //UpperArm
  double ArmXLength=0.1, ArmYLength=1.5,  ArmZLength= 0.1;
  //Elbow
  double ElbowXCenter = ShoulderXCenter, ElbowYCenter = ShoulderYCenter-ArmYLength-jointRadius-jointRadius, ElbowZCenter = ShoulderZCenter;
  //LowerArm
  double LowerArmXLength=ArmXLength, LowerArmYLength=ArmYLength,  LowerArmZLength= ArmZLength;
  //Wrist
  double WristXCenter= ElbowXCenter, WristYCenter = ElbowYCenter-LowerArmYLength-jointRadius-jointRadius, WristZCenter = ElbowZCenter;
  //Hand
  double HandXLength=0.5, HandYLength=0.2,  HandZLength= LowerArmZLength;
  //Knuckle
  double KnuckleXCenter = WristXCenter-0.15, KnuckleYCenter = WristYCenter-HandYLength-jointRadius-jointRadius,KnuckleZCenter = WristZCenter;
  //Finger
  double FingerXLength=0.1, FingerYLength=0.3,  FingerZLength= 0.1;
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[FINGER])->SetXLength(FingerXLength);
  static_cast<vtkCubeSource*>(objects[FINGER])->SetYLength(FingerYLength);
  static_cast<vtkCubeSource*>(objects[FINGER])->SetZLength(FingerZLength);
  mappers[FINGER]->SetInput(objects[FINGER]->GetOutput());
  actors[FINGER]->SetMapper(mappers[FINGER]);
  actors[FINGER]->SetPosition(KnuckleXCenter,KnuckleYCenter-jointRadius-FingerYLength/2,KnuckleZCenter);
  actors[FINGER]->SetOrigin(KnuckleXCenter,KnuckleYCenter-jointRadius,KnuckleZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEX])->SetRadius(jointRadius);
  mappers[KNUCKLEX]->SetInput(objects[KNUCKLEX]->GetOutput());
  actors[KNUCKLEX]->SetMapper(mappers[KNUCKLEX]);
  actors[KNUCKLEX]->SetPosition(KnuckleXCenter,KnuckleYCenter,WristZCenter);
  actors[KNUCKLEX]->SetOrigin(KnuckleXCenter,KnuckleYCenter,KnuckleZCenter);
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[HAND])->SetXLength(HandXLength);
  static_cast<vtkCubeSource*>(objects[HAND])->SetYLength(HandYLength);
  static_cast<vtkCubeSource*>(objects[HAND])->SetZLength(HandZLength);
  mappers[HAND]->SetInput(objects[HAND]->GetOutput());
  actors[HAND]->SetMapper(mappers[HAND]);
  actors[HAND]->SetPosition(WristXCenter,WristYCenter-jointRadius-HandYLength/2,WristZCenter);
  actors[HAND]->SetOrigin(WristXCenter,WristYCenter-jointRadius,WristZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTX])->SetRadius(jointRadius);
  mappers[WRISTX]->SetInput(objects[WRISTX]->GetOutput());
  actors[WRISTX]->SetMapper(mappers[WRISTX]);
  actors[WRISTX]->SetPosition(WristXCenter,WristYCenter,WristZCenter);
  actors[WRISTX]->SetOrigin(WristXCenter,WristYCenter,WristZCenter);
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[LOWERARM])->SetXLength(LowerArmXLength);
  static_cast<vtkCubeSource*>(objects[LOWERARM])->SetYLength(LowerArmYLength);
  static_cast<vtkCubeSource*>(objects[LOWERARM])->SetZLength(LowerArmZLength);
  mappers[LOWERARM]->SetInput(objects[LOWERARM]->GetOutput());
  actors[LOWERARM]->SetMapper(mappers[LOWERARM]);
  actors[LOWERARM]->SetPosition(ElbowXCenter,ElbowYCenter-jointRadius-LowerArmYLength/2,ElbowZCenter);
  actors[LOWERARM]->SetOrigin(ElbowXCenter, ElbowYCenter-jointRadius, ElbowZCenter);
  
  //ELBOW
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWY])->SetRadius(jointRadius);
  mappers[ELBOWY]->SetInput(objects[ELBOWY]->GetOutput());
  actors[ELBOWY]->SetMapper(mappers[ELBOWY]);
  actors[ELBOWY]->SetPosition(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  actors[ELBOWY]->SetOrigin(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWX])->SetRadius(jointRadius);
  mappers[ELBOWX]->SetInput(objects[ELBOWX]->GetOutput());
  actors[ELBOWX]->SetMapper(mappers[ELBOWX]);
  actors[ELBOWX]->SetPosition(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  actors[ELBOWX]->SetOrigin(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  
  //UPPERARM
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[UPPERARM])->SetXLength(ArmXLength);
  static_cast<vtkCubeSource*>(objects[UPPERARM])->SetYLength(ArmYLength);
  static_cast<vtkCubeSource*>(objects[UPPERARM])->SetZLength(ArmZLength);
  mappers[UPPERARM]->SetInput(objects[UPPERARM]->GetOutput());
  actors[UPPERARM]->SetMapper(mappers[UPPERARM]);
  actors[UPPERARM]->SetPosition(ShoulderXCenter, ShoulderYCenter-jointRadius-ArmYLength/2, ShoulderZCenter);
  actors[UPPERARM]->SetOrigin(ShoulderXCenter, ShoulderYCenter-jointRadius, ShoulderZCenter);
   
  //SHOULDER
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERX])->SetPhiResolution(25);
  mappers[SHOULDERX]->SetInput(objects[SHOULDERX]->GetOutput());
  actors[SHOULDERX]->SetMapper(mappers[SHOULDERX]);
  actors[SHOULDERX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERY])->SetPhiResolution(25);
  mappers[SHOULDERY]->SetInput(objects[SHOULDERY]->GetOutput());
  actors[SHOULDERY]->SetMapper(mappers[SHOULDERY]);
  actors[SHOULDERY]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERY]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
   objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERZ])->SetPhiResolution(25);
  mappers[SHOULDERZ]->SetInput(objects[SHOULDERZ]->GetOutput());
  actors[SHOULDERZ]->SetMapper(mappers[SHOULDERZ]);
  actors[SHOULDERZ]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERZ]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  assemblyActors(actors,assemblies);
}

void
Object3DRightArm::assemblyActors(vector<vtkActor*>& actors,vector<vtkAssembly*>& assemblies){
  
  assemblies .push_back(vtkAssembly::New());
  assemblies[FINGER]->AddPart(actors[FINGER]);
  
//   assemblies .push_back(vtkAssembly::New());
// //   assemblies[KNUCKLEX]->AddPart(actors[FINGER]);
// //   assemblies[KNUCKLEX]->AddPart(assemblies[FINGER]);
// //   
//   
//    assemblies .push_back(vtkAssembly::New());
//     assemblies .push_back(vtkAssembly::New());
//    assemblies .push_back(vtkAssembly::New());
//     assemblies .push_back(vtkAssembly::New());
//     //UPPERARM
//   assemblies .push_back(vtkAssembly::New());
//   assemblies[UPPERARM]->AddPart(actors[UPPERARM]);
//   
// //SHOULDERX
//   assemblies.push_back(vtkAssembly::New());
//   assemblies[SHOULDERX]->AddPart(actors[SHOULDERX]);
//   assemblies[SHOULDERX]->AddPart(assemblies[UPPERARM]);
// 
//   //SHOULDERY
//   assemblies .push_back(vtkAssembly::New());
//   assemblies[SHOULDERY]->AddPart(actors[SHOULDERY]);
//   assemblies[SHOULDERY]->AddPart(assemblies[SHOULDERX]);
// 
//   //SHOULDERZ
//   assemblies .push_back(vtkAssembly::New());
//   assemblies[SHOULDERZ]->AddPart(actors[SHOULDERZ]);
//   assemblies[SHOULDERZ]->AddPart(assemblies[SHOULDERY]);

  
  for(int i=1; i<static_cast<int>(actors.size()); ++i){
    assemblies .push_back(vtkAssembly::New());
    assemblies[i]->AddPart(assemblies[i-1]);
    assemblies[i]->AddPart(actors[i]);
  }
  
  assemblies[FINGER]->SetOrigin(actors[KNUCKLEX]->GetOrigin());
  assemblies[KNUCKLEX]->SetOrigin(actors[KNUCKLEX]->GetOrigin());
  assemblies[HAND]->SetOrigin(actors[WRISTX]->GetOrigin());
  assemblies[WRISTX]->SetOrigin(actors[WRISTX]->GetOrigin());
  assemblies[LOWERARM]->SetOrigin(actors[ELBOWX]->GetOrigin());
  assemblies[ELBOWY]->SetOrigin(actors[ELBOWY]->GetOrigin());
  assemblies[ELBOWX]->SetOrigin(actors[ELBOWX]->GetOrigin());
  assemblies[UPPERARM]->SetOrigin(actors[SHOULDERX]->GetOrigin());
  assemblies[SHOULDERX]->SetOrigin(actors[SHOULDERX]->GetOrigin());
  assemblies[SHOULDERY]->SetOrigin(actors[SHOULDERY]->GetOrigin());
  assemblies[SHOULDERZ]->SetOrigin(actors[SHOULDERZ]->GetOrigin());
 
  
  addNode(assemblies[SHOULDERZ],6000/*,AxesRotations(0,0,-1)*/);
  addNode(assemblies[SHOULDERY],6001/*,AxesRotations(0,1,0)*/);
  addNode(assemblies[SHOULDERX],6002/*,AxesRotations(-1,0,0)*/);
  
  addNode(assemblies[ELBOWX],6003/*,AxesRotations(-1,0,0)*/);
  addNode(assemblies[ELBOWY],6004/*,AxesRotations(0,1,0)*/);
  
  addNode(assemblies[WRISTX],6005/*,AxesRotations(-1,0,0)*/);
  addNode(assemblies[KNUCKLEX],6006/*,AxesRotations(1,0,0)*/);
  
  
  (_robotList[6000]).initValue = 138;
  (_robotList[6001]).initValue = 139;
  (_robotList[6002]).initValue = 125;
  (_robotList[6003]).initValue = 127;
  (_robotList[6004]).initValue = 106;
  (_robotList[6005]).initValue = 115;
  (_robotList[6006]).initValue = 117;
  
  return;
}
