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
  int sockfd, *ad_size;
  char c;
  struct sockaddr_in client = {AF_INET, INADDR_ANY, INADDR_ANY};
  struct sockaddr_in server = {AF_INET, 4321};
  socklen_t clientlen = sizeof(client);
  server.sin_family=AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port=htons(4321);
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  connect(sockfd, (struct sockaddr *)&server, sizeof(server));
  printf("Enter a lowercase char  ");
  for (;;)
  {
   read(0, &c, 1);
   sendto(sockfd, &c, 1, 0, (struct sockaddr *)&server, sizeof(server));
   recvfrom(sockfd, &c, 1, 0, (struct sockaddr *)&client, &clientlen);
   printf("%c\n",c);
  }
}
