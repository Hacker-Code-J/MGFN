#include "mgfn_config.h"

void stringToByte(u8* byteArray, const char* hexString);

void byteToHalfWord(u16* dst, const u8* src, const size_t halfWordLen);
void byteToWord(u32* dst, const u8* src, const size_t byteLen);

void wordToByte(u8* dst, const u32* src, const size_t wordLen);
void halfWordToByte(u8* dst, const u16* src, const size_t halfWordLen);

void printBitData(bool* data, size_t bitLen);
void printByteData(u8* data, size_t byteLen);
void printHalfWordData(u16* data, size_t halfWordLen);