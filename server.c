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
  ec_neg1( write(pollSrc->fd, "IchBinServer!", 14 ) ) 
  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
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
    .pollhupFnk = thePollUpFnk,
  },
};

static _pollMngServer_t ServerPollSrc = {
  .pPollSrc = &PollSrc[0],
};

int main(void)
{
  //char buf[100];
  int SocketFd = -1;
  //memset(&sockCon_server, 0, sizeof(_sockSocket_t));
  printf("server\n");
  
  ec_neg1(sockServerConnect(&ServerPollSrc,SOCKNAME) )
    
  ec_neg1( write(PollSrc[0].fd, "IchBinServer!\n", 15 ) )

 
    pollMngInit(PollSrc,1);
    ec_neg1( write(PollSrc[0].fd, "Hello!", 7 ) ) 

   

      pollMngPoll(PollSrc,1);

    /*
      ec_neg1( read(fd_com, buf, sizeof(buf)) )
     printf("Server got \"%s\"\n", buf);
 sleep(1);
  ec_neg1( write(fd_com, "Goodbye\n", 9 ) )
ec_neg1( write(fd_com, "Goodbye\n", 9 ) )
ec_neg1( write(fd_com, "Goodbye\n", 9 ) )
ec_neg1( write(fd_com, "Goodbye!\n", 10 ) )
    sleep(3);
    */
  ec_neg1(close(SocketFd) )
  ec_neg1(close(PollSrc[0].fd) )
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
