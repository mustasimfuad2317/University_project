#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t file_mutex;

// ---------------- ADD REMINDER THREAD ----------------
void* add_reminder(void* arg)
{
    while (1)
    {
        int d, m, y, h, min;
        char task[100];

        printf("\nEnter task (or type exit): ");
        fgets(task, sizeof(task), stdin);

        if (strncmp(task, "exit", 4) == 0)
            exit(0);

        printf("Enter date & time (DD-MM-YYYY HH:MM): ");
        scanf("%d-%d-%d %d:%d", &d, &m, &y, &h, &min);
        getchar(); // clear newline

        pthread_mutex_lock(&file_mutex);

        FILE *fp = fopen("reminders.txt", "a");
        if (fp)
        {
            fprintf(fp, "%d %d %d %d %d | %s",
                    y, m, d, h, min, task);
            fclose(fp);
            printf("✔ Reminder added\n");
        }
        else
        {
            printf("❌ File error\n");
        }

        pthread_mutex_unlock(&file_mutex);
    }
    return NULL;
}

// ---------------- CHECK REMINDER THREAD ----------------
void* check_reminder()
{
    while (1)
    {
        pthread_mutex_lock(&file_mutex);

        FILE *fp = fopen("reminders.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (!fp || !temp)
        {
            pthread_mutex_unlock(&file_mutex);
            sleep(1);
            continue;
        }

        int y, m, d, h, min;
        char task[100];
        time_t now = time(NULL);

        while (fscanf(fp, "%d %d %d %d %d | %[^\n]\n",
                      &y, &m, &d, &h, &min, task) == 6)
        {
            struct tm t = {0};
            t.tm_year = y - 1900;
            t.tm_mon  = m - 1;
            t.tm_mday = d;
            t.tm_hour = h;
            t.tm_min  = min;
            t.tm_isdst = -1;

            time_t reminder_time = mktime(&t);

            if (now >= reminder_time)
            {
               
                char cmd[256];
                snprintf(cmd, sizeof(cmd),
                         "notify-send \"Reminder\" \"%s\"",
                         task);
                system(cmd);
            }
            else
            {
                fprintf(temp, "%d %d %d %d %d | %s\n",
                        y, m, d, h, min, task);
            }
        }

        fclose(fp);
        fclose(temp);
        rename("temp.txt", "reminders.txt");

        pthread_mutex_unlock(&file_mutex);
        sleep(1);
    }
    return NULL;
}





// void start_reminder(){
//     pthread_t t1, t2;
//     pthread_mutex_init(&file_mutex, NULL);

//     // printf("===== MULTI-THREADED REMINDER SYSTEM =====\n");
//     // printf("✔ Desktop Notifications Enabled\n");
//     // printf("Type 'exit' to quit\n");

//     pthread_create(&t1, NULL, add_reminder, NULL);
//     pthread_create(&t2, NULL, check_reminder, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     pthread_mutex_destroy(&file_mutex);
    
// }






// // ---------------- MAIN ----------------
// int main()
// {
//     reminder();
//     return 0;
// }
