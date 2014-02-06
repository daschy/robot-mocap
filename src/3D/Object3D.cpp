#include "Object3D.h"

#include <iostream>
#include "vtkCubeSource.h"
#include "vtkSphereSource.h"
#include <vtkSTLReader.h>
#include <vtkDecimatePro.h>
#include <vtkProperty.h>

#include<debug.h>
#include<TokenIterator.h>

#include <Headers/MACROS.h>

Object3D* Object3D::Object3DFactory(const char* directory,const char* filename) throw( ExceptionFileNotFound){
  
  Object3D* objTemp = new Object3D();
  
  FILE*  file = fopen((string(directory)+string(filename)).c_str(), "rb");
  
  if (file) {
      char tempChar;
      string tempStr = "";
      //legge tutti i caratteri nel file
      while (!feof(file)) {
	  tempChar = getc(file);
	  tempStr += tempChar;
      }
      fclose(file);
      objTemp->genStruct(string(directory),tempStr);
      objTemp->makeRoot();
      return objTemp; 
  }
  else {
      throw ExceptionFileNotFound(string("File ") + string(directory) + string(filename) + string(" not found\n"));
  }
}

Object3D::Object3D():_root(0),_robotList() {
 
}

Object3D::~Object3D(){
  if(_root) _root->Delete();
  DEBOUT(("Object3D::~Object3D()\n"));
}

void 
Object3D::makeRoot(){
  if(_root==NULL){
   _root = (_robotList.begin())->second.piece;
  }
}


vtkAssembly* 
Object3D::getAssembly(int& id) throw (ExceptionIdOutOfRange){
  map<int,list_dRobot>::iterator it = _robotList.find(id);
  if(it==_robotList.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("Part not found"));
  }
  return (it->second.piece);
}

bool 
Object3D::rotatePartAngles(int id, double angleX, double angleY, double angleZ) throw (ExceptionIdOutOfRange){
  map<int,list_dRobot>::iterator it = _robotList.find(id);
  if(it==_robotList.end()) {
    char temp[128];
    sprintf(temp,"%d",id);
    throw ExceptionIdOutOfRange(string(DEBPOS)+string(temp)+string(" Part not found"));
  }
  //Solo angleX o angleY o angleZ è diverso da 0
  int currentValue = static_cast<int>(DEGREETOVALUE(angleX+angleY+angleZ));
//   DEBOUT(("%d : (%.2f,%.2f,%.2f) %d\n",id,angleX,angleY,angleZ,currentValue));
  if(currentValue!=it->second.lastValue){
    (it->second.piece)->SetOrientation(angleX,angleY,angleZ);
    it->second.lastValue = currentValue;
    DEBOUT(("Angles Object3D %d (%f,%f,%f)\n",id,angleX,angleY,angleZ));
    return true;
  } 
  else return false;
}

bool 
Object3D::rotatePartAngle(int id, double angle, AxesRotations& axes) throw (ExceptionIdOutOfRange){
  map<int,list_dRobot>::iterator it = _robotList.find(id);
  if(it==_robotList.end()) {
    char temp[128];
    sprintf(temp,"%d",id);
    throw ExceptionIdOutOfRange(string(DEBPOS)+string(temp)+string(" Part not found"));
  }
  
  return this->rotatePartAngles(id,(axes.X)*angle,(axes.Y)*angle,(axes.Z)*angle);
}

void 
Object3D::setAxesRotations(int jointID, AxesRotations axes) throw (ExceptionIdOutOfRange){
  map<int,list_dRobot>::iterator it = _robotList.find(jointID);
  if(it==_robotList.end()) {
    throw ExceptionIdOutOfRange(string(DEBPOS)+string("Part not found"));
  }
  it->second.rot_axies = axes;
}

void 
Object3D::setAxesRotations(vector<int> jointIDs, vector<AxesRotations> axesVec) throw (ExceptionIdOutOfRange){
  for(unsigned int i=0; i<jointIDs.size();++i){
    this->setAxesRotations(jointIDs[i],axesVec[i]);
  }
}

