/* 
Bastian Ruppert
*/

#ifndef __RUPSOCK_H__
#define __RUPSOCK_H__

//Socket Server Connection
typedef struct
{
  _pollMngSrc_t * pPollSrc;
  // int socketFd;   //file descriptor Socket
  //int (*readFnk)(char * buf,int len,int pMngIndex,void * dat);
}_pollMngServer_t;


//int sockCreateAfSocket(_sockSocket_t * sock,char * socketname);
int sockClientConnect(_pollMngSrc_t * sock,char * socketname);

int createServerSocketFd(char * socketname);

int sockServerConnect(_pollMngServer_t * sock);

int sockServerClose(_pollMngServer_t * sCon);

#endif /* __RUPSOCK_H__ */

