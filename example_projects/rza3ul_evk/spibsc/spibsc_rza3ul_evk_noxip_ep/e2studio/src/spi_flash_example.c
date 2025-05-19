/*
 * Copyright [2020-2025] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 * 
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "spi_flash_example.h"
#include "bsp_api.h"
#include "hal_data.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MEMORY_MAPPED_BASE                      (0x20000000UL)
#define MEMORY_MAPPED_SIZE                      (0x20000000UL)
#define MEMORY_MAPPED_CACHEABLE_BASE            (0x20000000UL)
#define MEMORY_MAPPED_CACHEABLE_SIZE            (0x10000000UL)
#define MEMORY_MAPPED_UNCACHEABLE_BASE          (0x30000000UL)
#define MEMORY_MAPPED_UNCACHEABLE_SIZE          (0x10000000UL)
#define ERASE_TEST_VALUE_U8                     (0xffU)
#define ERASE_TEST_VALUE                        (0xffffffffffffffffULL)
#define N1_TABLE_START_VADDR                    (0x00000000)
#define DISABLE_FLASH_AREA_WHILE_MANUAL_MODE    (false)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* These functions must be executed on a device other than the device they are writing to or erasing from. */
/* The simplest solution is to put the code in internal RAM. */
static int  internal_memcmp(const void * s1, const void * s2, size_t size) BSP_PLACE_IN_SECTION("FASTCODE");
static void example_wait_for_complete(const spi_flash_api_t * p_api,
                                      spi_flash_ctrl_t      * p_ctrl) BSP_PLACE_IN_SECTION("FASTCODE");
static bool      example_verifying_erased(uintptr_t buf, size_t size) BSP_PLACE_IN_SECTION("FASTCODE");
static fsp_err_t example_erase_sub(uint32_t address, uint32_t size) BSP_PLACE_IN_SECTION("FASTCODE");
static fsp_err_t example_write_sub(const uint8_t * data, uint32_t address, uint32_t size) BSP_PLACE_IN_SECTION(
    "FASTCODE");
static void example_mmu_entermanual(void) BSP_PLACE_IN_SECTION("FASTCODE");
static void example_mmu_exitmanual(void) BSP_PLACE_IN_SECTION("FASTCODE");
static void invalidate_tlb(void) BSP_PLACE_IN_SECTION("FASTCODE");

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static spi_flash_erase_command_t * erase_command = NULL;
static size_t erase_command_count                = 0;

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
extern uint64_t * __level2_table_1_base;

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Memory compare
 **********************************************************************************************************************/
static int internal_memcmp (const void * s1, const void * s2, size_t size)
{
    int       cmp;
    uint8_t * s1_c = (uint8_t *) s1;
    uint8_t * s2_c = (uint8_t *) s2;
    cmp = 0;

    while (!!size && 0 == cmp)
    {
        cmp = (int) *s1_c - (int) *s2_c;
        s1_c++;
        s2_c++;
        size--;
    }

    return cmp;
}

/*******************************************************************************************************************//**
 * Disallowing to access memory-mapped area for entering manual
 **********************************************************************************************************************/
static void example_mmu_entermanual (void)
{
    if (DISABLE_FLASH_AREA_WHILE_MANUAL_MODE)
    {
        mmu_section_info_t section_info;
        mmu_table_info_t   table_info;

        table_info.table_level     = MMU_TABLE_LEVEL_2;
        table_info.table_base_ptr  = (uint64_t) &__level2_table_1_base;
        table_info.table_base_addr = N1_TABLE_START_VADDR;
        section_info.vaddress      = MEMORY_MAPPED_CACHEABLE_BASE;
        section_info.size          = MEMORY_MAPPED_CACHEABLE_SIZE;
        section_info.paddress      = 0;
        section_info.attribute     = 0;
        R_MMU_WriteTableFault(&g_mmu_ctrl, &table_info, &section_info);
        section_info.vaddress = MEMORY_MAPPED_UNCACHEABLE_BASE;
        section_info.size     = MEMORY_MAPPED_UNCACHEABLE_SIZE;
        R_MMU_WriteTableFault(&g_mmu_ctrl, &table_info, &section_info);
        invalidate_tlb();
    }
}

