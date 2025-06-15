#ifndef MANAGER_H
#define MANAGER_H

void create_workers(int pipes[4][2], pid_t pids[4], char *names[4]);
void send_command_to_all(int pipes[4][2], const char *cmd);

#endif
