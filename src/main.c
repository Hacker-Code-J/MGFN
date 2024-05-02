#include "mgfn.h"
#include "mgfn_key.h"
#include "mgfn_utils.h"

int main(void) {
    u8 m_key[KEY_SIZE] = {
        0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87,
        0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F
    };
    printByteData(m_key, KEY_SIZE);

    u8 r_keys[BLOCK_SIZE];
    mgfn_getRoundKey(r_keys, m_key);
    printByteData(r_keys, BLOCK_SIZE);

    u8 pt[BLOCK_SIZE] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
    };
    
    u8 ct[BLOCK_SIZE];
    // u8 dt[BLOCK_SIZE];

    mgfn_encrypt(ct, pt, m_key);


    printf("\nKey:        "); printByteData(m_key, 16);
    mgfn_updateMasterKey(m_key, 1);
    printf("\nKey:        "); printByteData(m_key, 16);


    // printf("\nPlaintext:  "); printByteData(pt, 8);
    // printf("\nCiphertext: "); printByteData(ct, 8);
    // printf("\nDecrypted:  "); printByteData(dt, 8);

    return 0;
}