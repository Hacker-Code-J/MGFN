#include "mgfn.h"
#include "mgfn_key.h"
#include "mgfn_utils.h"

void mgfn_encrypt(u8* ct, u8* pt, u8* m_key) {
    u8 byte_state[8];
    u16 half_word_state[4];
    memcpy(byte_state, pt, 8);

    u8 m_temp[16];
    u8 r_temp[8];
    memcpy(m_temp, m_key, 16);


    printf("Key(0) | ");
    printByteData(m_temp, 16);

    mgfn_getRoundKey(r_temp, m_temp);
    mgfn_updateMasterKey(m_temp, 1);

    printf("Key(1) | ");
    printByteData(m_temp, 16);

    printf("PT     | ");
    printByteData(byte_state, 8);
    printf("RK(01) | ");
    printByteData(r_temp, 8);

    // Pre-whitening
    byte_state[0] ^= r_temp[0];
    byte_state[1] ^= r_temp[1];
    byte_state[2] ^= r_temp[2];
    byte_state[3] ^= r_temp[3];
    byte_state[4] ^= r_temp[4];
    byte_state[5] ^= r_temp[5];
    byte_state[6] ^= r_temp[6];
    byte_state[7] ^= r_temp[7];

    printf("WT(08) | ");
    printByteData(byte_state, 8);

    byteToHalfWord(half_word_state, byte_state, 4);

    printf("WT(16) | ");
    printHalfWordData(half_word_state, 4);

    // Main Round
    for (u8 i = 0; i < 1; i++) {
        printf("\n================================\n");
        mgfn_getRoundKey(r_temp, m_temp);
        printf("RK(%d) | ", i+1);
        printByteData(r_temp, 8);
    }

    // u16 state[4];
    // byteToHalfWord(state, pt, 4);
    // printHalfWordData(state, 4);
}

void mgfn_decrypt(u8* pt, u8* ct, u8* m_key) {
    // Decryption Logic
}