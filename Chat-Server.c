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
  int sockfd;
  char c;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int client_len = SIZE;
  server.sin_family=AF_INET;
  server.sin_port=htons(4321);
  server.sin_addr.s_addr=INADDR_ANY;
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  bind(sockfd, (struct sockaddr *)&server, SIZE);
  for (;;)
  {
    recvfrom(sockfd, &c, 1, 0, (struct sockaddr *)&client, &client_len);
    c= toupper(c);
    sendto(sockfd, &c, 1, 0, (struct sockaddr *)&client, client_len);
  }
}
