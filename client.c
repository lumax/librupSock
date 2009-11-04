/*
Bastian Ruppert
*/

#include <stdio.h>
#include <stdlib.h>


#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pollManager.h>
#include "rupSock.h"

#define SOCKNAME "RUPSOCKET"

static _pollMngSrc_t PollSrc[];

static int theSTDReadFnk(char * buf,int len,int pMngIndex,void * dat)
{
  //_pollMngSrc_t * pollSrc = (_pollMngSrc_t*)dat;
  //ec_neg1( tmp = read(sockCon_client.fd, buf, sizeof(buf)) )
  int i = 0;
  printf("SDTIN Read Fnk\n");
  for(i=0;i<len;i++)
    {
      printf("|%c", buf[i]);
    }
  //pollMngSuspendPolling();
  ec_neg1( write(PollSrc[0].fd,buf,len) ) 
  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

static int theReadFnk(char * buf,int len,int pMngIndex,void * dat)
{
  //_pollMngSrc_t * pollSrc = (_pollMngSrc_t*)dat;
  //ec_neg1( tmp = read(sockCon_client.fd, buf, sizeof(buf)) )
  int i = 0;
  for(i=0;i<len;i++)
    {
      printf("|%c", buf[i]);
    }
  //pollMngSuspendPolling();
  //ec_neg1( write(pollSrc->fd, "Hello2000!", 11 ) ) 
  return 0;
  /*EC_CLEANUP_BGN
    return -1;
    EC_CLEANUP_END*/
}

static int thePollUpFnk(int pMngIndex)
{
  printf("pollUp index : %i\n",pMngIndex);
  pollMngSuspendPolling();
  return 0;
}

static _pollMngSrc_t PollSrc[]={
  [0]={
    .readFnk = theReadFnk,
    //.writeFnk = theWriteFnk,
    .pollhupFnk = thePollUpFnk,
  },
  [1]={
    .fd = 0,       //fd STDIO
    .readFnk = theSTDReadFnk,
    //.writeFnk = theWriteFnk,
    .pollhupFnk = thePollUpFnk,
    },
};

 

int main(void)
{
  printf("client2000\n");

  ec_neg1(sockClientConnect(&PollSrc[0],SOCKNAME) )
    
    pollMngInit(PollSrc,2);
  ec_neg1( write(PollSrc[0].fd, "hello\n", 7 ) ) 
    
   
    
    pollMngPoll(PollSrc,2);

    //ec_neg1( write(sockCon_client.fd, "Hello!", 7 ) ) 
    //ec_neg1( tmp = read(sockCon_client.fd, buf, sizeof(buf)) )
    //printf("Client got \"%s\", bytes: %i\n", buf,tmp);

  ec_neg1(close(PollSrc[0].fd) )
  exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}
