
#include "Canvas3D.h"
#include <vtkTransform.h>
#include<vtkAxesActor.h>
#include<vtkCamera.h>
#include<debug.h>
    
Canvas3D::Canvas3D(vector<Object3D*> obj3D){
  _obj3D = obj3D;/*Object3D::Object3DFactory("../Config/ARM.txt");*/
  
  _renWin = vtkRenderWindow::New();
 
  double deltaX = 1.0/static_cast<double>(_obj3D.size());
//   double deltaY = 1.0/static_cast<double>(_obj3D.size());
  for(unsigned int i=0;i<_obj3D.size();++i){
    _ren = vtkRenderer::New();
    _renWin->AddRenderer(_ren);
    _ren->SetLayer(0);
    _ren->AddActor(_obj3D[i]->getRoot());
    vtkAxesActor *axesActor = vtkAxesActor::New();
    axesActor->SetTotalLength(10,10,10);
    _ren->AddActor(axesActor);
    _ren->ResetCamera();
    _ren->SetBackground(0,0,0); // Background color white
    _ren->SetViewport ( i*deltaX,0.0,(i+1)*deltaX,1.0); 
    
    
   
    DEBOUT(("%f,%f,%f,%f\n",i*deltaX,0.0,(i+1)*deltaX,1.0));
  }
  
  
  
  _renInt = vtkRenderWindowInteractor::New();
  _renInt->SetRenderWindow(_renWin);
}


Canvas3D::~Canvas3D(){
  _renInt->Delete();
  _renWin->Delete();
  _ren->Delete();
  cout<<"Canvas3D::~Canvas3D()"<<endl;
}

void
Canvas3D::start(){
  
  _renInt->SetRenderWindow(_renWin);

  // add the actor to the scene
 

  // render an image (lights and cameras are created automatically)
  _renWin->Render();

  // begin mouse interaction
  _renInt->Start();
  //stop();
}

void
Canvas3D::stop(){
  this->~Canvas3D();
}
