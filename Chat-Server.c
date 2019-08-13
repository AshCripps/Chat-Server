#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <time.h>
#define SIZE sizeof(struct sockaddr_un)
static int *clients;

int addClients(int socket){ //Create my array of sockets - Not working atm because the variable is not shared across processes
  int i;
  for(i = 0; i < sizeof(clients); i++){
    if (clients[i] == 0){
      clients[i] = socket;
      return i; //Socket added
    }
  }
  return -1;
}

int main () {
  int sockfd, clientsockfd, i, j, k, l, connection;
  char c, username[60], msg[150];
  time_t prevTime, currTime;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int client_len = SIZE;
  clients = mmap(NULL, sizeof(int) * 5, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  //printf("%d\n", sockfd);
  server.sin_family=AF_INET;
  server.sin_port=htons(4321);
  server.sin_addr.s_addr=INADDR_ANY;
  k = bind(sockfd, (struct sockaddr *)&server, SIZE);
  //printf("%d\n", k);
  j = listen(sockfd,5);
  //printf("%d\n", j);
  for (;;)
      {
         clientsockfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
         //printf("Clientsockfd: %d\n", clientsockfd);
         l = addClients(clientsockfd);
         if (fork() == 0)
         {
            recv(clientsockfd, &username, 60, 0);
            sprintf(msg, "Welcome %s!", username);
            send(clientsockfd, &msg, 150, 0);
            sprintf(msg, "|Server|: %s has connected", username);

            printf("Added client: %d\n", l);
            if (l < 0) {exit(1);}
            for(i = 0; i < sizeof(clients); i++){
              if (clients[i]>0){ //valid socket
                send(clients[i], &msg, 150, 0);
              }
            }
            printf("%s has connected\n", username);
            connection = 1;
            while (connection == 1){
              prevTime = time(NULL);
              recv(clientsockfd, &msg, 150, 0);
              printf("%s\n", msg);
              currTime = time(NULL) - prevTime;
              printf("Time taken to recieve message was %lld seconds\n", currTime);
              for(i = 0; i < sizeof(clients); i++){
                if (clients[i]>0){ //valid socket
                  prevTime = time(NULL);
                  send(clients[i], &msg, 150, 0);
                  currTime = time(NULL) - prevTime;
                  printf("Time taken to send message was %lld seconds\n", currTime);
                }
              }
            }
            //close(clientsockfd);
            //exit(0);
         }
         //send(clientsockfd, "hello", 150, 0);
         //close(clientsockfd);
   }
}
