/*==================================================================================================
* Project : MCAL_PORT_S32K144
* Platform : CORTEXM
* Peripheral : S32K144
* Dependencies : none
*
* Autosar Version : 21.11.0
* Autosar Revision : ASR_REL_21_11_REV_0000
* Autosar Conf.Variant :
* SW Version : 1.0.0
* Build Version :
*
* Author: PhucPH32
==================================================================================================*/
/**
* @file           OsIf_Cfg.h
* @implements     OsIf_Cfg.h_Artifact
* @brief          OS Interface configuration header
* @details        Configuration options for OsIf stub module
*
* @addtogroup     OSIF_MODULE
* @{
*/

#ifndef OSIF_CFG_H
#define OSIF_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the OsIf_Cfg header file
*/
#define OSIF_CFG_VENDOR_ID                      43U
#define OSIF_CFG_AR_RELEASE_MAJOR_VERSION       21U
#define OSIF_CFG_AR_RELEASE_MINOR_VERSION       11U
#define OSIF_CFG_AR_RELEASE_REVISION_VERSION    0U
#define OSIF_CFG_SW_MAJOR_VERSION               1U
#define OSIF_CFG_SW_MINOR_VERSION               0U
#define OSIF_CFG_SW_PATCH_VERSION               0U

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*-------------------------------------------------------------------------------------------------
*                               Timer Configuration
-------------------------------------------------------------------------------------------------*/
/**
* @brief Enable/Disable system timer (SysTick)
*/
#define OSIF_USE_SYSTEM_TIMER               (STD_ON)

/**
* @brief Enable/Disable custom timer
*/
#define OSIF_USE_CUSTOM_TIMER               (STD_OFF)

/**
* @brief Default timer frequency (S32K144 default: 48MHz)
*/
#define OSIF_DEFAULT_TIMER_FREQ             (48000000UL)

/**
* @brief SysTick load value for 1ms tick at 48MHz
* @details SysTick counts down from LOAD to 0
*          For 1ms: LOAD = (48000000 / 1000) - 1 = 47999
*/
#define OSIF_SYSTICK_LOAD_VALUE             (47999UL)

/*-------------------------------------------------------------------------------------------------
*                               Counter Configuration
-------------------------------------------------------------------------------------------------*/
/**
* @brief Maximum counter value before wrap-around
*/
#define OSIF_COUNTER_MAX_VALUE              (0xFFFFFFFFUL)

/**
* @brief Counter overflow threshold
*/
#define OSIF_COUNTER_OVERFLOW_THRESHOLD     (0x80000000UL)

/*-------------------------------------------------------------------------------------------------
*                               Timeout Configuration
-------------------------------------------------------------------------------------------------*/
/**
* @brief Enable/Disable timeout feature
*/
#define OSIF_ENABLE_TIMEOUT                 (STD_ON)

/**
* @brief Default timeout value in microseconds
*/
#define OSIF_DEFAULT_TIMEOUT_US             (1000000UL)

/*-------------------------------------------------------------------------------------------------
*                               Interrupt Configuration
-------------------------------------------------------------------------------------------------*/
/**
* @brief Enable/Disable interrupt nesting support
*/
#define OSIF_ENABLE_INTERRUPT_NESTING       (STD_ON)

/**
* @brief Maximum interrupt nesting level
*/
#define OSIF_MAX_INTERRUPT_NESTING          (8U)

/*-------------------------------------------------------------------------------------------------
*                               Debug Configuration
-------------------------------------------------------------------------------------------------*/
/**
* @brief Enable/Disable OsIf development error detection
*/
#define OSIF_DEV_ERROR_DETECT               (STD_OFF)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* OSIF_CFG_H */
