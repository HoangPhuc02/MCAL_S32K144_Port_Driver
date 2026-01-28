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
* @file           Mcal.h
* @implements     Mcal.h_Artifact
* @brief          MCAL common definitions
* @details        Contains common MCAL definitions, Core ID, compiler abstraction and 
*                 processor intrinsics
*
* @addtogroup     BASE_COMPONENT
* @{
*/

#ifndef MCAL_H
#define MCAL_H

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
* @brief Parameters that shall be published within the Mcal header file
*/
#define MCAL_VENDOR_ID                      43U
#define MCAL_MODULE_ID                      0U
#define MCAL_AR_RELEASE_MAJOR_VERSION       21U
#define MCAL_AR_RELEASE_MINOR_VERSION       11U
#define MCAL_AR_RELEASE_REVISION_VERSION    0U
#define MCAL_SW_MAJOR_VERSION               1U
#define MCAL_SW_MINOR_VERSION               0U
#define MCAL_SW_PATCH_VERSION               0U

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
*                               Platform Definitions
-------------------------------------------------------------------------------------------------*/
/**
* @brief ARM Platform definition
*/
#define MCAL_PLATFORM_ARM

/**
* @brief ARM Cortex-M architecture (S32K144)
*/
#define MCAL_ARM_MARCH

/**
* @brief Number of cores in S32K144 (single core)
*/
#define MCAL_NUMBER_OF_CORES    (1U)

/*-------------------------------------------------------------------------------------------------
*                               Core ID Macros
-------------------------------------------------------------------------------------------------*/
/**
* @brief Get current core ID
* @details S32K144 is single core, always returns 0
* @return Core ID (always 0 for S32K144)
*/
#define OsIf_GetCoreID()        ((uint32)0U)

/**
* @brief Alias for compatibility with RTD
*/
#define Mcal_GetCoreID()        OsIf_GetCoreID()

/*-------------------------------------------------------------------------------------------------
*                               Interrupt State Mask
-------------------------------------------------------------------------------------------------*/
/**
* @brief PRIMASK bit 0 for Cortex-M
*/
#define ISR_STATE_MASK          ((uint32)0x00000001UL)

/**
* @brief Check if interrupts are enabled
* @param[in] msr PRIMASK value
* @return TRUE if interrupts enabled, FALSE otherwise
*/
#define ISR_ON(msr)             (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) == (uint32)0U)

/*-------------------------------------------------------------------------------------------------
*                               Cortex-M4 Intrinsics
-------------------------------------------------------------------------------------------------*/
#if defined(__GNUC__)
    /**
    * @brief Read PRIMASK register (GCC)
    * @return Current PRIMASK value
    */
    LOCAL_INLINE uint32 Mcal_GetPrimask(void)
    {
        uint32 f_Result_u32;
        ASM_KEYWORD volatile ("MRS %0, primask" : "=r" (f_Result_u32));
        return f_Result_u32;
    }

    /**
    * @brief Write PRIMASK register (GCC)
    * @param[in] primask Value to write to PRIMASK
    */
    LOCAL_INLINE void Mcal_SetPrimask(uint32 p_Primask_u32)
    {
        ASM_KEYWORD volatile ("MSR primask, %0" :: "r" (p_Primask_u32) : "memory");
    }

    /**
    * @brief Disable interrupts (GCC)
    */
    LOCAL_INLINE void Mcal_DisableAllInterrupts(void)
    {
        ASM_KEYWORD volatile ("CPSID i" ::: "memory");
    }

    /**
    * @brief Enable interrupts (GCC)
    */
    LOCAL_INLINE void Mcal_EnableAllInterrupts(void)
    {
        ASM_KEYWORD volatile ("CPSIE i" ::: "memory");
    }

    /**
    * @brief Data Synchronization Barrier
    */
    LOCAL_INLINE void Mcal_DataSyncBarrier(void)
    {
        ASM_KEYWORD volatile ("DSB" ::: "memory");
    }

    /**
    * @brief Instruction Synchronization Barrier
    */
    LOCAL_INLINE void Mcal_InstructionSyncBarrier(void)
    {
        ASM_KEYWORD volatile ("ISB" ::: "memory");
    }

#elif defined(__ICCARM__)
    #include <intrinsics.h>
    
    #define Mcal_GetPrimask()               __get_PRIMASK()
    #define Mcal_SetPrimask(primask)        __set_PRIMASK(primask)
    #define Mcal_DisableAllInterrupts()     __disable_irq()
    #define Mcal_EnableAllInterrupts()      __enable_irq()
    #define Mcal_DataSyncBarrier()          __DSB()
    #define Mcal_InstructionSyncBarrier()   __ISB()

#else
    /* Default implementation for unknown compiler */
    #define Mcal_GetPrimask()               (0U)
    #define Mcal_SetPrimask(primask)        ((void)(primask))
    #define Mcal_DisableAllInterrupts()     
    #define Mcal_EnableAllInterrupts()      
    #define Mcal_DataSyncBarrier()          
    #define Mcal_InstructionSyncBarrier()   
#endif

/*-------------------------------------------------------------------------------------------------
*                               Suspend/Resume Interrupts
-------------------------------------------------------------------------------------------------*/
/**
* @brief Suspend all interrupts and save state
* @return Saved PRIMASK state
*/
LOCAL_INLINE uint32 Mcal_SuspendAllInterrupts(void)
{
    uint32 f_Msr_u32 = Mcal_GetPrimask();
    Mcal_DisableAllInterrupts();
    return f_Msr_u32;
}

/**
* @brief Resume all interrupts from saved state
* @param[in] msr Saved PRIMASK state
*/
LOCAL_INLINE void Mcal_ResumeAllInterrupts(uint32 p_Msr_u32)
{
    Mcal_SetPrimask(p_Msr_u32);
}

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

#endif /* MCAL_H */
