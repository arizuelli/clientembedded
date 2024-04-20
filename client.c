#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "192.168.160.132"

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[100];

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    int n, len;
    char *message = "Hello Server";

    // Send message to server
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Message sent.\n");

    // Wait until response from server is received
    n = recvfrom(sockfd, (char *)buffer, 100, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';

    // Process response
    printf("Server : %s\n", buffer);

    // Close the socket
    close(sockfd);

    return 0;
}

