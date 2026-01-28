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
* @file           OsIf.c
* @implements     OsIf.c_Artifact
* @brief          OS Interface stub implementation
* @details        Provides OS abstraction layer for timers, delays, and counters
*                 Stub implementation using SysTick for bare-metal environment
*
* @addtogroup     OSIF_MODULE
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "OsIf.h"
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_VENDOR_ID_C                    43U
#define OSIF_AR_RELEASE_MAJOR_VERSION_C     21U
#define OSIF_AR_RELEASE_MINOR_VERSION_C     11U
#define OSIF_AR_RELEASE_REVISION_VERSION_C  0U
#define OSIF_SW_MAJOR_VERSION_C             1U
#define OSIF_SW_MINOR_VERSION_C             0U
#define OSIF_SW_PATCH_VERSION_C             0U

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and OsIf header file are of the same vendor */
#if (OSIF_VENDOR_ID_C != OSIF_VENDOR_ID)
    #error "OsIf.c and OsIf.h have different vendor ids"
#endif

/* Check if source file and OsIf header file are of the same Autosar version */
#if ((OSIF_AR_RELEASE_MAJOR_VERSION_C    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_AR_RELEASE_MINOR_VERSION_C    != OSIF_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_AR_RELEASE_REVISION_VERSION_C != OSIF_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of OsIf.c and OsIf.h are different"
#endif

/* Check if source file and OsIf header file are of the same Software version */
#if ((OSIF_SW_MAJOR_VERSION_C != OSIF_SW_MAJOR_VERSION) || \
     (OSIF_SW_MINOR_VERSION_C != OSIF_SW_MINOR_VERSION) || \
     (OSIF_SW_PATCH_VERSION_C != OSIF_SW_PATCH_VERSION))
    #error "Software Version Numbers of OsIf.c and OsIf.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief SysTick Control and Status Register address
*/
#define OSIF_SYSTICK_CSR_ADDR               (0xE000E010UL)

/**
* @brief SysTick Reload Value Register address
*/
#define OSIF_SYSTICK_RVR_ADDR               (0xE000E014UL)

/**
* @brief SysTick Current Value Register address
*/
#define OSIF_SYSTICK_CVR_ADDR               (0xE000E018UL)

/**
* @brief SysTick registers structure
*/
typedef struct
{
    volatile uint32 CSR;    /**< @brief Control and Status Register */
    volatile uint32 RVR;    /**< @brief Reload Value Register */
    volatile uint32 CVR;    /**< @brief Current Value Register */
    volatile uint32 CALIB;  /**< @brief Calibration Value Register */
} OsIf_SysTickType;

/**
* @brief SysTick base pointer
*/
#define OSIF_SYSTICK                        ((OsIf_SysTickType *)OSIF_SYSTICK_CSR_ADDR)

/**
* @brief SysTick CSR bit definitions
*/
#define OSIF_SYSTICK_CSR_ENABLE_MASK        (0x00000001UL)
#define OSIF_SYSTICK_CSR_TICKINT_MASK       (0x00000002UL)
#define OSIF_SYSTICK_CSR_CLKSOURCE_MASK     (0x00000004UL)
#define OSIF_SYSTICK_CSR_COUNTFLAG_MASK     (0x00010000UL)

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#define OSIF_START_SEC_VAR_CLEARED_32
#include "OsIf_MemMap.h"

/**
* @brief Timer frequency in Hz
*/
static uint32 OsIf_l_TimerFreq_u32;

/**
* @brief Software counter for elapsed time
*/
static volatile uint32 OsIf_l_Counter_u32;

/**
* @brief Initialization status
*/
static boolean OsIf_l_Initialized_boo;

#if (OSIF_ENABLE_INTERRUPT_NESTING == STD_ON)
/**
* @brief Interrupt nesting counter
*/
static uint32 OsIf_l_NestingLevel_u32;

/**
* @brief Saved interrupt states for nesting
*/
static uint32 OsIf_l_SavedMsr_aa_u32[OSIF_MAX_INTERRUPT_NESTING];
#else
/**
* @brief Single saved interrupt state
*/
static uint32 OsIf_l_SavedMsr_u32;
#endif /* OSIF_ENABLE_INTERRUPT_NESTING */

