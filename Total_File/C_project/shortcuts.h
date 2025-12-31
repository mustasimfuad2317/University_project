#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <glib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void run_cmd(const char *cmd)
{
    if (fork() == 0)
    {
        setsid();
        system(cmd);
        _exit(0);
    }
}

gpointer hotkey_listener_thread(gpointer data)
{
    Display *display;
    Window root;
    XEvent event;

    display = XOpenDisplay(NULL);
    if (!display)
    {
        g_warning("Cannot open X display");
        return NULL;
    }

    root = DefaultRootWindow(display);

    unsigned int mod = ControlMask | ShiftMask;

    int key_c = XKeysymToKeycode(display, XK_C);
    int key_t = XKeysymToKeycode(display, XK_T);
    int key_b = XKeysymToKeycode(display, XK_B);
    int key_n = XKeysymToKeycode(display, XK_N);

    XGrabKey(display, key_c, mod, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, key_t, mod, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, key_b, mod, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, key_n, mod, root, True, GrabModeAsync, GrabModeAsync);

    XSelectInput(display, root, KeyPressMask);

    g_message("Hotkey listener started");

    while (1)
    {
        XNextEvent(display, &event);

        if (event.type == KeyPress)
        {
            XKeyEvent *key = (XKeyEvent *)&event;

            if ((key->state & mod) == mod)
            {
                if (key->keycode == key_c)
                    run_cmd("gnome-calendar &");

                else if (key->keycode == key_t)
                    run_cmd("gnome-terminal &");

                else if (key->keycode == key_b)
                    run_cmd("xdg-open https://www.google.com &");

                else if (key->keycode == key_n)
                    run_cmd("gedit &");
            }
        }
    }

    XCloseDisplay(display);
    return NULL;
}
