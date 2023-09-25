
//==============================================================================
//
//     crc.cpp
//
//============================================================================
//  Copyright (C) Guilaume Plante 2020 <guillaumeplante.qc@gmail.com>
//==============================================================================

#include "stdafx.h"
#include "crc.h"


uint16_t straight_16(uint16_t value) {
    return value;
}

uint16_t reverse_16(uint16_t value) {
    uint16_t reversed = 0;
    int i;
    for (i = 0; i < 16; ++i) {
        reversed <<= 1;
        reversed |= value & 0x1;
        value >>= 1;
    }
    return reversed;
}

uint8_t straight_8(uint8_t value) {
    return value;
}

uint8_t reverse_8(uint8_t value) {
    uint8_t reversed = 0;
    int i;
    for (i = 0; i < 8; ++i) {
        reversed <<= 1;
        reversed |= value & 0x1;
        value >>= 1;
    }
    return reversed;
}

uint16_t crc16common(uint8_t const *message, int nBytes,
        bit_order_8 data_order, bit_order_16 remainder_order,
        uint16_t remainder, uint16_t polynomial) {
	int byte;
	uint8_t bit;
    for (byte = 0; byte < nBytes; ++byte) {
        remainder ^= (data_order(message[byte]) << 8);
        for (bit = 8; bit > 0; --bit) {
            if (remainder & 0x8000) {
                remainder = (remainder << 1) ^ polynomial;
            } else {
                remainder = (remainder << 1);
            }
        }
    }
    return remainder_order(remainder);
}



uint16_t crc16x25(uint8_t const *message, int nBytes) {
    uint16_t swap = crc16common(message, nBytes, reverse_8, reverse_16, 0x0FFFF, 0x1021);
//    return ~((swap >> 8) | ((swap & 0xFF) << 8));
    return ~(swap);
}


uint16_t crc16(const uint8_t *data, uint16_t size)
{
    uint16_t out = 0;

    /* Sanity check: */
    if(data == 0)    return 0;

    out = crc16x25(data, size);


    return out;
}
