#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

#define MY_PORT		9999


int main(void)
{	int sd;

	struct sockaddr_in self;


	if ( (sd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}


	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_addr.s_addr = INADDR_ANY;
	self.sin_port = htons(MY_PORT);


	if ( bind(sd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("Bind");
		abort();
	}


	if ( listen(sd, 20) != 0 )
	{
		perror("Listen");
		abort();
	}


	while (1)
	{	static int client;
		int sd_copy, size;
		struct sockaddr_in client_info;
		size = sizeof(client_info);
		
                client = accept(sd, (struct sockaddr*)&client_info, &size);
		
                if ( client < 0 )
			perror("Accept");
		else
		{
		printf("Conectado por: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

		  //retorno do fork: <0=falha; =0 filho executa; >0 pai executa
                  if ( fork() != 0 ){
				   close(client);
				}
			else
			{
				close(sd);

				dup2(client, 0);
				dup2(client, 1);
				//dup2(client, 2);

				/* chama o programa externo */

				execlp("/bin/ls","ls",NULL);
			}
				}
	}

	close(sd);
	return 0;
}

