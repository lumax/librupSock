/* 
Bastian Ruppert
*/

#ifndef __RUPSOCK_H__
#define __RUPSOCK_H__

typedef struct
{
  struct sockaddr_un sa;
  int fd_skt;                 //file descriptor socket
  int fd_com;                 //file descriptor communication
}_sockCon_t;

int sockClientConnect(_sockCon_t * sCon, char * socketname);

int sockClientClose(_sockCon_t * sCon);

int sockServerConnect(_sockCon_t * sCon, char * socketname);

int sockServerClose(_sockCon_t * sCon);

#endif /* __RUPSOCK_H__ */
