#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main()
{
  int server_socket;
  server_socket=socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = inet_addr("172.16.83.253");

  struct sockaddr_in client_address;
  int client_addr_size = sizeof(struct sockaddr_in);

  bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

  listen(server_socket, 1);

  int client_socket;
  client_socket=accept(server_socket, (struct sockaddr *)&client_address , &client_addr_size);

  while (1)
  {
  char my_aa[140];
  recv(client_socket, &my_aa, 140, 0);
  if (strcmp(my_aa,"xxxx")==0) break;
  printf("Ayush: %s\nYou: ",my_aa);

  char arr[100];
  scanf("%s", arr);
  if (strcmp(arr,"xxxx")==0) break;
  send(client_socket, arr, sizeof(arr), 0);

  }

  close(client_socket);
  // printf("%d", close(client_socket));
  return 0;
}
