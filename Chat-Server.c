#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define SIZE sizeof(struct sockaddr_un)
#define NAME "/mnt/socketFile"


int main () {
int sockfd, clientsockfd;
char c;
struct sockaddr_un server, client;
   unlink(NAME);
   sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   //printf("%d\n", sockfd);
   server.sun_family=AF_UNIX;
   strcpy(server.sun_path, NAME);
   int b = bind(sockfd, (struct sockaddr *)&server, SIZE);
   printf("%d\n", b);
   int l = listen(sockfd,5);
   printf("%d\n", l);
for (;;)
      {
		 socklen_t len = sizeof(client);
         clientsockfd = accept(sockfd, (struct sockaddr *)&client, &len);
		 if (clientsockfd > 0){
			if (fork() == 0)
			{
				while (recv(clientsockfd, &c, 1, 0) >0 )
				{
					c= toupper(c);
					send(clientsockfd, &c, 1, 0);
				}
				close(clientsockfd);
				exit(0);
			}
		 }
         close(clientsockfd);
         unlink(NAME);
   }
}