/*******************************************************************************************************************//**
 * Allowing to access memory-mapped area for exiting manual
 **********************************************************************************************************************/
static void example_mmu_exitmanual (void)
{
    if (DISABLE_FLASH_AREA_WHILE_MANUAL_MODE)
    {
        mmu_section_info_t section_info;
        mmu_table_info_t   table_info;

        table_info.table_level     = MMU_TABLE_LEVEL_2;
        table_info.table_base_ptr  = (uint64_t) &__level2_table_1_base;
        table_info.table_base_addr = N1_TABLE_START_VADDR;
        section_info.vaddress      = MEMORY_MAPPED_CACHEABLE_BASE;
        section_info.size          = MEMORY_MAPPED_CACHEABLE_SIZE;
        section_info.paddress      = MEMORY_MAPPED_BASE;
        section_info.attribute     = R_MMU_PG_ATTRIBUTE_NORMAL_CACHEABLE;
        R_MMU_WriteTable(&g_mmu_ctrl, &table_info, &section_info);
        section_info.vaddress  = MEMORY_MAPPED_UNCACHEABLE_BASE;
        section_info.size      = MEMORY_MAPPED_UNCACHEABLE_SIZE;
        section_info.paddress  = MEMORY_MAPPED_BASE;
        section_info.attribute = R_MMU_PG_ATTRIBUTE_NORMAL_UNCACHE;
        R_MMU_WriteTable(&g_mmu_ctrl, &table_info, &section_info);
        invalidate_tlb();
    }
}

/*******************************************************************************************************************//**
 * TLB invalidate
 **********************************************************************************************************************/
static void invalidate_tlb (void)
{
    __asm volatile (
        "DSB ISH\n"
        "TLBI ALLE3\n"
        "DSB ISH\n"
        "ISB\n"
        : : : "memory"
        );
}

/*******************************************************************************************************************//**
 * Wait for write/erase completion
 **********************************************************************************************************************/
