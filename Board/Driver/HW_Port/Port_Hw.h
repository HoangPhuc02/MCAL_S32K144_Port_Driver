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
*   @file    Port_Hw.h
*
*   @brief   Port Hardware Abstraction Layer header file
*   @details This file contains the function prototypes and macros for Port Hardware driver.
*            Based on Port_Ci_Port_Ip.h from NXP RTD
*
*   @addtogroup Port_HW
*   @{
*/

#ifndef PORT_HW_H
#define PORT_HW_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port_Hw_Types.h"
#include "devassert.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
*/
#define PORT_HW_VENDOR_ID_H                    43
#define PORT_HW_AR_RELEASE_MAJOR_VERSION_H     21
#define PORT_HW_AR_RELEASE_MINOR_VERSION_H     11
#define PORT_HW_AR_RELEASE_REVISION_VERSION_H  0
#define PORT_HW_SW_MAJOR_VERSION_H             1
#define PORT_HW_SW_MINOR_VERSION_H             0
#define PORT_HW_SW_PATCH_VERSION_H             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Port_Hw.h and Port_Hw_Types.h are of the same vendor */
#if (PORT_HW_VENDOR_ID_H != PORT_HW_TYPES_VENDOR_ID_H)
    #error "Port_Hw.h and Port_Hw_Types.h have different vendor ids"
#endif

/* Check if Port_Hw.h and Port_Hw_Types.h are of the same Autosar version */
#if ((PORT_HW_AR_RELEASE_MAJOR_VERSION_H    != PORT_HW_TYPES_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_HW_AR_RELEASE_MINOR_VERSION_H    != PORT_HW_TYPES_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_HW_AR_RELEASE_REVISION_VERSION_H != PORT_HW_TYPES_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "Autosar Version Numbers of Port_Hw.h and Port_Hw_Types.h are different"
#endif

/* Check if Port_Hw.h and Port_Hw_Types.h are of the same software version */
#if ((PORT_HW_SW_MAJOR_VERSION_H != PORT_HW_TYPES_SW_MAJOR_VERSION_H) || \
     (PORT_HW_SW_MINOR_VERSION_H != PORT_HW_TYPES_SW_MINOR_VERSION_H) || \
     (PORT_HW_SW_PATCH_VERSION_H != PORT_HW_TYPES_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_Hw.h and Port_Hw_Types.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
/**
* @brief Number of pins per port
*/
#define PORT_HW_PINS_PER_PORT_U8           ((uint8)32U)

/**
* @brief Number of available ports
*/
#define PORT_HW_PORT_COUNT_U8              ((uint8)5U)

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Enable or disable development error detection
*/
#define PORT_HW_DEV_ERROR_DETECT           (STD_ON)

#if (PORT_HW_DEV_ERROR_DETECT == STD_ON)
    #define PORT_HW_DEV_ASSERT(condition)  DEV_ASSERT(condition)
#else
    #define PORT_HW_DEV_ASSERT(condition)
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/**
* @brief Array of PORT base addresses for all port instances
*/
extern PORT_Type* const PortHw_g_PortBaseAddr_ptr[PORT_HW_PORT_COUNT_U8];

/**
* @brief Array of GPIO base addresses for all port instances
*/
extern GPIO_Type* const PortHw_g_GpioBaseAddr_ptr[PORT_HW_PORT_COUNT_U8];

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief       Initializes multiple pins with the given configuration array
*
* @details     This function configures multiple pins using the provided configuration
*              structure array. Each element configures one pin. Also initializes unused pins.
*
* @param[in]   PinCount_u32       Number of pins to configure
* @param[in]   Config_ptr         Pointer to array of pin configuration structures
* @param[in]   NumUnusedPins_u16  Number of unused pins to configure
* @param[in]   UnusedPads_ptr     Pointer to array of unused pad indices
* @param[in]   UnusedPadConfig_ptr Pointer to unused pad configuration
*
* @return      PortHw_StatusType
* @retval      PORT_HW_STATUS_SUCCESS  All pins configured successfully
* @retval      PORT_HW_STATUS_ERROR    Configuration failed
*
* @api
*
* @pre         None
* @post        Pins are configured according to the provided configuration
*
* @implements  PortHw_Init_Activity
*/
PortHw_StatusType PortHw_Init(
    uint32 PinCount_u32,
    const PortHw_PinSettingsConfigType Config_ptr[],
    uint16 NumUnusedPins_u16,
    const uint16* UnusedPads_ptr,
    const PortHw_UnusedPinConfigType* UnusedPadConfig_ptr
);

/**
* @brief       Configures the pin multiplexing (alternate function)
*
* @details     This function sets the pin mux mode for a specific pin.
*              The pin must not be locked before calling this function.
*
* @param[in]   Base_ptr  Pointer to PORT peripheral base address
* @param[in]   Pin_u32   Pin number within the port (0-31)
* @param[in]   Mux_en    Desired mux mode selection
*
* @return      void
*
* @api
*
* @pre         Pin must not be locked (LK bit = 0)
* @post        Pin mux mode is changed
*
* @implements  Port_Hw_SetMuxModeSel_Activity
*/
void PortHw_SetMuxModeSel(
    PORT_Type* const Base_ptr,
    uint32 Pin_u32,
    PortHw_MuxType Mux_en
);

/**
* @brief       Sets the direction of a GPIO pin
*
* @details     This function configures a GPIO pin as input or output.
*
* @param[in]   Base_ptr       Pointer to GPIO peripheral base address
* @param[in]   Pin_u32        Pin number within the port (0-31)
* @param[in]   Direction_en   Desired pin direction
*
* @return      void
*
* @api
*
* @pre         Pin must be configured as GPIO (MUX = 1)
* @post        Pin direction is changed
*
* @implements  Port_Hw_SetPinDirection_Activity
*/
void PortHw_SetPinDirection(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32,
    PortHw_DirectionType Direction_en
);


/**
* @brief       Quickly configures multiple pins with the same configuration
*
* @details     This function uses Global Pin Control registers to configure multiple
*              pins within the same port simultaneously. Can configure either lower
*              16 pins (0-15) or upper 16 pins (16-31).
*
* @param[in]   Base_ptr   Pointer to PORT peripheral base address
* @param[in]   Pins_u16   Bitmask of pins to configure (bit 0 = pin 0/16, bit 15 = pin 15/31)
* @param[in]   Value_u16  Configuration value to apply
* @param[in]   HalfPort_en Selection of lower or upper half of pins
*
* @return      void
*
* @api
*
* @implements  Port_Hw_SetGlobalPinControl_Activity
*/
void PortHw_SetGlobalPinControl(
    PORT_Type* const Base_ptr,
    uint16 Pins_u16,
    uint16 Value_u16,
    PortHw_GlobalControlPinsType GlobalCtrlPins_en
);

/**
* @brief       Writes a value to GPIO output pin
*
* @details     This function sets or clears the output value of a GPIO pin.
*
* @param[in]   Base_ptr  Pointer to GPIO peripheral base address
* @param[in]   Pin_u32   Pin number within the port (0-31)
* @param[in]   Value_u8  Output value (0 = LOW, 1 = HIGH)
*
* @return      void
*
* @api
*
* @pre         Pin must be configured as GPIO output
*
* @implements  Port_Hw_WritePin_Activity
*/
void PortHw_WritePin(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32,
    uint8 Value_u8
);

/**
* @brief       Reads the input value of a GPIO pin
*
* @details     This function reads the current input value of a GPIO pin.
*
* @param[in]   Base_ptr  Pointer to GPIO peripheral base address
* @param[in]   Pin_u32   Pin number within the port (0-31)
*
* @return      uint8
* @retval      0  Pin is LOW
* @retval      1  Pin is HIGH
*
* @api
*
* @implements  Port_Hw_ReadPin_Activity
*/
uint8 PortHw_ReadPin(
    const GPIO_Type* const Base_ptr,
    uint32 Pin_u32
);

/**
* @brief       Toggles the output value of a GPIO pin
*
* @details     This function inverts the current output value of a GPIO pin.
*
* @param[in]   Base_ptr  Pointer to GPIO peripheral base address
* @param[in]   Pin_u32   Pin number within the port (0-31)
*
* @return      void
*
* @api
*
* @pre         Pin must be configured as GPIO output
*
* @implements  Port_Hw_TogglePin_Activity
*/
void PortHw_TogglePin(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32
);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* PORT_HW_H */
