/*
Bastian Ruppert
*/

#include <stdio.h>
#include <stdlib.h>


#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "rupSock.h"

#define SOCKNAME "RUPSOCKET"
int main(void)
{
  int tmp = 0;
  char buf[100];
  _sockCon_t sockCon_client;

  memset(&sockCon_client, 0, sizeof(_sockCon_t));


  printf("client\n");
  ec_neg1(sockClientConnect(&sockCon_client,SOCKNAME) )
  
    ec_neg1( write(sockCon_client.fd_com, "Hello!", 7 ) ) 
    ec_neg1( tmp = read(sockCon_client.fd_com, buf, sizeof(buf)) )
    printf("Client got \"%s\", bytes: %i\n", buf,tmp);

  ec_neg1(sockClientClose(&sockCon_client) )
  exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}
