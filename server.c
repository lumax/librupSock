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

#define SOCKNAME "RUPSOCKET"

static _sockSocket_t sockCon_server;
static int fd_com;

int main(void)
{
  char buf[100];
  memset(&sockCon_server, 0, sizeof(_sockSocket_t));

  printf("server\n");
  ec_neg1(sockCreateAfSocket(&sockCon_server,SOCKNAME) )
    ec_neg1(sockServerConnect(&sockCon_server,SOCKNAME,&fd_com) )//block until success

  ec_neg1( read(fd_com, buf, sizeof(buf)) )
  printf("Server got \"%s\"\n", buf);
  ec_neg1( write(fd_com, "Goodbye!", 9 ) )

  ec_neg1(close(sockCon_server.fd) )
  ec_neg1(close(fd_com) )
    exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}

/*
static int theReadFnk(char * buf,int len,int index)
{
  printf("Server bekam \"%s\" len:%i\n", buf,len);
  //ec_neg1( write(pollSrc.pollfd_t.fd, "Goodbye!", 9 ) )
  if(0 == len)
    {
      EC_FAIL
    }
  return 0;
  EC_CLEANUP_BGN
    return -1;//exit(EXIT_FAILURE);
  EC_CLEANUP_END
}

static int thePollhupFnk(int index)
{
  printf("thepollhubFnk index : %i\n",index);
  return 0;
}*/

/*static char * hallo = "hallo";
static int theWriteFnk(char * buf)
{
  buf = hallo;
  return sizeof(hallo);
  }*/
