#include "mgfn.h"
#include "mgfn_key.h"
#include "mgfn_utils.h"

void mgfn_encrypt(u8* ct, u8* pt, u8* m_key) {
    u8 byte_state[8];
    u16 half_word_state[4];
    memcpy(byte_state, pt, 8);
    byteToHalfWord(half_word_state, byte_state, 4);

    u8 m_temp[16];
    u8 r_temp[8];
    memcpy(m_temp, m_key, 16);

    mgfn_getRoundKey(r_temp, m_temp);

    // Pre-whitening



    printf("PT | ");
    printByteData(byte_state, 8);
    printHalfWordData(half_word_state, 4);

    for (u8 i = 0; i < 24; i++) {
        //
    }

    // u16 state[4];
    // byteToHalfWord(state, pt, 4);
    // printHalfWordData(state, 4);
}

void mgfn_decrypt(u8* pt, u8* ct, u8* m_key) {
    // Decryption Logic
}