#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    // Receive array size
    uint32_t array_size;
    if (recv(sock, &array_size, sizeof(uint32_t), 0) != sizeof(uint32_t)) {
        printf("Failed to receive array size\n");
        return -1;
    }
    array_size = ntohl(array_size);
    
    // Allocate memory for array
    int32_t *array = malloc(array_size * sizeof(int32_t));
    if (!array) {
        printf("Memory allocation failed\n");
        return -1;
    }
    
    // Receive array data
    recv(sock, array, array_size * sizeof(int32_t), 0);
    
    // Print received array
    printf("Received array: ");
    for (uint32_t i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    free(array);
    close(sock);
    return 0;
}