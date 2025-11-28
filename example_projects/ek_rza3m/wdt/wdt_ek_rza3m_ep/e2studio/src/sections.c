/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bsp_api.h"

/* List of the section of variables with initial value */
typedef struct
{
    void * rom_s;                      /* Top address on ROM    */
    void * rom_e;                      /* Bottom address on ROM */
    void * ram_s;                      /* Top address on RAM    */
} dtbl_t;

/* List of the section of variables with zero clear */
typedef struct
{
    void * b_s;                        /* Top address    */
    void * b_e;                        /* Bottom address */
} btbl_t;

extern uint16_t __bss_start;
extern uint16_t __bss_end;

extern uint16_t __bss2_start;
extern uint16_t __bss2_end;

extern uint16_t __uncached_RAM_start;
extern uint16_t __uncached_RAM_end;

#if !defined(BSP_SRAM_LOAD)
extern uint16_t __sram_load_start;
extern uint16_t __sram_load_end;
extern uint16_t __sram_exec_start;
#endif

#if defined(BSP_XIP_LOAD)
extern uint16_t __data_load_start;
extern uint16_t __data_load_end;
extern uint16_t __data_exec_start;
#endif

extern uint16_t __sram_fastcopy_load_start;
extern uint16_t __sram_fastcopy_load_end;
extern uint16_t __sram_fastcopy_exec_start;

const dtbl_t DTBL[] =
{
/*  {  rom start address,     rom end address,     ram start address    },*/
#if !defined(BSP_SRAM_LOAD)
    {&__sram_load_start, &__sram_load_end, &__sram_exec_start},
#endif
#if defined(BSP_XIP_LOAD)
    {&__data_load_start, &__data_load_end, &__data_exec_start},
#endif
    {0,                  0,                0                 }, /* terminator */
};

const btbl_t BTBL[] =
{
/*  {  bss start address,    bss end address     },*/
    {&__bss_start,          &__bss_end         },
    {&__bss2_start,         &__bss2_end        },
#if !defined(BSP_SRAM_LOAD)
    {&__uncached_RAM_start, &__uncached_RAM_end},
#endif
    {0,                     0                  }, /* terminator */
};

const dtbl_t DTBL_F[] =
{
/*  {  rom start address,     rom end address,     ram start address    },*/
    {&__sram_fastcopy_load_start, &__sram_fastcopy_load_end, &__sram_fastcopy_exec_start},
    {0, 0, 0},                         /* terminator */
};

const btbl_t BTBL_F[] =
{
/*  {  bss start address,    bss end address     },*/
    {0, 0},                            /* terminator */
};

/* End of File */
