#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include "client.h"

// --- Global variables ---
int client_fd = -1;
char server_ip[64];

// --- GTK globals ---
GtkWidget *text_view;
GtkTextBuffer *text_buffer;
GtkWidget *entry;
GtkWidget *ip_entry_window;
GtkWidget *ip_entry;

// --- Text alignment tags ---
GtkTextTag *tag_left;
GtkTextTag *tag_right;

// --- Append message with left/right alignment ---
void append_message(const char *msg, gboolean is_self)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(text_buffer, &end);

    if (is_self) {
        gtk_text_buffer_insert_with_tags(text_buffer, &end, msg, -1, tag_right, NULL);
    } else {
        gtk_text_buffer_insert_with_tags(text_buffer, &end, msg, -1, tag_left, NULL);
    }

    gtk_text_buffer_insert(text_buffer, &end, "\n\n", -1);
}

// --- GTK idle callback for thread-safe GUI update ---
gboolean ui_append_cb(gpointer data)
{
    UiMsg *m = data;
    append_message(m->msg, m->is_self);
    g_free(m->msg);
    g_free(m);
    return FALSE; // run once
}

// --- Connect to server ---
int connect_to_server(const char *ip)
{
    if (client_fd >= 0) {
        return 0; // already connected
    }

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(client_fd);
        client_fd = -1;
        return -1;
    }

    strncpy(server_ip, ip, sizeof(server_ip) - 1);
    return 0;
}

// --- Receive thread ---
gpointer receive_thread(gpointer data)
{
    char buffer[BUF_SIZE];
    
    // Send welcome message
    UiMsg *welcome = g_malloc(sizeof(UiMsg));
    welcome->msg = g_strdup("Connected to server!");
    welcome->is_self = FALSE;
    g_idle_add(ui_append_cb, welcome);
    
    while (1) {
        int n = recv(client_fd, buffer, BUF_SIZE - 1, 0);
        if (n <= 0) {
            // Connection closed
            UiMsg *disconnected = g_malloc(sizeof(UiMsg));
            disconnected->msg = g_strdup("Disconnected from server.");
            disconnected->is_self = FALSE;
            g_idle_add(ui_append_cb, disconnected);
            break;
        }

        buffer[n] = '\0';
        UiMsg *m = g_malloc(sizeof(UiMsg));
        m->msg = g_strdup(buffer);
        m->is_self = FALSE;

        g_idle_add(ui_append_cb, m);
    }
    
    close(client_fd);
    client_fd = -1;
    return NULL;
}

// --- Send button callback ---
void on_send_clicked(GtkButton *button, gpointer data)
{
    if (client_fd < 0) {
        append_message("Not connected to server.", FALSE);
        return;
    }

    const char *msg = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(msg) == 0) return;

    // Send to server
    send(client_fd, msg, strlen(msg), 0);
    
    // Check for exit command
    if (strcmp(msg, "exit") == 0) {
        close(client_fd);
        client_fd = -1;
        append_message("Disconnected from server.", FALSE);
    }

    // Display message in chat
    UiMsg *m = g_malloc(sizeof(UiMsg));
    m->msg = g_strdup(msg);
    m->is_self = TRUE;
    g_idle_add(ui_append_cb, m);

    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// --- IP submit callback ---
void on_ip_submit(GtkButton *button, gpointer data)
{
    const char *ip = gtk_entry_get_text(GTK_ENTRY(ip_entry));
    if (strlen(ip) == 0) return;
    
    // Try to connect
    if (connect_to_server(ip) == 0) {
        // Close IP window
        gtk_widget_destroy(ip_entry_window);
        
        // Start receive thread
        g_thread_new("recv", receive_thread, NULL);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Failed to connect to server.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// --- Create IP input window ---
void create_ip_window(GtkApplication *app)
{
    GtkWidget *vbox, *hbox, *label;
    
    ip_entry_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(ip_entry_window), "Connect to Server");
    gtk_window_set_default_size(GTK_WINDOW(ip_entry_window), 400, 150);
    gtk_window_set_position(GTK_WINDOW(ip_entry_window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(ip_entry_window), 20);
    
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_container_add(GTK_CONTAINER(ip_entry_window), vbox);
    
    label = gtk_label_new("Enter Server IP Address:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    
    ip_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(ip_entry), "e.g., 127.0.0.1");
    gtk_box_pack_start(GTK_BOX(vbox), ip_entry, FALSE, FALSE, 0);
    
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    
    GtkWidget *connect_btn = gtk_button_new_with_label("Connect");
    g_signal_connect(connect_btn, "clicked", G_CALLBACK(on_ip_submit), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), connect_btn, TRUE, TRUE, 0);
    
    GtkWidget *quit_btn = gtk_button_new_with_label("Quit");
    g_signal_connect(quit_btn, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), quit_btn, TRUE, TRUE, 0);
    
    gtk_widget_show_all(ip_entry_window);
}

// --- Create chat window ---
void create_chat_window(GtkApplication *app)
{
    GtkWidget *win, *vbox, *hbox;
    GtkWidget *scroll, *send_btn;

    win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Chat Client");
    gtk_window_set_default_size(GTK_WINDOW(win), 500, 400);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    // --- Chat view ---
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view), 10);

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Create alignment tags
    tag_left = gtk_text_buffer_create_tag(text_buffer, "left",
                                         "justification", GTK_JUSTIFY_LEFT, NULL);
    tag_right = gtk_text_buffer_create_tag(text_buffer, "right",
                                          "justification", GTK_JUSTIFY_RIGHT, NULL);

    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(scroll), 5);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    // --- Entry + send button ---
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);

    entry = gtk_entry_new();
    send_btn = gtk_button_new_with_label("Send");
    g_signal_connect(send_btn, "clicked", G_CALLBACK(on_send_clicked), NULL);
    
    // Allow Enter key to send message
    g_signal_connect(entry, "activate", G_CALLBACK(on_send_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), send_btn, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    gtk_widget_show_all(win);
}

// --- Application activate callback ---
static void app_activate(GtkApplication *app, gpointer user_data)
{
    create_ip_window(app);
}

// --- Main function ---
int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("com.example.chatclient", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}