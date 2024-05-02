#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sys/resource.h>
#include <inttypes.h>
#include <ctype.h>
#include <unistd.h>
#include <x86intrin.h>

#ifndef _MGFN_CONFIG_H
#define _MGFN_CONFIG_H

#define NUM_ROUNDS 24
#define BLOCK_SIZE 64                   // Block size in bits
#define KEY_SIZE 128                    // Key size in bits
#define SUBKEY_SIZE 64                  // Subkey size in bits
#define NUM_SUBKEYS (NUM_ROUNDS + 2)    // Number of subkeys needed

typedef int8_t      i8;
typedef int32_t     i32;
typedef int64_t     i64;

typedef uint8_t     u8;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef uint16_t    blk[4];

#endif /* _MGFN_CONFIG_H */