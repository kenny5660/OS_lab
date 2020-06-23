#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "commands.h"

void print_server_ans(int sock_id) {
  char buff[1024];
  int n = 0;
  while ((n = recv(sock_id, buff, sizeof(buff) - 1, 0)) == sizeof(buff) - 1) {
    buff[n] = '\0';
    printf(buff);
  }
  if (n < 0) {
    printf("Error ride");
  } else {
    buff[n] = '\0';
    printf(buff);
  }
}


void write2server(int sock_id, enum Command c, char *s) {
  char snum[1024];
  memset(snum, '\0', sizeof(snum));
  sprintf(snum, "%d %s", c, s);
  if (send(sock_id, snum, strlen(snum) + 1, 0) < 0) {
    printf("Error write");
  };
}

void get_time(int sock_id) {
  write2server(sock_id, get_time_sc, "");
  print_server_ans(sock_id);
}

void get_file(int sock_id, char *way) {
  write2server(sock_id, read_sc, way);
  print_server_ans(sock_id);
}


int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    if(argv[2][0] == '-' && argv[2][1] == 't'){
       get_time(sockfd);
    }
    if(argv[2][0] == '-' && argv[2][1] == 'f'){
               get_file(sockfd, argv[3]);
    }


    return 0;
}