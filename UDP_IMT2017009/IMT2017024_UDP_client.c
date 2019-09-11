#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int sock, length, n;
  char arr[256];

  //Creating a Client Socket
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  //Declaring sockaddress for client socket and
  //Initialising sockaddress(IP, Port, Family) for Server Socket
  struct sockaddr_in server, client;
  server.sin_family = AF_INET;
  server.sin_port =htons(atoi(argv[2]));
  server.sin_addr.s_addr= inet_addr(argv[1]);

  length=sizeof(struct sockaddr_in);

  printf("Input the sequence as string: ");
  scanf("%s", arr);

  n=sendto(sock, arr, strlen(arr), 0, (struct sockaddr*)&server, length);
  

  n=recvfrom(sock, arr, 256, 0, (struct sockaddr*)&client, &length);

  printf("Descending sequence is: %s\n", arr);
}
