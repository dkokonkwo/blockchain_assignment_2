**QUESTION TWO:**

`HOW TO RUN:`
1. compile the main.c file using the command "gcc -o main main.c blockchain_functions.c -lssl -lcrypto"
2. Run the main executable file and follow the prompts to simulate the blockchain

Objective:

To understand and implement the basic mechanics of blockchain mining, including the proof-of-work algorithm, using the C programming language.

Requirements:

Access to a C development environment (such as GCC Compiler, Visual Studio Code with C extension, or any C IDE).
Basic to intermediate knowledge of C programming, particularly pointers, structures, dynamic memory management, and file handling.
Familiarity with cryptographic hashing, specifically SHA-256 (a library can be used for this purpose).
Assignment Tasks:

Task 1: Setting Up the Blockchain Environment

Objective: Implement a basic blockchain structure capable of supporting mining operations.
Instructions:
Define the Block structure in C to include index, timestamp, list of transactions (simplified to just strings or integers for this assignment), previous hash, and nonce.
Implement the SHA-256 hashing function or integrate an existing library to compute block hashes.
Task 2: Implementing Proof of Work (PoW)

Objective: Develop the proof-of-work mechanism to secure blockchain creation.
Instructions:
Implement a function to calculate the hash of a block that includes a changing nonce until the hash meets certain criteria (e.g., a hash beginning with a predefined number of zeroes).
This task will demonstrate how miners compete to find the nonce that results in a hash that meets the blockchain network’s difficulty level.
Task 3: Mining a Block

Objective: Simulate the mining process to add a new block to the blockchain.
Instructions:
Create a function that takes transactions and previous block’s hash as input, finds the correct nonce for the new block using the proof of work function, and adds the new block to the blockchain.
Verify the integrity of the blockchain after adding the new block to ensure that the PoW has been successfully implemented.
Task 4: Adjusting Blockchain Difficulty

Objective: Understand how changing the difficulty affects mining time and computational effort.
Instructions:
Implement functionality to adjust the difficulty of the PoW algorithm (number of leading zeros in the hash).
Simulate mining multiple blocks with different difficulties and record the time and computational resources required for each difficulty level.
Deliverables:

Complete C source code for each task.
A detailed report documenting:
The implementation process and a detailed description of each part of the code.
Output results showing the hash values and the nonce found for each mined block.
Challenges encountered and how they were resolved.
Analysis of how difficulty impacts mining effort and time.