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
} block_t;

typedef struct Blockchain {
    block_t *head;
    block_t *tail;
    int length;
    int difficulty;
} Blockchain;

#endif /* BLOCKCHAIN.H */