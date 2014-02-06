/*
 this->pvtkMFCWindow->GetRenderWindow()->SetNumberOfLayers ( 2 ); 
    this->pvtkMFCWindow->GetRenderWindow()->AddRenderer ( this->pvtkRendererAxes ); 
    this->pvtkRendererAxes->SetLayer ( 1 ); 
    this->pvtkRendererAxes->SetBackground ( 1.0, 1.0, 1.0 ); 
    this->pvtkRendererAxes->SetViewport ( 0.8, 0.8, 1.0, 1.0 ); 
    this->pvtkRendererAxes->AddActor ( axes ); 
     
    this->pvtkMFCWindow->GetRenderWindow()->AddRen

*/
    
#include<math.h>
#include <algorithm>
#include<debug.h>

#include "Frame3D.h"
#include<vtkCommand.h>
#include<vtkAxesActor.h>
#include<vtkStructuredGrid.h>
#include<vtkAxes.h>
#include<vtkTubeFilter.h>
#include<vtkDataSetMapper.h>
#include<vtkFloatArray.h>
#include<vtkRectilinearGrid.h>
#include<vtkRectilinearGridGeometryFilter.h>
#include<vtkProperty.h>
   

using namespace std;

 
Frame3D::Frame3D(const wxString& title, const wxPoint& pos, const wxSize& size,Object3D* objs3D, int id, long style, wxFrame* parent)
  : wxFrame(parent, id, title, pos, size, style){
    
  _objs3D=objs3D;
  _obj3DIDs = _objs3D->getIDs();
  
  _stateChanged=false;
   _VTKWindow = new wxVTKRenderWindowInteractor(this, VTKWININT);
  
  static_cast<wxGLCanvas*>(_VTKWindow)->SetSize(size.GetWidth(),
                           size.GetHeight()); 
    _VTKWindow->UseCaptureMouseOn();
#ifdef DEBUGGING
//   _VTKWindow->DebugOn();
#endif
    do_layout();
   ConstructVTK();
   ConfigureVTK();
   
    DEBOUT(("Frame3D::Frame3D()\n"));
}

Frame3D::~Frame3D(){
if(this->IsShown()) this->Show(false);
  if(_VTKWindow!=0)delete(_VTKWindow);
   DestroyVTK();
  DEBOUT(("Frame3D::~Frame3D()\n"));
}

BEGIN_EVENT_TABLE(Frame3D, wxFrame)
    EVT_SIZE(Frame3D::OnResize)
    EVT_CLOSE(Frame3D::OnCloseWindow)
END_EVENT_TABLE();

void 
Frame3D::do_layout(){
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  wxFlexGridSizer* sizer_bar = new wxFlexGridSizer(1, 5, 0, 0);
  wxBoxSizer* sizer_slider=new wxBoxSizer(wxVERTICAL);
/*  
  SetSizer(sizer);
  sizer->Add(_VTKWindow, 0, wxEXPAND, 0);
  sizer->Add(sizer_slider, 0, wxALL, 0);
  sizer_slider->Add(_slider, 0, wxALL|wxADJUST_MINSIZE, 0);
  sizer_slider->Add(sizer_bar, 0, wxALL, 0);
  
  sizer_bar->Add(_beginPosition, 0, wxALL, 0);
  sizer_bar->Add(_play, 0, wxALL, 0);
  sizer_bar->Add(_stop, 0, wxALL, 0);
  
  sizer_bar->Add(_loop, 0, wxALL, 0);
  sizer_bar->Add(_endPosition, 0, wxALL|wxADJUST_MINSIZE, 0);*/
  
  
  SetAutoLayout(true);
  Layout();
}

void Frame3D::ConstructVTK(){
  _renCollection     = vtkRendererCollection::New();
  //FRONT
  _renCollection->AddItem(vtkRenderer::New());
  //SIDE
  _renCollection->AddItem(vtkRenderer::New());
  //PLANT
  _renCollection->AddItem(vtkRenderer::New());
  //GLOBAL
  _renCollection->AddItem(vtkRenderer::New());
}

