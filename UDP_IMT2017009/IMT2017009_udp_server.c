#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//This fuction swaps the values
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
        if (arr[j] < arr[j+1])
          swap(&arr[j], &arr[j+1]);
}

int main(int argc, char *argv[]){
    int sock, length, fromlen, n;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    char buf[500];
    // creating the socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // if socket is not created then an error message is displayed
    if (sock < 0)
        printf("there was an error creating the socket");

    // entering the server address details,  which include the server's IP address and also the port number
    // the port number has been taken as command line input
    length = sizeof(server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(atoi(argv[1]));

    // binding the server to the given port number
    bind(sock, (struct sockaddr *)&server_address, length);

    fromlen = sizeof(struct sockaddr_in);

    // recieving the message from the client
    n = recvfrom(sock, buf, 500, 0,(struct sockaddr *) &client_address, (socklen_t *)&fromlen);
    printf ("%s\n", buf);

    //Converting the Recieved string to an Array
    int i = 0;
    char *p = strtok (buf, ",");
    char *array[100];
    int arr[100] = {0};
    while (p != NULL)
    {
      array[i++] = p;
      p = strtok (NULL, ",");
    }

    for (int j = 0; j < i; j++)
      arr[j]=atoi(array[j]);

    bubbleSort(arr, i);

    char arr_Send[500];
    int k = 0;

  //Converting the Array back to String to send(with commas inserted)
  for (int j = 0; j < i; j++)
  {
    k += sprintf (&arr_Send[k], "%d", arr[j]);
    if (j<i-1) {
      k += sprintf (&arr_Send[k], ",");
    }
  }
    // sending the sorted string back to the client.
    k = sendto(sock, arr_Send, 500, 0, (struct sockaddr*) &client_address, fromlen);
    return 0;
} 
