#include <stdio.h>
#include <stdlib.h>



// void sysinfo(){
//     int choice;

//     do
//     {
//         show_menu();
//         scanf("%d", &choice);
//         handle_choice(choice);
//     } while (choice != 0);
// }


// void show_menu()
// {
//     printf(
//         "\nPlease choose one option:\n"
//         "1. OS Info\n"
//         "2. CPU Info\n"
//         "3. RAM Info\n"
//         "4. Storage Info\n"
//         "5. Network Info\n"
//         "6. GPU Info\n"
//         "7. System Uptime\n"
//         "8. Save Report to File\n"
//         "9. Running Processes\n"
//         "0. Exit\n"
//         "Enter your choice: ");
// }




/* ---------------- Clear file ---------------- */

void clearFile(const char *filename)
{
    FILE *fp = fopen(filename, "w");  // "w" truncates the file
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    fclose(fp);
}




/* ---------------- OS INFO ---------------- */
void show_os_info()
{
#ifdef _WIN32
    system("ver");
#else
    clearFile("system_report.txt");
    system("uname -a >> system_report.txt");
#endif
}

/* ---------------- CPU INFO ---------------- */
void show_cpu_info()
{
#ifdef _WIN32
    system("wmic cpu get name,NumberOfCores,NumberOfLogicalProcessors,MaxClockSpeed");
#else
    clearFile("system_report.txt");
    system("lscpu >> system_report.txt");
#endif
}

/* ---------------- RAM INFO ---------------- */
void show_ram_info()
{
#ifdef _WIN32
    system("wmic memorychip get capacity,speed");
#else
    clearFile("system_report.txt");
    system("free -h >> system_report.txt");
#endif
}

/* ---------------- STORAGE INFO ---------------- */
void show_storage_info()
{
#ifdef _WIN32
    system("wmic logicaldisk get name,size,freespace,description");
#else
    clearFile("system_report.txt");
    system("df -h >> system_report.txt");
#endif
}

/* ---------------- NETWORK INFO ---------------- */
void show_network_info()
{
#ifdef _WIN32
    system("ipconfig /all");
#else
    clearFile("system_report.txt");
    system("ip a >> system_report.txt");
#endif
}

/* ---------------- GPU INFO ---------------- */
void show_gpu_info()
{
#ifdef _WIN32
    system("wmic path win32_VideoController get name,AdapterRAM");
#else
    clearFile("system_report.txt");
    system("lspci | grep -i vga >> system_report.txt");
#endif
}

/* ---------------- SYSTEM UPTIME ---------------- */
void show_system_uptime()
{
#ifdef _WIN32
    system("net stats workstation | find \"Statistics since\"");
#else
    clearFile("system_report.txt");
    system("uptime >> system_report.txt");
#endif
}

/* ---------------- SAVE REPORT ---------------- */
void save_report_to_file()
{
#ifdef _WIN32
    system("systeminfo > system_report.txt");
#else
    clearFile("system_report.txt");
    system(
        "echo \"===== OS INFO =====\" > system_report.txt && "
        "uname -a >> system_report.txt && "
        "echo \"\n===== CPU INFO =====\" >> system_report.txt && "
        "lscpu >> system_report.txt && "
        "echo \"\n===== RAM INFO =====\" >> system_report.txt && "
        "free -h >> system_report.txt && "
        "echo \"\n===== STORAGE INFO =====\" >> system_report.txt && "
        "df -h >> system_report.txt");
#endif
    // printf("Report saved to system_report.txt\n");
}

/* ---------------- RUNNING PROCESSES ---------------- */
void show_running_processes()
{
#ifdef _WIN32
    system("tasklist");
#else
    system("ps aux >> system_report.txt");
#endif
}

/* ---------------- HANDLE MENU ---------------- */
// void handle_choice(int choice)
// {
//     switch (choice)
//     {
//     case 1: show_os_info(); break;
//     case 2: show_cpu_info(); break;
//     case 3: show_ram_info(); break;
//     case 4: show_storage_info(); break;
//     case 5: show_network_info(); break;
//     case 6: show_gpu_info(); break;
//     case 7: show_system_uptime(); break;
//     case 8: save_report_to_file(); break;
//     case 9: show_running_processes(); break;
//     case 0: printf("Exiting...\n"); break;
//     default: printf("Invalid choice!\n");
//     }
// }

/* ---------------- MAIN ---------------- */
// int main()
// {
//     int choice;

//     do
//     {
//         show_menu();
//         scanf("%d", &choice);
//         handle_choice(choice);
//     } while (choice != 0);

//     return 0;
// }
