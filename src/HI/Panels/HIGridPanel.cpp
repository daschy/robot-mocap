#include "HIGridPanel.h"
#include<debug.h>


HIGridPanel::HIGridPanel(wxWindow * parent, wxWindowID id, wxPoint position,long style):wxFrame(parent, id, wxEmptyString,position, wxDefaultSize,style/*wxDEFAULT_FRAME_STYLE*/)
{
    
 
  if ( wxSystemSettings::GetScreenType() > wxSYS_SCREEN_SMALL )
    SetSize(wxSize(520, 300));
  
    _titles.push_back(wxT("SENSOR ID"));
    _titles.push_back(wxT("STATE"));
    _titles.push_back(wxT("CURR VALUE"));
    _titles.push_back(wxT("JOINT ID"));
    _titles.push_back(wxT("JOINT VALUE"));
    _titles.push_back(wxT("INITVALUE"));
    _titles.push_back(wxT("CLEANED VALUE"));
    _titles.push_back(wxT("DEGREE"));
    _titles.push_back(wxT("URAD"));
    _titles.push_back(wxT("MIN VALUE"));
    _titles.push_back(wxT("MAX VALUE"));
    _titles.push_back(wxT("HISTORY"));
    
    _initValue=-1;
    _numCols = static_cast<int>(_titles.size());
    _numRows = 14;
    
//     _grid = new wxGrid( this,
//                        wxID_ANY,
//                        wxPoint( 0, 0 ),
//                        wxDefaultSize, wxWANTS_CHARS );

    
    _listGrid = new wxListCtrl(this, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxLC_REPORT);
    
    for ( unsigned int i = 0; i < _titles.size(); ++i )
    {
      _listGrid->InsertColumn(i, _titles[i] , wxLIST_FORMAT_CENTER, 100);
      _listGrid->SetColumnWidth( i, wxLIST_AUTOSIZE_USEHEADER );
    }

    
    
   makeTextMatrix();
   do_layoutMatrix();
    do_layout();
    
    
    
    DEBOUT(("HIGridPanel::HIGridPanel()\n"));
}

HIGridPanel::~HIGridPanel()
{
    DestroyChildren();
    DEBOUT(("HIGridPanel::~HIGridPanel()\n"));
}


void HIGridPanel::do_layout()
{
//     wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
//     topSizer->Add( _listGrid,
//                    1,
//                    wxEXPAND );
//     
//     
//     //topSizer->Fit(this);
    //SetAutoLayout(true);
//     SetSizer(topSizer);

    
//     Layout();
    
//     wxSize size = GetClientSize();
//     wxCoord y = (2*size.y)/3;
//     SetSize(0, 0, size.x, size.y);
}

void HIGridPanel::makeTextMatrix()
{

 
long temp;
  for ( int i = 0; i < _numRows; ++i )
  {
    temp = _listGrid->InsertItem(i,wxString::Format(wxT("%d"), _initValue));
    for (int j = 0; j < _numCols; ++j )
    {
      
      _listGrid->SetItem(temp,j,wxString::Format(wxT("%d"), _initValue));
    }
  }


}

void HIGridPanel::setText(int row, int col, string str)
{
    _listGrid->SetItem(row,col,wxString(str.c_str(), wxConvUTF8));
    return;
}

void HIGridPanel::setText(int row, int col, int value)
{
  _listGrid->SetItem(row,col,wxString::Format(wxT("%d"), value));
    return;
}

void HIGridPanel::setColText(int col, vector < int >& value)
{

    for (unsigned int i = 0; i < value.size(); ++i) {
  _listGrid->SetItem(i,col,wxString::Format(wxT("%d"), value[i]));
    }

}

void HIGridPanel::setText(int row, int col, double value)
{
  _listGrid->SetItem(row,col,wxString::Format(wxT("%f"), value));
    return;
}

void HIGridPanel::setColText(int col, vector<double>& value)
{

    for (unsigned int i = 0; i < value.size(); ++i) {
      _listGrid->SetItem(i,col,wxString::Format(wxT("%f"), value[i]));
    }
}

// vector<int> 
// HIGridPanel::getIDsColumn(){
//    vector<int> tempVec;
//   int temp=0;
//   
//   for(int i=0; i<_numRows; ++i){
//     sscanf(_listGrid->GetItemText(static_cast<long>(i)).fn_str(),"%d",&temp);
//     tempVec.push_back(temp);
//   }
//   return tempVec;
// }
// 
// vector<int> 
// HIGridPanel::getCurrentValuesColumn(){
//   vector<int> tempVec;
//   int tempID=0, tempState=0,tempValue=0;
//   for(int i=0; i<_numRows; ++i){
//    /* sscanf(_listGrid->OnGetItemText(static_cast<long>(i),CURRVALUE_COLUMN).fn_str(),"%d",&tempValue);
// //    */
//   
//     tempVec.push_back(tempValue);
//   }
//      
//  
//   return tempVec;
// }

void HIGridPanel::initAll(int value)
{
    for (int i = 0; i < _numRows; ++i) {
	for (int j = 0; j < _numCols; ++j) {
// 	    _listGrid->SetItem(i,j,wxString::Format(wxT("(%d,%d)"), i,j));
	    _listGrid->SetItem(i,j,wxString::Format(wxT("%d"), value));
	}
    }
}

void 
HIGridPanel::resizeRows(int numRows){
  _listGrid->Hide();
  if(numRows<=0) numRows = 1;
  
  _numRows = numRows;
  
  _listGrid->DeleteAllItems();
  
  makeTextMatrix();
  
  do_layoutMatrix();
  _listGrid->Show();
//   int cw , ch;
//   this->GetClientSize( &cw, &ch );
//    SetSize(wxSize(cw,_grid->GetNumberRows()*(_grid->GetRowSize(0)+1)+ _grid->GetColLabelSize()+10));
  return;
}

void HIGridPanel::do_layoutMatrix(){
  
    for (int i = 0; i < _numRows; ++i) {
	for (int j = 0; j < _numCols; ++j) {
	   setText(i,j, _initValue);
// 	   _listGrid->SetReadOnly( i, j );
// 	   Marca grigio chiaro solo le righe pari
	}
	   if(i%2) _listGrid->SetItemBackgroundColour(static_cast<long>(i), *wxLIGHT_GREY);
	}

// 	DEBOUT(("size = %d %d\n", _listGrid->GetSize().GetWidth(),_listGrid->GetSize().GetHeight()));
	
//     _grid->AutoSize();
//     _grid->Refresh();
}
