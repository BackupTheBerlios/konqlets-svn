#include <qcstring.h>
#include <qsocket.h>
#include <qdatetime.h>
#include <qbitarray.h>

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include <kapplication.h>
#include <kconfigbase.h>
#include <kdebug.h>
#include <kmessagebox.h>
#include <kinstance.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include <klocale.h>
#include <kurl.h>
#include <ksock.h>
#include <dcopclient.h>
#include <dcopref.h>

#include "javascript.h"

using namespace KIO;

#define DBG_JS 7101

kio_javascriptProtocol::kio_javascriptProtocol(const QCString &pool_socket, const QCString &app_socket)
    : SlaveBase("kio_javascript", pool_socket, app_socket)
{
  kdDebug(DBG_JS) << "kio_javascript::kio_javascriptProtocol" << endl ;

  m_client = dcopClient();
  m_client->registerAs("kio_javascriptProtocol");
  kdDebug(DBG_JS) << "DCOP: " << m_client->name() << endl;

}


kio_javascriptProtocol::~kio_javascriptProtocol()
{}

void kio_javascriptProtocol::
executeJS(const QString &script)
{
  // Grab the HTML widget
  DCOPReply part = DCOPRef( m_foundApp, m_foundObj ).call( "currentPart" );

  if(part.isValid())
  {
    DCOPRef r;
    part.get(r);
    kdDebug(DBG_JS) << "Part App: " << r.app() << " Obj: " << r.object() << endl;
    r.send( "evalJS", script );
  }
}