void Frame3D::ConfigureVTK()
{ 
  // connect the render window and wxVTK window
  vtkRenderWindow   *_renWin = _VTKWindow->GetRenderWindow();
  
  _renWin ->SetNumberOfLayers (Frame3D::NUMLAYERS);
   
  vtkAxesActor *axesActor = vtkAxesActor::New();
  
  double rootBound[6];
  vector<double> lengths;
  this->getObject3D()->getRoot()->GetBounds(rootBound);
  lengths.push_back((rootBound[1])- (rootBound[0]));
  lengths.push_back((rootBound[3])- (rootBound[2]));
  lengths.push_back((rootBound[5])- (rootBound[4]));
  
  sort(lengths.begin(),lengths.end());
  axesActor->SetTotalLength(lengths[2]*0.3,lengths[2]*0.3,lengths[2]*0.3);
 
  int numCellX = 15, numCellZ = 15;
  double step = lengths[2]/numCellX;
  vtkActor* grid = makeGrid(Point3D(-numCellX*step/2,0,-numCellZ*step/2),step,numCellX,1,numCellZ);
  grid->GetProperty()->SetColor(0.5,0.5,0.5);
  
  //Set Camera
  
  vtkRenderer* _ren  = static_cast<vtkRenderer*>( _renCollection->GetItemAsObject (FRONT));
 // connect renderer and render window and configure render window	
  _renWin->AddRenderer(_ren);
  _ren->SetLayer(0);
  _ren->SetViewport ( 0.0, 0.5, .5, 1.0 ); 
  _ren->SetBackground ( .5, .5, .5 ); 
  _ren->AddActor((_objs3D)->getRoot());
  _ren->AddActor(axesActor);
  _ren->AddActor(grid);
  _ren->GetActiveCamera()->Azimuth(0);
  _ren->ResetCamera();
  _ren->GetActiveCamera()->Elevation(0);
  _ren->GetActiveCamera()->Zoom(2.0);
 
    //axesActor->SetOrigin((_objs3D)->getRoot()->GetOrigin()[0],(_objs3D)->getRoot()->GetOrigin()[1],(_objs3D)->getRoot()->GetOrigin()[2]);
//   DEBOUT(("Rif origin %f %f %f\n",axesActor->GetOrigin()[0],axesActor->GetOrigin()[1],axesActor->GetOrigin()[2]));
//   DEBOUT(("Rif position %f %f %f\n",axesActor->GetPosition()[0],axesActor->GetPosition()[1],axesActor->GetPosition()[2]));
//   _ren->AddActor(axesActor);
  // configure renderer

  
    
     
    _ren  = static_cast<vtkRenderer*>( _renCollection->GetItemAsObject (PLANT));
    _renWin->AddRenderer(_ren); 
    _ren->SetLayer(0);
    _ren->SetViewport ( 0.0, 0.0, .5, .5 ); 

    _ren->SetBackground ( .5, .5, .5 ); 
    _ren->AddActor((_objs3D)->getRoot());
    _ren->AddActor(axesActor);
    _ren->AddActor(grid);
    _ren->GetActiveCamera()->Azimuth(0.0);
    _ren->ResetCamera();
    _ren->GetActiveCamera()->Elevation(90.0);
    _ren->GetActiveCamera()->Zoom(2.0);
   
   // axesActor = vtkAxesActor::New();
  _ren  = static_cast<vtkRenderer*>( _renCollection->GetItemAsObject (SIDE));
  _renWin->AddRenderer(_ren); 
  _ren->SetLayer(0);
  _ren->SetViewport ( .5, .5, 1.0, 1.0 ); 
  _ren->SetBackground ( .5, .5, .5 ); 
  _ren->AddActor((_objs3D)->getRoot());
   _ren->AddActor(axesActor);
   _ren->AddActor(grid);
   _ren->GetActiveCamera()->Azimuth(90.0);
   _ren->ResetCamera();
   _ren->GetActiveCamera()->Elevation(0.0);
   _ren->GetActiveCamera()->Zoom(2.0);
   
   _ren  = static_cast<vtkRenderer*>( _renCollection->GetItemAsObject (OTHERSIDE));
   _renWin->AddRenderer(_ren); 
   _ren->SetLayer(0);
   _ren->SetViewport ( .5, 0.0, 1.0, .5 ); 
   _ren->SetBackground ( 0.5, 0.5, 0.5 );
   _ren->AddActor((_objs3D)->getRoot());
   _ren->AddActor(axesActor);
   _ren->AddActor(grid);
   _ren->GetActiveCamera()->Azimuth(270.0);
   _ren->ResetCamera();
   _ren->GetActiveCamera()->Elevation(0.0);
   _ren->GetActiveCamera()->Zoom(2.0);
  
   
   _VTKWindow->Enable(true);
}

