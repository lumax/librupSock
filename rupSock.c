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

/*int sockCreateAfSocket(_sockSocket_t * sock,char * socketname)
 {
  strcpy(sock->sa.sun_path, socketname);
  sock->sa.sun_family = AF_UNIX;
  if(sock->fd)
    {
      errno = EINVAL;
      EC_FAIL
    }
  ec_neg1( sock->fd = socket(AF_UNIX, SOCK_STREAM, 0) ) 
    return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
  }*/

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

static int ServerPollReadFnk(char * buf,int len,int pMngIndex,void * dat)
{
  _pollMngServer_t * sCon = (_pollMngServer_t *)dat;

  //eine Neue Connection!
  ec_neg1( sCon->pPollSrc->fd = accept(sCon->socketFd, NULL, 0) )
    
  //original Fnkpnt wiederherstellen 
  sCon->pPollSrc->readFnk = sCon->readFnk;
  
  return 0;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

static int ServerPollHupFnk(int index,void * dat)
{
  return 0;
}

int sockServerConnect(_pollMngServer_t * sCon,char * socketname)
{   
  struct sockaddr_un sa;
  /* if(sCon->pPollSrc->pollhupFnk)
    {
      errno = EINVAL;
      return -1;
      }*/

  (void)unlink(socketname);
  strcpy(sa.sun_path, socketname);
  sa.sun_family = AF_UNIX;
  ec_neg1( sCon->socketFd = socket(AF_UNIX, SOCK_STREAM, 0) ) 

  ec_neg1( bind(sCon->socketFd, (struct sockaddr *)&sa, sizeof(sa)) )
  ec_neg1( listen(sCon->socketFd, 2) )//SOMAXCONN) )

    /*  sCon->pPollSrc->userDat = (void *)sCon;// Server-struct bekannt machen
  sCon->readFnk = sCon->pPollSrc->readFnk;     //Fnk pointer sichern
  sCon->pollhupFnk = sCon->pPollSrc->pollhupFnk;

  sCon->pPollSrc->readFnk = ServerPollReadFnk;//Fnkpnt mit listenern belegen
  sCon->pPollSrc->pollhupFnk = ServerPollHupFnk;
  sCon->pPollSrc->*/

  ec_neg1( sCon->pPollSrc->fd = accept(sCon->socketFd, NULL, 0) )
    return 0;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

int sockServerClose(_pollMngServer_t * sCon)
{
  ec_neg1(close(sCon->socketFd) )
  ec_neg1(close(sCon->pPollSrc->fd) )
    exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
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
