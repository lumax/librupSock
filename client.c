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
  _sockSocket_t sockCon_client;

  memset(&sockCon_client, 0, sizeof(_sockSocket_t));

  printf("client\n");
  ec_neg1(sockCreateAfSocket(&sockCon_client,SOCKNAME) )
  ec_neg1(sockClientConnect(&sockCon_client) )
  
    ec_neg1( write(sockCon_client.fd, "Hello!", 7 ) ) 
    ec_neg1( tmp = read(sockCon_client.fd, buf, sizeof(buf)) )
    printf("Client got \"%s\", bytes: %i\n", buf,tmp);

  ec_neg1(close(sockCon_client.fd) )
  exit(EXIT_SUCCESS);
  
  EC_CLEANUP_BGN
    exit(EXIT_FAILURE);
  EC_CLEANUP_END
}
