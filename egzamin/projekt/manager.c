#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "manager.h"

void create_workers(int pipes[4][2], pid_t pids[4], char *names[4]) {
    for (int i = 0; i < 4; i++) {
        pipe(pipes[i]);
        pid_t pid = fork();
        if (pid == 0) {
            dup2(pipes[i][0], STDIN_FILENO);
            close(pipes[i][1]);
            execl("./projekt", "./projekt", names[i], NULL);
            perror("execl");
            exit(1);
        } else {
            pids[i] = pid;
            close(pipes[i][0]);
        }
    }
}

void send_command_to_all(int pipes[4][2], const char *cmd) {
    for (int i = 0; i < 4; i++) {
        write(pipes[i][1], cmd, strlen(cmd));
    }
}
