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

#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/**
*   @file    Port_Types.h
*
*   @implements Port_Types.h_Artifact
*   @defgroup   Port_CFG Port CFG
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Std_Types.h" 
#include "Port_Hw_Types.h"
/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief        Parameters that shall be published within the Port driver header file and also in the
*               module description file
* @details      The integration of incompatible files shall be avoided.
*
*/

#define PORT_TYPES_VENDOR_ID_H                       43
#define PORT_TYPES_AR_RELEASE_MAJOR_VERSION_H        21
#define PORT_TYPES_AR_RELEASE_MINOR_VERSION_H        11
#define PORT_TYPES_AR_RELEASE_REVISION_VERSION_H     0
#define PORT_TYPES_SW_MAJOR_VERSION_H                1
#define PORT_TYPES_SW_MINOR_VERSION_H                0
#define PORT_TYPES_SW_PATCH_VERSION_H                0

/*=================================================================================================
*                                      FILE VERSION CHECKS
=================================================================================================*/
/* Check if the files Port_Cfg.h and Port_VS_0_PBcfg.h are of the same version */
#if (PORT_TYPES_VENDOR_ID_H != PORT_VENDOR_ID_VS_0_PBCFG_H)
    #error "Port_Cfg.h and Port_VS_0_PBcfg.h have different vendor IDs"
#endif
 /* Check if the files Port_Cfg.h and Port_VS_0_PBcfg.h are of the same Autosar version */
#if ((PORT_TYPES_AR_RELEASE_MAJOR_VERSION_H != PORT_AR_RELEASE_MAJOR_VERSION_VS_0_PBCFG_H) ||   \
     (PORT_TYPES_AR_RELEASE_MINOR_VERSION_H != PORT_AR_RELEASE_MINOR_VERSION_VS_0_PBCFG_H) ||   \
     (PORT_TYPES_AR_RELEASE_REVISION_VERSION_H != PORT_AR_RELEASE_REVISION_VERSION_VS_0_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and Port_VS_0_PBcfg.h are different"
#endif
/* Check if the files Port_Cfg.h and Port_VS_0_PBcfg.h are of the same software version */
#if ((PORT_TYPES_SW_MAJOR_VERSION_H != PORT_SW_MAJOR_VERSION_VS_0_PBCFG_H) || \
     (PORT_TYPES_SW_MINOR_VERSION_H != PORT_SW_MINOR_VERSION_VS_0_PBCFG_H) || \
     (PORT_TYPES_SW_PATCH_VERSION_H != PORT_SW_PATCH_VERSION_VS_0_PBCFG_H)     \
    )
    #error "Software Version Numbers of Port_Cfg.h and Port_VS_0_PBcfg.h are different"
#endif
/* Check if the files Port_Cfg.h and PORT_HW_Types.h are of the same version */
#if (PORT_TYPES_VENDOR_ID_H != PORT_HW_TYPES_VENDOR_ID_H)
    #error "Port_Cfg.h and PORT_HW_Types.h have different vendor IDs"
#endif
/* Check if the files Port_Cfg.h and PORT_HW_Types.h are of the same Autosar version */
#if ((PORT_TYPES_AR_RELEASE_MAJOR_VERSION_H != PORT_HW_TYPES_AR_RELEASE_MAJOR_VERSION_H) ||   \
     (PORT_TYPES_AR_RELEASE_MINOR_VERSION_H != PORT_HW_TYPES_AR_RELEASE_MINOR_VERSION_H) ||   \
     (PORT_TYPES_AR_RELEASE_REVISION_VERSION_H != PORT_HW_TYPES_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and PORT_HW_Types.h are different"
#endif
/* Check if the files Port_Cfg.h and PORT_HW_Types.h are of the same software version */
#if ((PORT_TYPES_SW_MAJOR_VERSION_H != PORT_HW_TYPES_SW_MAJOR_VERSION_H) || \
     (PORT_TYPES_SW_MINOR_VERSION_H != PORT_HW_TYPES_SW_MINOR_VERSION_H) || \
     (PORT_TYPES_SW_PATCH_VERSION_H != PORT_HW_TYPES_SW_PATCH_VERSION_H)     \
    )
    #error "Software Version Numbers of Port_Cfg.h and PORT_HW_Types.h are different"
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/
/* @implements Port_PinType_typedef */
typedef uint32 Port_PinType;

/**
* @brief Different port pin modes.
* @details A port pin shall be configurable with a number of port pin modes (type Port_PinModeType).
*        The type Port_PinModeType shall be used with the function call Port_SetPinMode
* @implements Port_PinModeType_typedef
*/
typedef uint8 Port_PinModeType;

/**
* @brief Possible directions of a port pin.
* @implements Port_PinDirectionType_enumeration
*/
typedef enum
{
    PORT_PIN_DISABLED = 0,         /**< @brief Sets port pin as bidirectional. */
    PORT_PIN_IN,                   /**< @brief Sets port pin as input. */
    PORT_PIN_OUT,                  /**< @brief Sets port pin as output. */
} Port_PinDirectionType;


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/
typedef struct
{
    uint32                  PinControlRegister_u32;     /**< Content of Mscr Register */
    Port_PinDirectionType   PinDirection_en;            /**< @brief Pad Data Direction */
    uint8                   PinOutputValue_u8;          /**< Pad Data Output */
} Port_UnUsedPinConfigType;

/**
* @brief   Single pin configuration.
* @details This structure contains all configuration parameters of a single pin
*          identified by @p SIUPin.
*/
typedef struct
{
    uint16 PinIndex_u16;                                /**< @brief Index of the pin's Mscr */
    uint32 PinControlRegister_u32;                      /**< @brief Pad Control Register */
    uint8 PinOutputValue_u8;                            /**< @brief Pad Data Output */
    Port_PinDirectionType PinDirection_en;              /**< @brief Pad Data Direction */
    boolean IsGpioMode_bool;                            /**< @brief GPIO initial mode*/
    boolean DirectionChangeable_bool;                   /**< @brief Direction changebility*/
    boolean ModeChangeable_bool;                        /**< @brief Mode changebility*/
} Port_PinConfigType;

/**
* @brief   Structure needed by @p Port_Init().
* @details The structure @p Port_ConfigType is a type for the external data
*          structure containing the initialization data for the PORT Driver.
* @note    The user must use the symbolic names defined in the configuration
*          tool.
*
* @implements Port_ConfigType_struct
*/
typedef struct
{
    uint16 NumPins_u16;                                                       /**< @brief Number of used pads (to be configured) */
    uint16 NumUnusedPins_u16;                                                 /**< @brief Number of unused pads */
    const uint16 * UnusedPads_ptr;                                              /**< @brief Unused pad id's array */
    const Port_UnUsedPinConfigType * UnusedPadConfig_ptr;                       /**< @brief Unused pad configuration */
    const Port_PinConfigType * UsedPadConfig_ptr;                               /**< @brief Used pads data configuration */
    const PortHw_PinSettingsConfigType *IpConfig_ptr;                    /**< @brief Ip configuration */
} Port_ConfigType;


#endif /* PORT_TYPES_H */
