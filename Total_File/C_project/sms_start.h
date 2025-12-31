#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9000
#define BUF_SIZE 512

static int server_fd = -1;
static int client_fd = -1;

int start_chat()
{
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 1);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    return client_fd > 0 ? 0 : -1;
}

int send_message(const char *msg)
{
    if (client_fd < 0) return -1;
    return send(client_fd, msg, strlen(msg), 0);
}

int receive_message(char *buffer)
{
    if (client_fd < 0) return -1;
    memset(buffer, 0, BUF_SIZE);
    return recv(client_fd, buffer, BUF_SIZE - 1, 0);
}

void close_chat()
{
    if (client_fd >= 0) close(client_fd);
    if (server_fd >= 0) close(server_fd);
}
