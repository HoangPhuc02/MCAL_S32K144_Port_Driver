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
* @file           OsIf.h
* @implements     OsIf.h_Artifact
* @brief          OS Interface stub header
* @details        Provides OS abstraction layer for timers, delays, and counters
*                 Stub implementation for bare-metal environment
*
* @addtogroup     OSIF_MODULE
* @{
*/

#ifndef OSIF_H
#define OSIF_H

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
#include "OsIf_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the OsIf header file
*/
#define OSIF_VENDOR_ID                      43U
#define OSIF_MODULE_ID                      255U
#define OSIF_AR_RELEASE_MAJOR_VERSION       21U
#define OSIF_AR_RELEASE_MINOR_VERSION       11U
#define OSIF_AR_RELEASE_REVISION_VERSION    0U
#define OSIF_SW_MAJOR_VERSION               1U
#define OSIF_SW_MINOR_VERSION               0U
#define OSIF_SW_PATCH_VERSION               0U

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/**
* @brief OsIf Counter type
* @details Defines the type of counter to use
*/
typedef enum
{
    OSIF_COUNTER_DUMMY  = 0U,   /**< @brief Dummy counter (no real timing) */
    OSIF_COUNTER_SYSTEM = 1U,   /**< @brief System counter (SysTick) */
    OSIF_COUNTER_CUSTOM = 2U    /**< @brief Custom counter (user defined) */
} OsIf_CounterType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define OSIF_START_SEC_CODE
#include "OsIf_MemMap.h"

/**
* @brief       Initialize OsIf module
* @details     Initializes the OsIf module. Should be called during startup,
*              before any other MCAL initialization except Mcu.
*
* @param[in]   Config   Pointer to configuration (unused in stub)
*
* @return      void
*
* @api
*
* @pre         None
* @post        OsIf module is initialized
*
* @implements  OsIf_Init_Activity
*/
void OsIf_Init(const void* p_Config_pv);

/**
* @brief       Get current counter value
* @details     Returns the current value of the selected counter
*
* @param[in]   SelectedCounter   Type of counter to read
*
* @return      uint32   Current counter value
*
* @api
*
* @pre         OsIf must be initialized
* @post        None
*
* @implements  OsIf_GetCounter_Activity
*/
uint32 OsIf_GetCounter(OsIf_CounterType p_SelectedCounter_en);

/**
* @brief       Get elapsed time since reference
* @details     Returns elapsed time and updates reference counter
*
* @param[in,out]   CurrentRef        Pointer to reference counter value (updated)
* @param[in]       SelectedCounter   Type of counter to use
*
* @return      uint32   Elapsed ticks since reference
*
* @api
*
* @pre         OsIf must be initialized
* @post        CurrentRef is updated with current counter value
*
* @implements  OsIf_GetElapsed_Activity
*/
uint32 OsIf_GetElapsed(uint32* p_CurrentRef_pu32, OsIf_CounterType p_SelectedCounter_en);

/**
* @brief       Set timer frequency
* @details     Sets the timer frequency for conversion functions
*
* @param[in]   Freq   Timer frequency in Hz
*
* @return      void
*
* @api
*
* @pre         None
* @post        Timer frequency is updated
*
* @implements  OsIf_SetTimerFrequency_Activity
*/
void OsIf_SetTimerFrequency(uint32 p_Freq_u32);

/**
* @brief       Convert microseconds to ticks
* @details     Converts a time value in microseconds to timer ticks
*
* @param[in]   Micros            Time in microseconds
* @param[in]   SelectedCounter   Type of counter
*
* @return      uint32   Equivalent ticks
*
* @api
*
* @pre         Timer frequency must be set
* @post        None
*
* @implements  OsIf_MicrosToTicks_Activity
*/
uint32 OsIf_MicrosToTicks(uint32 p_Micros_u32, OsIf_CounterType p_SelectedCounter_en);

/**
* @brief       Suspend all interrupts
* @details     Disables all interrupts (global interrupt disable)
*
* @return      void
*
* @api
*
* @pre         None
* @post        All interrupts are disabled
*
* @implements  OsIf_SuspendAllInterrupts_Activity
*/
void OsIf_SuspendAllInterrupts(void);

/**
* @brief       Resume all interrupts
* @details     Enables all interrupts (global interrupt enable)
*
* @return      void
*
* @api
*
* @pre         OsIf_SuspendAllInterrupts must have been called
* @post        All interrupts are re-enabled
*
* @implements  OsIf_ResumeAllInterrupts_Activity
*/
void OsIf_ResumeAllInterrupts(void);

/**
* @brief       Get core ID
* @details     Returns the current core ID (always 0 for single-core S32K144)
*
* @return      uint32   Core ID (0)
*
* @api
*
* @pre         None
* @post        None
*
* @implements  OsIf_GetCoreID_Activity
*/
uint32 OsIf_GetCoreID(void);

#define OSIF_STOP_SEC_CODE
#include "OsIf_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* OSIF_H */
