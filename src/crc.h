
//==============================================================================
//
//     crc.cpp
//
//============================================================================
//  Copyright (C) Guilaume Plante 2020 <guillaumeplante.qc@gmail.com>
//==============================================================================


#ifndef INC_CRC_H_
#define INC_CRC_H_

#include <stdlib.h>

#define	CRC16X25



typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;


typedef uint16_t bit_order_16(uint16_t value);
typedef uint8_t bit_order_8(uint8_t value);

uint16_t crc16(const uint8_t *data, uint16_t size);


#endif /* INC_CRC_H_ */