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

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include "bsp_api.h"
#include "hal_data.h"
/*  #include "r_os_abstraction_api.h"  */
#if (BSP_CFG_RTOS == 2)
#include "event_groups.h"
#include "semphr.h"
#endif

/******************************************************************************
 Macro Definitions
 ******************************************************************************/
/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
int stdio_open(void);
void stdio_close(void);
int stdio_read(uint8_t *pbyBuffer, uint32_t uiCount);
int stdio_write(const uint8_t * pbyBuffer, uint32_t uiCount);

void app_read(unsigned char* p_data);
int app_check_data();
/******************************************************************************
 Imported global variables and functions (from other files)
 ******************************************************************************/
static uint32_t stdio_initialized = 0;
#if (BSP_CFG_RTOS == 2)
static EventGroupHandle_t  printf_event = NULL;
static SemaphoreHandle_t  printf_semaphore = NULL;
#else
static volatile int wait_tx = 0;
#endif
static volatile uint32_t scan_write = 0;
static uint32_t scan_read = 0;
static uint8_t scan_buffer[1024];

char g_buff[1024];   // Stream buff

/**********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* Dummy driver configuration */


int stdio_open(void)
{
    int ret = 0;
    if (stdio_initialized == 0)
    {
#if (BSP_CFG_RTOS == 2)
        printf_event = xEventGroupCreate();
        printf_semaphore = xSemaphoreCreateBinary();
        xSemaphoreGive(printf_semaphore);
#endif
        scan_write = 0;
        scan_read = 0;
        memset(scan_buffer,0,sizeof(scan_buffer));
        stdio_initialized = 1;
    }
    ret = g_uart0.p_api->open(g_uart0.p_ctrl, g_uart0.p_cfg);
    g_uart0.p_api->read(g_uart0.p_ctrl, &scan_buffer[scan_write], 0);
    return ret;
}

void stdio_close(void)
{
    g_uart0.p_api->close(g_uart0.p_ctrl);
}

int stdio_read(uint8_t *pbyBuffer, uint32_t uiCount)
{
#if 1 /* if you use only getchar for standard input, change 1 -> 0 */
    uint32_t ret = 0;
    uint8_t  current_data;
    if (stdio_initialized == 0)
    {
        stdio_open();
    }

    while(ret < uiCount)
    {
        while(scan_write == scan_read)
        {
#if (BSP_CFG_RTOS == 2)
            vTaskDelay(1);
#else
#endif
        }
        current_data = scan_buffer[scan_read];
        *pbyBuffer = current_data;
        scan_read++;
        pbyBuffer++;
        ret++;
        if( scan_read >= sizeof(scan_buffer) )
        {
            scan_read = 0;
        }
        if( current_data == '\n' )
        {
            break;
        }
        if( current_data == '\r' )
        {
            if( scan_buffer[scan_read] != '\n' )
            {
                break;
            }
        }
    }
    return (int)ret;
#else
    int ret = 0;

    if (stdio_initialized == 0)
    {
        stdio_open();
    }
    while(scan_write == scan_read)
    {
#if (BSP_CFG_RTOS == 2)
        vTaskDelay(1);
#else
#endif
    }

    if( scan_write < scan_read )
    {
        if( scan_read + uiCount < sizeof(scan_buffer) )
        {
            ret = uiCount;
        }
        else
        {
            ret = sizeof(scan_buffer) - scan_read;
        }
    }
    else
    {
        if( scan_read + uiCount < scan_write )
        {
            ret = uiCount;
        }
        else
        {
            ret = scan_write - scan_read;
        }
    }
    memcpy(pbyBuffer,&scan_buffer[scan_read],ret);
    scan_read += ret;
    if( scan_read > sizeof(scan_buffer) )
    {
        scan_read = 0;
    }
    return ret;
#endif
}

int stdio_write(const uint8_t * pbyBuffer, uint32_t uiCount)
{
    int ret;

    if (stdio_initialized == 0)
    {
        stdio_open();
    }
#if (BSP_CFG_RTOS == 2)
    xSemaphoreTake(printf_semaphore,portMAX_DELAY);
#else
    wait_tx = 0;
#endif
    ret = g_uart0.p_api->write(g_uart0.p_ctrl, pbyBuffer, uiCount);
#if (BSP_CFG_RTOS == 2)
    xEventGroupWaitBits(printf_event,1,pdTRUE,pdTRUE,portMAX_DELAY);
    xSemaphoreGive(printf_semaphore);
#else
    while(wait_tx == 0);
#endif
    return ret;
}

void uart0_cb_stdio (uart_callback_args_t * p_args)
{
    if (stdio_initialized == 0)
    {
        stdio_open();
    }
    if(p_args!=NULL)
    {
        if(p_args->event & UART_EVENT_TX_COMPLETE)
        {
#if (BSP_CFG_RTOS == 2)
            BaseType_t xHigherPriorityTaskWoken, xResult;

            /* xHigherPriorityTaskWoken must be initialised to pdFALSE. */
            xHigherPriorityTaskWoken = pdFALSE;

            /* Set bit 0 and bit 4 in xEventGroup. */
            xResult = xEventGroupSetBitsFromISR(
                                  printf_event,   /* The event group being updated. */
                                  1, /* The bits being set. */
                                  &xHigherPriorityTaskWoken );

            /* Was the message posted successfully? */
            if( xResult != pdFAIL )
            {
                /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context
                switch should be requested.  The macro used is port specific and will
                be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() - refer to
                the documentation page for the port being used. */
                portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
            }
#else
            wait_tx = 1;
#endif
        }
        if(p_args->event & UART_EVENT_RX_CHAR)
        {
            scan_buffer[scan_write] = (uint8_t)p_args->data;


            if(scan_write < sizeof(scan_buffer))
            {
                scan_write++;
            }
            if (scan_write >= sizeof(scan_buffer))
            {
                scan_write = 0;
            }
        }
    }
}

void app_read(unsigned char* p_data)
{
    if (stdio_initialized == 0)
    {
        stdio_open();
    }
    scanf("%1023s", p_data);
    sscanf(g_buff, "%1023s", p_data);
    fflush(stdin);

}

int app_check_data()
{
    if (stdio_initialized == 0)
    {
        stdio_open();
    }
    if (scan_write != scan_read)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/***********************************************************************************************************************
 End  Of File
 **********************************************************************************************************************/
