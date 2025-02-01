#include "todolist.h"

/**
 * create_todo_list - initializes a new todo list
 * Return: pointer to new todo list on succes else NULL
 */
tlist_t *create_todo_list(void) {
    tlist_t *nlist = (tlist_t *)malloc(sizeof(tlist_t));
    if (!nlist) {
        printf("Failed to allocate memory for new list.\n");
        return (NULL);
    }
    nlist->head = NULL;
    nlist->tail = NULL;
    nlist->nb_tasks = 0;
    return (nlist);
}

/**
 * create_task - creates new task
 * @description: task description
 * @status: task status
 * Return: pointer to task on success else NULL
 */
Task *create_task(char description[STRING_MAX], int status) {
    Task *ntask;
    if (!description)
    {
        printf("No description or status given.\n");
        return (NULL);
    }
    ntask = (Task *)malloc(sizeof(Task));
    if (!ntask)
    {
        printf("Could not allocate memory for new task.\n");
        return (NULL);
    }
    ntask->next = NULL;
    strncpy(ntask->description, description, STRING_MAX - 1);
    ntask->description[STRING_MAX - 1] = '\0';
    ntask->status = int_to_status(status);
    calculate_hash(ntask, ntask->hash);
    return (ntask);
}

/**
 * int_to_status - converts integer to enum
 * @status: integer value to conver to enum
 * Return: enum Status
 */
Status int_to_status(int status) {
    switch (status) {
    case 0: return PENDING;
    case 1: return IN_PROGRESS;
    case 2: return COMPLETED;
    default: return PENDING;
    }
}

/**
 * add_task - adds task to todo list
 * @list: pointer to todo list
 * @description: task description
 * @stats: task status
 * Return 1 on success else 0 
 */
int add_task(tlist_t *list, char description[STRING_MAX], int stats) {
    Task *ntask;
    if (!list || !description) {
        printf("No list or description given.\n");
        return (0);
    }
    ntask = create_task(description, stats);
    if (!ntask) {
        printf("Could not create new task.\n");
        return (0);
    }
    
    if (!list->head) {
        list->head = ntask;
        list->tail = ntask;
    }
    else {
        list->tail->next = ntask;
        list->tail = ntask;
    }
    ntask->task_id = list->nb_tasks++;
    return (1);
}

/**
 * update_task - update task status if hash is valid
 * @list: pointer to list of tasks
 * @task_id: uniques index of the task
 * @status: status as an integer
 * Return: 1 on success else 0
 */
int update_task(tlist_t *list, int task_id, int status) {
    Task *ctask;
    if (!list || task_id >= list->nb_tasks || status > 2)
    {
        printf("Wrong input information.\n");
        return (0);
    }
    for (ctask = list->head; ctask && ctask->task_id != task_id; ctask = ctask->next)
        ;

    if (!ctask || !task_validity(ctask)) {
        printf("task integrity is compromised\n");
        return (0);
    }
    ctask->status = int_to_status(status);
    return (calculate_hash(ctask, ctask->hash));
}

void printStatus(Status status) {
    switch (status) {
        case PENDING:
            printf("PENDING\n\n");
            break;
        case IN_PROGRESS:
            printf("IN PROGRESS\n\n");
            break;
        case COMPLETED:
            printf("COMPLETED\n\n");
            break;
        default:
            printf("UNKNOWN STATUS\n\n");
    }
}

/**
 * print_all_tasks - prints all tasks in list
 * @list: pointer to todo list to print all tasks
 */
void print_all_tasks(tlist_t *list) {
    Task *ctask;
    if (!list || !list->head)
        return;
    for (ctask = list->head; ctask; ctask = ctask->next) {
        printf("ID: %d\nDescription: %s\nStatus: ", ctask->task_id, ctask->description);
        printStatus(ctask->status);
    }
}

/**
 * delete_task - deletes a task in a todo list
 * @list: pointer to todo list to delete task from
 * @task_id: task id to delete
 * Return: 1 on success else 0 on failure
 */
int delete_task(tlist_t *list, int task_id) {
    Task *ctask, *prev;
    int new_id;
    if (!list || !list->nb_tasks || task_id >= list->nb_tasks)
    {
        printf("Invalid task ID.\n");
        return (0);
    }
    ctask = list->head;
    if (task_id == 0)
    {
        list->head = ctask->next;
        if (!list->head)
            list->tail = NULL;
        free(ctask);
    }
    else {
        while (ctask && ctask->next != task_id) {
            prev = ctask;
            ctask = ctask->next;
        }
        if (!ctask) {
            printf("Task not found\n");
            return (0);
        }

        prev->next = ctask->next;
        if (ctask == list->tail)
            list->tail = prev;
        free(ctask);
    }
    new_id = 0;
    for (ctask = list->head; ctask; ctask = ctask->next) {
        ctask->task_id = new_id++;
        calculate_hash(ctask, ctask->hash);
    }
    list->nb_tasks--;
    return (1);
}

/**
 * free_todolist - frees todo list
 * @list: pointer to todo list to free
 */
void free_todolist(tlist_t *list) {
    Task *ctask, *tmp;
    if (!list)
        return;
    ctask = list->head;
    while (ctask)
    {
        tmp = ctask->next;
        free(ctask);
        ctask = tmp;
    }
    free(list);
}

/**
 * calculate_hash - calculates the hash of a task in a todo list
 * @task: pointer to task to calculate hash
 * @hash: buffer to store the computed hash
 * Return: 1 on success else 0
 */
int calculate_hash(Task *task, uint8_t hash[SHA256_DIGEST_LENGTH]) {
    if (!task)
        return (0);
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        printf("Failed to create EVP_MD_XTX\n");
        return (0);
    }
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1 ||
    EVP_DigestUpdate(ctx, &task->status, sizeof(task->status)) != 1 ||
    EVP_DigestUpdate(ctx, task->description, strlen(task->description)) != 1 ||
    EVP_DigestFinal(ctx, hash, NULL) != 1) {
        printf("Failed to calculate hash\n");
        EVP_MD_CTX_free(ctx);
        return (0);
    }

    EVP_MD_CTX_free(ctx);
    return (1);
}

/**
 * task_validity - ensures that task hash has not been tampered with
 * @task: pointer to check validity
 * Return: 1 in valid else 0
 */
int task_validity(Task *task) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    calculate_hash(task, hash);
    if (memcmp(task->hash, hash, SHA256_DIGEST_LENGTH) != 0) {
        printf("Current task not valid\n");
        return (0);
    }
    return (1);
}