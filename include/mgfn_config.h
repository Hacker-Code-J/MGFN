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

#define BLOCK_SIZE 8    // Block size in bytes
#define KEY_SIZE 16     // Key size in bytes
#define NUM_ROUNDS 24   // Number of rounds
#define ROUND_KEY_SIZE 8 // Round key size in bytes

typedef int8_t      i8;
typedef int32_t     i32;
typedef int64_t     i64;

typedef uint8_t     u8;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef uint16_t    blk[4];

#endif /* _MGFN_CONFIG_H */