#ifndef IOMCD_DEFINED
#define IOMCD_DEFINED

#include<stdio.h>
#include <sys/stat.h>
#include<string>
#include<vector>
#include<Headers/IOTypes.h>
#include<Headers/Exceptions.h>


using namespace std;

/** Classe che gestisce Input e Output dei file \em .mcd.\n
    Essi contengono le informazioni di MoCap.\n
    La struttura di un file \em .mcd �la seguente:\n
    frames =#_numFrames   markers = #_numMarkers  Hz = #_frameRate \n
    \em FRAME1 \n
    \em FRAME2. \n
    Ciascun \em FRAME# �formato da un numero di righe pari a #_numMarkers. \n
    @author Milo Ertola
    @version 0.1
 */
class IOMCD{
public:
  /** 
  Costruisce la classe: inizializza gli attributi della classe con i parametri di input. Definisce i pattern dell'attributo #_pattern
  @param[in] path indica il path del file compresa l'estensione. Se il file non esiste viene creato, se esiste viene sovrascritto
  @param[in] numMarkers numero di markers
  @param[in] frameRate frame rate.*/
  IOMCD(string path,int numMarkers, int frameRate) throw(ExceptionErrorOpeningFile);
  
  /**
  Distruttore: se il #_file �aperto lo chiude.
  */
  virtual ~IOMCD();
  
  
  
  /**
  Restituisce il percorso e il nome del file
  @return path del file.
   */
  string getPath(){return _filename;};
  
  /**
  Imposta la variabile #_numFrames.
  @param[in]numFrame numero di frames.
  */
  void setNumFrames( int numFrames){_numFrames=numFrames;};
  
  /**
  Imposta la variabile #_numMarkers.
  @param[in] numMarkers numero di markers.
  */
  void setNumMarkers(int numMarkers){_numMarkers=numMarkers;};
  
  /**
  Imposta la variabile #_frameRate.
  @param[in] frameRate numero di frame al secondo (u.m. Hz).
  */
  void setFramerate(int frameRate){_frameRate=frameRate;};
  
  /**
  Aggiunge gli angoli di rotazione di asse \em X di TUTTI marker in un frame. Il metodo aggiorna la variabile #_numFrames \n
  @param[in] data angoli di rotazione di ciascun marker di un frame.
  */
  void addFrame(vector<RotationInt> data) throw (ExceptionMCDFile);
  
  /**
  Il metodo fa il parsing del file definito da #_filename nel costruttore.Se trova un er
  rore lancia un'eccezione di tipo #ExceptionParseError.\n
  */
  bool importData(string filename) throw(ExceptionParseError);
  
  /**
  Il metodo scrive su file le informazioni memorizzate.\n
  @param[in] append se false scrive anche l'header, altrimenti scrive solo #_data
  @return true se tutto �andato a buon fine, false altrimenti.
  */
  bool writeData(string filename);
  
  /**
  Il metodo ritorna il reference alla rappresentazione interna dei dati
  @return #_data.
  */
  map<int, vector<RotationInt> >& getData(){return _data;};
  
  /**
  Il metodo ritorna il numero di frames memorizzati. \n
  @return #_numFrames.
  */
  int getNumFrames(){return _numFrames;};
  
  /**
  Il metodo ritorna l'indice associato al frame corrente. L'indicizzazione inizia da 0 fino a #_numFrames -1. \n
  @return #_currentFrame.
  */
  int getCurrentFrame(){return _currentFrame;};
  
  /**
  Il metodo ritorna il frame rate definito. \n
  @return #_frameRate.
  */
  int getFramerate(){return _frameRate;};
  
  /**
  Il metodo ritorna il numero di markers definiti. \n
  @return #_numMarkers.
  */
  int getNumMarkers(){return _numMarkers;};
  
  /**
  Il metodo ritorna il valore del marker nel frame di input. \n
  @param[in] frame frame voluto
  @param[in] joint marker voluto
  @return valore del marker al frame desiderato.
   */
  RotationInt getValue(int frame, int marker)throw(ExceptionMCDFile);
  
  /**
  Il metodo ritorna il valore del marker nel frame di indice #_currentFrame. \n
  @param[in] marker marker voluto
  @return valore del marker al frame di indice #_currentFrame.
   */
  RotationInt getValue(int marker)throw(ExceptionMCDFile);
  
  /**
  Il metodo fa avanzare l'indice #_currentFrame. \n
  */
  void next(){_currentFrame=_currentFrame+1; _currentFrame=_currentFrame%_numFrames;};
  
  /**
  Il metodo ritorna un vettore con i valori dei markers nel frame n mod #_numFrames.\n
  @param[in] n indice del frame
  @return vettore di \em AxesRotations.
  */
  vector<RotationInt> getFrame(int n) throw(ExceptionMCDFile);
  /**
  Il metodo ritorna un vettore con i valori dei markers nel frame corrente.\n
  @return vettore di \em AxesRotations.
    */
  vector<RotationInt> getFrame();
  
  /**
  Il metodo cancella o resetta gli attributi della classe.
   */
  void eraseData();
  
  /**
  Il metodo pone a 0 #_currentFrame, in altre parole, #_currentFrame riparte dal primo frame.
   */
  void resetCurrentFrame(){_currentFrame=0;};

private:
  
  /**
  Imposta la variabile #_filename.
  @param[in] path path e nome del file
   */
  void setPath(string path){_filename=path;};
  
  /**
  Il metodo scrive su #_file la stringa data.\n
  @param[in] str stringa di input
  @param[in] append flag che indica se fare l'append della stringa del file
  @return true se la scrittura �andata a buon fine, false altrimenti.
  */
  bool writeString(string str,  bool append=false);
  
  /**
  Il metodo scrive su #_file il vettore di char di input.\n
      @param[in] str vettore di char di input
      @param[in] append flag che indica se fare l'append della stringa del file
      @return true se la scrittura �andata a buon fine, false altrimenti.
  */
  bool writeString(const char* str,  bool append=false);
  
  /**
  Indica l'indice del frame corrente. Esso pu�variare nell'intervallo [0, #_numFrames-1].\n
  */
  int _currentFrame;
  
  /**
  Enum che indica gli indici di #_pattern.
  */
  enum{
  HEAD=0,
  FRAMES
  };
  
  /**
  File logico.
  */
  FILE* _file;
  
  /**
  Nome del file.
  */
  string _filename;
  
  /**
  Frame rate.
  */
  int _frameRate;
  
  /**
  Numero di frame.
  */
  int _numFrames;
  
  /**
  Numero di markers
  */
  int _numMarkers;
  
  /**
  Numero di informazioni salvate. VARIABILE NON UTILIZZATA. \n
  */
  int _bufferData;
  
  /**
  Rappresentazione interna dei dati letti in #importData().\n
  */
  map<int ,vector<RotationInt> > _data;
  
  /**
  Pattern utilizzati in #importData(), per fare parsing e in #writeData() per scrivere. \n
  */
  vector<string> _pattern;
};
#endif
