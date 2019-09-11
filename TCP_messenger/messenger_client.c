#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
    

    // creating a network socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9001);
    server_address.sin_addr.s_addr = inet_addr("172.16.87.4");

    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9005);
    client_address.sin_addr.s_addr = INADDR_ANY;
    
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // checking for error in connection
    if (connection_status == -1){
        printf ("There was an error making a connection to the remote socket \n");
        return 0;
    }
    
    
    bind(network_socket, (struct sockaddr *) &client_address, sizeof(client_address));
    
    while(1){
        char end_statement[4] = "xxxx";
        //sending data to the server
        char array[140];
        printf ("You : ");
        scanf("%s", array);
        send(network_socket, array, sizeof(array), 0); 
    
        // receive data from the server
        char server_response[256];
        recv(network_socket, &server_response, sizeof(server_response), 0);
    
        if (strcmp(array, end_statement) == 0)
            break;
        //print out the server's response
        printf("Kaushal : %s \n", server_response);

        }
    
    // closing the socket
    close(network_socket);
    return 0;
}
