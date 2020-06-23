#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include "commands.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>

#define MAX_CLIENT_N (10)

void get_time(int c_id, char *s) {
  char buff[1024];
  time_t ticks;
  ticks = time(NULL);
  snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
  write(c_id, buff, strlen(buff));
}

void get_file(int c_id, char *s) {
  char buff[1024];
  unsigned int n = 0;
  int was_space = 0;
  for (; (*s) == ' ' || !was_space; s++) {
    printf("%c", *s);
    was_space = was_space || (*s) == ' ';
  }
  FILE *f = fopen(s, "r");
  if (!f) {
    send(c_id, "File err", 9, 0);
    return;
  }

  while ((n = fread(buff, 1, 1024, f)) > 0) {
    send(c_id, buff, n, 0);
  }
}

void (*command2run[2])(int c_id, char *s) = {get_time, get_file};

void add_client(int *c, int client) {
  for (unsigned int i = 0; i < MAX_CLIENT_N; i++) {
    if (c[i] < 0) {
      c[i] = client;
      return;
    }
  }
}

void on_sig() {
    printf("Sig");
}

void get_events(int sock_id, int *clients, fd_set *read_set) {
  struct timeval timeout;
  timeout.tv_sec = 1500;
  timeout.tv_usec = 0;
  int max_client = sock_id;

  FD_ZERO(read_set);
  FD_SET(sock_id, read_set);
  for(unsigned int i = 0; i < MAX_CLIENT_N; i++) {
    if (clients[i] >= 0) {
      FD_SET(clients[i], read_set);
    }
    if (max_client < clients[i]) {
      max_client = clients[i];
    }
  }

  if (select(max_client + 1, read_set, NULL, NULL, &timeout) <= 0) {
    printf("Select err");
    exit(1);
  }
}

void execute_events(int sock_id, int *clients, fd_set *read_set, int *client_n) {
  // Определяем тип события и выполняем соответствующие действия
  if(FD_ISSET(sock_id, read_set) && (*client_n < MAX_CLIENT_N)) {
      struct sockaddr_in client_addr;
    // Поступил новый запрос на соединение, используем accept
    socklen_t client_addr_size = sizeof(client_addr);
    int accepted_conn = accept(sock_id, (struct sockaddr *)&client_addr, &client_addr_size);
    if(accepted_conn < 0) {
      perror("accept error");
      close(sock_id);
      exit(1);
    }
    printf("New client IP address is: %s\n", inet_ntoa(client_addr.sin_addr));
    fcntl(accepted_conn, F_SETFL, O_NONBLOCK); // делаем сокет асинхронымм, неблокируемым
    add_client(clients, accepted_conn);
    FD_SET(accepted_conn, read_set);
    (*client_n)++;
  }

  char buff[1024];

  for(unsigned int i = 0; i < MAX_CLIENT_N; i++) {
    if(clients[i] > 0 && FD_ISSET(clients[i], read_set)) {
      // Поступили данные от клиента, читаем их
      int n = recv(clients[i], buff, sizeof(buff) - 1, 0);

      if(n > 0) {
        command2run[atoi(buff)](clients[i], buff);
      }
    }
  }
}

int main(int argc, char *argv[]) {
    int listenfd = 0, accepted_conn = 0;
    struct sockaddr_in serv_addr,client_addr;
    pid_t pid_new;
    char sendBuff[1025];
    time_t ticks;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd< 0){
        perror("socket error");
        exit(1);
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("bind error");
        exit(1);
    }

    if(listen(listenfd, 10) < 0 ){
        perror("listen error");
        exit(1);
    }

    int clients[MAX_CLIENT_N];
    for (unsigned int i = 0; i < MAX_CLIENT_N; i++) {
      clients[i] = -1;
    }
    unsigned int number_clients = 0;
    unsigned int client_n = 1;
    while(1) {
    fd_set read_set;
    get_events(listenfd, clients, &read_set);
    execute_events(listenfd, clients, &read_set, &client_n);
    }
}