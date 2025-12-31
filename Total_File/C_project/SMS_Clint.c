#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000
#define BUF_SIZE 512




 int join_chat(){
        int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    char server_ip[64];

    printf("Enter Server IP: ");
    scanf("%63s", server_ip);
    getchar();   // consume newline

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to server!\n");
    while (1) {
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    send(client_fd, buffer, strlen(buffer), 0);

    if (strcmp(buffer, "exit") == 0)
        break;
}

    close(client_fd);
    return 0;
 }


int main() {
    join_chat();
}
