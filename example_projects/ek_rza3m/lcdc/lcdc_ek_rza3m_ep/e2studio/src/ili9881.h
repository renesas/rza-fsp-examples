/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ILI9881_H_
#define ILI9881_H_

#include "r_mipi_dsi_b.h"
#include "bsp_api.h"

/* Command send data */
#define COMMAND_SEND_DATA(_op, _data0, _data1)  \
        ((command_type_t){ .operation = (_op), .data0 = (_data0), .data1 = (_data1) })

typedef struct command_type
{
    uint8_t operation;  /* 0    :change page to data0 page
                         * 1    :short packet without parameter
                         * 2    :short packet with parameter
                         * 0x10 :Delay "data0" mili seconds wait
                         * 0xFF :terminate command flow
                         * */
    uint8_t data0;
    uint8_t data1;
}command_type_t;

extern command_type_t g_command_flow_ili9881[];

void ili9881_init(mipi_dsi_ctrl_t * const p_api_ctrl);
void ili9881_changepage(mipi_dsi_ctrl_t * const p_api_ctrl, uint8_t page);
void ili9881_cmd_send(mipi_dsi_ctrl_t * const p_api_ctrl, command_type_t * command_flow);

#endif /* ILI9881_H_ */
