#include "mgfn.h"

int main(void) {
    printf("TEST\n");
    u8 MK[16] = {
        0x2a, 0x21, 0xc1, 0x41, 0x91, 0xef, 0xf1, 0x01,
        0x0b, 0xff, 0x1c, 0x22, 0xab, 0xcd, 0x1f, 0x11
    };
    for (u8 i = 0; i < 16; i++)
        printf("%02x", MK[i]);

    rotate_right(MK);
    printf("\n=======================================\n");
    for (u8 i = 0; i < 16; i++)
        printf("%02x", MK[i]);
    puts("");

    return 0;
}