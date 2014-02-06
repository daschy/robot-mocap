//per eseguire un eseguibile in vtk fare export LD_LIBRARY_PATH=/usr/local/lib

#ifndef CANVAS3D_H
#define CANVAS3D_H

#include <vector>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vector>

#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataSource.h>
#include <vtkCubeSource.h>
#include "Object3D.h"

using namespace std;

class Canvas3D {

public:
  Canvas3D(vector<Object3D*> obj3D);
  ~Canvas3D();
  inline Object3D* getObject3D(int i){return _obj3D[i];};
  void start();
  void stop();
  inline void render(){_renWin->Render();};

public:
  vtkRenderWindow *_renWin;
  vtkRenderWindowInteractor * _renInt;
  vtkRenderer * _ren;
  
  vector<Object3D*> _obj3D;
  
};
#endif
