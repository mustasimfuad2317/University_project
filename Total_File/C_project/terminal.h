#include <unistd.h>
#include <stdlib.h>

void openTerminal() {
    if (fork() == 0) {
        setsid();
        execlp(
            "x-terminal-emulator",
            "x-terminal-emulator",
            "-e",
            "./Cmdshall",
            NULL
        );
        exit(1);
    }
}

// int main() {
//     openTerminalWithShell();
//     return 0;
// }
