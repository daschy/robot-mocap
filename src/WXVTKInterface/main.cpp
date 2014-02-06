#include <wx/wx.h>
#include <wx/image.h>
#include "Frame3D.h"
#include<3D/Object3D.h>
#include<debug.h>

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkFloatArray.h"
#include "vtkRectilinearGrid.h"
#include "vtkRectilinearGridGeometryFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkAxesActor.h"



#include <IO/IOMCD.h>




class MyApp: public wxApp {
  public:
    bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  wxInitAllImageHandlers();
  
  Frame3D *frame3D1 = new Frame3D(_T("Frame3D"),wxPoint(50, 50), wxSize(600, 600), Object3D::Object3DFactory("../../../Model/","HALFNICE.assembly"), wxID_ANY, wxDEFAULT_FRAME_STYLE);
  
  
  Frame3D *frame3D = new Frame3D(_T("Frame3D"),wxPoint(50, 50), wxSize(600, 600), new Object3DLeftArm(Point3D(0,5,0)), wxID_ANY, wxDEFAULT_FRAME_STYLE);
  
  //frame3D->get
  IOMCD* _fileMCD = new IOMCD("",0,0);
//   _fileMCD->setPath("../Config/BraccioSuGomito90.mcd");
//   _fileMCD->eraseData();
//   _fileMCD->importData();
//   frame3D->setData(_fileMCD->getData());
  frame3D->Render();
  frame3D1->getObject3D()->getRoot()->RotateX(-90.0);
  
  AxesRotations ax(0,0,1);
  
  
  
  frame3D->getObject3D()->rotatePartAngle(5001,90.0,ax);
  
  
  frame3D1->getRenderer(Frame3D::FRONT)->GetActiveCamera()->Zoom(0.5);
  
  frame3D1->getRenderer(Frame3D::PLANT)->GetActiveCamera()->Zoom(0.5);
  
  frame3D1->getRenderer(Frame3D::SIDE)->GetActiveCamera()->Zoom(0.5);
  
  frame3D1->getRenderer(Frame3D::OTHERSIDE)->GetActiveCamera()->Zoom(0.5);
  SetTopWindow(frame3D);
  
//   frame3D1->Show();
  frame3D->Show();
  
  
  return true;
}

