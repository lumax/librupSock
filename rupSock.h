/* 
Bastian Ruppert
*/

#ifndef __RUPSOCK_H__
#define __RUPSOCK_H__

//#include <pollManager.h>

//Socket Connection
typedef struct
{
  struct sockaddr_un sa;
  int fd;                 //file descriptor communication
}_sockSocket_t;

//int (*readFnk)(char * buf,int len,void * src,int pMngIndex);

typedef struct
{
  int fd_skt;                 //file descriptor socket
}_sockServer_t;


int sockCreateAfSocket(_sockSocket_t * sock,char * socketname);

int sockClientConnect(_sockSocket_t * sock);

int sockServerConnect(_sockSocket_t * sock,char * socketname,int * fd_com);

#endif /* __RUPSOCK_H__ */
