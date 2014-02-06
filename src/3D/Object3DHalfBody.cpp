#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include "Object3D.h"

Object3DHalfBody::Object3DHalfBody(Point3D root){
  

  makeHalfBody(root);

  
  makeRoot();
}
  
void 
Object3DHalfBody::makeHalfBody(Point3D root){

  
  vector<vtkPolyDataAlgorithm*> objects;
  vector<vtkActor*> actors;
  vector<vtkActor*> actorsLeftArm;
  vector<vtkActor*> actorsRightArm;
  vector<vtkPolyDataMapper *> mappers;
  
  double RootXCenter=root.X , RootYCenter=root.Y, RootZCenter=root.Z;

  double BachelorXLength=1.5, BachelorYLength=0.1,  BachelorZLength= 0.1;
  
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[BACHELOR])->SetXLength(BachelorXLength);
  static_cast<vtkCubeSource*>(objects[BACHELOR])->SetYLength(BachelorYLength);
  static_cast<vtkCubeSource*>(objects[BACHELOR])->SetZLength(BachelorZLength);
  mappers[BACHELOR]->SetInput(objects[BACHELOR]->GetOutput());
  actors[BACHELOR]->SetMapper(mappers[BACHELOR]);
  actors[BACHELOR]->SetPosition(RootXCenter,RootYCenter,RootZCenter);
  actors[BACHELOR]->SetOrigin(RootXCenter,RootYCenter,RootZCenter);
  
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ROOT])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ROOT])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ROOT])->SetRadius(jointRadius);
  mappers[ROOT]->SetInput(objects[ROOT]->GetOutput());
  actors[ROOT]->SetMapper(mappers[ROOT]);
  actors[ROOT]->SetPosition(RootXCenter,RootYCenter,RootZCenter);
  actors[ROOT]->SetOrigin(RootXCenter,RootYCenter,RootZCenter);
  
  
  actorsLeftArm = makeLeftArm(Point3D(RootXCenter+BachelorXLength/2.0,RootYCenter,RootZCenter));
  
  actorsRightArm=makeRightArm(Point3D(RootXCenter-BachelorXLength/2.0,RootYCenter,RootZCenter));
  
  
  
  assemblyActors(actors,actorsLeftArm,actorsRightArm);
}


