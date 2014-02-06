#ifndef EXCEPTIONS_H_DEFINED
#define EXCEPTIONS_H_DEFINED
#include <stdexcept>
#include<SharedSensorArray.h>
#include<debug.h>

/*
 _____                    _   _          __     __         _
| ____|_  _____ ___ _ __ | |_(_) ___  _ _\ \   / /_ _ _ __(_)_   _  ___  ___
|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \ \ / / _` | '__| | | | |/ _ \/ __|
| |___ >  < (_|  __/ |_) | |_| | (_) | | | \ V / (_| | |  | | |_| | (_) \__ \
|_____/_/\_\___\___| .__/ \__|_|\___/|_| |_|\_/ \__,_|_|  |_|\__,_|\___/|___/
                   |_|
*/
typedef SharedSensorArray::ExceptionIdOutOfRange ExceptionIdOutOfRange;
// /** ECCEZIONE: ID non indicizzato nell'array in memoria.*/
// class ExceptionIdOutOfRange  : public std::runtime_error {
//  public:
//   /** Costruttore di default.*/
//   ExceptionIdOutOfRange() : runtime_error(""){};
//   /** Costruisce un'eccezione con una stringa che identifica
//       l'errore. @param str stringa dell'eccezione.*/
//   ExceptionIdOutOfRange(const std::string& str) : runtime_error(str){};
// };

  /** ECCEZIONE: errore durante il parsing del file di configurazione.*/
class ExceptionParseError : public std::runtime_error{
 public:
  /** Costruttore di default.*/
  ExceptionParseError() : runtime_error("") {};

  /** Costruisce un'eccezione con una stringa che identifica
   l'errore. @param str stringa dell'eccezione.*/
  ExceptionParseError(const std::string&  str) : runtime_error(str){};
  ExceptionParseError(const char*  str) : runtime_error(str){};
};
  
   /** ECCEZIONE: errore nell'apertura del file di configurazione.*/
  class ExceptionErrorOpeningFile : public std::runtime_error{
    public:
      /** Costruttore di default.*/
      ExceptionErrorOpeningFile() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionErrorOpeningFile(const std::string&  str) : runtime_error(str){};
      ExceptionErrorOpeningFile(const char *  str) : runtime_error(str){};
  };
  
   

  /** ECCEZIONE: valore non trovato. Lanciata quando non viene trovato
  il valore specificato.*/
  class ExceptionValueNotFound : public std::runtime_error{
    public:
      /** Costruttore di default.*/
      ExceptionValueNotFound() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionValueNotFound(const std::string&  str) : runtime_error(str){};
  };

  /** ECCEZIONE: sezione non trovata. Lanciata quando non viene trovata
  la sezione specificata.*/
  class ExceptionSectionNotFound : public std::runtime_error{
    public:
      /** Costruttore di default.*/
      ExceptionSectionNotFound() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionSectionNotFound(const std::string&  str) : runtime_error(str){};
      ExceptionSectionNotFound(const char *  str) : runtime_error(str){};
  };


/*
 _____                    _   _             ____
| ____|_  _____ ___ _ __ | |_(_) ___  _ __ / ___|  ___ _ __  ___  ___  _ __ ___
|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \\___ \ / _ \ '_ \/ __|/ _ \| '__/ __|
| |___ >  < (_|  __/ |_) | |_| | (_) | | | |___) |  __/ | | \__ \ (_) | |  \__ \
|_____/_/\_\___\___| .__/ \__|_|\___/|_| |_|____/ \___|_| |_|___/\___/|_|  |___/
                   |_|
*/

class ExceptionSensors: public std::runtime_error {
public:
  /** Costruttore di default.*/
  ExceptionSensors() : runtime_error(""){};
  /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
  ExceptionSensors(const std::string& str) : runtime_error(str){};
};


/** ECCEZIONE: Errore generico nella creazione del sensore.*/
class ExceptionSensorCreationError : public ExceptionSensors {
 public:
  /** Costruttore di default.*/
  ExceptionSensorCreationError() : ExceptionSensors(){};
  /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
  ExceptionSensorCreationError(const std::string& str) : ExceptionSensors(str){};
};

/** ECCEZIONE: Indirizzo del sensore non corretto.*/
class ExceptionSensorBadAddress : public ExceptionSensors {
 public:
  /** Costruttore di default.*/
  ExceptionSensorBadAddress() : ExceptionSensors(){};
  /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
  ExceptionSensorBadAddress(const char* str) : ExceptionSensors(str){};
};


/** ECCEZIONE: Interfaccia hardware utilizzata dal sensore non
    trovata.*/
class ExceptionSensorNoInterface : public ExceptionSensors {
 public:
  /** Costruttore di default.*/
  ExceptionSensorNoInterface() : ExceptionSensors(){};
  /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
  ExceptionSensorNoInterface(const char* str) : ExceptionSensors(str){};
};


/**ECCEZIONE: interfaccia SensorsSystem non disponibile*/
class ExceptionNoSensorsSystem : public ExceptionSensors{
 public:
   /** Costruttore di default.*/
   ExceptionNoSensorsSystem() : ExceptionSensors() {};

   /** Costruisce un'eccezione con una stringa che identifica l'errore. @param str stringa dell'eccezione.*/
   ExceptionNoSensorsSystem(const std::string&  str) : ExceptionSensors(str){};
};

/*
 _____                    _   _             ___ ___
| ____|_  _____ ___ _ __ | |_(_) ___  _ __ |_ _/ _ \
|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \ | | | | |
| |___ >  < (_|  __/ |_) | |_| | (_) | | | || | |_| |
|_____/_/\_\___\___| .__/ \__|_|\___/|_| |_|___\___/
                   |_|
*/
class ExceptionIO: public std::runtime_error{
   public:
      /** Costruttore di default.*/
      ExceptionIO() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionIO(const std::string&  str) : runtime_error(str){};	
};

