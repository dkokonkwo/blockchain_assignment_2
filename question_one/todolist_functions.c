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
    ntask->description[STRING_MAX - 1] = "\0";
    switch (status) {
        case 0:
            ntask->status = PENDING;
            break;
        case 1:
            ntask->status = IN_PROGRESS;
            break;
        case 2:
            ntask->status = COMPLETED;
            break;
        default:
            printf("Unknown\n");
            return (0);
    }
    return (ntask);
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
    int is_valid;
    Task *ctask;
    if (!list || task_id > list->nb_tasks - 1 || status > 2)
    {
        printf("Wrong input information.\n");
        return (0);
    }
    if (task_id == list->nb_tasks - 1) {
        ctask = list->tail;
    }
    else {
        for (ctask = list->head; ctask->task_id != list->nb_tasks; ctask = ctask->next) {
            ;
        }
    }
    is_valid = task_validity(ctask);
    if (!is_valid) {
        printf("task integrity is compromised\n");
        return (0);
    }
    
    switch (status) {
        case 0:
            ctask->status = PENDING;
            break;
        case 1:
            ctask->status = IN_PROGRESS;
            break;
        case 2:
            ctask->status = COMPLETED;
            break;
        default:
            printf("Unknown\n");
            return (0);
    }

    if (!calculate_hash(ctask, ctask->hash))
        return (0);

    return (1);
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
    Task *ctask, *tmp;
    int new_id;
    if (!list || list->nb_tasks || task_id > list->nb_tasks - 1)
    {
        printf("Invalid task id.\n");
        return (0);
    }
    if (task_id == 0) {
        ctask = list->head->next;
        free(list->head);
        list->head = ctask;
        new_id = 0;
    }
    else {
        for (ctask = list->head; ctask->next->task_id != task_id; ctask = ctask->next) {
            ;
        }
        tmp = ctask->next;
        ctask->next = tmp->next;
        new_id = tmp->task_id;
        free(tmp);
    }
    while (ctask) {
        ctask->task_id = new_id++;
        calculate_hash(ctask, ctask->hash);
        ctask = ctask->next;
    }
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
    while (ctask) {
        tmp = ctask->next;
        free(ctask);
        ctask = tmp;
    }
    free(list);
}
// calculate hash
// verify integrity, free task,

int task_validity(Task *task);

int calculate_hash(Task *task, uint8_t hash[SHA256_DIGEST_LENGTH]);