#ifndef HICOMMINTERFACENET_H
#define HICOMMINTERFACENET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include<debug.h>
#include<cgConnection.h>

#include<Headers/Exceptions.h>
#include<Headers/CommTypes.h>

#include"CommInterface.h"

class CommInterface;

class CommInterfaceNetwork : public CommInterface {
  public:
    CommInterfaceNetwork(int socket,const char* ipAddress, PROTOCOL protocol=TCP) throw(ExceptionConnectionError);
    virtual ~CommInterfaceNetwork();

    /*
     ____                 _
    / ___|  ___ _ __   __| |
    \___ \ / _ \ '_ \ / _` |
     ___) |  __/ | | | (_| |
    |____/ \___|_| |_|\__,_|

    */
    virtual size_t sendData(const unsigned char* data, size_t sizeOfData) throw(ExceptionConnectionInvalid);
    virtual size_t sendData(std::string& str) throw(ExceptionConnectionInvalid);
    virtual size_t sendData(std::vector<unsigned char>& vec) throw(ExceptionConnectionInvalid);
    virtual size_t sendData(cgMessage* msg) throw(ExceptionConnectionInvalid);
    
    /*
    ____               _
    |  _ \ ___  ___ ___(_)_   __
    | |_) / _ \/ __/ _ \ \ \ / /
    |  _ <  __/ (_|  __/ |\ V /
    |_| \_\___|\___\___|_| \_/

    */
    
    virtual std::vector<unsigned char> recvDataAsVector() throw(ExceptionReceiveError, ExceptionConnectionInvalid);
    virtual std::string recvDataAsString() throw(ExceptionReceiveError, ExceptionConnectionInvalid);
    virtual size_t recv(unsigned char* ptr, size_t maxSize)  throw(ExceptionReceiveError, ExceptionConnectionInvalid);
    
    
    
    virtual bool closeConnection() throw(ExceptionConnectionInvalid);

    /** Fa un restart della connessione.*/
    virtual void restart() throw(ExceptionConnectionError);
  
    /**Indirizzo IP del terminale collegato. @return indirizzo IP in
    formato string. @exception ExceptionConnectionInvalid errore
    connessione non valida.
     */
    inline virtual std::string getRemoteIpAdd() throw(ExceptionConnectionInvalid);

    /**Porta in ascolto. 
    @return porta in ascolto. 
    @exception ExceptionConnectionInvalid errore connessione non valida.
     */
    inline virtual int getPort() throw(ExceptionConnectionInvalid);

    /** Durata della connessione (in secondi), ritorna la durata della
    connessione.
    @return durata della connessione (in secondi). 
    @exception ExceptionConnectionInvalid errore connessione non valida.
     */
    inline virtual time_t getElapsedTime() throw(ExceptionConnectionInvalid);

    inline bool someActivities(){
      return _connectionNet->someActivities();
    };
    
    /** Controlla che la connessione sia valida. @return true se e'
    valida; false altrimenti.
     */  
    inline bool isValidConnection();

    /** Ritorna il File descriptor della socket. @return fd della
    socket.
     */
    inline int getSocketFd();

        
  protected:
    
    cgConnection* _connectionNet;
    
   PROTOCOL _protocol;
};
#endif