vtkActor* 
Frame3D::makeGrid(Point3D origin,double step,int numCellX,int numCellY, int numCellZ){
  numCellX++; 
  numCellZ++;
  numCellY=1;
  
  float x[numCellX+1];
  
  float y[numCellY+1];
  
  float z[numCellZ+1];
  
  
  for(int i=0;i< (numCellX+1);++i){
    x[i]=origin.X + step*static_cast<double>(i);
  }
  
//   for(int i=0;i< numCellX+1;++i){
//     DEBOUT(("x[%d] = %f\n",i,x[i]));
//   }
  
  
  for(int i=0;i< (numCellY+1);++i){
    y[i]=origin.Y + step*static_cast<double>(i);;
  }
//   for(int i=0;i< numCellY+1;++i){
//     DEBOUT(("y[%d] = %f\n",i,y[i]));
//   }
  
  for(int i=0;i< (numCellZ+1);++i){
    z[i]=origin.Z + step*static_cast<double>(i);
  }
//   for(int i=0;i< numCellZ+1;++i){
//     DEBOUT(("z[%d] = %f\n",i,z[i]));
//   }
//   
   vtkFloatArray *xCoords = vtkFloatArray::New();
  for (int i=0; i<numCellX+1; ++i) xCoords->InsertNextValue(x[i]);
  
  vtkFloatArray *yCoords = vtkFloatArray::New();
  for (int i=0; i<numCellY+1; ++i) yCoords->InsertNextValue(y[i]);
  
  vtkFloatArray *zCoords = vtkFloatArray::New();
  for (int i=0; i<numCellZ+1; ++i) zCoords->InsertNextValue(z[i]);
  
   vtkRectilinearGrid *rgrid = vtkRectilinearGrid::New();
    rgrid->SetDimensions(numCellX,numCellY,numCellZ);
    rgrid->SetXCoordinates(xCoords);
    rgrid->SetYCoordinates(yCoords);
    rgrid->SetZCoordinates(zCoords);

    
    // Extract a plane from the grid to see what we've got.
  vtkRectilinearGridGeometryFilter *plane = vtkRectilinearGridGeometryFilter::New();
    plane->SetInput(rgrid);
    plane->SetExtent(0,numCellX, (numCellY)/2,(numCellY)/2, 0,numCellZ);
    
  vtkPolyDataMapper *rgridMapper = vtkPolyDataMapper::New();
      rgridMapper->SetInputConnection(plane->GetOutputPort());
      
  vtkActor *wireActor = vtkActor::New();
      wireActor->SetMapper(rgridMapper);
      wireActor->GetProperty()->SetRepresentationToWireframe();
      wireActor->GetProperty()->SetColor(0.5,0.5,0.5);

      
      xCoords->Delete();
      yCoords->Delete();
      zCoords->Delete();
      rgrid->Delete();
      plane->Delete();
      rgridMapper->Delete();
      
  return wireActor;
  
}

void Frame3D::DestroyVTK()
{
//http://www.vtk.org/pipermail/vtkusers/2003-September/019894.html
 
    if (_objs3D != 0) delete(_objs3D);
    if (_renCollection != 0) _renCollection->Delete();
}

void
Frame3D::enableWidgets(const int* idArray, int dimension, bool enable){
  
  for(int i=0; i<dimension; i++){
    switch(idArray[i]){
      default:
	break;
    }//end switch
    //DEBOUT(("ArrayLenght=%d, selected = %d\n",dimension, i));
  }//end for
}

void 
Frame3D::Render(){
  _VTKWindow->Render(); 
  _stateChanged=false;
};

void 
Frame3D::defaultPosition(/*vector<int> ids, vector<int> values*/) /*throw (ExceptionIdOutOfRange)*/{
  vector<int> ids = _objs3D->getIDs();
  AxesRotations axes;
  for(unsigned int i=0;i<ids.size();++i){
    _objs3D->rotatePartAngle(ids[i],0.0,axes);
  }

  Render();
}

void
Frame3D::OnResize (wxSizeEvent &event){
//this->SetSize(event.GetSize().GetWidth(),event.GetSize().GetHeight());

// _VTKWindow->SetSize(event.GetSize().GetWidth(),
//                           event.GetSize().GetHeight()-(_play->GetSize()).GetHeight()-(_slider->GetSize()).GetHeight());

// this->Refresh();
DEBOUT(("Frame3D::OnResize() Width=%d, Height=%d\n",event.GetSize().GetWidth(),event.GetSize().GetHeight()));
}

void 
Frame3D::OnCloseWindow(wxCloseEvent & event){
this->Show(!this->IsShown());
}
