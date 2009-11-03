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

_pollMngPollSource_t  pollMngPollSources[1];
/*
_pollMngPollSource_t  pollMngPollSources[]={
  [0] = {
    .pollfd_t.fd = 0,//myAmazingFileDescriptor
    //  .name = "server",
    //.readFnk = 0,
    //.writeFnk = 0,
  },
}
*/

static int theReadFnk(char * buf,int len,int index);
static int thePollhupFnk(int index);
//static int theWriteFnk(char * buf);  
static _pollMngPollSource_t pollSrc;

int main(void)
{
  _sockCon_t sockCon_server;

  memset(&sockCon_server, 0, sizeof(_sockCon_t));

  printf("server\n");
  ec_neg1(sockServerConnect(&sockCon_server,SOCKNAME) ) //block until success

  pollSrc.pollfd_t.fd = sockCon_server.fd_com;
  pollSrc.readFnk = theReadFnk;
  pollSrc.pollhupFnk = thePollhupFnk;
  //pollSrc.writeFnk = theWriteFnk;
  pollMngPollSources[0] = pollSrc;
  ec_neg1( pollMngInit(pollMngPollSources) )
  
  ec_neg1( pollMngPoll(pollMngPollSources) )
  //ec_neg1( read(sockCon_server.fd_com, buf, sizeof(buf)) )
  //printf("Server got \"%s\"\n", buf);
  //ec_neg1( write(sockCon_server.fd_com, "Goodbye!", 9 ) )

  ec_neg1(sockServerClose(&sockCon_server) )
    exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}

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
}

/*static char * hallo = "hallo";
static int theWriteFnk(char * buf)
{
  buf = hallo;
  return sizeof(hallo);
  }*/