static void example_wait_for_complete (const spi_flash_api_t * p_api, spi_flash_ctrl_t * p_ctrl)
{
    spi_flash_status_t status;
    fsp_err_t          err;

    while (true)
    {
        /* Obtaining status */
        err = p_api->statusGet(p_ctrl, &status);
        assert(FSP_SUCCESS == err);

        /* Check it and break if not in progress */
        if (false == status.write_in_progress)
        {
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Verifying erased
 **********************************************************************************************************************/
static bool example_verifying_erased (uintptr_t buf, size_t size)
{
    const uint8_t  * u8test;
    const uint64_t * u64test;

    /* Unaligned top part */
    if (buf & 7)
    {
        u8test = (const uint8_t *) buf;
        uintptr_t remain = buf & 7;
        while (size && remain)
        {
            if (ERASE_TEST_VALUE_U8 != *u8test)
            {
                return false;
            }

            size--;
            remain--;
            u8test++;
        }

        buf = (uintptr_t) u8test;
    }

    /* Aligned part */
    u64test = (const uint64_t *) buf;
    while (size >= 8)
    {
        if (ERASE_TEST_VALUE != *u64test)
        {
            return false;
        }

        size -= 8;
        u64test++;
    }

    buf = (uintptr_t) u64test;

    /* Unaligned bottom part */
    u8test = (const uint8_t *) buf;
    while (size)
    {
        if (ERASE_TEST_VALUE_U8 != *u8test)
        {
            return false;
        }

        size--;
        u8test++;
    }

    return true;
}

/*******************************************************************************************************************//**
 * Erase example code (sub-routine)
 * @note Disabling exceptions may be necessary if exception handler is stored in the same flash device to be erased.
 * @note Size must match one of the erase configuration list.
 **********************************************************************************************************************/
static fsp_err_t example_erase_sub (uint32_t address, uint32_t size)
{
    fsp_err_t err;

    /* Copy the API table to use while the SPIBSC mode is in manual. */
    spi_flash_api_t    api    = *g_spi_flash0.p_api;
    spi_flash_ctrl_t * p_ctrl = g_spi_flash0.p_ctrl;

    /* Stop scheduling for RTOS */
#if (2 == BSP_CFG_RTOS)

    /* FreeRTOS */
    vTaskSuspendAll();
#elif (1 == BSP_CFG_RTOS)

    /* ThreadX */
    UINT old_priority;
    {
        TX_THREAD thread;
        tx_thread_priority_change(&my_thread, 0, &my_old_priority);
    }
#endif

    /* Disabling interrupts (for baremetal environment) */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER
    ;

    /* MMU setup for entering manual mode */
    example_mmu_entermanual();

    /* Call erase API. */
    err = api.erase(p_ctrl, (void *) (address + MEMORY_MAPPED_BASE), size);

    /* Wait for complete */
    example_wait_for_complete(&api, p_ctrl);

    /* MMU setup for exiting manual mode */
    example_mmu_exitmanual();

    if (FSP_SUCCESS == err)
    {
        /* Required for invalidating SPIBSC cache before invalidating L1~L3 cache */
        R_SPIBSC->DRCR_b.RCF = 1;

        /* Invalidating cache */
        R_BSP_CACHE_InvalidateRange((uint64_t) address + MEMORY_MAPPED_BASE, size);

        /* Verifying erase */
        if (!example_verifying_erased((uintptr_t) address + MEMORY_MAPPED_BASE, size))
        {
            err = FSP_ERR_ERASE_FAILED;
        }
    }

    /* Enabling interrupts (for baremetal environment) */
    FSP_CRITICAL_SECTION_EXIT;

    /* Resume scheduling for RTOS */
#if (2 == BSP_CFG_RTOS)

    /* FreeRTOS */
    xTaskResumeAll();
#elif (1 == BSP_CFG_RTOS)

    /* ThreadX */
    UINT old_priority;
    {
        TX_THREAD thread;
        UINT      dummy;
        tx_thread_priority_change(&my_thread, old_priority, &dummy);
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Write example code (sub-routine)
 * @note Disabling exceptions may be necessary if exception handler is stored in the same flash device to be written.
 **********************************************************************************************************************/
static fsp_err_t example_write_sub (const uint8_t * data, uint32_t address, uint32_t size)
{
    fsp_err_t err;

    /* Copy the API table to use while the SPIBSC mode is in manual. */
    spi_flash_api_t    api    = *g_spi_flash0.p_api;
    spi_flash_ctrl_t * p_ctrl = g_spi_flash0.p_ctrl;

    /* Stop scheduling for RTOS */
#if (2 == BSP_CFG_RTOS)

    /* FreeRTOS */
    vTaskSuspendAll();
#elif (1 == BSP_CFG_RTOS)

    /* ThreadX */
    UINT old_priority;
    {
        TX_THREAD thread;
        tx_thread_priority_change(&my_thread, 0, &my_old_priority);
    }
#endif

    /* Disabling interrupts (for baremetal environment) */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER
    ;

    /* MMU setup for entering manual mode */
    example_mmu_entermanual();

    /* Call write API. */
    err = api.write(p_ctrl, data, (void *) (address + MEMORY_MAPPED_BASE), size);

    /* Wait for complete */
    example_wait_for_complete(&api, p_ctrl);

    /* MMU setup for exiting manual mode */
    example_mmu_exitmanual();

    if (FSP_SUCCESS == err)
    {
        /* Required for invalidating SPIBSC cache before invalidating L1~L3 cache */
        R_SPIBSC->DRCR_b.RCF = 1;

        /* Invalidating cache */
        R_BSP_CACHE_InvalidateRange((uint64_t) address + MEMORY_MAPPED_BASE, size);

        /* Verifying wrote data */
        if (0 != internal_memcmp(data, (void *) (address + MEMORY_MAPPED_BASE), size))
        {
            /* Verifying failed */
            err = FSP_ERR_WRITE_FAILED;
        }
    }

    /* Enabling interrupts (for baremetal environment) */
    FSP_CRITICAL_SECTION_EXIT;

    /* Resume scheduling for RTOS */
#if (2 == BSP_CFG_RTOS)

    /* FreeRTOS */
    xTaskResumeAll();
#elif (1 == BSP_CFG_RTOS)

    /* ThreadX */
    UINT old_priority;
    {
        TX_THREAD thread;
        UINT      dummy;
        tx_thread_priority_change(&my_thread, old_priority, &dummy);
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Initialize example code
 **********************************************************************************************************************/
extern void example_init (void)
{
    size_t len = (size_t) g_spi_flash0.p_cfg->erase_command_list_length;
    size_t i;
    size_t j;

    if (!!erase_command)
    {
        vPortFree(erase_command);
    }

    erase_command = pvPortMalloc(sizeof(spi_flash_erase_command_t) * len);
    if (!erase_command)
    {
        return;
    }

    /* copy */
    erase_command_count = len;
    for (i = 0; i < len; i++)
    {
        erase_command[i] = g_spi_flash0.p_cfg->p_erase_command_list[i];
        if (SPI_FLASH_ERASE_SIZE_CHIP_ERASE == erase_command[i].size)
        {
            erase_command[i].size = 0;
        }
    }

    /* sort by size desc */
    for (i = 0; i < (len - 1); i++)
    {
        spi_flash_erase_command_t * a = &erase_command[i];
        for (j = i + 1; j < len; j++)
        {
            spi_flash_erase_command_t * b = &erase_command[j];
            if (a->size < b->size)
            {
                spi_flash_erase_command_t tmp = *a;
                *a = *b;
                *b = tmp;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * Erase example code
 * @note Disabling exceptions may be necessary if exception handler is stored in the same flash device to be erased.
 * @note Size must match one of the erase configuration list.
 **********************************************************************************************************************/
fsp_err_t example_erase (uint32_t address, uint32_t size)
{
    fsp_err_t err           = FSP_SUCCESS;
    bool      address_error = false;
    bool      size_error    = false;

    /* parameter assertion */
    FSP_ASSERT(0 != size);

    while (!!size && FSP_SUCCESS == err)
    {
        /* Use commands that fit the boundaries */
        for (size_t i = 0; (i < erase_command_count) && (FSP_SUCCESS == err); i++)
        {
            spi_flash_erase_command_t const * cur = &erase_command[i];
            if (0 == cur->size)
            {
                continue;
            }

            uint32_t act_size        = cur->size;
            uint32_t erase_size_mask = act_size - 1U;

            /* Skip not in boundary */
            if (address & erase_size_mask)
            {
                address_error = true;
                continue;
            }

            address_error = false;

            /* Skip not match the size */
            if (size < act_size)
            {
                size_error = true;
                continue;
            }

            size_error = false;

            err      = example_erase_sub(address, act_size);
            address += act_size;
            size    -= act_size;
            break;
        }

        if ((FSP_SUCCESS == err) && (size_error || address_error))
        {
            err = address_error ? FSP_ERR_INVALID_ADDRESS : FSP_ERR_INVALID_SIZE;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Write example code
 **********************************************************************************************************************/
fsp_err_t example_write (const uint8_t * data, uint32_t address, uint32_t size)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  act_size;

    /* parameter assertion */
    FSP_ASSERT(0 != size);
    FSP_ASSERT(NULL != data);

    /* page boundary mask */
    uint32_t page_size          = g_spi_flash0.p_cfg->page_size_bytes;
    uint32_t page_reminder_mask = page_size - 1U;

    /* Unaligned top part */
    if (address & page_reminder_mask)
    {
        act_size = 256U - (address & page_reminder_mask);
        if (act_size > size)
        {
            act_size = size;
        }

        err      = example_write_sub(data, address, act_size);
        address += act_size;
        data    += act_size;
        size    -= act_size;
    }

    /* Aligned or unaligned bottom part */
    while (!!size && (FSP_SUCCESS == err))
    {
        act_size = page_size;
        if (act_size > size)
        {
            act_size = size;
        }

        err      = example_write_sub(data, address, act_size);
        address += act_size;
        data    += act_size;
        size    -= act_size;
    }

    return err;
}
