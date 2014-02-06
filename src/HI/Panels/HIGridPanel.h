#ifndef HIGRIDPANEL_H
#define HIGRIDPANEL_H

#include <wx/wx.h>
#include <wx/image.h>
#include<wx/grid.h>
#include<wx/listctrl.h>
#include<vector>


using namespace std;

/**
La classe rappresenta la grigla presente in HIFrame
*/
class HIGridPanel:public wxFrame {
  public:
    HIGridPanel(wxWindow * parent, wxWindowID id,wxPoint position = wxDefaultPosition, long style = wxFRAME_TOOL_WINDOW|wxRESIZE_BORDER|wxSTAY_ON_TOP);
     virtual ~ HIGridPanel();
    
     
    void setText(int row, int col, string str);
    void setText(int row, int col, int value);
    void setText(int row, int col, double value);
    
    void setColText(int col, vector<int>& value);
    void setColText(int col, vector<double>& value);
    
    void setColTitle(int numCol);
    void resizeRows(int numRows);	//da implementare
    void initAll(int value);
    int getNumCols() {
	return _numCols;
    };
    
    int getNumRows() {
      return _numRows;
    };
    
// /*    vector<int> getIDsColumn();
//     vector<int> getCurrentValuesColumn*/();
    
  public:
      enum{
      ID_COLUMN = 0,
      STATE_COLUMN,
      CURRVALUE_COLUMN,
      JOINTID_COLUMN,
      JOINTVALUE_COLUMN,
      INITVALUE_COLUMN,
      CLEANEDVALUE_COLUMN,
      DEGREEVALUE_COLUMN,
      URADIANTSVALUE_COLUMN,
      MINVALUE_COLUMN,
      MAXVALUE_COLUMN,
      HISTORY_COLUMN
    };


  private:
    void makeTextMatrix();
    void do_layout();
    void do_layoutMatrix();
  private:
    int _numRows, _numCols, _initValue;
    vector < wxString > _titles;
    
    
    
//     wxGrid* _grid;
    wxListCtrl* _listGrid;
    
};
#endif
