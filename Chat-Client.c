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


int main () {
  int sockfd, errnum, polval;
  char c, rc, username[60], msg[150], msgR[150], msgS[150], d;
  struct sockaddr_in toserver;
  struct pollfd poll_list[1];
  toserver.sin_family=AF_INET;
  toserver.sin_addr.s_addr = inet_addr("127.0.0.1");
  //toserver.sin_addr.s_addr = INADDR_ANY;
  toserver.sin_port=htons(4321);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  errnum = errno;
  printf("Error is: %s the number is: %d\n", strerror(errno), errnum);
  int con = connect(sockfd, (struct sockaddr *)&toserver, SIZE);
  poll_list[0].fd = sockfd; //Add the server to poll list
  poll_list[0].events = POLLIN|POLLPRI; //Intrested in when the socket is available to be read;
  errnum = errno;
  printf("Error is: %s the number is: %d\n", strerror(errno), errnum);
  printf("%d\n", sockfd);
  printf("%d\n", con);
  printf("Enter username: ");
  scanf("%s", username);
  //fgets(username, 60, stdin);
  send(sockfd, &username, 60, 0);
  sprintf(username, "%s: ", username);
  recv(sockfd, &msgR, 150, 0);
  getchar();
  printf("%s\n", msgR);
  for (rc='\n';;)
   {
      if (rc == '\n'){
        printf("Enter 'r' to recieve a msg or 't' to type a msg \n");
        d = getchar();
        if (d == 't'){
          printf("> ");
          getchar();
          //scanf("%[^\n]%*c", msg);
          fflush(stdin);
          fgets(msg, 150, stdin);
          strcpy(msgS, username);
          strcat(msgS, msg);
          send(sockfd, &msgS, 150, 0);
          recv(sockfd, &msgR, 150, 0);
          printf("%s\n", msgR);
        }else if (d == 'r') {
          printf("Checking for message....\n");
          polval = poll(poll_list, 1, 5000);
          printf("polval: %d\n", polval);
          printf("revent: %d\n", poll_list[0].revents&POLLIN);
          if (polval > 0){
            recv(sockfd, &msgR, 150, 0);
            printf("%s\n",msgR);
          }else {
            printf("No message to be recieved\n");
          }
        }
    }


   }
}
