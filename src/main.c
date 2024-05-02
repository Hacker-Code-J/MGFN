#include "mgfn.h"

int main(void) {
    // printf("TEST\n");
    // u8 MK[16] = {
    //     0x2a, 0x21, 0xc1, 0x41, 0x91, 0xef, 0xf1, 0x01,
    //     0x0b, 0xff, 0x1c, 0x22, 0xab, 0xcd, 0x1f, 0x11
    // };
    // for (u8 i = 0; i < 16; i++)
    //     printf("%02x", MK[i]);

    // rotate_right(MK);
    // printf("\n=======================================\n");
    // for (u8 i = 0; i < 16; i++)
    //     printf("%02x", MK[i]);
    // puts("");

    // return 0;

    uint8_t master_key[KEY_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    uint8_t plaintext[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    uint8_t ciphertext[BLOCK_SIZE];
    uint8_t decrypted[BLOCK_SIZE];
    uint8_t round_keys[NUM_ROUNDS][ROUND_KEY_SIZE];

    key_schedule(master_key, round_keys);
    encrypt(plaintext, ciphertext, round_keys);
    decrypt(ciphertext, decrypted, round_keys);


    printf("\nKey:        ");
    for (int i = 0; i < KEY_SIZE; i++) printf("%02x:", master_key[i]);
    puts("");
    printf("\nPlaintext:  ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02x:", plaintext[i]);
    printf("\nCiphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02x:", ciphertext[i]);
    printf("\nDecrypted:  ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02x:", decrypted[i]);
    printf("\n");

    return 0;
}