void Object3D::addNode(vtkAssembly * item, int id, vtkAssembly* armPiece){
  
  _robotList[id] = list_dRobot(id, AxesRotations() , item);
  _robotList[id].armPiece0 = armPiece;
}

void Object3D::addNode(vtkAssembly * item, int id, vtkAssembly * armPiece0,vtkAssembly * armPiece1){
  _robotList[id] = list_dRobot(id, AxesRotations() , item);
  _robotList[id].armPiece0 = armPiece0;
  _robotList[id].armPiece1 = armPiece1;
}

void 
Object3D::addNode (vtkAssembly *item, int id, AxesRotations axRot) {	
  _robotList[id] = list_dRobot(id, axRot, item);
}

void 
Object3D::addNode(vtkAssembly * item, int id){
  _robotList[id] = list_dRobot(id, AxesRotations() , item);
}

vtkAssembly* 
Object3D::getRoot(){
 return  _root;
}




vector<int> 
Object3D::getIDs(){
  map<int, list_dRobot>::iterator it;
  vector<int> temp;
  for(it=_robotList.begin(); it!=_robotList.end();++it){
    temp.push_back(it->second.id);
  }
  return temp; 
  
}

void 
Object3D::addNode (vtkAssembly *item, int id, int axRot, bool rot_direction) { 
  AxesRotations rot_axies; 
  switch (axRot) {
	    case 0:
	      rot_axies.X = 0;
	      rot_axies.Y = 0;
	      rot_axies.Z = 0;
	      break;
	    case 1:{
		    rot_axies.X = (rot_direction? 1:-1);
		    rot_axies.Y = 0;
		    rot_axies.Z = 0;
		    break;
		}
	    case 2:{
	            rot_axies.X = 0;
		    rot_axies.Y = (rot_direction? 1:-1);
		    rot_axies.Z = 0;
		    break;
		}
	    case 3:{
	            rot_axies.X = 0;
		    rot_axies.Y = 0;
		    rot_axies.Z = (rot_direction? 1:-1);
		    break;
		}
	    case 4:{
		    rot_axies.X = (rot_direction? 1:-1);
		    rot_axies.Y = (rot_direction? 1:-1);
		    rot_axies.Z = 0;
		    break;
		}
	    case 5:{
		    rot_axies.X = (rot_direction? 1:-1);
		    rot_axies.Y = 0;
		    rot_axies.Z = (rot_direction? 1:-1);
		    break;
		}
	    case 6:{
		    rot_axies.X =0;
		    rot_axies.Y = (rot_direction? 1:-1);
		    rot_axies.Z = (rot_direction? 1:-1);
		    break;
		}
	    case 7:{
	            rot_axies.X = (rot_direction? 1:-1);
	            rot_axies.Y = (rot_direction? 1:-1);
		    rot_axies.Z = (rot_direction? 1:-1);
		    break;
		}
	      default:
		break;
	    }
 addNode(item, id,rot_axies );
}