#define OSIF_STOP_SEC_VAR_CLEARED_32
#include "OsIf_MemMap.h"

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define OSIF_START_SEC_CODE
#include "OsIf_MemMap.h"

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
/**
* @brief       Initialize SysTick timer
* @details     Configures SysTick for basic timing operations
*
* @return      void
*/
static void OsIf_InitSysTick(void);

/**
* @brief       Get SysTick current value
* @details     Reads the current SysTick counter value
*
* @return      uint32   Current SysTick value
*/
static uint32 OsIf_GetSysTickValue(void);
#endif /* OSIF_USE_SYSTEM_TIMER */

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
/**
* @brief       Initialize SysTick timer
*/
static void OsIf_InitSysTick(void)
{
    /* Disable SysTick during configuration */
    OSIF_SYSTICK->CSR = 0U;

    /* Set reload value (counts down to 0) */
    OSIF_SYSTICK->RVR = OSIF_SYSTICK_LOAD_VALUE;

    /* Clear current value */
    OSIF_SYSTICK->CVR = 0U;

    /* Enable SysTick with processor clock, no interrupt */
    OSIF_SYSTICK->CSR = OSIF_SYSTICK_CSR_ENABLE_MASK | OSIF_SYSTICK_CSR_CLKSOURCE_MASK;
}

/**
* @brief       Get SysTick current value
*/
static uint32 OsIf_GetSysTickValue(void)
{
    return OSIF_SYSTICK->CVR;
}
#endif /* OSIF_USE_SYSTEM_TIMER */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
* @brief       Initialize OsIf module
*/
void OsIf_Init(const void* p_Config_pv)
{
    /* Suppress unused parameter warning */
    (void)p_Config_pv;

    /* Set default timer frequency */
    OsIf_l_TimerFreq_u32 = OSIF_DEFAULT_TIMER_FREQ;

    /* Reset counter */
    OsIf_l_Counter_u32 = 0U;

#if (OSIF_ENABLE_INTERRUPT_NESTING == STD_ON)
    uint8 f_Index_u8;
    OsIf_l_NestingLevel_u32 = 0U;
    for (f_Index_u8 = 0U; f_Index_u8 < OSIF_MAX_INTERRUPT_NESTING; f_Index_u8++)
    {
        OsIf_l_SavedMsr_aa_u32[f_Index_u8] = 0U;
    }
#else
    OsIf_l_SavedMsr_u32 = 0U;
#endif /* OSIF_ENABLE_INTERRUPT_NESTING */

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
    /* Initialize SysTick */
    OsIf_InitSysTick();
#endif /* OSIF_USE_SYSTEM_TIMER */

    /* Set initialization flag */
    OsIf_l_Initialized_boo = TRUE;
}

/*================================================================================================*/
/**
* @brief       Get current counter value
*/
uint32 OsIf_GetCounter(OsIf_CounterType p_SelectedCounter_en)
{
    uint32 f_RetVal_u32 = 0U;

    switch (p_SelectedCounter_en)
    {
        case OSIF_COUNTER_DUMMY:
            /* Simple incrementing counter */
            f_RetVal_u32 = OsIf_l_Counter_u32;
            OsIf_l_Counter_u32++;
            break;

#if (OSIF_USE_SYSTEM_TIMER == STD_ON)
        case OSIF_COUNTER_SYSTEM:
            /* Get SysTick value (counts down, so invert) */
            f_RetVal_u32 = OSIF_SYSTICK_LOAD_VALUE - OsIf_GetSysTickValue();
            break;
#endif /* OSIF_USE_SYSTEM_TIMER */

#if (OSIF_USE_CUSTOM_TIMER == STD_ON)
        case OSIF_COUNTER_CUSTOM:
            /* Custom timer - use software counter */
            f_RetVal_u32 = OsIf_l_Counter_u32;
            OsIf_l_Counter_u32++;
            break;
#endif /* OSIF_USE_CUSTOM_TIMER */

        default:
            /* Invalid counter type - return 0 */
            f_RetVal_u32 = 0U;
            break;
    }

    return f_RetVal_u32;
}

