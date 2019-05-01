#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#define SIZE sizeof(struct sockaddr_un)

int bogoPrimes(int n){
  //find the highest prime smaller then X
  int high = 2;
  for (int i = 2; i <= n; i++){
    int prime = 1; //Set the number to be prime at first

    for (int j = 2; j < i; j++){
      if (i % j == 0){
        prime = 0;
      }
    }
    if (prime == 1){

      if (i > high){
        high = i;
      }
    }
    }
    return high;
  }

int main () {
  int sockfd, errnum, polval, x, y;
  char c, rc, username[60], msg[150], msgS[150], *substr, d;
  struct sockaddr_in toserver;
  struct pollfd poll_list[1];
  toserver.sin_family=AF_INET;
  toserver.sin_addr.s_addr = inet_addr("127.0.0.1");
  toserver.sin_port=htons(4321);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  errnum = errno;
  printf("Error is: %s the number is: %d\n", strerror(errno), errnum);
  int con = connect(sockfd, (struct sockaddr *)&toserver, SIZE);
  poll_list[0].fd = sockfd; //Add the server to poll list
  poll_list[0].events = POLLIN|POLLPRI; //Intrested in when the socket is available to be read;
  errnum = errno;
  printf("Error is: %s the number is: %d\n", strerror(errno), errnum);
  sprintf(username, "PrimesBot: ");
  send(sockfd, &username, 60, 0);
  for (;;)
   {
      recv(sockfd, &msg, 150, 0);
      substr = strstr(msg, "primes");
      if (substr != NULL){
        substr += 7;
        x = atoi(substr);
        y = bogoPrimes(x);
        sprintf(msg, "Biggest prime below %d is %d", x, y);
        printf("%s\n", msg);
        strcpy(msgS, username);
        strcat(msgS, msg);
        send(sockfd, &msgS, 150, 0);
      }



   }
}
