#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#define SIZE sizeof(struct sockaddr_un)
#define NAME "/mnt/socketFile"



int main () {
int sockfd, len;
char c,rc;
struct sockaddr_un toserver;
   toserver.sun_family=AF_UNIX;
   strcpy(toserver.sun_path,NAME);
   len = sizeof(toserver);
   sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   printf("%d\n", sockfd);
   int connection = connect(sockfd, (struct sockaddr *)&toserver, len);
   printf("%d\n", connection);
 for (rc='\n';;)
   {
      if (rc == '\n')
         printf("Enter a lowercase char \n");
		c= getchar();
		send(sockfd, &c, 1, 0);
		if (recv(sockfd, &rc, 1, 0)>0)
			printf("%c\n",rc);
		else
			exit(1);
   }
}