vector<vtkActor*> 
Object3DHalfBody::makeLeftArm(Point3D root){
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
  double KnuckleXCenter = WristXCenter+0.15, KnuckleYCenter = WristYCenter-HandYLength-jointRadius-jointRadius,KnuckleZCenter = WristZCenter;
  //Finger
  double FingerXLength=0.1, FingerYLength=0.3,  FingerZLength= 0.1;
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[FINGERSX])->SetXLength(FingerXLength);
  static_cast<vtkCubeSource*>(objects[FINGERSX])->SetYLength(FingerYLength);
  static_cast<vtkCubeSource*>(objects[FINGERSX])->SetZLength(FingerZLength);
  mappers[FINGERSX]->SetInput(objects[FINGERSX]->GetOutput());
  actors[FINGERSX]->SetMapper(mappers[FINGERSX]);
  actors[FINGERSX]->SetPosition(KnuckleXCenter,KnuckleYCenter-jointRadius-FingerYLength/2,KnuckleZCenter);
  actors[FINGERSX]->SetOrigin(KnuckleXCenter,KnuckleYCenter-jointRadius,KnuckleZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[KNUCKLEXSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEXSX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEXSX])->SetRadius(jointRadius);
  mappers[KNUCKLEXSX]->SetInput(objects[KNUCKLEXSX]->GetOutput());
  actors[KNUCKLEXSX]->SetMapper(mappers[KNUCKLEXSX]);
  actors[KNUCKLEXSX]->SetPosition(KnuckleXCenter,KnuckleYCenter,WristZCenter);
  actors[KNUCKLEXSX]->SetOrigin(KnuckleXCenter,KnuckleYCenter,KnuckleZCenter);
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[HANDSX])->SetXLength(HandXLength);
  static_cast<vtkCubeSource*>(objects[HANDSX])->SetYLength(HandYLength);
  static_cast<vtkCubeSource*>(objects[HANDSX])->SetZLength(HandZLength);
  mappers[HANDSX]->SetInput(objects[HANDSX]->GetOutput());
  actors[HANDSX]->SetMapper(mappers[HANDSX]);
  actors[HANDSX]->SetPosition(WristXCenter,WristYCenter-jointRadius-HandYLength/2,WristZCenter);
  actors[HANDSX]->SetOrigin(WristXCenter,WristYCenter-jointRadius,WristZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[WRISTXSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTXSX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTXSX])->SetRadius(jointRadius);
  mappers[WRISTXSX]->SetInput(objects[WRISTXSX]->GetOutput());
  actors[WRISTXSX]->SetMapper(mappers[WRISTXSX]);
  actors[WRISTXSX]->SetPosition(WristXCenter,WristYCenter,WristZCenter);
  actors[WRISTXSX]->SetOrigin(WristXCenter,WristYCenter,WristZCenter);
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[LOWERARMSX])->SetXLength(LowerArmXLength);
  static_cast<vtkCubeSource*>(objects[LOWERARMSX])->SetYLength(LowerArmYLength);
  static_cast<vtkCubeSource*>(objects[LOWERARMSX])->SetZLength(LowerArmZLength);
  mappers[LOWERARMSX]->SetInput(objects[LOWERARMSX]->GetOutput());
  actors[LOWERARMSX]->SetMapper(mappers[LOWERARMSX]);
  actors[LOWERARMSX]->SetPosition(ElbowXCenter,ElbowYCenter-jointRadius-LowerArmYLength/2,ElbowZCenter);
  actors[LOWERARMSX]->SetOrigin(ElbowXCenter, ElbowYCenter-jointRadius, ElbowZCenter);
  
  //ELBOW
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWYSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWYSX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWYSX])->SetRadius(jointRadius);
  mappers[ELBOWYSX]->SetInput(objects[ELBOWYSX]->GetOutput());
  actors[ELBOWYSX]->SetMapper(mappers[ELBOWYSX]);
  actors[ELBOWYSX]->SetPosition(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  actors[ELBOWYSX]->SetOrigin(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWXSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWXSX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWXSX])->SetRadius(jointRadius);
  mappers[ELBOWXSX]->SetInput(objects[ELBOWXSX]->GetOutput());
  actors[ELBOWXSX]->SetMapper(mappers[ELBOWXSX]);
  actors[ELBOWXSX]->SetPosition(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  actors[ELBOWXSX]->SetOrigin(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  
  //UPPERARMSX
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[UPPERARMSX])->SetXLength(ArmXLength);
  static_cast<vtkCubeSource*>(objects[UPPERARMSX])->SetYLength(ArmYLength);
  static_cast<vtkCubeSource*>(objects[UPPERARMSX])->SetZLength(ArmZLength);
  mappers[UPPERARMSX]->SetInput(objects[UPPERARMSX]->GetOutput());
  actors[UPPERARMSX]->SetMapper(mappers[UPPERARMSX]);
  actors[UPPERARMSX]->SetPosition(ShoulderXCenter, ShoulderYCenter-jointRadius-ArmYLength/2, ShoulderZCenter);
  actors[UPPERARMSX]->SetOrigin(ShoulderXCenter, ShoulderYCenter-jointRadius, ShoulderZCenter);
   
  //SHOULDER
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERXSX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERXSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERXSX])->SetPhiResolution(25);
  mappers[SHOULDERXSX]->SetInput(objects[SHOULDERXSX]->GetOutput());
  actors[SHOULDERXSX]->SetMapper(mappers[SHOULDERXSX]);
  actors[SHOULDERXSX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERXSX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERYSX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERYSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERYSX])->SetPhiResolution(25);
  mappers[SHOULDERYSX]->SetInput(objects[SHOULDERYSX]->GetOutput());
  actors[SHOULDERYSX]->SetMapper(mappers[SHOULDERYSX]);
  actors[SHOULDERYSX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERYSX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERZSX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERZSX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERZSX])->SetPhiResolution(25);
  mappers[SHOULDERZSX]->SetInput(objects[SHOULDERZSX]->GetOutput());
  actors[SHOULDERZSX]->SetMapper(mappers[SHOULDERZSX]);
  actors[SHOULDERZSX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERZSX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  
  return actors;
  
  
}


