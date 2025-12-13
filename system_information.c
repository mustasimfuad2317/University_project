#include <stdio.h>
#include <stdlib.h>

void show_menu()
{
    printf(
        "\n===== System Information Menu =====\n"
        "1. OS Info\n"
        "2. CPU Info\n"
        "3. RAM Info\n"
        "4. Storage Info\n"
        "5. Network Info\n"
        "6. GPU Info\n"
        "7. System Uptime\n"
        "8. Save Report to File\n"
        "9. Running Processes\n"
        "0. Exit\n"
        "Enter your choice: ");
}


void show_os_info()
{
    system("ver");
}

void show_cpu_info()
{
    system("wmic cpu get name,NumberOfCores,NumberOfLogicalProcessors,MaxClockSpeed");
}

void show_ram_info()
{
    system("wmic memorychip get capacity, speed");
}

void show_storage_info()
{
    system("wmic logicaldisk get name,size,freespace,description");
}

void show_network_info()
{
    system("ipconfig /all");
}

void show_gpu_info()
{
    system("wmic path win32_VideoController get name,AdapterRAM");
}

void show_system_uptime()
{
    system("net stats workstation | find \"Statistics since\"");
}

void save_report_to_file()
{
    system("systeminfo > system_report.txt");
    printf("Report saved to system_report.txt\n");
}

void show_running_processes()
{
    system("tasklist");
}

// choice handle করার জন্য আলাদা ফাংশন
void handle_choice(int choice)
{
    switch (choice)
    {
    case 1:
        show_os_info();
        break;
    case 2:
        show_cpu_info();
        break;
    case 3:
        show_ram_info();
        break;
    case 4:
        show_storage_info();
        break;
    case 5:
        show_network_info();
        break;
    case 6:
        show_gpu_info();
        break;
    case 7:
        show_system_uptime();
        break;
    case 8:
        save_report_to_file();
        break;
    case 9:
        show_running_processes();
        break;
    case 0:
        printf("Exiting...\n");
        break;
    default:
        printf("Invalid choice!\n");
    }
}

int main()
{
    int choice;

    do
    {
        show_menu(); // শুধু menu print
        scanf("%d", &choice);

        handle_choice(choice); // কাজ সব বাইরে
    } while (choice != 0);

    return 0;
}