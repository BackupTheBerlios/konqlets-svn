#ifndef _javascript_H_
#define _javascript_H_

#include <qstring.h>
#include <qcstring.h>

#include <kurl.h>
#include <kio/global.h>
#include <kio/slavebase.h>

#include <dcopclient.h>

class QCString;

class kio_javascriptProtocol : public KIO::SlaveBase
{
public:
    kio_javascriptProtocol(const QCString &pool_socket, const QCString &app_socket);
    virtual ~kio_javascriptProtocol();
    virtual void mimetype(const KURL& url);
    virtual void get(const KURL& url);
private:
    bool     m_found;		//< Whether or not a valid Konqueror instance was found.
    QCString m_foundApp, 	//< Name of application found in search.
    	     m_foundObj;	//< Name of object found in search.
    DCOPClient *m_client;	//< Reference to DCOP client	  
    
    void executeJS(const QString &); //< Executes JavaScript in the current Konq instance. 
};

#endif
