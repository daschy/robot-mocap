#ifndef FRAME3D_H
#define FRAME3D_H

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include<vector>

#include <wx/config.h>
#include <wx/mediactrl.h>
#include <wx/setup.h>

#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkTextActor.h>
#include <vtkPolyDataReader.h>
#include <vtkRendererCollection.h>

#include<3D/Object3D.h>
#include<Headers/IOTypes.h>
#include<Headers/SensorsTypes.h>
#include<Headers/Exceptions.h>


#include "wxVTKRenderWindowInteractor.h"

using namespace std;

// class Frame3D;
/**
La classe rappresenta un wxFrame, il quale a sua volta contiene una vtkRendereWindow
*/
class Frame3D : public wxFrame
{
  public:
    enum POINTOFVIEW{
      FRONT=0,
      PLANT,
      SIDE,
      OTHERSIDE
    };
    
  public:
    // Actor(s)
    Frame3D(const wxString& title, const wxPoint& pos, const wxSize& size, Object3D* obj3D, int id=-1, long style=wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN, wxFrame* parent=NULL);
    ~Frame3D();
    Object3D* getObject3D(){return _objs3D;};
    void Render();
    int getNumOfRenderers(){return _renCollection->GetNumberOfItems();};
    inline vtkRenderer* getRenderer(int side){return static_cast<vtkRenderer*>( _renCollection->GetItemAsObject (side));}; 
    void setObject3D(Object3D* newObj3D){};//non implementato
    inline bool isStateChanged(){return _stateChanged;};
    inline void changeState(bool state){_stateChanged=state;};
    void defaultPosition(/*vector<int> ids, vector<int> values*/) /*throw (ExceptionIdOutOfRange)*/;
    void OnResize (wxSizeEvent &event);
    void OnCloseWindow(wxCloseEvent & event);
    DECLARE_EVENT_TABLE();
    
  protected:
    void ConstructVTK();
    void ConfigureVTK();
    vtkActor* makeGrid(Point3D center,double step,int numCellX,int numCellY, int numCellZ);
    void DestroyVTK();
    void do_layout();
    
  private:
    void enableWidgets(const int* idArray, int dimension, bool enable=true);
   
  private:
    enum WIDGETS{ 
      TIMER_ID=-1,
      VTKWININT=0,
    };
    
  private:
     wxVTKRenderWindowInteractor *_VTKWindow;
    
    static const int NUMLAYERS =1;
    
    // vtk classes
    vtkRendererCollection   *_renCollection;
    
    bool _stateChanged;
    
    Object3D* _objs3D;
    vector<int> _obj3DIDs;
    
    enum{
     ARM 
    };
    
};

#endif
