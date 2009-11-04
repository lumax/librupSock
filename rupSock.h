/* 
Bastian Ruppert
*/

#ifndef __RUPSOCK_H__
#define __RUPSOCK_H__

//Socket Connection
typedef struct
{
  struct sockaddr_un sa;
  int fd;   //file descriptor communication
}_sockSocket_t;


//int sockCreateAfSocket(_sockSocket_t * sock,char * socketname);
int sockClientConnect(_pollMngSrc_t * sock,char * socketname);

int sockServerConnect(_pollMngSrc_t * sock,char * socketname,int * socketFd);

#endif /* __RUPSOCK_H__ */
/*typedef struct
{
  int fd;                 //file descriptor
  int (*readFnk)(char * buf,int len,int pMngIndex,void * dat);
  int (*pollhupFnk)(int pMngIndex); // Gegenseite hat aufgelegt
}_sockConnection_t;
*/
