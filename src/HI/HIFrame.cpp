#include<wx/filename.h>
    
#include<iostream>
#include<vector>
#include<string>

#include<wx/dir.h>

#include <MyConfigParser/MyConfigParser.h>
  
#include<Headers/CommTypes.h>
#include <3D/ObjectMoCap.h>

#include "HIFrame.h"
 
using namespace std; 
     
HIFrame::HIFrame(wxWindow * parent, int id, const wxString & title,
		 const wxPoint & pos, const wxSize & size,
		 long style): wxFrame(parent, id, title, pos, size,style), _sensSysSelected(0), _title(title), _gridPanel(0), _rS(0), _currentSensSys(0),_virtualStick(0), _commIntSend(0), _commIntSystemState(0), _naisIp(""),_projectPath(""), _mcdPath(""), _mmdPath(""), _models3dPath(""), FPSFRAME3D(0), FPSREADING(0), FPSMOCAP(0), FPSSENDDATA(0), FPSVIRTUALROBOTDATA(0), MVJOINTSTYPE(MVJOINTUWTIME), MVJOINTSPARAMETER(100), _scene3DTimer(0), _readSensorsTimer(0), _moCapTimer(0), _commTimer(0){
  
  try{ 
 this->Show(false);
 if(!fopen("./Config/project.cfg","r")){
   wxCommandEvent e;
    this->OnReadProjectVars(e);
 }
 else { 
   readProjectVars("./Config/project.cfg");
 }
    
    createMenu();
    
    _gridPanel = new HIGridPanel(this, GRIDPANEL_ID, wxPoint(this->GetPosition().x,this->GetPosition().y+this->GetSize().GetHeight()/2),wxSTAY_ON_TOP|wxCENTRE_ON_SCREEN);
    
    _gridPanel->Show(this->GetMenuBar()->IsChecked( SHOWGRID_ID ));
    
    _fileMMD = new IOMMD();
    _fileMCD = new IOMCD("", 0, 0);
    _rS = 0;
    
    //StatusBar   
    HIFrame_statusbar = CreateStatusBar(2, 0);
 
    createFrames3D();
    
    createTimers();

    do_layout();
    //Look
    set_properties();
   
    int list[] = {CALIBRATEBUTTON_ID, RESETBUTTON_ID,
      SAVECALIBRATIONBUTTON_ID, MOCAPBUTTON_ID, READBUTTON_ID, CONNECTION_ID, MEDIACTRL_ID, SIMULATIONBUTTON_ID, BEGINBUTTON_ID,PREVIOUSFRAMEBUTTON_ID,PLAYBUTTON_ID,STOPBUTTON_ID,LOOPBUTTON_ID,NEXTFRAMEBUTTON_ID,ENDBUTTON_ID,SLIDER_ID
    };
    enableWidgets(list, sizeof(list) / sizeof(int), false);
  }
   catch(runtime_error e) {
    wxMessageDialog error(this, wxString((string(e.what())+string(" not found")).c_str(), wxConvUTF8),wxT("Message box"), wxOK, wxDefaultPosition);
    error.ShowModal();
    this->~HIFrame();
  }  

}//End constructor

BEGIN_EVENT_TABLE(HIFrame, wxFrame)
    EVT_COMBOBOX(COMBOBOX_ID, HIFrame::OnComboBox)
    EVT_BUTTON(MOCAPBUTTON_ID, HIFrame::OnMoCap)
    EVT_MENU(CALIBRATEBUTTON_ID, HIFrame::OnCalibrate)
    EVT_MENU(RESETBUTTON_ID, HIFrame::OnReset)
    EVT_MENU(SAVECALIBRATIONBUTTON_ID, HIFrame::OnSaveCalibration)
    EVT_MENU(OPENFILE_ID, HIFrame::OnOpenFile)
    EVT_MENU(CONNECTION_ID, HIFrame::OnConnection)
    EVT_MENU(STARTCORTEX_ID, HIFrame::OnStartCortex)
    EVT_MENU(UPDATEVARS_ID, HIFrame::OnReadProjectVars)
    EVT_MENU(SHOWGRID_ID, HIFrame::OnShowGrid)
    EVT_MENU(VIRTUALSTICKBUTTON_ID, HIFrame::OnVirtualStickModel)
    EVT_MENU(VIRTUALROBOTBUTTON_ID, HIFrame::OnVirtualRobotModel)
    EVT_MENU(READBUTTON_ID, HIFrame::OnRead)
    EVT_MENU(EXIT_ID, HIFrame::OnExit)
    EVT_MENU(SIMULATIONBUTTON_ID, HIFrame::OnSimulation)
    EVT_CLOSE(HIFrame::OnCloseWindow)
//     EVT_TIMER(TIMERREADSENSORS_ID, HIFrame::OnTimer)
    EVT_BUTTON(BEGINBUTTON_ID, HIFrame::OnBegin)
    EVT_BUTTON(PREVIOUSFRAMEBUTTON_ID, HIFrame::OnPreviousFrame)
    EVT_BUTTON(PLAYBUTTON_ID,HIFrame::OnPlay)
    EVT_BUTTON(STOPBUTTON_ID,HIFrame::OnStop)
    EVT_BUTTON(NEXTFRAMEBUTTON_ID, HIFrame::OnNextFrame)
    EVT_BUTTON(ENDBUTTON_ID,HIFrame::OnEnd)
    EVT_BUTTON(LOOPBUTTON_ID,HIFrame::OnLoop)
    EVT_SLIDER(SLIDER_ID,HIFrame::OnSlider)
END_EVENT_TABLE();


