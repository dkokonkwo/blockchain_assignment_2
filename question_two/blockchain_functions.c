#include "blockchain.h"

/**
 * hash_to_hex - converts binary hash to hex string
 * @hash: pointer to hash
 * @output: pointer to buffer to store converted data
 * Return: Nothing
 */
void hash_to_hex(unsigned char *hash, char *output) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH * 2] = '\0';
}

/**
 * is_valid_hash - checks to see that diffculty requisite is met for the hash
 * @hash: pointer to hash to check validity
 * @difficulty: PoW difficulty level
 * Return: 1 if valid else 0
 */
int is_valid_hash(unsigned char *hash, int difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != 0)
            return 0;
    }
    return 1;
}

/**
 * calculate_block_hash - calculates the hash of a block
 * @block: pointer to block to calculate the hash
 * @nonce: number used once
 * @out_hash: buffer to store calculated hash
 * Return: Nothing
 */
void calculate_block_hash(block_t *block, unsigned int nonce, unsigned char *out_hash) {
    char input[DATASIZE_MAX * 2 + 128];
    snprintf(input, sizeof(input), "%d%lu%s%s%u",
             block->index, block->timestamp,
             block->transactions, block->prevHash, nonce);

    SHA256((unsigned char *)input, strlen(input), out_hash);
}

/**
 * mine_block - mines a block in a blockchain
 * @block: pointer to block to mine
 * @difficulty: PoW difficulty level
 * Return: Nothing
 */
void mine_block(block_t *block, int difficulty) {
    unsigned int nonce = 0;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Mining block %d at difficulty %d...\n", block->index, difficulty);

    do {
        calculate_block_hash(block, nonce, hash);
        nonce++;
    } while (!is_valid_hash(hash, difficulty));

    memcpy(block->currHash, hash, SHA256_DIGEST_LENGTH);

    printf("Block %d mined with nonce: %u\n", block->index, nonce - 1);
}

/**
 * create_block - creates a new block for a blockchain
 * @index: index of the block
 * @transactions: transactions to store in the new block
 * @preHash: hash of the preious block
 * @difficulty: PoW difficulty level
 * Return: pointer to created block else NULL
 */
block_t *create_block(int index, char transactions[DATASIZE_MAX], unsigned char *prevHash, int difficulty) {
    block_t *block = malloc(sizeof(block_t));
    if (!block) {
        printf("Failed to allocate memory for block/\n");
        return NULL;
    }

    block->index = index;
    block->timestamp = (uint64_t)time(NULL);
    memcpy(block->transactions, transactions, DATASIZE_MAX - 1);
    block->transactions[DATASIZE_MAX - 1] = '\0';
    if (prevHash)
        memcpy(block->prevHash, prevHash, SHA256_DIGEST_LENGTH);
    else
        memset(block->prevHash, 0, SHA256_DIGEST_LENGTH);  // Genesis block creation
    memset(block->currHash, 0, SHA256_DIGEST_LENGTH);
    block->next = NULL;

    mine_block(block, difficulty);
    return block;
}

/**
 * add_block - adds a new block to blockchain
 * @chain: pointer to blockchain
 * @block: pointer to new block to blockchain
 * Return: Nothing
 */
void add_block(Blockchain *chain, block_t *block) {
    if (!chain->head) {
        chain->head = chain->tail = block;
    } else {
        chain->tail->next = block;
        chain->tail = block;
    }
    chain->length++;
}


/**
 * validateBlockchain - ensures that previous block's hash matches with new block's hash
 * @blockchain: pointer to blockchain to validate
 * Return: 1 if valid, or 0 if invalid
 */
int validateBlockchain(Blockchain *blockchain) {
    if (!blockchain || !blockchain->head)
        return 0;
    unsigned char tmpHash[SHA256_DIGEST_LENGTH] = {0};
    unsigned char calculatedHash[SHA256_DIGEST_LENGTH];
    block_t *current = blockchain->head;

    while (current)
    {
        calculateHash(current, calculatedHash);
        if (memcmp(current->currHash, calculatedHash, SHA256_DIGEST_LENGTH) != 0 || memcmp(current->prevHash, tmpHash, SHA256_DIGEST_LENGTH) != 0) {
            return 0;
        }    
        memcpy(tmpHash, current->currHash, SHA256_DIGEST_LENGTH);
        current = current->next;
    }
    return 1;
}

/**
 * adjust_difficulty - adjusts mining difficulty based on block time
 * @prevTime: timestamp of previous block
 * @currentTime: timestamp of current block
 * @currentDifficulty: current difficulty level
 * Return: new difficulty level
 */
int adjust_difficulty(uint64_t prevTime, uint64_t currentTime, int currentDifficulty) {
    double timeDiff = difftime(currentTime, prevTime);
    if (timeDiff < 5) {
        return currentDifficulty + 1;  // Increase difficulty
    } else if (timeDiff > 20 && currentDifficulty > 1) {
        return currentDifficulty - 1;  // Decrease difficulty
    }
    return currentDifficulty;
}
