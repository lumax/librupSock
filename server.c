/*
Bastian Ruppert
*/

//#include <stdio.h>
//#include <stdlib.h>


#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <pollManager.h>

#include <rupSock.h>

#define SOCKNAME "RUPSOCKET"

static _pollMngSrcContainer_t PollSrc;

static int theReadFnk(char * buf,int len,int pMngIndex,void * dat)
{
  _pollMngSrc_t * pollSrc = (_pollMngSrc_t*)dat;
  //ec_neg1( tmp = read(sockCon_client.fd, buf, sizeof(buf)) )
  int i = 0;
  for(i=0;i<len;i++)
    {
      printf("|%c", buf[i]);
    }
  //pollMngSuspendPolling();
  ec_neg1( write(pollSrc->fd, "Server!\n", 9 ) ) 
  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

static _pollMngSrcContainer_t PollSrc={
  .Srcs[0]={
    .readFnk = theReadFnk,
  },
 .Srcs[1]={
    .readFnk = theReadFnk,
  },
};

int main(void)
{
  printf("server\n");
  ec_neg1(createServerSocketFd(SOCKNAME) )
  ec_neg1(sockServerConnect(&PollSrc.Srcs[0]) )
  ec_neg1(sockServerConnect(&PollSrc.Srcs[1]) )
 
  pollMngInit(&PollSrc,2);

  pollMngPoll();

  exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}
