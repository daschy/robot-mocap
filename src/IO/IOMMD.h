#ifndef IOMMD_DEFINED
#define IOMMD_DEFINED

#include<math.h>
#include<map>
#include<vector>
#include<string>
#include<debug.h>
#include<TokenIterator.h>
#include<Headers/IOTypes.h>
#include<Sensors/SensorsSystem.h>
#include<Headers/Exceptions.h>


using namespace std;

/** Classe che gestisce Input e Output dei file \em .mmd.\n
    I file \em .mmd contengono informazioni circa i markers presenti nel sistema di acquisizione; inoltre sono contenute informazioni utili per il rettargetting.\n
    Segue un esempio della struttura di un file \em .mmd .\n
    La sezione \em MARKERS_AND_LABELS specifica il numero di makers e i loro nomi. \n
    #######BEGIN_MARKERS_AND_LABELS_SECTION######## \n
    1-SHOULDER \n
    2-ELBOW \n
    3-KNUCKLE \n
    #######END_MARKERS_AND_LABELS_SECTION######## \n \n
    La sezione \em MIN_&_MAX specifica la bounding box nella quale si muove il modello.\n
    #######BEGIN_MIN_&_MAX_SECTION######## \n
    minX: 0 MaxX: 0 \n
    minY: 0 MaxY: 0 \n
    minZ: 0 MaxZ: 0 \n
    #######END_MIN_&_MAX_SECTION######## \n \n
    La sezione \em STICKS_AVERAGE specifica media e varianza (rispettivamente) di ciascun marker. \n
    #######BEGIN_STICKS_AVERAGE_SECTION######## \n
    1-nan,nan \n
    2-nan,nan \n
    3-4.000000,5.000000 \n
    #######END_STICKS_AVERAGE_SECTION######## \n \n
    La sezione \em CALIBRATION specifica i parametri di calibrazione di ciascun marker. \n
    #######BEGIN_CALIBRATION_SECTION######## \n
    1-nan,nan \n
    2-nan,nan \n
    3-5,6 \n
    #######END_CALIBRATION_SECTION######## \n
    @author Milo Ertola
    @version 0.1
 */
class IOMMD{
  public:
    /**
    Costruisce la classe: inizializza gli attributi della classe con i parametri di input. Definisce il formato del file \em .mmd .
    @param[in] path indica il path del file compresa l'estensione. Se il file non esiste viene creato, se esiste viene sovrascritto
    */
    IOMMD();
    
    /**
    Distruttore della classe. Distrugge tutti gli attributi contenitore delle classe (vectors e map).
    */
    virtual ~IOMMD();
    
    bool writeData(SensorsSystem* sensSys, const char* path, const char* filename);

    bool writeData(SensorsSystem* sensSys, string path, string filename);
    
    SensorsSystem* importData(const char *path,const char* filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error);
    
    SensorsSystem* importData(string path, string filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile, runtime_error);
    
  private:
    
    /**
    Il metodo scrive su #_file la stringa data.\n
    @param[in] str stringa di input
    @param[in] append flag che indica se fare l'append della stringa del file
    @return true se la scrittura �andata a buon fine, false altrimenti.
    */
    bool writeString(string str, string filename,  bool append=false);
    
    /**
    Il metodo scrive su #_file il vettore di char di input.\n
    @param[in] str vettore di char di input
    @param[in] append flag che indica se fare l'append della stringa del file
    @return true se la scrittura �andata a buon fine, false altrimenti.
    */
    bool writeString(const char* str, const char* filename, bool append=false);
    
   vector<SensorsAttributes>  importSensors(const char *path,const char* filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error);
   
    vector<SensorsAttributes> importSensorCollection(const char *path,const char* filename) throw (ExceptionSensors,ExceptionValueNotFound,ExceptionSectionNotFound,ExceptionParseError,ExceptionErrorOpeningFile,runtime_error);


  private:
    
};
#endif
