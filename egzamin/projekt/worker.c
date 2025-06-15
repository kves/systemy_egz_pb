#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "worker.h"

static const char *worker_name = "";

void handle_signal(int sig) {
    if (sig == SIGHUP) {
        printf("%s: Odpoczywam\n", worker_name);
    } else if (sig == SIGUSR1) {
        printf("%s: Startuję!\n", worker_name);
    } else if (sig == SIGINT) {
        printf("%s: Kończę\n", worker_name);
        exit(0);
    }
    fflush(stdout);
}

void handle_worker(const char *name) {
    worker_name = name;
    printf("%s: Gotowy do pracy\n", name);

    signal(SIGHUP, handle_signal);
    signal(SIGUSR1, handle_signal);
    signal(SIGINT, handle_signal);

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strncmp(buffer, "Podaj imię", 10) == 0) {
            printf("My name is %s\n", name);
        } else if (strncmp(buffer, "PID?", 4) == 0) {
            printf("%s: My PID is %d\n", name, getpid());
        }
        fflush(stdout);
    }
}
