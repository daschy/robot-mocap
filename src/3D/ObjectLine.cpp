#include "ObjectLine.h"
#include <vtkLine.h>

ObjectLine::ObjectLine():Object3D(){
  vtkLine* object = vtkLine::New();
  vtkActor* actor = vtkActor::New();
  vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
  
  object->GetPointIds()->SetId(0, 0);
  object->GetPointIds()->SetId(1, 1);

//   mapper->SetInput(object->GetOutput());
//   actor->SetMapper(mapper);
//   
// 
//   vtkAssembly* assembly;
//   assembly .push_back(vtkAssembly::New());
//   assembly->AddPart(actor);
//   
//    addNode(assembly,0/*,AxesRotations(0,0,-1)*/);

}