vector<vtkActor*> 
Object3DHalfBody::makeRightArm(Point3D root){
  
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
  static_cast<vtkCubeSource*>(objects[FINGERDX])->SetXLength(FingerXLength);
  static_cast<vtkCubeSource*>(objects[FINGERDX])->SetYLength(FingerYLength);
  static_cast<vtkCubeSource*>(objects[FINGERDX])->SetZLength(FingerZLength);
  mappers[FINGERDX]->SetInput(objects[FINGERDX]->GetOutput());
  actors[FINGERDX]->SetMapper(mappers[FINGERDX]);
  actors[FINGERDX]->SetPosition(KnuckleXCenter,KnuckleYCenter-jointRadius-FingerYLength/2,KnuckleZCenter);
  actors[FINGERDX]->SetOrigin(KnuckleXCenter,KnuckleYCenter-jointRadius,KnuckleZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[KNUCKLEXDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEXDX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[KNUCKLEXDX])->SetRadius(jointRadius);
  mappers[KNUCKLEXDX]->SetInput(objects[KNUCKLEXDX]->GetOutput());
  actors[KNUCKLEXDX]->SetMapper(mappers[KNUCKLEXDX]);
  actors[KNUCKLEXDX]->SetPosition(KnuckleXCenter,KnuckleYCenter,WristZCenter);
  actors[KNUCKLEXDX]->SetOrigin(KnuckleXCenter,KnuckleYCenter,KnuckleZCenter);
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[HANDDX])->SetXLength(HandXLength);
  static_cast<vtkCubeSource*>(objects[HANDDX])->SetYLength(HandYLength);
  static_cast<vtkCubeSource*>(objects[HANDDX])->SetZLength(HandZLength);
  mappers[HANDDX]->SetInput(objects[HANDDX]->GetOutput());
  actors[HANDDX]->SetMapper(mappers[HANDDX]);
  actors[HANDDX]->SetPosition(WristXCenter,WristYCenter-jointRadius-HandYLength/2,WristZCenter);
  actors[HANDDX]->SetOrigin(WristXCenter,WristYCenter-jointRadius,WristZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[WRISTXDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTXDX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[WRISTXDX])->SetRadius(jointRadius);
  mappers[WRISTXDX]->SetInput(objects[WRISTXDX]->GetOutput());
  actors[WRISTXDX]->SetMapper(mappers[WRISTXDX]);
  actors[WRISTXDX]->SetPosition(WristXCenter,WristYCenter,WristZCenter);
  actors[WRISTXDX]->SetOrigin(WristXCenter,WristYCenter,WristZCenter);
  
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[LOWERARMDX])->SetXLength(LowerArmXLength);
  static_cast<vtkCubeSource*>(objects[LOWERARMDX])->SetYLength(LowerArmYLength);
  static_cast<vtkCubeSource*>(objects[LOWERARMDX])->SetZLength(LowerArmZLength);
  mappers[LOWERARMDX]->SetInput(objects[LOWERARMDX]->GetOutput());
  actors[LOWERARMDX]->SetMapper(mappers[LOWERARMDX]);
  actors[LOWERARMDX]->SetPosition(ElbowXCenter,ElbowYCenter-jointRadius-LowerArmYLength/2,ElbowZCenter);
  actors[LOWERARMDX]->SetOrigin(ElbowXCenter, ElbowYCenter-jointRadius, ElbowZCenter);
  
  //ELBOW
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWYDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWYDX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWYDX])->SetRadius(jointRadius);
  mappers[ELBOWYDX]->SetInput(objects[ELBOWYDX]->GetOutput());
  actors[ELBOWYDX]->SetMapper(mappers[ELBOWYDX]);
  actors[ELBOWYDX]->SetPosition(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  actors[ELBOWYDX]->SetOrigin(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[ELBOWXDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWXDX])->SetPhiResolution(25);
  static_cast<vtkSphereSource*>(objects[ELBOWXDX])->SetRadius(jointRadius);
  mappers[ELBOWXDX]->SetInput(objects[ELBOWXDX]->GetOutput());
  actors[ELBOWXDX]->SetMapper(mappers[ELBOWXDX]);
  actors[ELBOWXDX]->SetPosition(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  actors[ELBOWXDX]->SetOrigin(ElbowXCenter,ElbowYCenter,ElbowZCenter);
  
  //UPPERARMDX
  objects.push_back(vtkCubeSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkCubeSource*>(objects[UPPERARMDX])->SetXLength(ArmXLength);
  static_cast<vtkCubeSource*>(objects[UPPERARMDX])->SetYLength(ArmYLength);
  static_cast<vtkCubeSource*>(objects[UPPERARMDX])->SetZLength(ArmZLength);
  mappers[UPPERARMDX]->SetInput(objects[UPPERARMDX]->GetOutput());
  actors[UPPERARMDX]->SetMapper(mappers[UPPERARMDX]);
  actors[UPPERARMDX]->SetPosition(ShoulderXCenter, ShoulderYCenter-jointRadius-ArmYLength/2, ShoulderZCenter);
  actors[UPPERARMDX]->SetOrigin(ShoulderXCenter, ShoulderYCenter-jointRadius, ShoulderZCenter);
   
  //SHOULDER
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERXDX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERXDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERXDX])->SetPhiResolution(25);
  mappers[SHOULDERXDX]->SetInput(objects[SHOULDERXDX]->GetOutput());
  actors[SHOULDERXDX]->SetMapper(mappers[SHOULDERXDX]);
  actors[SHOULDERXDX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERXDX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERYDX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERYDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERYDX])->SetPhiResolution(25);
  mappers[SHOULDERYDX]->SetInput(objects[SHOULDERYDX]->GetOutput());
  actors[SHOULDERYDX]->SetMapper(mappers[SHOULDERYDX]);
  actors[SHOULDERYDX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERYDX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  objects.push_back(vtkSphereSource::New());
  actors.push_back(vtkActor::New());
  mappers.push_back(vtkPolyDataMapper::New());
  static_cast<vtkSphereSource*>(objects[SHOULDERZDX])->SetRadius(jointRadius);
  static_cast<vtkSphereSource*>(objects[SHOULDERZDX])->SetThetaResolution(25);
  static_cast<vtkSphereSource*>(objects[SHOULDERZDX])->SetPhiResolution(25);
  mappers[SHOULDERZDX]->SetInput(objects[SHOULDERZDX]->GetOutput());
  actors[SHOULDERZDX]->SetMapper(mappers[SHOULDERZDX]);
  actors[SHOULDERZDX]->SetPosition(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  actors[SHOULDERZDX]->SetOrigin(ShoulderXCenter, ShoulderYCenter, ShoulderZCenter);
  
  
  return actors;
  
  
  
}

void 
Object3DHalfBody::assemblyActors(vector<vtkActor*>& actors,vector<vtkActor*>& actorsLeftArm,vector<vtkActor*>& actorsRightArm){
  
  
  vector<vtkAssembly*> assembliesLeftArm;
  assembliesLeftArm .push_back(vtkAssembly::New());
  assembliesLeftArm[FINGERSX]->AddPart(actorsLeftArm[FINGERSX]);
  
  
  for(int i=1; i<static_cast<int>(actorsLeftArm.size()); ++i){
    assembliesLeftArm .push_back(vtkAssembly::New());
    assembliesLeftArm[i]->AddPart(assembliesLeftArm[i-1]);
    assembliesLeftArm[i]->AddPart(actorsLeftArm[i]);
  }
  
  assembliesLeftArm[FINGERSX]->SetOrigin(actorsLeftArm[KNUCKLEXSX]->GetOrigin());
  assembliesLeftArm[KNUCKLEXSX]->SetOrigin(actorsLeftArm[KNUCKLEXSX]->GetOrigin());
  assembliesLeftArm[HANDSX]->SetOrigin(actorsLeftArm[WRISTXSX]->GetOrigin());
  assembliesLeftArm[WRISTXSX]->SetOrigin(actorsLeftArm[WRISTXSX]->GetOrigin());
  assembliesLeftArm[LOWERARMSX]->SetOrigin(actorsLeftArm[ELBOWXSX]->GetOrigin());
  assembliesLeftArm[ELBOWYSX]->SetOrigin(actorsLeftArm[ELBOWYSX]->GetOrigin());
  assembliesLeftArm[ELBOWXSX]->SetOrigin(actorsLeftArm[ELBOWXSX]->GetOrigin());
  assembliesLeftArm[UPPERARMSX]->SetOrigin(actorsLeftArm[SHOULDERXSX]->GetOrigin());
  assembliesLeftArm[SHOULDERXSX]->SetOrigin(actorsLeftArm[SHOULDERXSX]->GetOrigin());
  assembliesLeftArm[SHOULDERYSX]->SetOrigin(actorsLeftArm[SHOULDERYSX]->GetOrigin());
  assembliesLeftArm[SHOULDERZSX]->SetOrigin(actorsLeftArm[SHOULDERZSX]->GetOrigin());
 
  //addNode: l'assembly corrisponde al sensore, l'id al joint
  //l'ordine degli assembly deve rispecchiare l'ordine della struttura
  addNode(assembliesLeftArm[SHOULDERZSX],5001/*,AxesRotations(0,0,-1)*/);
  addNode(assembliesLeftArm[SHOULDERYSX],5002/*,AxesRotations(0,1,0)*/);
  addNode(assembliesLeftArm[SHOULDERXSX],5000/*,AxesRotations(-1,0,0)*/);
  
  addNode(assembliesLeftArm[ELBOWXSX],5003/*,AxesRotations(-1,0,0)*/);
  addNode(assembliesLeftArm[ELBOWYSX],5004/*,AxesRotations(0,1,0)*/);
  
  addNode(assembliesLeftArm[WRISTXSX],5005/*,AxesRotations(-1,0,0)*/);
  addNode(assembliesLeftArm[KNUCKLEXSX],5006/*,AxesRotations(1,0,0)*/);
  
  
  
  //RightArm
  vector<vtkAssembly*> assembliesRightArm;
  assembliesRightArm .push_back(vtkAssembly::New());
  assembliesRightArm[FINGERDX]->AddPart(actorsRightArm[FINGERDX]);
  
  
  for(int i=1; i<static_cast<int>(actorsRightArm.size()); ++i){
    assembliesRightArm .push_back(vtkAssembly::New());
    assembliesRightArm[i]->AddPart(assembliesRightArm[i-1]);
    assembliesRightArm[i]->AddPart(actorsRightArm[i]);
  }
  
  assembliesRightArm[FINGERDX]->SetOrigin(actorsRightArm[KNUCKLEXDX]->GetOrigin());
  assembliesRightArm[KNUCKLEXDX]->SetOrigin(actorsRightArm[KNUCKLEXDX]->GetOrigin());
  assembliesRightArm[HANDDX]->SetOrigin(actorsRightArm[WRISTXDX]->GetOrigin());
  assembliesRightArm[WRISTXDX]->SetOrigin(actorsRightArm[WRISTXDX]->GetOrigin());
  assembliesRightArm[LOWERARMDX]->SetOrigin(actorsRightArm[ELBOWXDX]->GetOrigin());
  assembliesRightArm[ELBOWYDX]->SetOrigin(actorsRightArm[ELBOWYDX]->GetOrigin());
  assembliesRightArm[ELBOWXDX]->SetOrigin(actorsRightArm[ELBOWXDX]->GetOrigin());
  assembliesRightArm[UPPERARMDX]->SetOrigin(actorsRightArm[SHOULDERXDX]->GetOrigin());
  assembliesRightArm[SHOULDERXDX]->SetOrigin(actorsRightArm[SHOULDERXDX]->GetOrigin());
  assembliesRightArm[SHOULDERYDX]->SetOrigin(actorsRightArm[SHOULDERYDX]->GetOrigin());
  assembliesRightArm[SHOULDERZDX]->SetOrigin(actorsRightArm[SHOULDERZDX]->GetOrigin());
 
  
  addNode(assembliesRightArm[SHOULDERZDX],6001/*,AxesRotations(0,0,-1)*/);
  addNode(assembliesRightArm[SHOULDERYDX],6002/*,AxesRotations(0,1,0)*/);
  addNode(assembliesRightArm[SHOULDERXDX],6000/*,AxesRotations(-1,0,0)*/);
  
  addNode(assembliesRightArm[ELBOWXDX],6003/*,AxesRotations(-1,0,0)*/);
  addNode(assembliesRightArm[ELBOWYDX],6004/*,AxesRotations(0,1,0)*/);
  
  addNode(assembliesRightArm[WRISTXDX],6005/*,AxesRotations(-1,0,0)*/);
  addNode(assembliesRightArm[KNUCKLEXDX],6006/*,AxesRotations(1,0,0)*/);

  
  
  vector<vtkAssembly*> assembliesRoot;
  assembliesRoot.push_back(vtkAssembly::New());
  assembliesRoot[BACHELOR]->AddPart(actors[BACHELOR]);
  
  assembliesRoot.push_back(vtkAssembly::New());
  assembliesRoot[ROOT]->AddPart(assembliesRoot[BACHELOR]);
  assembliesRoot[ROOT]->AddPart(actors[ROOT]);
  
  addNode(assembliesRoot[ROOT],0);
  
  assembliesRoot[ROOT]->AddPart(assembliesLeftArm[SHOULDERZSX]);
  assembliesRoot[ROOT]->AddPart(assembliesRightArm[SHOULDERZDX]);
  
  
  
  
  
  
  
}
