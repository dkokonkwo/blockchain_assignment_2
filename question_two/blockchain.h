#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <openssl/sha.h>
#include <sys/types.h>
#include <unistd.h>

#define DATASIZE_MAX 1024
#define INITIAL_DIFFICULTY 2  /* Starting difficulty level */

typedef struct block_s {
    int index;
    uint64_t timestamp;
    char transactions[DATASIZE_MAX];
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char currHash[SHA256_DIGEST_LENGTH];
    struct block_s *next;
    int nonce;
} block_t;

typedef struct Blockchain {
    block_t *head;
    block_t *tail;
    int length;
    int difficulty;
} Blockchain;

/* BLOCKCHAIN FUNCTIONS */
void hash_to_hex(unsigned char *hash, char *output);
int is_valid_hash(unsigned char *hash, int difficulty);
void calculate_block_hash(block_t *block, unsigned int nonce, unsigned char *out_hash);
void mine_block(block_t *block, int difficulty);
block_t *create_block(int index, const char *transactions, unsigned char *prevHash, int difficulty);
void add_block(Blockchain *chain, block_t *block);
int validateBlockchain(Blockchain *blockchain);
int adjust_difficulty(uint64_t prevTime, uint64_t currentTime, int currentDifficulty);

#endif /* BLOCKCHAIN.H */