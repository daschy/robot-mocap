#include "HIFrame.h"

bool HIFrame::loadMCD(wxString str) throw(ExceptionMCDFile)
{
    return loadMCD(string(str.fn_str()));
}

bool HIFrame::loadMCD(string str) throw(ExceptionMCDFile)
{
    try {
	_fileMCD->eraseData();
	_fileMCD->importData(str);
// 	_virtualStick->setData(_fileMCD->getData());
	//_fileMCD->eraseData();
	DEBOUT(("num frames loaded %d\n",_fileMCD->getNumFrames()));
        DEBOUT(("HIFrame::loadMCD(string str) FINE\n"));
	return true;
    }
    catch(ExceptionParseError e) {
	char buffer[128];
        sprintf(buffer,  DEBPOS"In file %s %s",
		_fileMCD->getPath().c_str(), e.what());
	throw ExceptionMCDFile(buffer);
    }

}

bool HIFrame::saveCurrentMoCapData(string str) throw(ExceptionMCDFile)
{
//   DEBOUT(("Prova1\n"));
	_fileMCD->setFramerate(FPSMOCAP);
	_fileMCD->setNumMarkers(_currentSensSys->getNumSensors());
	DEBOUT(("saveCurrentMoCapData() %s\n",str.c_str()));
    bool temp = _fileMCD->writeData(str);
//   DEBOUT(("Prova5\n"));
    return temp;
}

bool HIFrame::saveCurrentMoCapData(wxString str) throw(ExceptionMCDFile)
{
    return this->saveCurrentMoCapData(string(str.fn_str()));
}


// bool HIFrame::writeData() throw(ExceptionMCDFile)
// {
//     if (!_fileMCD)
// 	throw ExceptionMCDFile(DEBPOS "File .mcd not present");
//     return _fileMCD->writeData();
// }
