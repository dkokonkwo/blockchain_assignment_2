#ifndef TODOLIST_H
#define TODOLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define STRING_MAX 1024

typedef enum
{
    PENDING,
    IN_PROGRESS,
    COMPLETED,
} Status;

/**
 * task_t - structure for a task
 * @task_id: integer uniquely identifies the task
 * @description: string containing task description
 * @status: enum presenting task status
 * @hash: task's hash
 * @next: pointer to next task in list
 */
typedef struct Task {
    int task_id;
    char description[STRING_MAX];
    Status status;
    uint8_t hash[SHA256_DIGEST_LENGTH];
    Task *next;
} Task;

/**
 * tlist_t - todo list structure
 * @head: pointer to first task in todo list
 * @tail: pointer to last task in todo list
 * @nb_tasks: number of tasks in todo list
 */
typedef struct tlist_s {
    Task *head;
    Task *tail;
    int nb_tasks;
} tlist_t;

tlist_t *create_todo_list(void);
Task *create_task(char description[STRING_MAX], int status);
int add_task(tlist_t *list, char description[STRING_MAX], int stats);
int update_task(tlist_t *list, int task_id, int status);
void printStatus(Status status);
void print_all_tasks(tlist_t *list);
int delete_task(tlist_t *list, int task_id);
void free_todolist(tlist_t *list);
int task_validity(Task *task);

#endif /* TODOLIST_H */