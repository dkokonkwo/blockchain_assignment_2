**Question One**

`HOW TO RUN`
1. compile the main.c file using the command "gcc -o main main.c todolist_functions.c -lssl -lcrypto"
2. Run the main executable file and follow the prompts to simulate the blockchain todolist. ✅

**BACKGROUND**
Develop a to-do list application in C that simulates storing, retrieving, and managing tasks as if they were stored on the Ethereum blockchain. Implement functions to add, delete, update, and list tasks while ensuring the immutability and integrity of the data by using cryptographic hashing (e.g., SHA-256) to mimic how data is secured on the blockchain. Demonstrate how tasks are managed in a way that simulates interaction with a blockchain-based system.

Submission Requirements:
Programming Environment:

Use the C programming language.
Install necessary libraries for cryptographic functions, such as OpenSSL, for hashing tasks.
Data Structures:

1. Define a struct for a Task that includes:
- task_id: An integer that uniquely identifies the task.
- description: A string containing the task description.
- status: An enum or integer representing the task status ("Pending," "In Progress," "Completed").
- Use an array or a linked list to manage multiple Task structures.

2. Hashing for Data Integrity:

- Implement a hashing function using SHA-256 to create a hash for each task.
- Store each task's hash along with its data to simulate blockchain-like immutability.
- Implement a function to verify the integrity of tasks by comparing stored hashes with recalculated hashes whenever a task is retrieved or updated.

3.Task Management Functions:

- Add Task: Implement a function to add a new task, generate its hash, and store it in a list or array.
- Update Task Status: Implement a function to update the status of a task, recalculate its hash, and ensure the hash chain's integrity is maintained.
- Delete Task: Implement a function to delete a task and handle the adjustment of subsequent task hashes to simulate blockchain-like data consistency.
- List Tasks: Implement a function to display all tasks along with their status, description, and hashes.

4. Simulate Blockchain-Like Features:

- Implement a function to simulate the linking of tasks, where each task’s hash is influenced by the hash of the previous task, mimicking a simple blockchain structure.
- Provide feedback if any task's hash does not match its recalculated hash, indicating potential tampering.

5. User Interaction and Demonstration:

- Create a menu-driven interface in the C program where users can add, update, delete, and view tasks.
- Demonstrate the immutability feature by attempting to alter a task’s data directly and showing how the integrity check fails.

6. Error Handling:

- Ensure proper error handling for tasks that cannot be added, updated, or deleted due to integrity check failures.
- Provide clear error messages and handling for memory allocation failures and hash calculation issues.

7. Documentation and Comments:

- Include thorough comments in the code explaining each function and the logic behind it.
- Provide a README file with instructions for compiling and running the program and an explanation of the simulated blockchain-like features.
