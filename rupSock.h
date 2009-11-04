/* 
Bastian Ruppert
*/

#ifndef __RUPSOCK_H__
#define __RUPSOCK_H__

//Socket Server Connection
typedef struct
{
  _pollMngSrc_t * pPollSrc;
  int socketFd;   //file descriptor Socket
  int (*readFnk)(char * buf,int len,int pMngIndex,void * dat);
  int (*pollhupFnk)(int pMngIndex); // Gegenseite hat aufgelegt
}_pollMngServer_t;


//int sockCreateAfSocket(_sockSocket_t * sock,char * socketname);
int sockClientConnect(_pollMngSrc_t * sock,char * socketname);

int sockServerConnect(_pollMngServer_t * sock,char * socketname);

#endif /* __RUPSOCK_H__ */
/*typedef struct
{
  int fd;                 //file descriptor
  int (*readFnk)(char * buf,int len,int pMngIndex,void * dat);
  int (*pollhupFnk)(int pMngIndex); // Gegenseite hat aufgelegt
}_sockConnection_t;
*/
