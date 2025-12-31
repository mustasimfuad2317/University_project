#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void mycmd(){
        char mycmd[50];

        printf("\033[0;32m");   // Green text
        printf("\t\t\t||========== Welcome ==========||\n");
        printf("\033[0m");     // Reset


    while (1)
    {   
        printf("\033[0;32m");
        printf("\nTaskbot >> ");
        
        scanf("%49s", mycmd);
        printf("\033[0m"); 

        /* -------- TEXT EDITOR -------- */
        if (strcmp(mycmd, "Note") == 0)
        {
#ifdef _WIN32
            system("start notepad");
#else
            system("nano");
#endif
        }

        /* -------- CALCULATOR -------- */
        else if (strcmp(mycmd, "Calc") == 0)
        {
#ifdef _WIN32
            system("start calc");
#else
            system("gnome-calculator || bc");
#endif
        }

        /* -------- BROWSER -------- */
        else if (strcmp(mycmd, "Chrome") == 0)
        {
#ifdef _WIN32
            system("start chrome");
#else
            system("xdg-open https://www.google.com");
#endif
        }

        /* -------- PAINT -------- */
        else if (strcmp(mycmd, "Paint") == 0)
        {
#ifdef _WIN32
            system("start mspaint");
#else
            system("gimp");
#endif
        }

        /* -------- FILE MANAGER -------- */
        else if (strcmp(mycmd, "Files") == 0)
        {
#ifdef _WIN32
            system("start explorer");
#else
            system("xdg-open .");
#endif
        }

        /* -------- TERMINAL -------- */
        else if (strcmp(mycmd, "Terminal") == 0)
        {
#ifdef _WIN32
            system("start cmd");
#else
            system("gnome-terminal || xterm");
#endif
        }

        /* -------- TASK MANAGER -------- */
        else if (strcmp(mycmd, "Task") == 0)
        {
#ifdef _WIN32
            system("start taskmgr");
#else
            system("top");
#endif
        }

        /* -------- SYSTEM INFO -------- */
        else if (strcmp(mycmd, "Sysinfo") == 0)
        {
#ifdef _WIN32
            system("start msinfo32");
#else
            system("uname -a");
#endif
        }

        /* -------- CLEAR SCREEN -------- */
        else if (strcmp(mycmd, "Clear") == 0)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }

        /* -------- SHUTDOWN -------- */
        else if (strcmp(mycmd, "Shutdown") == 0)
        {
#ifdef _WIN32
            system("shutdown /s /t 10");
#else
            system("shutdown -h +1");
#endif
        }

        /* -------- RESTART -------- */
        else if (strcmp(mycmd, "Restart") == 0)
        {
#ifdef _WIN32
            system("shutdown /r /t 10");
#else
            system("shutdown -r +1");
#endif
        }

        /* -------- HELP -------- */
        else if (strcmp(mycmd, "Help") == 0)
        {
            printf("\nAvailable Commands:\n");
            printf("Note | Calc | Chrome | Paint | Files\n");
            printf("Terminal | Task | Sysinfo | Clear\n");
            printf("Shutdown | Restart | Exit\n");
        }

        /* -------- EXIT -------- */
        else if (strcmp(mycmd, "Exit") == 0)
        {
            printf("Exiting My_CMD Shell...\n");
            break;
        }

        /* -------- UNKNOWN -------- */
        else
        {
            printf("Unknown command! Type Help\n");
        }
    }

}

int main(){
        mycmd();

}

