/* 
Bastian Ruppert
*/

#ifndef __RUPSOCK_H__
#define __RUPSOCK_H__

int sockClientConnect(_pollMngSrc_t * sock,char * socketname);

int createServerSocketFd(char * socketname);

int sockServerConnect(_pollMngSrc_t * sock);

#endif /* __RUPSOCK_H__ */