void HIFrame::createMenu(){
   //Menu
  HIFrame_menubar = new wxMenuBar();
  SetMenuBar(HIFrame_menubar);
    //File
  wxMenu *_menuFile = new wxMenu();
  HIFrame_menubar->Append(_menuFile, wxT("&File"));
  _menuFile->Append(EXIT_ID, wxT("E&xit"), wxEmptyString, wxITEM_NORMAL);
  _menuFile->Append(OPENFILE_ID, wxT("&Open MoCap File"), wxEmptyString,
		    wxITEM_NORMAL);
   
    
    //Option
  wxMenu *_menuOptions = new wxMenu();
  HIFrame_menubar->Append(_menuOptions, wxT("&Options"));
  _menuOptions->Append(STARTCORTEX_ID, wxT("&Start Cortex"), wxEmptyString,wxITEM_NORMAL);
  _menuOptions->Append(UPDATEVARS_ID, wxT("&Update Project Vars"), wxEmptyString,wxITEM_NORMAL);
    
    //View
  wxMenu *_menuView = new wxMenu();
  HIFrame_menubar->Append(_menuView, wxT("&View"));
  _menuView->Append(SHOWGRID_ID, wxT("Show &grid"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check( SHOWGRID_ID, false );
  _menuView->Append(VIRTUALSTICKBUTTON_ID, wxT("Show &sticks"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check( VIRTUALSTICKBUTTON_ID, false );
  _menuView->Append(VIRTUALROBOTBUTTON_ID, wxT("Show &robot"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check(VIRTUALROBOTBUTTON_ID, false );
    
     //Actions
  wxMenu *_menuActions = new wxMenu();
  HIFrame_menubar->Append(_menuActions, wxT("&Actions"));
  _menuActions->Append(READBUTTON_ID, wxT("&Read sensors"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check(READBUTTON_ID,false);
  _menuActions->Append(CONNECTION_ID, wxT("Co&nnect"), wxEmptyString,wxITEM_NORMAL);
  this->GetMenuBar()->Check(READBUTTON_ID,false);
  _menuActions->Append(SIMULATIONBUTTON_ID, wxT("Si&mulation"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check(SIMULATIONBUTTON_ID,false);
  _menuActions->Append(CALIBRATEBUTTON_ID, wxT("Ca&librate"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check(CALIBRATEBUTTON_ID,false);
  _menuActions->Append(SAVECALIBRATIONBUTTON_ID, wxT("Save Calibra&tion"), wxEmptyString,wxITEM_CHECK);
  this->GetMenuBar()->Check(SAVECALIBRATIONBUTTON_ID,false);
  _menuActions->Append(RESETBUTTON_ID, wxT("&Reset\tCtrl+R"), wxEmptyString,wxITEM_NORMAL);
    
    //Help
  wxMenu *_menuHelp = new wxMenu();
  _menuHelp->Append(ABOUT_ID, wxT("&About.."), wxEmptyString, wxITEM_NORMAL);
  HIFrame_menubar->Append(_menuHelp, wxT("&Help"));
}


void HIFrame::readProjectVars(string projectVarFile) throw (runtime_error){
  MyConfigParser par;
   
    par=MyConfigParser(projectVarFile.c_str());
    par.selectFirstSection("general");
    _naisIp = par.getValueInCurrentSection("NAISIP");
    _naisPort=atoi(par.getValueInCurrentSection("NAISPORT").c_str());
    _projectPath = par.getValueInCurrentSection("PATH");
    _mcdPath = par.getValueInCurrentSection("MCDPATH");
    _mmdPath = par.getValueInCurrentSection("MMDPATH");
    _models3dPath = par.getValueInCurrentSection("MODELS3DPATH");
    FPSFRAME3D = atoi(par.getValueInCurrentSection("FPSFRAME3D").c_str());
    FPSREADING = atoi(par.getValueInCurrentSection("FPSREADING").c_str());
    FPSMOCAP = atoi(par.getValueInCurrentSection("FPSMOCAP").c_str());
    
    FPSSENDDATA=atoi(par.getValueInCurrentSection("FPSSENDDATA").c_str());
    FPSVIRTUALROBOTDATA = atoi(par.getValueInCurrentSection("FPSVIRTUALROBOTDATA").c_str());

     MVJOINTSPARAMETER = atoi(par.getValueInCurrentSection("MVJOINTSPARAMETER").c_str());
     
     string mvJointTypeString = par.getValueInCurrentSection("MVJOINTSTYPE");
     
     if(mvJointTypeString=="MVJOINTWSPEED"){
       MVJOINTSTYPE = MVJOINTWSPEED;
     }
     else if(mvJointTypeString=="MVJOINTWTIME"){
       MVJOINTSTYPE = MVJOINTWTIME;
     }
     else if(mvJointTypeString=="MVJOINTUWSPEED"){
       MVJOINTSTYPE = MVJOINTUWSPEED;
     }
     else if(mvJointTypeString=="MVJOINTUWTIME"){
       MVJOINTSTYPE = MVJOINTUWTIME;
     }
     else{
       MVJOINTSTYPE = MVJOINTUWTIME;
     }
    
 
}

void HIFrame::createTimers(){
  _scene3DTimer = new HIScene3DTimer(this,_virtualStick,TIMERSCENE3D_ID);
  int delayScene3DTimer = static_cast <int >((1.0 / static_cast < double >(FPSFRAME3D))*1000.0);
  _scene3DTimer->Start(delayScene3DTimer,wxTIMER_CONTINUOUS);
  
  _virtualRobotTimer = new HIVirtualRobotTimer(this,TIMERVIRTUALROBOT_ID);
   
  _readSensorsTimer = new HIReadSensorsTimer(this, _gridPanel, _virtualStick, TIMERREADSENSORS_ID);
}    
  
void HIFrame::createFrames3D(){
   _virtualStick = new Frame3D(wxString(_T("Virtual Sticks")),
	 		   wxPoint(this->GetPosition().x+this->GetSize().GetWidth()*2,this->GetPosition().y), wxSize(600, 500),
                           new ObjectMoCap(Point3D(0,60,0)),
			   /*new Object3DHalfBody(Point3D(0,5,0)),*/ FRAMEVIRTUALSTICKS_ID,wxSTAY_ON_TOP|wxCENTRE_ON_SCREEN,this);
    
    _virtualStick->getObject3D()->getRoot()->SetScale(0.8,0.75,0.8);
   
    _virtualRobot = new Frame3D(wxString(_T("Virtual Robot")),
				wxPoint(this->GetPosition().x+this->GetSize().GetWidth()*2,this->GetPosition().y), wxSize(600, 500),
				Object3D::Object3DFactory(_models3dPath.c_str(),"HALFNICE.assembly"), FRAMEVIRTUALROBOT_ID,wxSTAY_ON_TOP|wxCENTRE_ON_SCREEN,this);
  
    _virtualRobot->getObject3D()->getRoot()->RotateX(-90.0);
    _virtualRobot->getObject3D()->getRoot()->SetScale(0.5,0.5,0.5);
  
}


HIFrame::~HIFrame()
{
    DEBOUT(("HIFrame::~HIFrame()\n"));
   
    if(_commTimer!=0) {
      _commTimer->Stop();
      delete(_commTimer);
      _commTimer =0;
    }
    if(_virtualRobotTimer!=0) {
      _virtualRobotTimer->Stop();
      delete(_virtualRobotTimer);
      _virtualRobotTimer =0;
    }
    
    if(  _moCapTimer!=0) {
      _moCapTimer->Stop();
      delete(_moCapTimer);
      _moCapTimer =0;
    }
    
    
    if(_readSensorsTimer!=0) {
      _readSensorsTimer->Stop();
      delete(_readSensorsTimer); _readSensorsTimer =0;
    }
	
    if(_scene3DTimer!=0) {
      _scene3DTimer->Stop();
      delete(_scene3DTimer); _scene3DTimer =0;
    }
	
    if(_currentSensSys!=0) {
    	delete(_currentSensSys);
	_currentSensSys =0;
	}
    if(_rS!=0) {
    	delete(_rS);
	_rS=0;
	}
    if(_virtualStick!=0) {
    	delete(_virtualStick);
	_virtualStick =0;
	}
   
    
    if(_commIntSend!=0) {
      cgMessageBye bye;
      _commIntSend->sendData(&bye);
      delete(_commIntSend); _commIntSend=0;
    } 
    if(_commIntSystemState!=0){
      cgMessageBye bye;
      _commIntSystemState->sendData(&bye);
      delete(_commIntSystemState); _commIntSystemState=0;
    }
    
    if(_gridPanel!=0) {
    	delete(_gridPanel);
	_gridPanel =0;
	}
    
    DEBOUT(("HIFrame::~HIFrame()\n"));
}

void
 HIFrame::set_properties()
{
    SetTitle(_title);
    int HIFrame_statusbar_widths[] = { -1, -1 };
    HIFrame_statusbar->SetStatusWidths(2, HIFrame_statusbar_widths);
    const wxString HIFrame_statusbar_fields[] = {
	wxT(""),
	wxT("")
    };
    for (int i = 0; i < HIFrame_statusbar->GetFieldsCount(); ++i) {
	HIFrame_statusbar->SetStatusText(HIFrame_statusbar_fields[i], i);
    }
    combo_box_sensors_system->SetSelection(0);
}


void HIFrame::do_layout()
{
    
  wxGridSizer *frame_grid_sizer = new wxGridSizer(2, 1, 0, 0);
  //     Frame diviso con frame_grid_sizer
  this->SetSizer(frame_grid_sizer);
  createMediaCtrl(frame_grid_sizer);
//     frame_grid_sizer->Fit(this);
//     frame_grid_sizer->SetSizeHints(this);
//     SetAutoLayout(true);
//     Layout();
}

void HIFrame::createMediaCtrl(wxSizer* frame_grid_sizer){ 
  wxSize frameSize = this->GetSize();
  
  wxPanel* itemPanel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize(frameSize.GetWidth(),(frameSize.GetHeight()/2)-65), wxTAB_TRAVERSAL );
  
  frame_grid_sizer->Add(itemPanel1, 0,wxEXPAND /*wxALL | wxADJUST_MINSIZE*/, 0);
    
    
  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
  itemPanel1->SetSizer(itemBoxSizer2);
     
    
  wxArrayString files;
  
  wxDir::GetAllFiles(wxString(_mmdPath.c_str() , wxConvUTF8), &files, wxT("*.cfg"));
  for(size_t i = 0; i<files.Count();++i){
    files.Item(i) = wxFileNameFromPath(files.Item(i));
// 	    DEBOUT(("File %d = %s\n",i,static_cast <
// 			    const char *>( files.Item(i).fn_str()) ));
  }
  files.Sort();
  files.Insert(wxT("NONE"),0);
	
  combo_box_sensors_system =
      new wxComboBox(itemPanel1, COMBOBOX_ID, wxT(""), wxDefaultPosition,
		     wxDefaultSize, files,
		     wxCB_DROPDOWN);
  itemBoxSizer2->Add(combo_box_sensors_system, 0,
		     wxALL | wxADJUST_MINSIZE, 0);
    
  button_MoCap = new wxButton(itemPanel1, MOCAPBUTTON_ID, wxT("MoCap START"));
  itemBoxSizer2->Add(button_MoCap, 0, wxALL | wxADJUST_MINSIZE, 0);
  
    
    
  wxPanel* itemPanel2 = new wxPanel( this,  MEDIACTRL_ID,wxPoint(0,itemPanel1->GetSize().GetHeight()-HIFrame_statusbar->GetSize().GetHeight()*2), wxSize(frameSize.GetWidth(),(frameSize.GetHeight()/2)-(HIFrame_statusbar->GetSize().GetHeight())), wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    
    
  frame_grid_sizer->Add( 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
  wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
  itemPanel2->SetSizer(itemBoxSizer3);
    
    
  wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    

  _beginPosition = new wxButton(itemPanel2, BEGINBUTTON_ID, wxT("|<"), wxPoint(0,225), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_beginPosition, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
  _previousPosition = new wxButton(itemPanel2, PREVIOUSFRAMEBUTTON_ID, wxT("<<"),wxPoint(_beginPosition->GetPosition().x+_beginPosition->GetSize().GetWidth(),_beginPosition->GetPosition().y), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_previousPosition, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
   
    
  _play = new wxButton(itemPanel2, PLAYBUTTON_ID, wxT(">"),wxPoint(_previousPosition->GetPosition().x+_previousPosition->GetSize().GetWidth(),_previousPosition->GetPosition().y), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_play, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
  _stop = new wxButton(itemPanel2, STOPBUTTON_ID, wxT("[]"), wxPoint(_play->GetPosition().x+_play->GetSize().GetWidth(),_play->GetPosition().y), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_stop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
  _nextPosition = new wxButton(itemPanel2, NEXTFRAMEBUTTON_ID, wxT(">>"), wxPoint(_stop->GetPosition().x+_stop->GetSize().GetWidth(),_stop->GetPosition().y), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_nextPosition, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
  _endPosition = new wxButton(itemPanel2, ENDBUTTON_ID, wxT(">|"), wxPoint( _nextPosition->GetPosition().x+ _nextPosition->GetSize().GetWidth(), _nextPosition->GetPosition().y), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_endPosition, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
  //     
  //     
  _loop = new wxButton(itemPanel2, LOOPBUTTON_ID, wxT("<=/=>"), wxPoint(_endPosition->GetPosition().x+_endPosition->GetSize().GetWidth(),_endPosition->GetPosition().y), wxSize(itemPanel2->GetSize().GetWidth()/7,wxDefaultSize.GetHeight()), 0 );
  itemBoxSizer4->Add(_loop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
  //     
  _slider = new wxSlider( itemPanel2, SLIDER_ID, 0, 0, 100, wxPoint(0,_beginPosition->GetPosition().y+_beginPosition->GetSize().GetHeight()), wxSize(itemPanel2->GetSize().GetWidth()-4,wxDefaultSize.GetHeight()), wxSL_AUTOTICKS|wxSL_HORIZONTAL|wxSL_LABELS);
  itemBoxSizer3->Add(_slider, 0, wxEXPAND, 5);
  
}


void HIFrame::enableWidgets(const int *idArray, int dimension, bool enable)
{

    for (int i = 0; i < dimension; ++i) {
	switch (idArray[i]) {
	case GRIDPANEL_ID:
	    _gridPanel->Enable(enable);
	    break;
	case FRAMEVIRTUALSTICKS_ID:
	    _virtualStick->Enable(enable);
	    break;
	case FRAMEVIRTUALROBOT_ID:
	    _virtualRobot->Enable(enable);
	break;
	case CALIBRATEBUTTON_ID:
// 	    button_calibrate->Enable(enable);
	    HIFrame_menubar->FindItem(CALIBRATEBUTTON_ID)->Enable(enable);
	    break;
	case RESETBUTTON_ID:
// 	    button_reset->Enable(enable);
	    HIFrame_menubar->FindItem(RESETBUTTON_ID)->Enable(enable);
	    break;
	case SAVECALIBRATIONBUTTON_ID:
// 	    button_save_calibration->Enable(enable);
	    HIFrame_menubar->FindItem(SAVECALIBRATIONBUTTON_ID)->Enable(enable);
	    break;
	case VIRTUALSTICKBUTTON_ID:
// 	    button_3d_model->Enable(enable);
	  HIFrame_menubar->FindItem(VIRTUALSTICKBUTTON_ID)->Enable(enable);
	    break;
	  case VIRTUALROBOTBUTTON_ID:
// 	    button_3d_model->Enable(enable);
	    HIFrame_menubar->FindItem(VIRTUALROBOTBUTTON_ID)->Enable(enable);
	    break;
	case MOCAPBUTTON_ID:
	    button_MoCap->Enable(enable);
	    break;
	case SIMULATIONBUTTON_ID:
// 	    button_Simulation->Enable(enable);
	    HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->Enable(enable);
	    break;
        case READBUTTON_ID:
//             button_Read->Enable(enable);
	    HIFrame_menubar->FindItem(READBUTTON_ID)->Enable(enable);
            break;
	case COMBOBOX_ID:
	    combo_box_sensors_system->Enable(enable);
	    break;
	case OPENFILE_ID:
	    HIFrame_menubar->FindItem(OPENFILE_ID)->Enable(enable);
	    break;
	case CONNECTION_ID:
	    HIFrame_menubar->FindItem(CONNECTION_ID)->Enable(enable);
	    break;
	case STARTCORTEX_ID:
	    HIFrame_menubar->FindItem(STARTCORTEX_ID)->Enable(enable);
	    break;
	case UPDATEVARS_ID:
	  HIFrame_menubar->FindItem(UPDATEVARS_ID)->Enable(enable);
	  break;
	case SHOWGRID_ID:
	    HIFrame_menubar->FindItem(SHOWGRID_ID)->Enable(enable);
	    break;
	case EXIT_ID:
	    HIFrame_menubar->FindItem(EXIT_ID)->Enable(enable);
	    break;
	case BEGINBUTTON_ID:
	     _beginPosition->Enable(enable);
	    break;
	case PREVIOUSFRAMEBUTTON_ID:
	    _previousPosition->Enable(enable);
	    break;
	case PLAYBUTTON_ID:
	  _play->Enable(enable);
	    break;
	case STOPBUTTON_ID:
	  _stop->Enable(enable);
	    break;
	case NEXTFRAMEBUTTON_ID:
	    _nextPosition->Enable(enable);
	   break;
	case ENDBUTTON_ID:
	  _endPosition->Enable(enable);
	    break;
	case LOOPBUTTON_ID:
	  _loop->Enable(enable);
	    break; 
	  case SLIDER_ID:
	    _slider->Enable(enable);
	    break;
	default:
	    break;
	}			//end switch
	//DEBOUT(("ArrayLenght=%d, selected = %d\n",dimension, i));
    }				//end for

    HIFrame_menubar->Refresh();
}

bool HIFrame::startConnection(int port, string ip) throw (ExceptionConnectionError){
 
    
    string receivedString;
    _commIntSend =
	CommInterface::CommInterfaceFactory(port, ip.c_str(), TCP);
    
    _commIntSystemState =
	CommInterface::CommInterfaceFactory(port, ip.c_str(), TCP);
    
    int numTentativi = 20;
    bool ricevuto = false;
    string receivedStringCommSend="", receivedStringSysState="";
    
    while(numTentativi>0 && !ricevuto ){
      if(_commIntSend->someActivities() && _commIntSystemState->someActivities()) {
	
	receivedStringCommSend = _commIntSend-> recvDataAsString();
	receivedStringSysState = _commIntSystemState-> recvDataAsString();
	
	if(receivedStringCommSend.size()!=0 && receivedStringSysState.size()!=0) {
	  DEBOUT(("Receive HELLO _commIntSend %s\n", (receivedStringCommSend).c_str()));
	  DEBOUT(("Receive HELLO _commIntSystemState %s\n", (receivedStringSysState).c_str()));
	  ricevuto = true;
	}
      }
        numTentativi--;
        usleep(100000);
    }
    if(!ricevuto){
      throw ExceptionConnectionError("Can't get welcome message");
    }
  
    cgMessageHello hello;
    _commIntSend ->sendData(&hello);
    _commIntSystemState ->sendData(&hello);
   
    numTentativi = 10;
    ricevuto=false;
   
    
    while(numTentativi>0 && !ricevuto ){
      if(_commIntSend->someActivities() && _commIntSystemState->someActivities()) {
	receivedStringCommSend = _commIntSend-> recvDataAsString();
	receivedStringSysState = _commIntSystemState-> recvDataAsString();
	
	if(receivedStringCommSend.size()!=0 && receivedStringSysState.size()!=0) {
	  DEBOUT(("Receive HELLO _commIntSend %s\n", (receivedStringCommSend).c_str()));
	 
	  DEBOUT(("Receive HELLO _commIntSystemState %s\n", (receivedStringSysState).c_str()));
	 
	 ricevuto = true;
	}
      }
	numTentativi--;
	usleep(100000); 
    }
    if(!ricevuto){
      throw ExceptionConnectionError("Can't get hello message");
    }
    
//     _isCommunicating = true;
    if(this->GetMenuBar()->IsChecked(READBUTTON_ID)){
      int delayCommunication = static_cast <int >((1.0 / static_cast < double >(FPSSENDDATA))*1000.0);
      _commTimer = new HICommunicationDeviceConnectedTimer(this,TIMERCOMMUNICATION_ID,MVJOINTSTYPE,MVJOINTSPARAMETER);
      
      _commTimer->setSensorsSystem(_currentSensSys);
      _commTimer->setCommunicationInterface(_commIntSend);
      static_cast<HICommunicationDeviceConnectedTimer*>(_commTimer)->setReadSensors(_rS);
      _commTimer->Start(delayCommunication,wxTIMER_CONTINUOUS);
    }
     
    if(this->GetMenuBar()->IsChecked(SIMULATIONBUTTON_ID)){
//       static_cast<HIMoCapOfflineTimer*>(_moCapTimer)->setCommunicationInterface(_commIntSend);
      _commTimer = new HICommunicationDeviceNotConnectedTimer(this,_slider,TIMERCOMMUNICATION_ID,MVJOINTSTYPE,MVJOINTSPARAMETER); 
      _commTimer->setCommunicationInterface(_commIntSend);
      _commTimer->setSensorsSystem(_currentSensSys);
      static_cast<HICommunicationDeviceNotConnectedTimer*>(_commTimer)->setIOMCD(_fileMCD);
    }
    
    int delayVirtualRobot = static_cast <int >((1.0 / static_cast < double >(FPSVIRTUALROBOTDATA))*1000.0);
    _virtualRobotTimer->setSensorsSystem(_currentSensSys);
    _virtualRobotTimer->setCommunicationInterface(_commIntSystemState);
    _virtualRobotTimer->setFrame3D(_virtualRobot);
    _virtualRobotTimer->Start(delayVirtualRobot,wxTIMER_CONTINUOUS);
    
    HIFrame_menubar->FindItem(CONNECTION_ID)->SetText(_T("Disco&nnect"));

    return true;
}

void HIFrame::stopConnection()
{
  try{
    _virtualRobotTimer->Stop();
    
    if(_commTimer){
      _commTimer->Stop();
      delete(_commTimer);
    }
    _commTimer=0;
    
    cgMessageBye bye;
    
    if(_commIntSend) {
      _commIntSend->sendData(&bye);
      delete(_commIntSend);
    }
    _commIntSend=0;
    
    if(_commIntSystemState){
      _commIntSystemState->sendData(&bye);
      delete(_commIntSystemState); 
    }
    _commIntSystemState=0;
    
    HIFrame_menubar->FindItem(CONNECTION_ID)->SetText(wxT("Co&nnect"));
  }
  catch(runtime_error e) {
    char str[128];
    sprintf(str, DEBPOS"%s", e.what());
    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
  }
}

void HIFrame::OnCalibrate(wxCommandEvent & event)
{
    try {
      if (this->GetMenuBar()->IsChecked(CALIBRATEBUTTON_ID)) {
	    this->startCalibrate();
// 	    _isCalibrating = true;
	    HIFrame_statusbar->SetStatusText(wxT("Calibrating"));
	    int enableList[] = { RESETBUTTON_ID };
	    int disableList[] = { COMBOBOX_ID, MOCAPBUTTON_ID };
	    enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
	    enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
	} else {
	    stopCalibrate();
// 	    _isCalibrating = false;
	    
	    HIFrame_statusbar->SetStatusText(wxT("STOP Calibrating"));
	    int enableList[] = { SAVECALIBRATIONBUTTON_ID };
	    int disableList[] = { RESETBUTTON_ID };
	    enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
	    enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
	}
	event.Skip();
	return;
    }
    catch(runtime_error e) {
      char str[128];
      sprintf(str, DEBPOS"%s", e.what());
      wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
    }
    DEBOUT(("HIFrame::OnCalibrate()\n"));
}


void HIFrame::OnReset(wxCommandEvent & event)
{
    try {
      vector<int> vecIDs = _currentSensSys->getSensorsIDs();
      if(_virtualStick->IsShown())_virtualStick->defaultPosition();
      for(unsigned int i=0;i<vecIDs.size();++i){
	_currentSensSys->setInitValue(vecIDs[i], _rS->getCalibratedSensorValue(vecIDs[i]));
      }
      if(_fileMMD->writeData(_currentSensSys, _mmdPath, _currentSensSys->getSensorsSystemName())){
	DEBOUT(("Write data on file %s\n",(_mmdPath+ _currentSensSys->getSensorsSystemName()).c_str()));
	
      }
	return;
    }
    catch(runtime_error e) {
      char str[128];
      sprintf(str, DEBPOS"%s", e.what());
      wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
    }
}

void HIFrame::OnComboBox(wxCommandEvent & event)
{
    int sel = event.GetInt();
    wxString strSel = combo_box_sensors_system->GetValue();
//     string str = strSel.fn_str();
	DEBOUT(("Selezionato %d\n", sel));
    event.Skip();
    if (_sensSysSelected != sel) {
	_sensSysSelected = sel;
	
	_readSensorsTimer->Stop();
// 	_scene3DTimer->Stop();
	try {
	    if(_currentSensSys) {
	      delete(_currentSensSys);
	     _currentSensSys=0;
	    }
	    
	   if(strSel.Contains(wxT("NONE"))){	//NONE
	     //ripeto per chiarezza
	     _currentSensSys=0;
		
	   }
	   else {
	     _currentSensSys = _fileMMD->importData(_mmdPath,string(strSel.fn_str()));
	     DEBOUT(("HIFrame::OnComboBox()->Case  %s\n",(_mmdPath+string(strSel.fn_str())).c_str()));
	   }
	   
	    if (sel == 0) {
 	      _gridPanel->resizeRows(14);
// 		 this->Fit();
		int disableList[] = { CALIBRATEBUTTON_ID,
		  MOCAPBUTTON_ID, CONNECTION_ID, READBUTTON_ID, RESETBUTTON_ID, SIMULATIONBUTTON_ID 
		};
		int enableList[] = {};
		enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			      true);
		enableWidgets(disableList,
			      sizeof(disableList) / sizeof(int), false);
	    }
	    
	    if (sel > 0) {
// 	      if(!_rS){
// 	       	_rS = new FilteredReadSensors(_currentSensSys);
// 	       }
// 	      else {
// 	      	_rS->setSensorsSystem(_currentSensSys);
// 	      }
	      vector<AxesRotations> tempAxes = _currentSensSys->getSensorsJoint(SensorsAttributes::VIRTUALJOINTS);
// 	      _actuators->setAxesRotations(ActuatorType::VIRTUALSTICKJOINTS,  tempAxes);
              
	      vector<AxesRotations> tempAxes2 = _currentSensSys->getSensorsJoint(SensorsAttributes::NAISJOINTS);
	      
// 	      for(unsigned int i=0; i<tempAxes.size(); ++i)
// 		DEBOUT(("%d (%d,%d,%d) (%d,%d,%d)\n",  _currentSensSys->getIDSensor(i), tempAxes[i].X,tempAxes[i].Y,tempAxes[i].Z,tempAxes2[i].X,tempAxes2[i].Y,tempAxes2[i].Z));
	      
	      int enableList[] = { READBUTTON_ID, SIMULATIONBUTTON_ID
		};
		int disableList[] = { CONNECTION_ID};
		enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			      true);
		enableWidgets(disableList,
			      sizeof(disableList) / sizeof(int), false);
// 		_readSensorsTimer->Start(static_cast <
// 		     int >((1.0 / static_cast < double >(FPSREADING))
// 			   *1000.0),false);
// 	        _scene3DTimer->Start(static_cast <
// 		     int >((1.0 / static_cast < double >(FPSFRAME3D))
// 			   *1000.0),false);
	    }

	    HIFrame_statusbar->SetStatusText(wxT("Selected ") +
					     combo_box_sensors_system->
					     GetValue(), 0);
	    

	}			//end try
	
	catch(runtime_error e) {
	  combo_box_sensors_system->SetSelection(0, 0);
	  char str[128];
	  sprintf(str, DEBPOS"%s", e.what());
	  wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
	}
    }//end if(_sensSysSelected!=sel)
    
}



void HIFrame::OnRead(wxCommandEvent & event){
  
  try {
    if(!_rS){
      _rS = new FilteredReadSensors(_currentSensSys);
    }
    else {
      _rS->setSensorsSystem(_currentSensSys);
    }
     //Se ho appena messo il check inizia a leggere dai sensori
    if (this->GetMenuBar()->IsChecked(READBUTTON_ID)) {
      _gridPanel->resizeRows(14/*_currentSensSys->getNumSensors()*/);
     this->startReadSensors();
      this->GetMenuBar()->Check( READBUTTON_ID, true);
      
      int enableList[] = { GRIDPANEL_ID, CALIBRATEBUTTON_ID,
	MOCAPBUTTON_ID, CONNECTION_ID,RESETBUTTON_ID 
      };
      int disableList[] = { SIMULATIONBUTTON_ID,COMBOBOX_ID };
      enableWidgets(enableList, sizeof(enableList) / sizeof(int),
                    true);
      enableWidgets(disableList,
                    sizeof(disableList) / sizeof(int), false);
      HIFrame_statusbar->SetStatusText(wxT("Read Mode"), 0);
    }
    // se ho appena tolto il check nn leggere più dai sensori
    else {
      this->stopReadSensors();
      this->stopConnection();
      this->GetMenuBar()->Check( READBUTTON_ID, false);
      _gridPanel->resizeRows(14);

      int disableList[] = { CALIBRATEBUTTON_ID,
	MOCAPBUTTON_ID, CONNECTION_ID
      };
      int enableList[] = { SIMULATIONBUTTON_ID,COMBOBOX_ID };
      enableWidgets(enableList, sizeof(enableList) / sizeof(int),
                    true);
      enableWidgets(disableList,
                    sizeof(disableList) / sizeof(int), false);
      HIFrame_statusbar->SetStatusText(wxT("Selected ") +
	  combo_box_sensors_system->
	  GetValue(), 0);
    }
  }
  catch(runtime_error e) {
    char str[128];
    this->GetMenuBar()->Check( READBUTTON_ID, !this->GetMenuBar()->IsChecked( READBUTTON_ID));
    sprintf(str, DEBPOS"%s", e.what());
    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
  }
}


void HIFrame::OnSaveCalibration(wxCommandEvent & event)
{
    try {

	if (!_currentSensSys)
	    throw ExceptionNoSensorsSystem(DEBPOS
					   "SensorsSystem not Selected");
        wxString path = wxString(_mmdPath.c_str() , wxConvUTF8);
	wxFileDialog dialog(this, _T("Open file"), path,
			    wxEmptyString, _T("MMD files (*.mmd)|*.mmd"),
			    wxSAVE);
	
	dialog.CentreOnParent();

	if (dialog.ShowModal() == wxID_OK) {
	   
	    wxFileName fileName(dialog.GetPath(),wxPATH_UNIX);
	    if (_fileMMD->writeData(_currentSensSys,
		     string((dialog.GetDirectory()+wxString(_T("/"))).fn_str()),
		     string((fileName.GetName()+wxString(_T(".mmd"))).fn_str()))) {
                 DEBOUT(("File %s saved \n",
		    static_cast <
		    const char *>((dialog.GetDirectory()+wxString(_T("/"))+fileName.GetName()+wxString(_T(".mmd"))).fn_str())));
	    
		int enableList[] = { COMBOBOX_ID, MOCAPBUTTON_ID };
		int disableList[] =
		    { RESETBUTTON_ID, SAVECALIBRATIONBUTTON_ID };
		enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			      true);
		enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			      false);
		     }
	    DEBOUT(("HIFrame::OnSaveCalibration()\n"));
	    return;
	}
    }
    catch(runtime_error e) {
      char str[128];
      sprintf(str, DEBPOS"%s", e.what());
      wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
    }
    return;
}

void HIFrame::OnVirtualStickModel(wxCommandEvent & event){
  try {
	
    if(_virtualStick->IsShown()){
      _virtualStick->Show(false);
//       _actuators->deactiveChannel(ActuatorType::VIRTUALSTICKJOINTS);
    }
    else {
//       _actuators->activeChannel(ActuatorType::VIRTUALSTICKJOINTS);
      _virtualStick->Move(wxPoint(this->GetPosition().x+this->GetSize().GetWidth()*2,this->GetPosition().y));
      _virtualStick->Show(true);
      _virtualStick->Render();
    }
  }
  catch(runtime_error e) {
    char str[128];
    sprintf(str, DEBPOS"%s", e.what());
    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
  }
}

void HIFrame::OnVirtualRobotModel(wxCommandEvent & event){
  try {
	
    if(_virtualRobot->IsShown()){
      _virtualRobot->Show(false);
//       _actuators->deactiveChannel(ActuatorType::VIRTUALSTICKJOINTS);
    }
    else {
//       _actuators->activeChannel(ActuatorType::VIRTUALSTICKJOINTS);
      _virtualRobot->Move(wxPoint(this->GetPosition().x+this->GetSize().GetWidth()*2,this->GetPosition().y));
      _virtualRobot->Show(true);
      _virtualRobot->Render();
    }
  }
  catch(runtime_error e) {
    char str[128];
    sprintf(str, DEBPOS"%s", e.what());
    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
  }
}

void HIFrame::OnOpenFile(wxCommandEvent & event)
{
  wxString path = wxString(_mmdPath.c_str() , wxConvUTF8);
    wxFileDialog dialog
	(this, _T("Open file"), path, wxEmptyString,
	 _T("MMD files (*.mmd)|*.mmd"));

    dialog.CentreOnParent();

    if (dialog.ShowModal() == wxID_OK) {
	DEBOUT(("File %s opened \n",
		static_cast < const char *>(dialog.GetPath().fn_str())));
	try{
	  wxFileName fileName(dialog.GetPath(),wxPATH_UNIX);
	  if (_fileMMD->writeData(_currentSensSys,
	      string((dialog.GetDirectory()+wxString(_T("/"))).fn_str()),
	      string((fileName.GetName()+wxString(_T(".mmd"))).fn_str()))) {
		DEBOUT(("File %s saved \n",
			static_cast <
			    const char *>((dialog.GetDirectory()+wxString(_T("/"))+fileName.GetName()+wxString(_T(".mmd"))).fn_str())));
	    
		int enableList[] = { COMBOBOX_ID, MOCAPBUTTON_ID };
		int disableList[] =
		{ RESETBUTTON_ID, SAVECALIBRATIONBUTTON_ID };
		enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			      true);
		enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			      false);
	      }
	
	}
	catch(runtime_error e) {
	  char str[128];
	  sprintf(str, DEBPOS"%s", e.what());
	  wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
      }
      combo_box_sensors_system->Append(dialog.GetPath());
	
    }
    return;
}

void HIFrame::OnMoCap(wxCommandEvent & event){
   
	//Salva la label del bottone
	wxString str = button_MoCap->GetLabel();
	//Start del Mocap
	if (str.Contains(wxT("START"))) {
	  try {
	    //Controlla se esiste il SensorsSystem
	    if (!_currentSensSys)
		throw(ExceptionNoSensorsSystem
		      (DEBPOS "SensorsSystem not Selected"));
	    if (this->
		startMoCap(_currentSensSys->
			   getNumSensors())) {
		button_MoCap->SetLabel(wxT("MoCap STOP"));
		int listEnable[] = { };
		int listDisable[] = { COMBOBOX_ID, CALIBRATEBUTTON_ID, READBUTTON_ID };
		enableWidgets(listDisable,
			      sizeof(listDisable) / sizeof(int), false);
		enableWidgets(listEnable, sizeof(listEnable) / sizeof(int),
			      true);
		HIFrame_statusbar->SetStatusText(wxString::Format(_T("Frame\t%d/%d"),_fileMCD->getNumFrames()?_fileMCD->getNumFrames()-1:0,0),1);
	    }
	  }
	  catch(runtime_error e) {
	    char str[128];
	    sprintf(str, DEBPOS"%s", e.what());
	    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
	  }
	}
	//Stop del MoCap
	if (str.Contains(wxT("STOP"))) {
	  try{
	  DEBOUT(("OnMocap() contains STOP\n"));
	    //Ferma il timer
	    this->stopMoCap();
	    
	    //ricava il nome del file in cui salvare il movimento
            wxString path =  wxString(_mcdPath.c_str() , wxConvUTF8);
	    wxFileDialog dialog
		(this, _T("Save File"), path, wxEmptyString,
		 _T("MCD files (*.mcd)|*.mcd"), wxSAVE);
            
	    dialog.CentreOnParent();
	    //Se la finestra v�a buon fine salva le informazioni nel file .mcd
	    if (dialog.ShowModal() == wxID_OK) {
	      wxFileName fileName(dialog.GetPath(),wxPATH_UNIX);
		if (this->saveCurrentMoCapData(dialog.GetDirectory()+wxString(_T("/"))+fileName.GetName()+wxString(_T(".mcd"))))
		DEBOUT(("File %s saved \n",static_cast <const char *>( (dialog.GetDirectory()+wxString(_T("/"))+fileName.GetName()+wxString(_T(".mcd")) ).fn_str())));
               
	    }
	    //altrimenti lancia un'eccezione e avvisa che il file nn è stato salvato
	    else {
	      button_MoCap->SetLabel(wxT("MoCap START"));
	      throw ExceptionMCDFile("File not saved");
	      
	    }
	    //altrimenti il timer continua ad andre
// 	   _readSensorsTimer->Start(static_cast <int >((1.0 / static_cast <double>(FPSREADING))*1000.0));
	    button_MoCap->SetLabel(wxT("MoCap START"));
	    HIFrame_statusbar->SetStatusText(_T(""),1);
	  }
	  catch(runtime_error e) {
	    char str[128];
	    sprintf(str, DEBPOS"%s", e.what());
	    wxMessageBox(wxString::Format(DEBPOS _T("%s"), e.what()), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
	  }
	  
	  int listEnable[] = { CALIBRATEBUTTON_ID,READBUTTON_ID };
	  int listDisable[] = { };
	  enableWidgets(listDisable, sizeof(listDisable) / sizeof(int),
			false);
	  enableWidgets(listEnable, sizeof(listEnable) / sizeof(int),
			true);
	}
	
    //DEBOUT(("HIFrame::OnMoCap()\n"));
}


void HIFrame::OnStartCortex(wxCommandEvent & event)
{
  if (this->GetMenuBar()->IsChecked(STARTCORTEX_ID)) {	//start cortex
// 	int enableList[] = { COMBOBOX_ID };
// 	int disableList[] = { OPENFILE_ID, SIMULATIONBUTTON_ID };

	//enableWidgets(enableList,sizeof(enableList)/sizeof(int),true);
	//enableWidgets(disableList,sizeof(disableList)/sizeof(int),false);
	HIFrame_menubar->FindItem(STARTCORTEX_ID)->
	    SetText(wxT("&Stop Cortex"));
// 	_isCortexStarted = true;

    } else {			//stop cortex
// 	int enableList[] = { OPENFILE_ID, SIMULATIONBUTTON_ID };
// 	int disableList[] =
// 	    { COMBOBOX_ID, CALIBRATEBUTTON_ID, SAVECALIBRATIONBUTTON_ID,
// 	    RESETBUTTON_ID, MOCAPBUTTON_ID
// 	};

	//enableWidgets(enableList,sizeof(enableList)/sizeof(int),true);
	//enableWidgets(disableList,sizeof(disableList)/sizeof(int),false);
	HIFrame_menubar->FindItem(STARTCORTEX_ID)->
	    SetText(wxT("&Start Cortex"));
// 	_isCortexStarted = false;
    }
    DEBOUT(("HIFrame::OnStartCortex()\n"));
}

void HIFrame::OnShowGrid(wxCommandEvent & event){
  _gridPanel->Show(
        this->GetMenuBar()->IsChecked( SHOWGRID_ID ) );
	_gridPanel->CenterOnParent();
}



void HIFrame::OnCloseWindow(wxCloseEvent & event)
{

    if (_fileMMD) {
	delete(_fileMMD);
	_fileMMD =0;
    }
    this->~HIFrame();

//   DEBOUT(("OnCloseWindow()\n"));
}

void HIFrame::OnExit(wxCommandEvent & event)
{
    if (_fileMMD) {
	delete(_fileMMD);
	_fileMMD =0;
    }
    this->~HIFrame();

//   DEBOUT(("OnExit()\n"));
}

void HIFrame::OnSimulation(wxCommandEvent & event)
{
    try {
      if (HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->IsChecked()) {	//abilita la simulation
          wxString path = wxString(_mcdPath.c_str() , wxConvUTF8);
          
      
	  //DEBOUT(("Prima %s\n",string(path.fn_str()).c_str()));
	    wxFileDialog dialog
		(this, wxT("Open file"), path, wxEmptyString,
		 _T("MCD files (*.mcd)|*.mcd"), wxFILE_MUST_EXIST|wxCHANGE_DIR|wxOPEN);
	    
	    dialog.CentreOnParent();
            
	    if (dialog.ShowModal() == wxID_OK) {
		if (!wxFileExists(dialog.GetPath())) {
		    wxLogError(wxT("File ") + dialog.GetFilename() +
			       wxT(" not exist"),
			       wxT("wxWidgets Internal Error"));
		    OnSimulation(event);

		    return;
		}
// 		if (_scene3DTimer->IsRunning())
// 		    _scene3DTimer->Stop();

		this->loadMCD(dialog.GetPath());
		this->startSimulation();

		DEBOUT(("File %s opened \n",
			static_cast <
			const char *>(dialog.GetPath().fn_str())));
// 		_isSimulating = true;
// 		HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->SetText(wxT("Sim ON"));
		
		_virtualStick->SetTitle(dialog.GetFilename());
                
		
		HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->Check(true);
		int enableList[] = { FRAMEVIRTUALSTICKS_ID,GRIDPANEL_ID,  CONNECTION_ID,BEGINBUTTON_ID, PREVIOUSFRAMEBUTTON_ID,PLAYBUTTON_ID,STOPBUTTON_ID,LOOPBUTTON_ID,ENDBUTTON_ID,NEXTFRAMEBUTTON_ID,SLIDER_ID};

		int disableList[] = { READBUTTON_ID,MOCAPBUTTON_ID, RESETBUTTON_ID,
		    CALIBRATEBUTTON_ID,
		    SAVECALIBRATIONBUTTON_ID, COMBOBOX_ID,
		    STARTCORTEX_ID
		};

		enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			      true);
		enableWidgets(disableList,
			      sizeof(disableList) / sizeof(int), false);
		HIFrame_statusbar->SetStatusText(wxT("Simulation Mode"), 0);
		HIFrame_statusbar->SetStatusText(wxString::Format(_T("Frame\t%d/%d"), _slider->GetValue(),_slider->GetMax()-1),1);
	    }
	    else{
	      HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->Check(false);
	      return;
	    }
	} else {		//disabilita la simulazione
// 	    _isSimulating = false;
	    this->stopSimulation();
	    HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->Check(false);
// 	    _virtualStick->SimulationOff(event);
	    _virtualStick->SetTitle(_T("Virtual Sticks"));
            
	    
	    int enableList[] = { COMBOBOX_ID,READBUTTON_ID };
	    int disableList[] = { /*FRAME3D_ID,*/ BEGINBUTTON_ID,PREVIOUSFRAMEBUTTON_ID,PLAYBUTTON_ID,STOPBUTTON_ID,LOOPBUTTON_ID,NEXTFRAMEBUTTON_ID,ENDBUTTON_ID,SLIDER_ID,CONNECTION_ID };
	    enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
	    enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
	    HIFrame_statusbar->SetStatusText(wxT("Selected ") +
		combo_box_sensors_system->
		GetValue(), 0);
	    HIFrame_statusbar->SetStatusText(_T(""),1);
	}
	event.Skip();
    }
    catch(runtime_error e) {
      char str[128];
      sprintf(str, DEBPOS"%s", e.what());
      wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
    }
}

void HIFrame::OnConnection(wxCommandEvent & event){
    
	//Si vuole aprire una nuova comunicazione
	if ((HIFrame_menubar->FindItem(CONNECTION_ID)->GetText()).
	    Find(_T("Co_nnect")) >= 0) {
	  try {
	    char ip[32],tempAddress[128];
	    int port;
	    sprintf(tempAddress, "%s:%d", _naisIp.c_str(), _naisPort);
	    wxString address;
	    //restistuisce e converte il valore immesso in char*
	    address =
		wxGetTextFromUser(wxT("Example 127.0.0.1:66666"),
				  wxT("Insert IP Address and Port"),
				  wxString(tempAddress, wxConvUTF8), this,
				  wxDefaultCoord, wxDefaultCoord, true);
	    //caso in cui si clicca "Cancel"
	    if (address.IsEmpty()) {
		DEBOUT(("Empty\n"));
		return;
	    }
	    //Parsing dell'indirizzo IP e della porta
	    int pos = address.Find(wxT(":"));
	    //get ip address
	    
	    if (sscanf((address.SubString(0, pos - 1)).fn_str(), "%s", ip)
		== 1 &&
		//get port
		sscanf((address.SubString(pos + 1, address.Length() - 1)).fn_str(), "%d", &port) == 1) {
		
		this->startConnection( port, ip);
	    } 
	    else {
	      throw ExceptionAddress(DEBPOS "Address bad formed");
	    }
		
	    
	    
	    int enableList[] = {};
	    int disableList[] = {SIMULATIONBUTTON_ID,READBUTTON_ID,COMBOBOX_ID};
	    enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
	    enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
	 
	    return;
	  }
	  catch(runtime_error e) {
	    this->stopConnection();
	    char str[128];
	    sprintf(str, DEBPOS"%s", e.what());
	    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
// 	    wxLogError(wxString(str, wxConvUTF8));
	  }
	}
	//La comunicazione viene chiusa
	else if ((HIFrame_menubar->FindItem(CONNECTION_ID)->GetText()).
		 Find(_T("Disco_nnect")) >= 0) {
	  try{
	    this->stopConnection();
	    
	    int enableList[] = {HIFrame_menubar->FindItem(SIMULATIONBUTTON_ID)->IsChecked()?SIMULATIONBUTTON_ID:READBUTTON_ID};
	    int disableList[] = {
	      };
	    
	    enableWidgets(enableList, sizeof(enableList) / sizeof(int),
			  true);
	    enableWidgets(disableList, sizeof(disableList) / sizeof(int),
			  false);
	    
	    return;
	  }
	  catch(runtime_error e) {
	    char str[128];
	    sprintf(str, DEBPOS"%s", e.what());
	    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
	  }
	}
}

void HIFrame::OnReadProjectVars(wxCommandEvent & event){
  wxString path = wxString((_projectPath+string("/Config/")).c_str(), wxConvUTF8);
  wxFileDialog dialog
      (this, wxT("Open Config File"), path, wxEmptyString,
       _T("CFG (*.cfg)|*.cfg|All (*.*)|*.*"), wxFILE_MUST_EXIST|wxCHANGE_DIR|wxOPEN);
  dialog.CentreOnParent();
  if (dialog.ShowModal() == wxID_OK) {
    if (!wxFileExists(dialog.GetPath())) {
      wxLogError(wxT("File ") + dialog.GetFilename() +
	  wxT(" not exist"),
      wxT("wxWidgets Internal Error"));
      return;
    }
    else{
      readProjectVars(string((dialog.GetFilename()).fn_str()));
      DEBOUT(("Project Vars Readed\n"));
    }
  }
}

void HIFrame::connectionProblem(int idTimer){
  try{
    wxCommandEvent e;
  this->OnConnection(e);
  char str[128];
  sprintf(str, DEBPOS"Connection Error, server doesn't reply %d", idTimer);
  wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
  }
  catch(runtime_error e) {
    char str[128];
    sprintf(str, DEBPOS"%s", e.what());
    wxMessageBox(wxString(str, wxConvUTF8), wxString("Error", wxConvUTF8), wxOK|wxICON_ERROR,this);
  }
}

