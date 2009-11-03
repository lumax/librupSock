/*
Bastian Ruppert
*/

//#include <stdio.h>
//#include <stdlib.h>


#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "rupSock.h"

/*[pgm]*/

int sockClientConnect(_sockCon_t * sCon, char * socketname)
{
  strcpy(sCon->sa.sun_path, socketname);
  sCon->sa.sun_family = AF_UNIX;
  if(sCon->fd_com)
    {
      errno = EINVAL;
      return -1;
    }
  
  ec_neg1( sCon->fd_com = socket(AF_UNIX, SOCK_STREAM, 0) )
  
  while (connect(sCon->fd_com, (struct sockaddr *)&sCon->sa, sizeof(sCon->sa)) == -1)
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

int sockClientClose(_sockCon_t * sCon)
{
  ec_neg1( close(sCon->fd_com) )
    return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

int sockServerConnect(_sockCon_t * sCon, char * socketname)
{   
  (void)unlink(socketname);

  strcpy(sCon->sa.sun_path, socketname);
  sCon->sa.sun_family = AF_UNIX;
  if(sCon->fd_com||sCon->fd_skt)
    {
      errno = EINVAL;
      return -1;
    }
  
  ec_neg1( sCon->fd_skt = socket(AF_UNIX, SOCK_STREAM, 0) )

  ec_neg1( bind(sCon->fd_skt, (struct sockaddr *)&sCon->sa, sizeof(sCon->sa)) )
    ec_neg1( listen(sCon->fd_skt, 2) )//SOMAXCONN) )
  ec_neg1( sCon->fd_com = accept(sCon->fd_skt, NULL, 0) )
    return 0;
  
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

int sockServerClose(_sockCon_t * sCon)
{
  ec_neg1( close(sCon->fd_skt) )
  ec_neg1( close(sCon->fd_com) )
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
