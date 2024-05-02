#include "mgfn.h"

/* 
 * MK Schedule Process
 * 128-bit MK -> u8 MK[16]
 * 
 * 
 * 
 * 
*/

void rotate_right_128(u8* key, u8 bits) {
    u8 temp[KEY_SIZE];
    int byte_shift = bits / 8;
    int bit_shift = bits % 8;

    for (int i = 0; i < KEY_SIZE; ++i) {
        int source_index = (i + byte_shift) % KEY_SIZE;
        int source_next_index = (source_index + 1) % KEY_SIZE;
        temp[i] = (key[source_index] >> bit_shift) | (key[source_next_index] << (8 - bit_shift));
    }
    memcpy(key, temp, KEY_SIZE);
}

void key_schedule(u8* master_key, u8 round_keys[NUM_ROUNDS][ROUND_KEY_SIZE]) {
    u8 key[KEY_SIZE];
    memcpy(key, master_key, KEY_SIZE);

    for (int i = 0; i < NUM_ROUNDS; ++i) {
        memcpy(round_keys[i], key, ROUND_KEY_SIZE);  // Copy the first 8 bytes for the round key
        rotate_right_128(key, 61);  // Rotate the whole 128-bit key 61 bits to the right
    }
}


void encrypt(u8* plaintext, u8* ciphertext, u8 round_keys[NUM_ROUNDS][ROUND_KEY_SIZE]) {
    u8 state[BLOCK_SIZE];
    memcpy(state, plaintext, BLOCK_SIZE);

    for (int i = 0; i < NUM_ROUNDS; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            state[j] ^= round_keys[i][j % ROUND_KEY_SIZE];  // XOR state with round key
        }
        // Additional round operations (e.g., substitutions, permutations) go here
    }

    memcpy(ciphertext, state, BLOCK_SIZE);
}

void decrypt(u8* ciphertext, u8* plaintext, u8 round_keys[NUM_ROUNDS][ROUND_KEY_SIZE]) {
    u8 state[BLOCK_SIZE];
    memcpy(state, ciphertext, BLOCK_SIZE);

    for (int i = NUM_ROUNDS - 1; i >= 0; --i) {
        // Reverse round operations before applying the round key
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            state[j] ^= round_keys[i][j % ROUND_KEY_SIZE];  // XOR state with round key
        }
    }

    memcpy(plaintext, state, BLOCK_SIZE);
}


// void rotate_right(u8 MK[16]) {
    
// }

// void key_expansion(u8* MK, u8* RK) {
//     // Key expansion logic here
// }

// void round_function(blk* block, u8* RK) {
//     // Apply S-box, P-box, and round key mixing
// }

// void encrypt(blk* PT, blk* CT, u8* RK) {
//     // Encryption logic
// }

// void decrypt(blk* CT, blk* PT, u8* RK) {
//     // Decryption logic
// }