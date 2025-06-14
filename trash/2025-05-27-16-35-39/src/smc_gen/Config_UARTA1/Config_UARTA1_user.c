/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021, 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_UARTA1_user.c
* Component Version: 1.5.0
* Device(s)        : R7F100GSNxFB
* Description      : This file implements device driver for Config_UARTA1.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_UARTA1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_UARTA1_interrupt_receive(vect=INTUR1)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint16_t g_uarta1_rx_total_num;
extern volatile uint8_t * gp_uarta1_rx_address;
extern volatile uint16_t g_uarta1_rx_num;
/* Start user code for global. Do not edit comment generated here */
extern void touch_uart_callback(uint16_t event);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UARTA1_Create_UserInit
* Description  : This function adds user code after initializing UARTA1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UARTA1_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_Config_UARTA1_PollingEnd_UserCode
* Description  : This function is a callback function when UARTA1 finishes polling transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UARTA1_PollingEnd_UserCode(void)
{
    /* Start user code for R_Config_UARTA1_PollingEnd_UserCode. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UARTA1_callback_receiveend
* Description  : This function is a callback function when UARTA1 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UARTA1_callback_receiveend(void)
{
    /* Start user code for r_Config_UARTA1_callback_receiveend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UARTA1_callback_error
* Description  : This function is a callback function when UARTA1 reception error occurs.
* Arguments    : err_type -
*                     error type value
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UARTA1_callback_error(uint8_t err_type)
{
    /* Start user code for r_Config_UARTA1_callback_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UARTA1_interrupt_receive
* Description  : This function is UARTA1 receive interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_UARTA1_interrupt_receive(void)
{
    uint16_t temp;
    uint8_t err_type;

    err_type = (ASISA1 & (_04_UARTA_PARITY_ERROR_DETECTED | _02_UARTA_FRAME_ERROR_DETECTED | 
               _01_UARTA_OVERRUN_ERROR_DETECTED));
    if (err_type != 0U)
    {
        *gp_uarta1_rx_address = RXBA1;
        ASCTA1 |= (_04_UARTA_PARITY_FLAG_CLEAR | _02_UARTA_FRAME_FLAG_CLEAR | _01_UARTA_OVERRUN_FLAG_CLEAR);
        r_Config_UARTA1_callback_error(err_type);
    }
    else
    {
        temp = g_uarta1_rx_total_num;

        if (temp > g_uarta1_rx_num)
        {
            *gp_uarta1_rx_address = RXBA1;
            gp_uarta1_rx_address++;
            g_uarta1_rx_num++;
        }

        temp = g_uarta1_rx_total_num;

        if (temp == g_uarta1_rx_num)
        {
            r_Config_UARTA1_callback_receiveend();
        }
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