vtkAssembly* Object3D::genStruct (string directory,  string genTxt)  {
	if ( genTxt == "" ) return NULL;
	else {
		string actorValues;
		int pos;
		//VALORI PER ACTOR:
		int id, rot_axies;
		bool rot_direction;
		Point3D position, rotation;
		string file_name, nick;
		Delimiters delim(",");

		pos = genTxt.find_first_of ("ASSEMBLY<ACTOR<");
		if ( pos == 0 ){
			//tutto ok, creo l'assembly
			vtkAssembly *ass = vtkAssembly::New ();
			
			//Parse Actor
			actorValues = genTxt.substr ( pos + 15 );
			pos = actorValues.find_first_of (">");
			actorValues = actorValues.substr ( 0, pos );

			TokenIterator<std::string::iterator,Delimiters> iter(actorValues.begin(), actorValues.end(), delim);
			//TokenIterator<std::string::iterator,Delimiters> iterEnd;

			id = atoi((*iter).c_str());
			++iter;
			file_name = directory+((string)((*iter).c_str ()));
			++iter;
			nick = (string)((*iter).c_str ());
			++iter;
			position.X = atoi((*iter).c_str ());
			++iter;
			position.Y = atoi((*iter).c_str ());
			++iter;
			position.Z = atoi((*iter).c_str ());
			++iter;
			rotation.X = atoi((*iter).c_str ());
			++iter;
			rotation.Y = atoi((*iter).c_str ());
			++iter;
			rotation.Z = atoi((*iter).c_str ());
			++iter;
			rot_axies = atoi((*iter).c_str ());
			++iter;
			rot_direction = atoi((*iter).c_str ()) == 0 ? false : true;

			//creo l'attore e lo aggiungo all'assembly
			vtkPolyDataMapper *mapper = vtkPolyDataMapper::New ();
			if (file_name == "vtkCubeSource") {
				vtkCubeSource *obj = vtkCubeSource::New ();
				vtkDecimatePro* deci = vtkDecimatePro::New();
				deci->SetInputConnection(obj->GetOutputPort());
				deci->SetTargetReduction(0.9);
				deci->SplittingOn();
				deci->SetMaximumError(VTK_DOUBLE_MAX);
				deci->BoundaryVertexDeletionOn();
				deci->PreserveTopologyOn();
				mapper->SetInput ( deci->GetOutput () );
				deci->Delete();
				obj->Delete ();
			}
			else if (file_name == "vtkSphereSource") {
				vtkSphereSource *obj = vtkSphereSource::New ();
				vtkDecimatePro* deci = vtkDecimatePro::New();
				deci->SetInputConnection(obj->GetOutputPort());
				deci->SetTargetReduction(0.9);
				deci->SplittingOn();
				deci->SetMaximumError(VTK_DOUBLE_MAX);
				deci->BoundaryVertexDeletionOn();
				deci->PreserveTopologyOn();
				mapper->SetInput ( deci->GetOutput () );
				deci->Delete();
				obj->Delete ();
				
			}
			else {
				vtkSTLReader *obj = vtkSTLReader::New();
				obj->SetFileName (file_name.c_str());
				vtkDecimatePro* deci = vtkDecimatePro::New();
				deci->SetInputConnection(obj->GetOutputPort());
				deci->SetTargetReduction(0.9);
				deci->SplittingOn();
				deci->SetMaximumError(VTK_DOUBLE_MAX);
				deci->BoundaryVertexDeletionOn();
				deci->PreserveTopologyOn();
				mapper->SetInput ( deci->GetOutput ());
				deci->Delete();
				obj->Delete ();
				
			}

			vtkActor *act = vtkActor::New ();
			act->SetMapper ( mapper );
// 			act->GetProperty()->SetColor(0.5,0.3,0.2);
			//act->SetPosition ( x, y, 0 );
			act->SetPosition ( position.X, position.Y, position.Z );
			act->SetOrientation ( rotation.X, rotation.Y, rotation.Z );	
			act->GetProperty()->SetAmbient(0.5);
			act->GetProperty()->SetDiffuse(0.0);
			act->GetProperty()->SetSpecular(1.0);	
			ass->AddPart ( act );
			ass->SetOrigin ( position.X, position.Y, position.Z );
			//obj->Delete ();
			mapper->Delete ();
			act->Delete ();
			
			genTxt = genTxt.substr ( pos + 17 );
			string istruct = genTxt;

			while (genTxt.substr ( 0, 3 ) != "NIL") {
				
				//Isola l'istruzione tra parentesi...
				int parentesi = 0;
				int pos_istr = 0;
				int posOpen = 0, posClose = 0;
				do {
					posClose = istruct.find_first_of ( ">", pos_istr );
					posOpen = istruct.find_first_of ( "<", pos_istr );
					pos_istr = ( posOpen > 0 ? ((posClose < posOpen ? posClose : posOpen)+1) : posClose+1 );
					parentesi = parentesi + ( posOpen > 0 ? (posClose < posOpen ? -1 : 1) : -1 );
				} while (parentesi > 0);
				istruct = istruct.substr ( 0 , pos_istr );
				vtkAssembly *assTmp = genStruct ( directory,istruct );
				if ( assTmp != NULL )	ass->AddPart ( assTmp );

				genTxt = genTxt.substr ( pos_istr+1 );
				istruct = genTxt;
			}

			addNode ( ass, id, rot_axies, rot_direction );
			return ass;

		}else return NULL;
	}
}
