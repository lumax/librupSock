/*
Bastian Ruppert
*/

#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pollManager.h>

#include "rupSock.h"

static int ServerSocketFd;

/* \brief Baut eine Client Socketverbindung auf.
 * \param sCon PollManagerSource, welche den file descriptor enthällt
 * \param socketname Name des ZielSockets
 * \return a positive fd on success otherwise a negative error code
 * \retval -1 bie einem Fehler, errno wird gesetzt
 */
int sockClientConnect(char * socketname)
{
  struct sockaddr_un sa;
  int fd;
  strcpy(sa.sun_path, socketname);
  sa.sun_family = AF_UNIX;
  ec_neg1( fd = socket(AF_UNIX, SOCK_STREAM, 0) ) 

  ec_neg1(connect(fd, (struct sockaddr *)&sa, sizeof(sa) ) )
    return fd;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

/* \brief private function: Ein Client möchte verbinden, call accept 
 * \param pMngIndex Position der Verbindung beim pollManager
 * \param dat pointer auf die _pollMngSrc_t dieser Verbindung
 * \return 0 on success otherwise -1
 * \retval 0 on success
 * \retval -1 bie einem Fehler, errno wird gesetzt
 */
static int ServerPollConListener(int pMngIndex,void * dat)
{
  _pollMngSrc_t * sCon = (_pollMngSrc_t *)dat;

  //eine Neue Connection!
  ec_neg1( sCon->fd = accept(sCon->fd, NULL, 0) )
    
    sCon->conListenerFnk=0;//conListenerFnk deaktivieren
  
  ec_neg1(pollMngSetSrc(sCon,pMngIndex))//den pollMng über die neuen Verhältnisse informieren
  return 0;
    
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
  
}

/* \brief Die Verbindung wurde beendet, auf dem Socket auf eine Neue warten.
 * \param pMngIndex Position der Verbindung beim pollManager
 * \param dat pointer auf die _pollMngSrc_t dieser Verbindung
 * \return 0 on success otherwise -1
 * \retval 0 on success
 * \retval -1 bie einem Fehler, errno wird gesetzt
 */
static int ServerPollHupFnk(int pMngIndex,void * dat)
{
  _pollMngSrc_t * sCon = (_pollMngSrc_t *)dat;
  
  ec_neg1(close(sCon->fd) )
  
  sCon->fd = ServerSocketFd;//wir höhren jetzt wieder am Socket
  sCon->conListenerFnk = ServerPollConListener;//conListener wieder scharf machen

  ec_neg1(pollMngSetSrc(sCon,pMngIndex))//den pollMng über die neuen Verhältnisse informieren

  return 0;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END 
  return 0;
}

static struct sockaddr_un sa_Server;
/* \brief Creates the Socket ans bind and listen, call this fnk once before any 
 * \brief other fnk.
 * \param socketname Name des ZielSockets
 * \return 0 on success otherwise -1
 * \retval 0 on success
 * \retval -1 bie einem Fehler, errno wird gesetzt
 */
int createServerSocketFd(char * socketname)
{
  (void)unlink(socketname);
  strcpy(sa_Server.sun_path, socketname);
  sa_Server.sun_family = AF_UNIX;
  
  ec_neg1( ServerSocketFd = socket(AF_UNIX, SOCK_STREAM, 0) ) 
    
    ec_neg1( bind(ServerSocketFd, (struct sockaddr *)&sa_Server,\
		  sizeof(sa_Server)) )
    ec_neg1( listen(ServerSocketFd, 0))//SOMAXCONN) )
    return 0;  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

/* \brief Creates a "ConnectionListener".  
 * \param sCon _pollMngSrc um diese connection mit poll bedienen zu können
 * \return 0 on success otherwise -1
 * \retval 0 on success
 * \retval -1 bie einem Fehler, errno wird gesetzt
 */
int sockServerConnect(_pollMngSrc_t * sCon)
{   
 
  //hupFnk wird hier belegt und darf nicht userdefined sein
  if(sCon->pollhupFnk)
    {
      errno = EINVAL;
      return -1;
    }

  sCon->userDat = (void *)sCon;// Server-struct bekannt machen
  sCon->pollhupFnk = ServerPollHupFnk;//hupFnk belegen 
  sCon->conListenerFnk = ServerPollConListener;//Con-Listener scharf machen

  //wir hören hier auf dem socket bis eine connection akzeptiert wurde,
  //danach ist sCon->pPollSrc->fd der fd der Verbindung 
  sCon->fd = ServerSocketFd;

  return 0;
}

/*#define SOCKNAME "RUPSOCKET"
int main(void)
{
  _sockCon_t sockCon_server;
  _sockCon_t sockCon_client;

  memset(&sockCon_server, 0, sizeof(_sockCon_t));
  memset(&sockCon_client, 0, sizeof(_sockCon_t));


  if (fork() == 0)  // client 
    {
      ec_neg1(sockClientConnect(&sockCon_client,SOCKNAME) )
      exit(EXIT_SUCCESS);
    }
  else  // server 
    {
      ec_neg1(sockServerConnect(&sockCon_server,SOCKNAME) )
      exit(EXIT_SUCCESS);
    }
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}
*/
