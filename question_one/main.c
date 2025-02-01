#include "todolist.h"

/**
 * tamper_task - changes a task description maliciously
 * @task: pointer to task to tamper with
 */
void tamper_task(Task *task) {
    if (!task) return;
    printf("\nTampering with task ID %d...\n", task->task_id);
    strncpy(task->description, "Hacked Task!", STRING_MAX - 1);
    task->description[STRING_MAX - 1] = '\0';
}

/**
 * main - entry for CLI for users
 * Return: 0
 */
int main() {
    tlist_t *todo_list = create_todo_list();
    int choice, task_id, status;
    char description[STRING_MAX];

    while (1) {
        printf("\nTODO LIST MENU:\n");
        printf("1. Add Task\n");
        printf("2. Update Task\n");
        printf("3. Delete Task\n");
        printf("4. View All Tasks\n");
        printf("5. Tamper with a Task (Integrity Test)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, STRING_MAX, stdin);
                description[strcspn(description, "\n")] = '\0'; // Remove newline
                printf("Enter status (0: Pending, 1: In Progress, 2: Completed): ");
                scanf("%d", &status);
                add_task(todo_list, description, status);
                break;

            case 2:
                printf("Enter task ID to update: ");
                scanf("%d", &task_id);
                printf("Enter new status (0: Pending, 1: In Progress, 2: Completed): ");
                scanf("%d", &status);
                if (!update_task(todo_list, task_id, status)) {
                    printf("Task update failed due to integrity issues!\n");
                }
                break;

            case 3:
                printf("Enter task ID to delete: ");
                scanf("%d", &task_id);
                if (!delete_task(todo_list, task_id)) {
                    printf("Failed to delete task.\n");
                }
                break;

            case 4:
                printf("\nAll Tasks:\n");
                print_all_tasks(todo_list);
                break;

            case 5:
                printf("Enter task ID to tamper with: ");
                scanf("%d", &task_id);
                Task *task = todo_list->head;
                while (task && task->task_id != task_id) {
                    task = task->next;
                }
                if (task) {
                    tamper_task(task);
                    if (!task_validity(task)) {
                        printf("Task integrity compromised! Modification detected.\n");
                    } else {
                        printf("Task integrity not compromised (unexpected).\n");
                    }
                } else {
                    printf("Task ID not found.\n");
                }
                break;

            case 6:
                free_todolist(todo_list);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
