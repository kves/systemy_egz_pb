#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "manager.h"
#include "worker.h"
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        handle_worker(argv[1]);
        return 0;
    }

    char *names[4] = {"Alice", "Bob", "Eve", "Tom"};
    int pipes[4][2];
    pid_t pids[4];

    create_workers(pipes, pids, names);

    sleep(1);
    send_command_to_all(pipes, "Podaj imię\n");

    sleep(1);
    send_command_to_all(pipes, "PID?\n");

    sleep(1);
    for (int i = 0; i < 4; i++) {
        kill(pids[i], SIGUSR1);
    }

    sleep(1);
    for (int i = 0; i < 4; i++) {
        kill(pids[i], SIGHUP);
    }

    sleep(1);
    for (int i = 0; i < 4; i++) {
        kill(pids[i], SIGINT);
    }

    return 0;
}
