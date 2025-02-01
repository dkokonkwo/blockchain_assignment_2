#include "blockchain.h"

/**
 * main - creates a blockchain network and simulates block mining and PoW
 * Return: 0
 */
int main() {
    Blockchain blockchain = {NULL, NULL, 0, INITIAL_DIFFICULTY};
    unsigned char prevHash[SHA256_DIGEST_LENGTH] = {0};
    
    printf("\n--- Creating Genesis Block ---\n");
    block_t *genesisBlock = create_block(0, "Genesis Block", NULL, blockchain.difficulty);
    add_block(&blockchain, genesisBlock);
    memcpy(prevHash, genesisBlock->currHash, SHA256_DIGEST_LENGTH);

    for (int i = 1; i <= 2; i++) {
        printf("\n--- Mining Block %d ---\n", i);
        uint64_t startTime = (uint64_t)time(NULL);
        
        char transactionData[DATASIZE_MAX];
        snprintf(transactionData, sizeof(transactionData), "Transaction Data for Block %d", i);

        block_t *newBlock = create_block(i, transactionData, prevHash, blockchain.difficulty);
        uint64_t endTime = (uint64_t)time(NULL);
        
        add_block(&blockchain, newBlock);
        memcpy(prevHash, newBlock->currHash, SHA256_DIGEST_LENGTH);

        blockchain.difficulty = adjust_difficulty(startTime, endTime, blockchain.difficulty);
        printf("New Difficulty Level: %d\n", blockchain.difficulty);
    }

    printf("\n--- Verifying Blockchain Integrity ---\n");
    if (validateBlockchain(&blockchain)) {
        printf("Blockchain is valid.\n");
    }
    else {
        printf("Blockchain is invalid.\n");
    }

    return 0;
}