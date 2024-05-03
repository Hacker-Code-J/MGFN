#include "mgfn.h"
#include "mgfn_key.h"

/* 
 * MK Schedule Process
 * 128-bit MK -> u8 m_key[16]
 * 
 * 
 * 
 * 
*/

void mgfn_getRoundKey(u8* r_key, u8* m_key) {
    bool bit[128] = { 0, };

    for (u8 byteIndex = 0; byteIndex < 16; byteIndex++) {
        u8 bitIndex = byteIndex * 8;
        bit[bitIndex + 0] = (m_key[byteIndex] & 0x01) != 0;
        bit[bitIndex + 1] = (m_key[byteIndex] & 0x02) != 0;
        bit[bitIndex + 2] = (m_key[byteIndex] & 0x04) != 0;
        bit[bitIndex + 3] = (m_key[byteIndex] & 0x08) != 0;
        bit[bitIndex + 4] = (m_key[byteIndex] & 0x10) != 0;
        bit[bitIndex + 5] = (m_key[byteIndex] & 0x20) != 0;
        bit[bitIndex + 6] = (m_key[byteIndex] & 0x40) != 0;
        bit[bitIndex + 7] = (m_key[byteIndex] & 0x80) != 0;
    }

    // Perform a 61-bit rotation to the right
    bool temp[61];  
    u8 rotation = 61;

    // Save the last 61 bits that need to be moved to the front
    for (u8 i = 0; i < rotation; i++) {
        temp[i] = bit[61 - rotation + i];
    }

    // Shift the bits to the right
    for (i8 i = 60; i >= rotation; i--)
        bit[i] = bit[i - rotation];

    // Put the saved bits at the beginning
    for (u8 i = 0; i < rotation; i++)
        bit[i] = temp[i];

    // // Convert the first 64 bits back to bytes and store in r_key
    // for (u8 i = 0; i < 8; i++) {
    //     r_key[i] = 0;
    //     for (u8 j = 0; j < 8; j++) {
    //         if (bit[i * 8 + j]) r_key[i] |= (1 << j);
    //     }
    // }
    // 

    /*
     * 127 126 125 124 123 122 121 120 | (16 * 8 - (1 .. 8))
     * 119 118 117 116 115 114 113 112 | (15 * 8 - (1 .. 8))
     * ...
     * 071 070 069 068 067 066 065 064 | (08 * 8 - (1 .. 8))
     * 
     * RK[7] = 127 ... 120 | 7 - (120 .. 127) | (56 ... 63)
     * RK[6] = 119 ... 112 | 6 - (112 .. 119) | (48 ... 55)
     * ...
     * RK[2] = 087 ... 080 | 2 - (080 .. 087) | (16 ... 23)
     * RK[1] = 079 ... 072 | 1 - (072 .. 079) | (08 ... 15)
     * RK[0] = 071 ... 064 | 0 - (064 .. 071) | (00 ... 07)
    */

    for (i8 i = 7; i >= 0; i--) {
        r_key[i] = 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 8)] ? (1 << 0) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 7)] ? (1 << 1) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 6)] ? (1 << 2) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 5)] ? (1 << 3) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 4)] ? (1 << 4) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 3)] ? (1 << 5) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 2)] ? (1 << 6) : 0;
        r_key[i] |= bit[64 + ((i + 1) * 8 - 1)] ? (1 << 7) : 0;
    }
}
void mgfn_updateMasterKey(u8* m_key, u8 round_i) {
    bool bit[128] = { 0, };

    for (i8 byteIndex = 0; byteIndex < 16; byteIndex++) {
        u8 bitIndex = byteIndex * 8;
        bit[bitIndex + 0] = (m_key[byteIndex] & 0x01) != 0;
        bit[bitIndex + 1] = (m_key[byteIndex] & 0x02) != 0;
        bit[bitIndex + 2] = (m_key[byteIndex] & 0x04) != 0;
        bit[bitIndex + 3] = (m_key[byteIndex] & 0x08) != 0;
        bit[bitIndex + 4] = (m_key[byteIndex] & 0x10) != 0;
        bit[bitIndex + 5] = (m_key[byteIndex] & 0x20) != 0;
        bit[bitIndex + 6] = (m_key[byteIndex] & 0x40) != 0;
        bit[bitIndex + 7] = (m_key[byteIndex] & 0x80) != 0;
    }

    // printBitData(bit, 128);

    u8 sbox_input1 = (bit[127] << 3) ^
                     (bit[126] << 2) ^
                     (bit[125] << 1) ^
                     (bit[124] << 0);

    u8 sbox_input2 = (bit[123] << 3) ^
                     (bit[122] << 2) ^
                     (bit[121] << 1) ^
                     (bit[120] << 0);

    // printf("%x %x\n", sbox_input1, sbox_input2);

    u8 sbox_output1 = mgfn_sBox[sbox_input1];
    u8 sbox_output2 = mgfn_sBox[sbox_input2];

    // printf("%x %x\n", sbox_output1, sbox_output2);

    bit[127] = (sbox_output1 >> 3) & 1;
    bit[126] = (sbox_output1 >> 2) & 1;
    bit[125] = (sbox_output1 >> 1) & 1;
    bit[124] = (sbox_output1 >> 0) & 1;
    bit[123] = (sbox_output2 >> 3) & 1;
    bit[122] = (sbox_output2 >> 2) & 1;
    bit[121] = (sbox_output2 >> 1) & 1;
    bit[120] = (sbox_output2 >> 0) & 1;
    
    u8 rcon_data = (bit[66] << 4) ^
                   (bit[65] << 3) ^
                   (bit[64] << 2) ^
                   (bit[63] << 1) ^
                   (bit[62] << 0);

    rcon_data ^= round_i;

    bit[66] = (rcon_data >> 4) & 1;
    bit[65] = (rcon_data >> 3) & 1;
    bit[64] = (rcon_data >> 2) & 1;
    bit[63] = (rcon_data >> 1) & 1;
    bit[62] = (rcon_data >> 0) & 1;

    for (u8 i = 0; i < 16; i++) {
        m_key[i] = 0;
        m_key[i] |= bit[i * 8 + 0] ? (1 << 0) : 0;
        m_key[i] |= bit[i * 8 + 1] ? (1 << 1) : 0;
        m_key[i] |= bit[i * 8 + 2] ? (1 << 2) : 0;
        m_key[i] |= bit[i * 8 + 3] ? (1 << 3) : 0;
        m_key[i] |= bit[i * 8 + 4] ? (1 << 4) : 0;
        m_key[i] |= bit[i * 8 + 5] ? (1 << 5) : 0;
        m_key[i] |= bit[i * 8 + 6] ? (1 << 6) : 0;
        m_key[i] |= bit[i * 8 + 7] ? (1 << 7) : 0;
    }
}