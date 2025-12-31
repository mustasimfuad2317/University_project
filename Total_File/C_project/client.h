#ifndef CLIENT_H
#define CLIENT_H

#include <gtk/gtk.h>
#include <arpa/inet.h>

#define BUF_SIZE 512
#define PORT 9000

// Networking globals
extern int client_fd;
extern char server_ip[64];

// GTK globals
extern GtkWidget *text_view;
extern GtkTextBuffer *text_buffer;
extern GtkWidget *entry;

// Text alignment tags
extern GtkTextTag *tag_left;
extern GtkTextTag *tag_right;

// UI message structure
typedef struct {
    char *msg;
    gboolean is_self;
} UiMsg;

// Function declarations
void append_message(const char *msg, gboolean is_self);
gboolean ui_append_cb(gpointer data);
gpointer receive_thread(gpointer data);
void on_send_clicked(GtkButton *button, gpointer data);
void on_ip_submit(GtkButton *button, gpointer data);
void create_chat_window(GtkApplication *app);
void create_ip_window(GtkApplication *app);

#endif