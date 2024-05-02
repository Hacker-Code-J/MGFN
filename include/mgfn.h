#include "mgfn_config.h"

#ifndef _MGFN_H
#define _MGFN_H

static const u8 mgfn_sBox[16] = {
	0x7U, 0xEU, 0xFU, 0x0U, 0xDU, 0xBU, 0x8U, 0x1U,
	0x9U, 0x3U, 0x4U, 0xCU, 0x2U, 0x5U, 0xAU, 0x6U
};

static const u8 mgfn_permBit[32] = {
	0x04U, 0x0BU, 0x12U, 0x07U, 0x17U, 0x13U, 0x02U, 0x19U, 
	0x0EU, 0x1AU, 0x01U, 0x1CU, 0x14U, 0x08U, 0x1DU, 0x00U, 
	0x1FU, 0x05U, 0x0FU, 0x15U, 0x09U, 0x0DU, 0x18U, 0x06U, 
	0x11U, 0x0CU, 0x16U, 0x03U, 0x10U, 0x1EU, 0x0AU, 0x1BU
};

static inline u8 ROTL(u8 byte, u8 shift) {
    return (byte << shift) | (byte >> (8 - shift));
}

static inline u8 ROTR(u8 byte, u8 shift) {
    return (byte >> shift) | (byte << (8 - shift));
}

void mgfn_encrypt(u8* ct, u8* pt, u8* m_key);
void mgfn_decrypt(u8* pt, u8* ct, u8* m_key);

#endif /* _MGFN_H */