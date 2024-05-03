#include "mgfn.h"
#include "mgfn_key.h"
#include "mgfn_utils.h"

void mgfn_encrypt(u8* ct, u8* pt, u8* m_key) {
    u8 byte_state[8];
    u16 blk_state[4];
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
    
    printf("RK(01) | ");
    printByteData(r_temp, 8);

    printf("\n=================================\n");
    printf("PT     | ");
    printByteData(byte_state, 8);

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

    byteToHalfWord(blk_state, byte_state, 4);

    printf("WT(16) | ");
    printHalfWordData(blk_state, 4);

    // Main Round
    for (u8 i = 0; i < 1; i++) {
        u16 blk_r_temp[4] = { 0, };
        printf("\n=========Round(%02d-%02d)===========\n", i+1, i+2);
        mgfn_getRoundKey(r_temp, m_temp);
        byteToHalfWord(blk_r_temp, r_temp, 4);
        printf("RK(%02d) | ", i+1);
        printByteData(r_temp, 8);
        printf("RK(%02d) | ", i+1);
        printHalfWordData(blk_r_temp, 4);

        printHalfWordData(blk_state, 4);
        printf("\n< addKey Layer >\n");
        // addKey Layer
        blk_state[3] ^= blk_r_temp[3];
        blk_state[2] ^= blk_r_temp[2];
        printHalfWordData(blk_state, 4);

        printf("\n< RShift Layer >\n");
        // RShift Layer
        halfWordToByte(byte_state, blk_state, 4);
        printByteData(byte_state, 8);

        byte_state[0] = ROTR(byte_state[0], 3);
        byte_state[1] = ROTR(byte_state[1], 3);
        byte_state[2] = ROTR(byte_state[2], 3);
        byte_state[3] = ROTR(byte_state[3], 3);
        byte_state[4] = ROTR(byte_state[4], 3);
        byte_state[5] = ROTR(byte_state[5], 3);
        byte_state[6] = ROTR(byte_state[6], 3);
        byte_state[7] = ROTR(byte_state[7], 3);
        printByteData(byte_state, 8);

        printf("\n< sBox Layer >\n");
        // sBox Layer
        printByteData(byte_state, 8);
        byte_state[0] = (mgfn_sBox[(byte_state[0] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[0] >> 0x04) & 0xF] << 4);
        byte_state[1] = (mgfn_sBox[(byte_state[1] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[1] >> 0x04) & 0xF] << 4);
        byte_state[2] = (mgfn_sBox[(byte_state[2] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[2] >> 0x04) & 0xF] << 4);
        byte_state[3] = (mgfn_sBox[(byte_state[3] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[3] >> 0x04) & 0xF] << 4);
        byte_state[4] = (mgfn_sBox[(byte_state[4] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[4] >> 0x04) & 0xF] << 4);
        byte_state[5] = (mgfn_sBox[(byte_state[5] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[5] >> 0x04) & 0xF] << 4);
        byte_state[6] = (mgfn_sBox[(byte_state[6] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[6] >> 0x04) & 0xF] << 4);
        byte_state[7] = (mgfn_sBox[(byte_state[7] >> 0x00) & 0xF]) |
                        (mgfn_sBox[(byte_state[7] >> 0x04) & 0xF] << 4);

        printByteData(byte_state, 8);

        printf("\n< pBox Layer >\n");
        // pBox Layer
        printByteData(byte_state, 8);
        bool permBit[128] = { 0, };

        for (i8 byteIndex = 0; byteIndex < 8; byteIndex++) {
            u8 bitIndex = byteIndex * 8;
            permBit[bitIndex + 0] = (byte_state[byteIndex] & 0x01) != 0;
            permBit[bitIndex + 1] = (byte_state[byteIndex] & 0x02) != 0;
            permBit[bitIndex + 2] = (byte_state[byteIndex] & 0x04) != 0;
            permBit[bitIndex + 3] = (byte_state[byteIndex] & 0x08) != 0;
            permBit[bitIndex + 4] = (byte_state[byteIndex] & 0x10) != 0;
            permBit[bitIndex + 5] = (byte_state[byteIndex] & 0x20) != 0;
            permBit[bitIndex + 6] = (byte_state[byteIndex] & 0x40) != 0;
            permBit[bitIndex + 7] = (byte_state[byteIndex] & 0x80) != 0;
        }
        printBitData(permBit, 128);
        for (i = 0; i < 32; i++)
            permBit[mgfn_pBox[i]] = permBit[i];
        
        printBitData(permBit, 128);
    }

}

void mgfn_decrypt(u8* pt, u8* ct, u8* m_key) {
    // Decryption Logic
}