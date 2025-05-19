/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
#include "bsp_api.h"
#include <sys/types.h>
#include <errno.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* dummy function for newlib */
int  _write(int handle, char * data, int size);
int  _read(int handle, char * data, int size);
int  _close(int handle);
int  _fstat(int handle, char * data);
int  _lseek(int handle, char * data, int size);
int  _isatty(int fd);
int  _getpid(void);
int  _kill(int pid, int sig);
int  _open(const char * name, int flags, int mode);
void _exit(int status);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

int _write (int handle, char * data, int size)
{
    (void) handle;
    (void) data;
    (void) size;

    return 0;
}

int _read (int handle, char * data, int size)
{
    (void) handle;
    (void) data;
    (void) size;

    return 0;
}

int _close (int handle)
{
    (void) handle;

    return 0;
}

int _fstat (int handle, char * data)
{
    (void) handle;
    (void) data;

    return 0;
}

int _lseek (int handle, char * data, int size)
{
    (void) handle;
    (void) data;
    (void) size;

    return 0;
}

int _isatty (int fd)
{
    (void) fd;

    return 0;
}

int _getpid (void)
{
    return 0;
}

int _kill (int pid, int sig)
{
    (void) pid;
    (void) sig;

    return 0;
}

int _open (const char * name, int flags, int mode)
{
    (void) name;
    (void) flags;
    (void) mode;

    return 0;
}

void _exit (int status)
{
    (void) status;
    _write(1, "FSP exit\n", 9);
    while (1)
    {
        ;
    }
}

#endif

/******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU)
 *********************************************************************************************************************/
