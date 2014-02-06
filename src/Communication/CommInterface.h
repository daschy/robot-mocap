#ifndef HICOMMINTERFACE_H
#define HICOMMINTERFACE_H

#include<string>

#include<debug.h>
#include<cgMessages.h>

#include<Headers/Exceptions.h>

#include<Headers/CommTypes.h>
// #include"CommInterfaceNetwork.h"

//Implementare un factory... Metodo statico in CommImterface sar�CommInterfaceFactory(enum preferred interface);
using namespace std;

class CommInterfaceNetwork;

class CommInterface{
    
  public:
    inline virtual ~CommInterface() {};
    static CommInterface* CommInterfaceFactory(int port, const char* ip_address, PROTOCOL prot=TCP) throw(ExceptionConnectionError);

    static void cgMessageMvJointFactory(messageType& mvType, vector<int>& servo, vector<int>& uradposition, vector<int>& parameter, string& temp);
    
    static void cgMessageMvJointWTimeFactory(int servo, int uradposition, int utime, string& temp);
    static void cgMessageMvJointWTimeFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& utime, string& temp);
    static void cgMessageMvJointWSpeedFactory(int servo, int uradposition, int uspeed, string& temp);
    static void cgMessageMvJointWSpeedFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& uspeed, string& temp);
    
    static void cgMessageMvJointUWTimeFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& utime, string& temp);
    static void cgMessageMvJointUWSpeedFactory(vector<int>& servo, vector<int>& uradposition, vector<int>& uspeed, string& temp);
    
     static void cgMessageByeFactory(string& temp);
     static void cgMessageReqSensor(int sensorsID,string& temp);
     static void cgMessageReqSensor(vector<int>& sensorsID,string& temp);
     
    /*
      ____                 _
    / ___|  ___ _ __   __| |
    \___ \ / _ \ '_ \ / _` |
     ___) |  __/ | | | (_| |
    |____/ \___|_| |_|\__,_|

    */
    virtual size_t sendData(const unsigned char* data, size_t sizeOfData) throw(ExceptionConnectionInvalid) = 0;
    virtual size_t sendData(std::string& str) throw(ExceptionConnectionInvalid) = 0;
    virtual size_t sendData(std::vector<unsigned char>& vec) throw(ExceptionConnectionInvalid) = 0;
    virtual size_t sendData(cgMessage* msg) throw(ExceptionConnectionInvalid)=0;
    
    /*
     ____               _
    |  _ \ ___  ___ ___(_)_   __
    | |_) / _ \/ __/ _ \ \ \ / /
    |  _ <  __/ (_|  __/ |\ V /
    |_| \_\___|\___\___|_| \_/

    */
    
    virtual std::vector<unsigned char> recvDataAsVector() throw(ExceptionReceiveError, ExceptionConnectionInvalid) = 0;
    virtual std::string recvDataAsString() throw(ExceptionReceiveError, ExceptionConnectionInvalid) = 0;
    virtual size_t recv(unsigned char* ptr, size_t maxSize)  throw(ExceptionReceiveError, ExceptionConnectionInvalid) = 0;
    
    
    /*
    __     __         _
    \ \   / /_ _ _ __(_)_   _  ___  ___
     \ \ / / _` | '__| | | | |/ _ \/ __|
      \ V / (_| | |  | | |_| | (_) \__ \
       \_/ \__,_|_|  |_|\__,_|\___/|___/

    */
    
    /** Chiude la connessione.*/
    virtual bool closeConnection() throw(ExceptionConnectionInvalid)= 0;

    /** Fa un restart della connessione.*/
    virtual void restart() throw(ExceptionConnectionError)= 0;
  
    /**Indirizzo IP del terminale collegato. @return indirizzo IP in
    formato string. @exception ExceptionConnectionInvalid errore
    connessione non valida.
    */
    inline virtual std::string getRemoteIpAdd() throw(ExceptionConnectionInvalid) = 0;

    /**Porta in ascolto. 
        @return porta in ascolto. 
        @exception ExceptionConnectionInvalid errore connessione non valida.
    */
    virtual int getPort() throw(ExceptionConnectionInvalid) = 0;

    /** Durata della connessione (in secondi), ritorna la durta della
	connessione.
        @return durata della connessione (in secondi). 
        @exception ExceptionConnectionInvalid errore connessione non valida.
    */
    virtual time_t getElapsedTime() throw(ExceptionConnectionInvalid) = 0;

    /** Controlla che la connessione sia valida. @return true se e'
	valida; false altrimenti.
    */  
    virtual bool isValidConnection() =0 ;

    /** Ritorna il File descriptor della socket. @return fd della
	socket.
    */
    virtual int getSocketFd() = 0;

    virtual bool someActivities() =0;
    
    
  private:
    
    
    
};
#endif













