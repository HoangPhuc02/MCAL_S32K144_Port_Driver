/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : PORT_CI
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K1_RTD_1_0_1_D2202_ASR_REL_4_4_REV_0000_20220224
*
*   (c) Copyright 2020-2022 NXP Semiconductors
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file    PORT_HW_VS_0_PBcfg.c
*
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port_Hw.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief        Parameters that shall be published within the Port driver header file and also in the
*               module description file
* @details      The integration of incompatible files shall be avoided.
*
*/
#define PORT_HW_VENDOR_ID_VS_0_PBCFG_C                       43
#define PORT_HW_AR_RELEASE_MAJOR_VERSION_VS_0_PBCFG_C        21
#define PORT_HW_AR_RELEASE_MINOR_VERSION_VS_0_PBCFG_C        11
#define PORT_HW_AR_RELEASE_REVISION_VERSION_VS_0_PBCFG_C     0
#define PORT_HW_SW_MAJOR_VERSION_VS_0_PBCFG_C                1
#define PORT_HW_SW_MINOR_VERSION_VS_0_PBCFG_C                0
#define PORT_HW_SW_PATCH_VERSION_VS_0_PBCFG_C                0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files PORT_HW_VS_0_PBcfg.c and PORT_HW.h are of the same vendor */
#if (PORT_HW_VENDOR_ID_VS_0_PBCFG_C != PORT_HW_VENDOR_ID_H)
    #error "PORT_HW_VS_0_PBcfg.c and PORT_HW.h have different vendor ids"
#endif
/* Check if the files PORT_HW_VS_0_PBcfg.c and PORT_HW.h are of the same Autosar version */
#if ((PORT_HW_AR_RELEASE_MAJOR_VERSION_VS_0_PBCFG_C    != PORT_HW_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_HW_AR_RELEASE_MINOR_VERSION_VS_0_PBCFG_C    != PORT_HW_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_HW_AR_RELEASE_REVISION_VERSION_VS_0_PBCFG_C != PORT_HW_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "AutoSar Version Numbers of PORT_HW_VS_0_PBcfg.c and PORT_HW.h are different"
#endif
/* Check if the files PORT_HW_VS_0_PBcfg.c and PORT_HW.h are of the same software version */
#if ((PORT_HW_SW_MAJOR_VERSION_VS_0_PBCFG_C != PORT_HW_SW_MAJOR_VERSION_H) || \
     (PORT_HW_SW_MINOR_VERSION_VS_0_PBCFG_C != PORT_HW_SW_MINOR_VERSION_H) || \
     (PORT_HW_SW_PATCH_VERSION_VS_0_PBCFG_C != PORT_HW_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of PORT_HW_VS_0_PBcfg.c and PORT_HW.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"
const PortHw_PinSettingsConfigType PortHw_g_Pin_Mux_InitConfigArr_VS_0[NUM_OF_CONFIGURED_PINS] = 
{
    {
        .PortBase_ptr              = IP_PORTD,
        .GpioBase_ptr              = IP_PTD,
        .PinPortIndex_u32          = 0,
        .Mux_en                   = PORT_HW_MUX_AS_GPIO,
        .Direction_en             = PORT_HW_PIN_OUT,
        .PullConfig_en            = PORT_HW_PULL_NOT_ENABLED,
        .DriveStrength_en         = PORT_HW_DRIVE_STRENGTH_LOW,
        .LockRegister_en          = PORT_HW_LOCK_DISABLED,
        .InitValue_u8                = 0
    }
};
#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
