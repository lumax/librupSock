/*
Bastian Ruppert
*/

//#include <stdio.h>
//#include <stdlib.h>


#include <defs.h>
#include <sys/socket.h>
#include <sys/un.h>
/*[pgm]*/
#define SOCKETNAME "MySocket"

int main(void)
{
	struct sockaddr_un sa;

	(void)unlink(SOCKETNAME);
	strcpy(sa.sun_path, SOCKETNAME);
	sa.sun_family = AF_UNIX;
	if (fork() == 0) { /* client */
		int fd_skt;
		char buf[100];

		ec_neg1( fd_skt = socket(AF_UNIX, SOCK_STREAM, 0) )
		while (connect(fd_skt, (struct sockaddr *)&sa, sizeof(sa)) == -1)
			if (errno == ENOENT) {
				sleep(1);
				continue;
			}
			else
				EC_FAIL
		ec_neg1( write(fd_skt, "Hello!", 7 ) )
		ec_neg1( read(fd_skt, buf, sizeof(buf)) )
		printf("Client got \"%s\"\n", buf);
		ec_neg1( close(fd_skt) )
		exit(EXIT_SUCCESS);
	}
	else { /* server */
		int fd_skt, fd_client;
		char buf[100];

		ec_neg1( fd_skt = socket(AF_UNIX, SOCK_STREAM, 0) )
		ec_neg1( bind(fd_skt, (struct sockaddr *)&sa, sizeof(sa)) )
		ec_neg1( listen(fd_skt, SOMAXCONN) )
		ec_neg1( fd_client = accept(fd_skt, NULL, 0) )
		ec_neg1( read(fd_client, buf, sizeof(buf)) )
		printf("Server got \"%s\"\n", buf);
		ec_neg1( write(fd_client, "Goodbye!", 9 ) )
		ec_neg1( close(fd_skt) )
		ec_neg1( close(fd_client) )
		exit(EXIT_SUCCESS);
	}

EC_CLEANUP_BGN
		exit(EXIT_FAILURE);
EC_CLEANUP_END
}