void kio_javascriptProtocol::
get(const KURL& url)
{
  kdDebug(DBG_JS) << "kio_javascript::get(const KURL& url)" << endl ;
  //error(KIO::ERR_SLAVE_DEFINED, i18n("An active instance of Konqueror not found."));

  // JS URIs are real funky, so don't expect the regular info to come through. It
  // should be the JS code directly after the ':'.
  //kdDebug(DBG_JS) << "Query: " << url.query() << endl;
  //kdDebug(DBG_JS) << "Host: " << url.host() << endl;
  //   kdDebug(DBG_JS) << "Port: " << url.port() << endl;
  //   kdDebug(DBG_JS) << "FileName: " << url.fileName() << endl;

  // This is the only thing meaningful in JS
  kdDebug(DBG_JS) << "URL: " << url.url() << endl;
  kdDebug(DBG_JS) << "PrettyURL: " << url.prettyURL() << endl;

  // This works because we set URIMode=rawuri in javascript.protocol
  kdDebug(DBG_JS) << "Path: " << url.path() << endl;

  // Obtain information about the current Konqueror window.
  m_found = m_client->findObject( "konqueror-*",
                                  "konqueror-mainwindow#*",
                                  "isActiveWindow()",
                                  QByteArray(),
                                  m_foundApp,
                                  m_foundObj,
                                  true,
                                  5 );
  kdDebug(DBG_JS) << "App: " << m_foundApp << endl;
  kdDebug(DBG_JS) << "Obj: " << m_foundObj << endl;

  if(!m_found)
  {
    kdDebug(DBG_JS) << "Did not find object instance" << endl;
    // Error.
    // TODO: Causes SIGSEGV in KHTMLPart::slotFinished
    messageBox(Information, i18n("An active instance of Konqueror not found."),
               i18n("JavaScript Error"));
    finished();
    return;
  }

#if 0
  if(m_found)
  {
    // TODO: Lock history to prevent polluting back/forward buttons.
    // XXX - This doesn't work.
    DCOPReply view = DCOPRef( m_foundApp, m_foundObj ).call( "currentView" );

    if(view.isValid())
    {
      DCOPRef r;
      view.get(r);
      kdDebug(DBG_JS) << "View App: " << r.app() << " Obj: " << r.object() << endl;
      r.send("lockHistory");
    }
  }
#endif

 
  //DCOPRef(m_foundApp, m_foundObj).call("openURL",


  //  DCOPReply curl = DCOPRef( m_foundApp, m_foundObj ).call("currentURL");
  //  if(curl.isValid()) {
  //    QDataStream url(curl);
  //    kdDebug(DBG_JS) << "Curl: " << url.data() << endl;
  //    DCOPRef(m_foundApp, m_foundObj).send("openURL", url.data());
  //  }

  // Reload for fun
  //DCOPRef( m_foundApp, m_foundObj + "/action/reload" ).send( "activate" );

  // Then, display a progress message.
  //infoMessage(i18n("Executing JavaScript..."));



  // TODO: Check configuration to see if we need to ask the following question.
  kdDebug(DBG_JS) << "Checking MetaData" << endl;
  if(hasMetaData("always"))
  {
    kdDebug(DBG_JS) << "Previous answer to Always Allow" << endl;
    // Evaluate the JavaScript snipplet from the path
    executeJS(url.path());
    infoMessage(i18n("Done."));

    // Activate previous URI
     kdDebug(DBG_JS) << "Go back in the browser..." << endl;

    DCOPRef( m_foundApp, m_foundObj + "/action/back" ).send( "activate" );

    finished();
    return;
  }



  kdDebug(DBG_JS) << "Asking User..." << endl;
  // Ask the user if this is what they really want
  QString msg(i18n("You are about to invoke a bookmarklet in the location bar. This will be "
                   "run with the currently displayed web page and could have security "
                   "consequences. The script could modify the web page or notify external "
                   "users of the web page you're looking at. \nIf you would like to dismiss "
                   "this dialog from appearing again, click 'Always Allow'. \nIf you would "
                   "like to deny any future use of bookmarklets, click 'Never Allow'. \nOtherwise, "
                   "click 'Cancel' to stop execution for this bookmarklet."));
  QString cap(i18n("JavaScript Warning"));
  QString yes(i18n("Always Allow"));
  QString noo(i18n("Never Allow"));

  kdDebug(DBG_JS) << "User Select: ";
  int result;
tryagain:
  switch( result = messageBox(WarningYesNoCancel, msg, cap, yes, noo) )
  {
  case KMessageBox::Yes:
    // TODO: Need to store Data for future use in configuration.

    kdDebug(DBG_JS) << "Always Allow" << endl;

    // Session MetaData
    setMetaData("always","1");

    // Evaluate the JavaScript snipplet from the path
    executeJS(url.path());
    infoMessage(i18n("Done."));
    break;
  case KMessageBox::No:
    // TODO: Need to store Data for future use in configuration.

    kdDebug(DBG_JS) << "Never Allow" << endl;
    infoMessage(i18n("Never Allowed."));
    break;
  case KMessageBox::Cancel:
    kdDebug(DBG_JS) << "Cancel" << endl;
    infoMessage(i18n("Cancelled."));
    break;

  default:
    kdDebug(DBG_JS) << "Funky: " << result << endl;
    sleep(1);
    goto tryagain;
    break;
  }
       kdDebug(DBG_JS) << "Go back in the browser..." << endl;

  // Activate previous URI
  DCOPRef( m_foundApp, m_foundObj + "/action/back" ).send( "activate" );

  finished();
}


void kio_javascriptProtocol::mimetype(const KURL & /*url*/)
{
  kdDebug(DBG_JS) << "mimetype()" << endl;
  mimeType("application/x-javascript");
  finished();
}


extern "C"
{
  int kdemain(int argc, char **argv)
  {
    KInstance instance( "kio_javascript" );

    kdDebug(DBG_JS) << "*** Starting kio_javascript " << endl;

    if (argc != 4)
    {
      kdDebug(DBG_JS) << "Usage: kio_javascript  protocol domain-socket1 domain-socket2" << endl;
      exit(-1);
    }

    kio_javascriptProtocol slave(argv[2], argv[3]);


    slave.dispatchLoop();

    kdDebug(DBG_JS) << "*** kio_javascript Done" << endl;
    return 0;
  }
}
