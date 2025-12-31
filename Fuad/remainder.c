#include <stdio.h>
#include <time.h>
#include <unistd.h>

void input_task(char task[]);
time_t input_time();
void reminder(time_t future, char task[]);

void input_task(char task[])
{
    printf("Enter task: ");
    fgets(task, 100, stdin);
}

time_t input_time()
{
    int d, m, y, h, min;

    printf("Enter date & time (DD-MM-YYYY HH:MM): ");
    scanf("%d-%d-%d %d:%d", &d, &m, &y, &h, &min);

    struct tm t = {0};
    t.tm_mday = d;
    t.tm_mon = m - 1;
    t.tm_year = y - 1900;
    t.tm_hour = h;
    t.tm_min = min;
    t.tm_sec = 0;

    return mktime(&t);
}

void reminder(time_t future, char task[])
{
    printf("please wait...\n");

    while (1)
    {
        if (time(NULL) >= future)
        {
            printf("\n REMINDER \n");
            printf("Task: %s", task);
            break;
        }
        sleep(1);
    }
}

int main()
{
    char task[100];
    time_t future, now;
    struct tm *now_tm;

    input_task(task);
    future = input_time();

    now = time(NULL);
    now_tm = localtime(&now);
    now_tm->tm_sec = 0;
    now = mktime(now_tm);

    if (future < now)
    {
        printf("This time already passed.\n");
        return 0;
    }

    if (future == now)
    {
        printf("\n REMINDER \n");
        printf("Task: %s", task);
        return 0;
    }

    reminder(future, task);
    return 0;
}
