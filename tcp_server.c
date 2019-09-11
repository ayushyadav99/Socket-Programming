#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

int main()
{
  int server_socket;
  server_socket=socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9001);
  server_address.sin_addr.s_addr = inet_addr("192.168.43.54");

  struct sockaddr_in client_address;
  int client_addr_size = sizeof(struct sockaddr_in);

  bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

  listen(server_socket, 1);

  int client_socket;
  client_socket=accept(server_socket, (struct sockaddr *)&client_address , &client_addr_size);


  char arr_Rec[500];
  int arr[100];
  recv(client_socket, &arr_Rec,sizeof(arr_Rec), 0);
  printf("%s\n", arr_Rec);

  int i = 0;
    char *p = strtok (arr_Rec, ",");
    char *array[100];

    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, ",");
    }

    for (int j = 0; j < i; j++)
    {
      arr[j]=atoi(array[j]);
    }

  bubbleSort(arr, i);


  char arr_Send[500];
  int n = 0;

  for (int j = 0; j < i; j++)
  {
    n += sprintf (&arr_Send[n], "%d", arr[j]);
    if (j<i-1) {
      n += sprintf (&arr_Send[n], ",");
    }

  }


  send(client_socket, arr_Send, sizeof(arr_Send), 0);


  close(client_socket);
  // printf("%d", close(client_socket));
  return 0;
}
