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
#define NAME "/mnt/socketFile"



int main () {
  int sockfd, errnum, polval;
  char c, rc, username[60], msg[150], d;
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
  recv(sockfd, &msg, 150, 0);
  getchar();
  printf("%s\n", msg);
  for (rc='\n';;)
   {
      if (rc == '\n'){
        printf("Press any key to recieve a msg or type 't' to enter a msg \n");
        d = getchar();
        if (d == 't'){
          *msg = ""; //reset string
          printf("> ");
          scanf("%s", msg);
          printf("%s\n", msg);
          printf("%s\n", username);
          sprintf(msg, "|%s|: %s", username, msg);
          send(sockfd, &msg, 150, 0);
          recv(sockfd, &msg, 150, 0);
          printf("message sent is as follows: %s\n",msg);
        }else {
          printf("Checking for message....\n");
          polval = poll(poll_list, 1, 5000);
          printf("polval: %d\n", polval);
          printf("revent: %d\n", poll_list[0].revents&POLLIN);
          if (polval > 0){
            recv(sockfd, &msg, 150, 0);
            printf("%s\n",msg);
          }else {
            printf("No message to be recieved\n");
          }
        }
    }


   }
}











//   int sockfd, *ad_size;
//   char c;
//   char username[60];
//   char msg[150];
//   struct sockaddr_in client = {AF_INET, INADDR_ANY, INADDR_ANY};
//   struct sockaddr_in server = {AF_INET, 4321};
//   socklen_t clientlen = sizeof(client);
//   server.sin_family=AF_INET;
//   server.sin_addr.s_addr = inet_addr("127.0.0.1");
//   server.sin_port=htons(4321);
//
//   printf("Input username: ");
//   read(0, &username, 60);
//
//
//   sockfd = socket(PF_INET, SOCK_DGRAM, 0);
//   connect(sockfd, (struct sockaddr *)&server, sizeof(server));
//
//   printf("Connected %d", sockfd);
//   sendto(sockfd, &username, 60, 0, (struct sockaddr *)&server, sizeof(server));
//   recvfrom(sockfd, &msg, 60, 0, (struct sockaddr *)&client, &clientlen);
//
//   for (;;)
//   {
//    read(0, &c, 1);
//    sendto(sockfd, &c, 1, 0, (struct sockaddr *)&server, sizeof(server));
//    recvfrom(sockfd, &c, 1, 0, (struct sockaddr *)&client, &clientlen);
//    printf("%c\n",c);
//   }
// }
