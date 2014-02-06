#include "Canvas3D.h"
#include <debug.h>
    
#include<vtkCamera.h>
#include"Object3D.h"
#include"ObjectMoCap.h"

int main(){
//   Object3D* obj3d = 0;
//   obj3d = Object3D::Object3DFactory("../Config/ARM.txt");
//   
//   if(!obj3d) DEBOUT(("Obj3D == 0\n"));
//   
//   vector<int> temp = obj3d->getIDs();
//   for(int i=0; i<static_cast<int>(temp.size());++i){
//     DEBOUT(("%d\n",temp[i]));
//   }
//   delete(obj3d);
  vector<Object3D*> objs;
  objs.push_back(0); 
  objs[0] = new ObjectMoCap(Point3D(0,0,0));
  
  AxesRotations axes0(0,-1,0), axes1(-1,0,0),axes2(0,0,-1);
   objs[0]->rotatePartAngle(6003,90.0,axes1);
   objs[0]->rotatePartAngle(5003,90.0,axes1);
  objs[0]->rotatePartAngle(5005,90.0,axes1);
//   
//   objs[0]->rotatePartAngle(6002,0.0,axes0);
// //   objs[0]->rotatePartAngles(6000,0.0,0.0,-90.0);
//   objs[0]->rotatePartAngle(6003,90.0,axes1);
//   
//   objs[0]->rotatePartAngle(6001,90.0,axes2);
   objs.push_back(0); 
  objs[1] = Object3D::Object3DFactory("../../../Model/","HALFNICE.assembly");
  //objs.push_back(0); objs[0] = new Object3DRightArm(Point3D(0,0,0));
  //objs.push_back(0); objs[1] = new Object3DLeftArm(Point3D(0,0,0));
  
  
  
  Canvas3D *dc = new Canvas3D(objs);/* = new Canvas3D(Object3D::Object3DFactory("../Config/ARM.txt"));*/
   
  dc->_ren->ResetCamera();
  dc->_ren->GetActiveCamera()->Zoom(1);
  AxesRotations ax(1,0,0);
//   objs[0]->rotatePartAngle(6003,90,ax);
//   (dc->getObject3D())->rotatePartValue(4001,20);
//   (dc->getObject3D())->rotatePartValue(4002,30);
//   (dc->getObject3D())->rotatePartValue(4003,200);
//   (dc->getObject3D())->rotatePartValue(4004,200);
//   (dc->getObject3D())->rotatePartValue(4005,200);
//    (dc->getObject3D())->rotatePartValue(4006,150);
  dc->start();
  
}

