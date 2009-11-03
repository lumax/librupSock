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

int sockCreateAfSocket(_sockSocket_t * sock,char * socketname)
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
}

/*      Bsp: 
 *            _pollMngSrc_t  pollMngPollSources[]={
 *             [0] = {
 *                    .pollfd_t.fd = -1,
 *                    .name = "myAmazingFileDescriptor",
 *                    .readFnk = myReadFnk,
 *                   },
 *            };*/
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



int sockServerConnect(_sockSocket_t * sCon,char * socketname,int * fd_com)
{   
  (void)unlink(socketname);

  ec_neg1( bind(sCon->fd, (struct sockaddr *)&sCon->sa, sizeof(sCon->sa)) )
    ec_neg1( listen(sCon->fd, 2) )//SOMAXCONN) )
  ec_neg1( *fd_com = accept(sCon->fd, NULL, 0) )
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
