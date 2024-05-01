#include "mgfn.h"

/* 
 * MK Schedule Process
 * 128-bit MK -> u8 MK[16]
 * 
 * 
 * 
 * 
*/

void rotate_right(u8 MK[16]) {
    uint8_t temp[16]; // Temporary array to store the rotated MK

    // Number of byte shifts and bit shifts
    int byte_shift = 61 / 8; // 61 bits / 8 bits per byte = 7 bytes
    int bit_shift = 61 % 8;  // Remaining bits = 5 bits

    for (int i = 0; i < 16; ++i) {
        // Circular byte shift + handling bit shifts across byte boundaries
        temp[i] = (MK[(i + byte_shift) % 16] >> bit_shift) | 
                  (MK[(i + byte_shift + 1) % 16] << (8 - bit_shift));
    }

    memcpy(MK, temp, 16); // Copy the rotated bytes back to the original MK array
}