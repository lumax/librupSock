/*
Bastian Ruppert
*/

//#include <stdio.h>
//#include <stdlib.h>


#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pollManager.h>

#include "rupSock.h"

static int ServerSocketFd;

/* \brief Baut eine Client Socketverbindung auf.
 * \param sCon PollManagerSource, welche den file descriptor enthällt
 * \param socketname Name des ZielSockets
 * \return a positive value on success otherwise a negative error code
 * \retval 0 on success
 * \retval -1 bie einem Fehler, errno wird gesetzt
 */
int sockClientConnect(_pollMngSrc_t * sCon,char * socketname)
{
  struct sockaddr_un sa;
  strcpy(sa.sun_path, socketname);
  sa.sun_family = AF_UNIX;
  ec_neg1( sCon->fd = socket(AF_UNIX, SOCK_STREAM, 0) ) 
  while (connect(sCon->fd, (struct sockaddr *)&sa, sizeof(sa)) == -1)
    {
      if (errno == ENOENT) 
	{
	  sleep(1);
	  continue;
	}
      else
	{
	  EC_FAIL
	}
    }
    return 0;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

static int ServerPollConListener(int pMngIndex,void * dat)
{
  _pollMngServer_t * sCon = (_pollMngServer_t *)dat;

  //eine Neue Connection!
  ec_neg1( sCon->pPollSrc->fd = accept(sCon->pPollSrc->fd, NULL, 0) )
    
    sCon->pPollSrc->conListenerFnk=0;//conListenerFnk deaktivieren
  
  ec_neg1(pollMngSetSrc(sCon->pPollSrc,pMngIndex))//den pollMng über die neuen Verhältnisse informieren
  return 0;
    
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
  
}

/* \brief Die Verbindung wurde beendet, auf dem Socket auf eine Neue warten.
 */
static int ServerPollHupFnk(int pMngIndex,void * dat)
{
  _pollMngServer_t * sCon = (_pollMngServer_t *)dat;
  
  ec_neg1(close(sCon->pPollSrc->fd) )
  
  sCon->pPollSrc->fd = ServerSocketFd;//wir höhren jetzt wieder am Socket
  sCon->pPollSrc->conListenerFnk = ServerPollConListener;//conListener wieder scharf machen
 
  
  ec_neg1(pollMngSetSrc(sCon->pPollSrc,pMngIndex))//den pollMng über die neuen Verhältnisse informieren

  return 0;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END 
  return 0;
}

static struct sockaddr_un sa_Server;
int createServerSocketFd(char * socketname)
{
  (void)unlink(socketname);
  strcpy(sa_Server.sun_path, socketname);
  sa_Server.sun_family = AF_UNIX;
  
  ec_neg1( ServerSocketFd = socket(AF_UNIX, SOCK_STREAM, 0) ) 
    
    ec_neg1( bind(ServerSocketFd, (struct sockaddr *)&sa_Server,\
		  sizeof(sa_Server)) )
    ec_neg1( listen(ServerSocketFd, 2))//SOMAXCONN) )
    return 0;  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

int sockServerConnect(_pollMngServer_t * sCon)
{   
 
  //hupFnk wird hier belegt und darf nicht userdefined sein
  if(sCon->pPollSrc->pollhupFnk)
    {
      errno = EINVAL;
      return -1;
    }

  sCon->pPollSrc->userDat = (void *)sCon;// Server-struct bekannt machen
  sCon->pPollSrc->pollhupFnk = ServerPollHupFnk;//hupFnk belegen 
  sCon->pPollSrc->conListenerFnk = ServerPollConListener;//Con-Listener scharf machen

  //wir hören hier auf dem socket bis eine connection akzeptiert wurde,
  //danach ist sCon->pPollSrc->fd der fd der Verbindung 
  sCon->pPollSrc->fd = ServerSocketFd;

  return 0;
}

int sockServerClose(_pollMngServer_t * sCon)
{
  //ec_neg1(close(sCon->socketFd) )
  ec_neg1(close(sCon->pPollSrc->fd) )
    return 0;;
  
  EC_CLEANUP_BGN
    return 1;
  EC_CLEANUP_END
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
