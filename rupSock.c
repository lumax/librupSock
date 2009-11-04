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



int sockServerConnect(_pollMngSrc_t * sCon,char * socketname,int * socketFd )
{   
  struct sockaddr_un sa;
  (void)unlink(socketname);
  strcpy(sa.sun_path, socketname);
  sa.sun_family = AF_UNIX;
  ec_neg1( *socketFd = socket(AF_UNIX, SOCK_STREAM, 0) ) 

  ec_neg1( bind(*socketFd, (struct sockaddr *)&sa, sizeof(sa)) )
  ec_neg1( listen(*socketFd, 2) )//SOMAXCONN) )
  ec_neg1( sCon->fd = accept(*socketFd, NULL, 0) )
    return 0;
  
  EC_CLEANUP_BGN
    return -1;
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
