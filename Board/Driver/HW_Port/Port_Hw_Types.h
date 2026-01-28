/*==================================================================================================
*   Project              : MCAL_PORT_S32K144
*   Platform             : CORTEXM
*   Peripheral           : PORT
*   Dependencies         : none
*
*   Autosar Version      : 21.11.0
*   Autosar Revision     : ASR_REL_21_11_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        :
*
*   Author               : PhucPH32
==================================================================================================*/
/**
*   @file    Port_Hw_Types.h
*
*   @brief   Port Hardware Abstraction Layer type definitions
*   @details This file contains all types and structures needed for Port Hardware driver.
*            Based on Port_Ci_Port_Ip_Types.h from NXP RTD
*
*   @addtogroup Port_HW
*   @{
*/

#ifndef PORT_HW_TYPES_H
#define PORT_HW_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "S32K144.h"
#include "Std_Types.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
*/
#define PORT_HW_TYPES_VENDOR_ID_H                    43
#define PORT_HW_TYPES_AR_RELEASE_MAJOR_VERSION_H     21
#define PORT_HW_TYPES_AR_RELEASE_MINOR_VERSION_H     11
#define PORT_HW_TYPES_AR_RELEASE_REVISION_VERSION_H  0
#define PORT_HW_TYPES_SW_MAJOR_VERSION_H             1
#define PORT_HW_TYPES_SW_MINOR_VERSION_H             0
#define PORT_HW_TYPES_SW_PATCH_VERSION_H             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Macro to extract port number from GPIO channel
* @details Shifts channel number right by 5 bits to get port index (each port has 32 pins)
*/
#define PORT_HW_GET_PORT_U32(channel)      ((uint32)((uint32)(channel) >> 5U))

/**
* @brief Macro to extract pin number within a port from GPIO channel
* @details Masks channel number with 31 to get pin index (0-31)
*/
#define PORT_HW_GET_PIN_U32(channel)       ((uint32)((uint32)(channel) & 31U))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/**
* @brief   Port Hardware Status Type
* @details Return status for Port Hardware driver functions
*/
typedef enum Port_Hw_StatusType_t
{
    PORT_HW_STATUS_SUCCESS = 0U,    /**< @brief Operation completed successfully */
    PORT_HW_STATUS_ERROR   = 1U     /**< @brief Operation failed with error */
} PortHw_StatusType;

/**
* @brief   Port Pin Pull Configuration Type
* @details Configuration for internal pull-up/pull-down resistors
*/
typedef enum Port_Hw_PullConfigType_t
{
    PORT_HW_PULL_DOWN_ENABLED   = 0U,   /**< @brief Internal pull-down resistor enabled */
    PORT_HW_PULL_UP_ENABLED     = 1U,   /**< @brief Internal pull-up resistor enabled */
    PORT_HW_PULL_NOT_ENABLED    = 2U    /**< @brief Internal pull resistor disabled */
} PortHw_PullConfigType;

/**
* @brief   Port Pin Mux Configuration Type
* @details Configuration for pin multiplexing (alternate function selection)
*/
typedef enum Port_Hw_MuxType_t
{
    PORT_HW_MUX_ALT0            = 0U,   /**< @brief Pin disabled or ALT0 (Analog) mode */
    PORT_HW_MUX_AS_GPIO         = 1U,   /**< @brief Pin configured as GPIO */
    PORT_HW_MUX_ALT2            = 2U,   /**< @brief Alternate function 2 */
    PORT_HW_MUX_ALT3            = 3U,   /**< @brief Alternate function 3 */
    PORT_HW_MUX_ALT4            = 4U,   /**< @brief Alternate function 4 */
    PORT_HW_MUX_ALT5            = 5U,   /**< @brief Alternate function 5 */
    PORT_HW_MUX_ALT6            = 6U,   /**< @brief Alternate function 6 */
    PORT_HW_MUX_ALT7            = 7U    /**< @brief Alternate function 7 */
} PortHw_MuxType;

/**
* @brief   Port Pin Direction Type
* @details Configuration for GPIO pin direction
*/
typedef enum Port_Hw_DirectionType_t
{
    PORT_HW_PIN_DISABLED        = 0U,   /**< @brief Pin disabled (ALT0 mode) */
    PORT_HW_PIN_IN              = 1U,   /**< @brief Pin configured as input */
    PORT_HW_PIN_OUT             = 2U,   /**< @brief Pin configured as output */
    #if 0 
    PORT_HW_PIN_HIGH_Z          = 3U    /**< @brief Pin configured as high impedance */
    #endif 
} PortHw_DirectionType;

/**
* @brief   Port Pin Drive Strength Type
* @details Configuration for output drive strength
*/
typedef enum Port_Hw_DriveStrengthType_t
{
    PORT_HW_DRIVE_STRENGTH_LOW  = 0U,   /**< @brief Low drive strength */
    PORT_HW_DRIVE_STRENGTH_HIGH = 1U    /**< @brief High drive strength */
} PortHw_DriveStrengthType;

/**
* @brief   Port Pin Lock Register Type
* @details Configuration for pin configuration lock
*/
typedef enum Port_Hw_LockRegisterType_t
{
    PORT_HW_LOCK_DISABLED       = 0U,   /**< @brief Pin configuration is not locked */
    PORT_HW_LOCK_ENABLED        = 1U    /**< @brief Pin configuration is locked */
} PortHw_LockRegisterType;

/**
* @brief   Port Global Control Half Pins Type
* @details Selection for global pin control (lower or upper 16 pins)
*/
typedef enum Port_Hw_GlobalControlPinsType_t
{
    PORT_HW_GLOBAL_LOWER_HALF   = 0U,   /**< @brief Lower 16 pins (0-15) */
    PORT_HW_GLOBAL_UPPER_HALF   = 1U    /**< @brief Upper 16 pins (16-31) */
} PortHw_GlobalControlPinsType;

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief   Port Pin Level Type
* @details Type for representing pin output level (HIGH/LOW)
*/
typedef uint8 PortHw_PortPinsLevelType;

/**
* @brief   Unused Pin Configuration Structure
* @details Configuration structure for unused pins
*/
typedef struct PortHw_UnusedPinConfigType_t
{
    uint32                  PinControlRegister_u32; /**< @brief Content of PCR Register */
    PortHw_DirectionType    Direction_en;           /**< @brief Pin direction */
    uint8                   OutputValue_u8;         /**< @brief Pin output value */
} PortHw_UnusedPinConfigType;


/**
* @brief   Port Pin Settings Configuration Structure
* @details Main structure for configuring a single PORT pin
*/
typedef struct Port_Hw_PinSettingsConfigType_t
{
    PORT_Type*                  PortBase_ptr;       /**< @brief Pointer to PORT peripheral base */
    GPIO_Type*                  GpioBase_ptr;       /**< @brief Pointer to GPIO peripheral base */
    uint32                      PinPortIndex_u32;     /**< @brief Pin index within the port (0-31) */
    PortHw_PullConfigType      PullConfig_en;      /**< @brief Pull resistor configuration */
    PortHw_MuxType             Mux_en;             /**< @brief Pin mux (alternate function) */
    PortHw_DirectionType       Direction_en;       /**< @brief Pin direction (in/out/high-z) */
    PortHw_DriveStrengthType   DriveStrength_en;   /**< @brief Output drive strength */
    PortHw_LockRegisterType    LockRegister_en;    /**< @brief Configuration lock */
    PortHw_PortPinsLevelType        InitValue_u8;       /**< @brief Initial output value for GPIO */
} PortHw_PinSettingsConfigType;

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* PORT_HW_TYPES_H */
