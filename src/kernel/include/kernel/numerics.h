//
// Created by mafn on 3/5/17.
//

#ifndef MAFN_KERNEL_NUMERICS_H
#define MAFN_KERNEL_NUMERICS_H

#include <stdint.h>

#define U16_HIGH(val) (uint8_t)(val >> 8)
#define U16_LOW(val) (uint8_t)val

#define KiB_SIZE (1 << 10)
#define MiB_SIZE (KiB_SIZE << 10)
#define GiB_SIZE (MiB_SIZE << 10)

#endif //MAFN_KERNEL_NUMERICS_H
