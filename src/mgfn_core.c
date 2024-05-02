#include "mgfn.h"
#include "mgfn_utils.h"

void mgfn_encrypt(u8* ct, u8* pt, u8* m_key) {
    u16 state[4];
    byteToHalfWord(state, pt, 4);
    printHalfWordData(state, 4);
}

void mgfn_decrypt(u8* pt, u8* ct, u8* m_key) {
    // Decryption Logic
}