class ExceptionFileNotFound: public ExceptionIO{
   public:
	/** Costruttore di default.*/
	ExceptionFileNotFound() : ExceptionIO(){};

	/** Costruisce un'eccezione con una stringa che identifica
      	l'errore. @param str stringa dell'eccezione.*/
	ExceptionFileNotFound(const std::string& str): ExceptionIO(str){};
};

class ExceptionMCDFile : public ExceptionIO{
    public:
      /** Costruttore di default.*/
      ExceptionMCDFile() : ExceptionIO() {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionMCDFile(const std::string&  str) : ExceptionIO(str){};
};
  
class ExceptionMMDFile : public ExceptionIO{
    public:
      /** Costruttore di default.*/
      ExceptionMMDFile() : ExceptionIO() {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionMMDFile(const std::string&  str) : ExceptionIO(str){};
};

/*
 _____                    _   _             _   _ ___
| ____|_  _____ ___ _ __ | |_(_) ___  _ __ | | | |_ _|
|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \| |_| || |
| |___ >  < (_|  __/ |_) | |_| | (_) | | | |  _  || |
|_____/_/\_\___\___| .__/ \__|_|\___/|_| |_|_| |_|___|
                   |_|
*/

class ExceptionHI: public std::runtime_error{
   public:
      /** Costruttore di default.*/
      ExceptionHI() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionHI(const std::string&  str) : runtime_error(str){};
      	
      ExceptionHI(const char * str) : runtime_error(std::string(str)){};	
};

class ExceptionAddress: public ExceptionHI{
  public:
    /** Costruttore di default.*/
    ExceptionAddress() : ExceptionHI() {};

    /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionAddress(const std::string&  str) : ExceptionHI(str){};
   
    ExceptionAddress(const char *   str) : ExceptionHI(str){};
};



/*  
 _____                    _   _              ____                                      _           _   _
| ____|_  _____ ___ _ __ | |_(_) ___  _ __  / ___|___  _ __ ___  _ __ ___  _   _ _ __ (_) ___ __ _| |_(_) ___  _ __
|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \| |   / _ \| '_ ` _ \| '_ ` _ \| | | | '_ \| |/ __/ _` | __| |/ _ \| '_ \
| |___ >  < (_|  __/ |_) | |_| | (_) | | | | |__| (_) | | | | | | | | | | | |_| | | | | | (_| (_| | |_| | (_) | | | |
|_____/_/\_\___\___| .__/ \__|_|\___/|_| |_|\____\___/|_| |_| |_|_| |_| |_|\__,_|_| |_|_|\___\__,_|\__|_|\___/|_| |_|
                   |_|
*/

class ExceptionCommunication: public std::runtime_error{
  public:
    /** Costruttore di default.*/
      ExceptionCommunication() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
      l'errore. @param str stringa dell'eccezione.*/
      ExceptionCommunication(const std::string&  str) : runtime_error(str){};	
};

class ExceptionConnectionError : public ExceptionCommunication{
  public:
    /** Costruttore di default.*/
    ExceptionConnectionError() : ExceptionCommunication() {};
    
    /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionConnectionError(const std::string& str) : ExceptionCommunication(str){};
};
  
/** ECCEZIONE: errore connessione non valida.*/
class ExceptionConnectionInvalid : public ExceptionCommunication{
  public:
    /** Costruttore di default.*/
    ExceptionConnectionInvalid() : ExceptionCommunication() {};
  
  /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionConnectionInvalid(const std::string& str) : ExceptionCommunication(str){};
};

/** ECCEZIONE: errore nella ricezione dei dati dalla rete.*/
class ExceptionReceiveError : public ExceptionCommunication { 
  public:
    /** Costruttore di default.*/
    ExceptionReceiveError() : ExceptionCommunication() {};
  
  /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionReceiveError(const std::string& str) : ExceptionCommunication(str) {};
};


/*
 _____                    _   _                _        _               _
| ____|_  _____ ___ _ __ | |_(_) ___  _ __    / \   ___| |_ _   _  __ _| |_ ___  _ __ ___
|  _| \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \  / _ \ / __| __| | | |/ _` | __/ _ \| '__/ __|
| |___ >  < (_|  __/ |_) | |_| | (_) | | | |/ ___ \ (__| |_| |_| | (_| | || (_) | |  \__ \
|_____/_/\_\___\___| .__/ \__|_|\___/|_| |_/_/   \_\___|\__|\__,_|\__,_|\__\___/|_|  |___/
                   |_|
*/

class ExceptionActuators: public std::runtime_error{
  public:
    /** Costruttore di default.*/
    ExceptionActuators() : runtime_error("") {};

    /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionActuators(const std::string&  str) : runtime_error(str){};	
    
    ExceptionActuators(const char * str) : runtime_error(std::string(str)){};	
};


class ExceptionChannel: public ExceptionActuators{
  public:
    /** Costruttore di default.*/
    ExceptionChannel() : ExceptionActuators("") {};

    /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionChannel(const std::string&  str) : ExceptionActuators(str){};	
    
    ExceptionChannel(const char * str) : ExceptionActuators(str){};	
};

class ExceptionChannelNotPresent: public ExceptionActuators{
  public:
    /** Costruttore di default.*/
    ExceptionChannelNotPresent() : ExceptionActuators("") {};

    /** Costruisce un'eccezione con una stringa che identifica
    l'errore. @param str stringa dell'eccezione.*/
    ExceptionChannelNotPresent(const std::string&  str) : ExceptionActuators(str){};	
    
    ExceptionChannelNotPresent(const char * str) : ExceptionActuators(str){};	
};



#endif