/*================================================================================================*/
/**
* @brief       Get elapsed time since reference
*/
uint32 OsIf_GetElapsed(uint32* p_CurrentRef_pu32, OsIf_CounterType p_SelectedCounter_en)
{
    uint32 f_CurrentVal_u32;
    uint32 f_Elapsed_u32;

    if (NULL_PTR == p_CurrentRef_pu32)
    {
        f_Elapsed_u32 = 0U;
    }
    else
    {
        /* Get current counter value */
        f_CurrentVal_u32 = OsIf_GetCounter(p_SelectedCounter_en);

        /* Calculate elapsed time with wrap-around handling */
        if (f_CurrentVal_u32 >= *p_CurrentRef_pu32)
        {
            f_Elapsed_u32 = f_CurrentVal_u32 - *p_CurrentRef_pu32;
        }
        else
        {
            /* Counter wrapped around */
            f_Elapsed_u32 = (OSIF_COUNTER_MAX_VALUE - *p_CurrentRef_pu32) + f_CurrentVal_u32 + 1U;
        }

        /* Update reference */
        *p_CurrentRef_pu32 = f_CurrentVal_u32;
    }

    return f_Elapsed_u32;
}

/*================================================================================================*/
/**
* @brief       Set timer frequency
*/
void OsIf_SetTimerFrequency(uint32 p_Freq_u32)
{
    if (p_Freq_u32 > 0U)
    {
        OsIf_l_TimerFreq_u32 = p_Freq_u32;
    }
}

/*================================================================================================*/
/**
* @brief       Convert microseconds to ticks
*/
uint32 OsIf_MicrosToTicks(uint32 p_Micros_u32, OsIf_CounterType p_SelectedCounter_en)
{
    uint32 f_Ticks_u32;
    
    (void)p_SelectedCounter_en;

    if (OsIf_l_TimerFreq_u32 > 0U)
    {
        /* Calculate ticks: ticks = micros * (freq / 1000000) */
        /* Use 64-bit intermediate to avoid overflow */
        uint64 f_Temp_u64 = (uint64)p_Micros_u32 * (uint64)OsIf_l_TimerFreq_u32;
        f_Ticks_u32 = (uint32)(f_Temp_u64 / 1000000ULL);
    }
    else
    {
        f_Ticks_u32 = p_Micros_u32;
    }

    return f_Ticks_u32;
}

/*================================================================================================*/
/**
* @brief       Suspend all interrupts
*/
void OsIf_SuspendAllInterrupts(void)
{
#if (OSIF_ENABLE_INTERRUPT_NESTING == STD_ON)
    if (OsIf_l_NestingLevel_u32 < OSIF_MAX_INTERRUPT_NESTING)
    {
        /* Save current interrupt state */
        OsIf_l_SavedMsr_aa_u32[OsIf_l_NestingLevel_u32] = Mcal_GetPrimask();
        OsIf_l_NestingLevel_u32++;
    }
#else
    /* Save current interrupt state */
    OsIf_l_SavedMsr_u32 = Mcal_GetPrimask();
#endif /* OSIF_ENABLE_INTERRUPT_NESTING */

    /* Disable all interrupts */
    Mcal_DisableAllInterrupts();
}

/*================================================================================================*/
/**
* @brief       Resume all interrupts
*/
void OsIf_ResumeAllInterrupts(void)
{
#if (OSIF_ENABLE_INTERRUPT_NESTING == STD_ON)
    if (OsIf_l_NestingLevel_u32 > 0U)
    {
        OsIf_l_NestingLevel_u32--;
        /* Restore saved interrupt state */
        Mcal_SetPrimask(OsIf_l_SavedMsr_aa_u32[OsIf_l_NestingLevel_u32]);
    }
#else
    /* Restore saved interrupt state */
    Mcal_SetPrimask(OsIf_l_SavedMsr_u32);
#endif /* OSIF_ENABLE_INTERRUPT_NESTING */
}

/*================================================================================================*/
/**
* @brief       Get core ID
*/
uint32 OsIf_GetCoreID(void)
{
    /* S32K144 is single core, always return 0 */
    return 0U;
}

#define OSIF_STOP_SEC_CODE
#include "OsIf_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
