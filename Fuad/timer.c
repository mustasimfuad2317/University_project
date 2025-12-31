#include <stdio.h>
#include <unistd.h>

int main()
{
    int h, m, s;

    printf("Hour dao: ");
    scanf("%d", &h);

    printf("Minute dao: ");
    scanf("%d", &m);

    printf("Second dao: ");
    scanf("%d", &s);

    while (h != 0 || m != 0 || s != 0)
    {
        printf("\rTime Left: %02d:%02d:%02d", h, m, s);
        fflush(stdout);
        sleep(1);

        if (s > 0)
            s--;
        else
        {
            s = 59;
            if (m > 0)
                m--;
            else
            {
                m = 59;
                h--;
            }
        }
    }

    printf("\n TIME UP!\n");

    return 0;
}