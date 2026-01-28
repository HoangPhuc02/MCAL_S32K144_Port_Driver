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
*   @file    Port_Hw.c
*
*   @brief   Port Hardware Abstraction Layer source file
*   @details This file contains the implementation of Port Hardware driver functions.
*            Based on Port_Ci_Port_Ip.c from NXP RTD
*
*   @addtogroup Port_HW
*   @{
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
#include "Port_Hw.h"
#include "Port.h"
#include "S32K144.h"
#include "SchM_Port.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
*/
#define PORT_HW_VENDOR_ID_C                    43
#define PORT_HW_AR_RELEASE_MAJOR_VERSION_C     21
#define PORT_HW_AR_RELEASE_MINOR_VERSION_C     11
#define PORT_HW_AR_RELEASE_REVISION_VERSION_C  0
#define PORT_HW_SW_MAJOR_VERSION_C             1
#define PORT_HW_SW_MINOR_VERSION_C             0
#define PORT_HW_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Port_Hw.c and Port_Hw.h are of the same vendor */
#if (PORT_HW_VENDOR_ID_C != PORT_HW_VENDOR_ID_H)
    #error "Port_Hw.c and Port_Hw.h have different vendor ids"
#endif

/* Check if Port_Hw.c and Port_Hw.h are of the same Autosar version */
#if ((PORT_HW_AR_RELEASE_MAJOR_VERSION_C    != PORT_HW_AR_RELEASE_MAJOR_VERSION_H)  || \
     (PORT_HW_AR_RELEASE_MINOR_VERSION_C    != PORT_HW_AR_RELEASE_MINOR_VERSION_H)  || \
     (PORT_HW_AR_RELEASE_REVISION_VERSION_C != PORT_HW_AR_RELEASE_REVISION_VERSION_H)  \
    )
    #error "Autosar Version Numbers of Port_Hw.c and Port_Hw.h are different"
#endif

/* Check if Port_Hw.c and Port_Hw.h are of the same software version */
#if ((PORT_HW_SW_MAJOR_VERSION_C != PORT_HW_SW_MAJOR_VERSION_H) || \
     (PORT_HW_SW_MINOR_VERSION_C != PORT_HW_SW_MINOR_VERSION_H) || \
     (PORT_HW_SW_PATCH_VERSION_C != PORT_HW_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Port_Hw.c and Port_Hw.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"

/**
* @brief Base address array for PORT instances
*/
PORT_Type* const PortHw_g_PortBaseAddr_ptr[PORT_HW_PORT_COUNT_U8] =
{
    IP_PORTA,  /**< @brief Port A base address */
    IP_PORTB,  /**< @brief Port B base address */
    IP_PORTC,  /**< @brief Port C base address */
    IP_PORTD,  /**< @brief Port D base address */
    IP_PORTE   /**< @brief Port E base address */
};

/**
* @brief Base address array for GPIO instances
*/
GPIO_Type* const PortHw_g_GpioBaseAddr_ptr[PORT_HW_PORT_COUNT_U8] =
{
    IP_PTA,    /**< @brief GPIO A base address */
	IP_PTB,    /**< @brief GPIO B base address */
	IP_PTC,    /**< @brief GPIO C base address */
	IP_PTD,    /**< @brief GPIO D base address */
	IP_PTE     /**< @brief GPIO E base address */
};

#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief       Initializes a single pin with the given configuration
*
* @details     Internal function to configure one pin with all its settings
*
* @param[in]   Config_ptr  Pointer to pin configuration structure
*
* @return      void
*/
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"
static void PortHw_PinInit(const PortHw_PinSettingsConfigType* Config_ptr);

static void PortHw_Init_UnusedPins(
    uint16 NumUnusedPins_u16,
    const uint16* UnusedPads_ptr,
    const PortHw_UnusedPinConfigType* UnusedPadConfig_ptr
);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief       Initializes a single pin with the given configuration
* @details     This internal function configures a single pin including:
*              - Pull configuration
*              - Drive strength
*              - Lock register
*              - Passive filter
*              - Mux mode
*              - Digital filter
*              - GPIO direction and initial value
*
* @param[in]   Config_ptr  Pointer to pin configuration structure
*
* @return      void
*/
static void PortHw_PinInit(const PortHw_PinSettingsConfigType* Config_ptr)
{
    uint32 f_PinsValues_u32 = 0U;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Config_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Config_ptr->PinPortIndex_u32 < PORT_HW_PINS_PER_PORT_U8);
    /* Check if pin is not locked before configuring */
    PORT_HW_DEV_ASSERT((Config_ptr->PortBase_ptr->PCR[Config_ptr->PinPortIndex_u32] & PORT_PCR_LK_MASK) == 0U);

    /* Configure pull resistor */
    if (Config_ptr->PullConfig_en != PORT_HW_PULL_NOT_ENABLED)
    {
        f_PinsValues_u32 |= PORT_PCR_PE(1U);
        f_PinsValues_u32 |= PORT_PCR_PS(Config_ptr->PullConfig_en);
    }

    /* Configure drive strength */
    f_PinsValues_u32 |= PORT_PCR_DSE(Config_ptr->DriveStrength_en);

    /* Configure lock register */
    f_PinsValues_u32 |= PORT_PCR_LK(Config_ptr->LockRegister_en);

    /* Configure pin mux */
    f_PinsValues_u32 |= PORT_PCR_MUX(Config_ptr->Mux_en);

    /* Configure GPIO if mux is set to GPIO mode */
    if (PORT_HW_MUX_AS_GPIO == Config_ptr->Mux_en)
    {
        /* Configure output direction */
        if (PORT_HW_PIN_OUT == Config_ptr->Direction_en)
        {
            /* Set initial output value */
            if ((uint8)1U == Config_ptr->InitValue_u8)
            {
                SchM_Enter_Port_PORT_EXCLUSIVE_AREA_01();
                Config_ptr->GpioBase_ptr->PSOR = (1UL << Config_ptr->PinPortIndex_u32);
                SchM_Exit_Port_PORT_EXCLUSIVE_AREA_01();
            }
            else if((uint8)0U == Config_ptr->InitValue_u8)
            {
                SchM_Enter_Port_PORT_EXCLUSIVE_AREA_02();
                Config_ptr->GpioBase_ptr->PCOR = (1UL << Config_ptr->PinPortIndex_u32);
                SchM_Exit_Port_PORT_EXCLUSIVE_AREA_02();
            }
            else
            {
                /* No action to be done */
            }

            /* Set pin direction as output */
            Config_ptr->GpioBase_ptr->PDDR |= (1UL << Config_ptr->PinPortIndex_u32);
        }
        /* Configure input or high-z direction */
        else
        {
            /* Clear pin direction (set as input) */
            Config_ptr->GpioBase_ptr->PDDR &= ~(1UL << Config_ptr->PinPortIndex_u32);

            /* Enable input for normal input mode */
            Config_ptr->GpioBase_ptr->PIDR &= ~(1UL << Config_ptr->PinPortIndex_u32);

        }
    }

    /* Write configuration to PCR register */
    Config_ptr->PortBase_ptr->PCR[Config_ptr->PinPortIndex_u32] = f_PinsValues_u32;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*FUNCTION**********************************************************************
*
* Function Name : PortHw_Init
* Description   : Initializes multiple pins with the given configuration array
*                 and unused pins configuration
*
* @implements PortHw_Init_Activity
******************************************************************************/
void PortHw_Init(
    uint32 PinCount_u32,
    const PortHw_PinSettingsConfigType Config_ptr[],
    uint16 NumUnusedPins_u16,
    const uint16* UnusedPads_ptr,
    const PortHw_UnusedPinConfigType* UnusedPadConfig_ptr
)
{
    uint32 f_Index_u32;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Config_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(PinCount_u32 > 0U);

    /* Initialize each configured pin with its configuration */
    for (f_Index_u32 = 0U; f_Index_u32 < PinCount_u32; f_Index_u32++)
    {
        PortHw_PinInit(&Config_ptr[f_Index_u32]);
    }

    /* Initialize All Unused Port Pins */
    if ((NumUnusedPins_u16 > 0U) && (UnusedPads_ptr != NULL_PTR) && (UnusedPadConfig_ptr != NULL_PTR))
    {
        PortHw_Init_UnusedPins(NumUnusedPins_u16, UnusedPads_ptr, UnusedPadConfig_ptr);
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : PortHw_Init_UnusedPins
* Description   : Initializes all unused port pins with the configuration
*                 set pointed to by the parameter UnusedPadConfig_ptr
*
* @implements PortHw_Init_UnusedPins_Activity
******************************************************************************/
static void PortHw_Init_UnusedPins(
    uint16 NumUnusedPins_u16,
    const uint16* UnusedPads_ptr,
    const PortHw_UnusedPinConfigType* UnusedPadConfig_ptr
)
{
    uint16 f_PinIndex_u16;
    uint32 f_PortIndex_u32;
    uint32 f_PinInPort_u32;
    uint8  f_OutputValue_u8;
    uint32 f_PcrValue_u32;
    PortHw_DirectionType f_Direction_en;

    /* Get unused pin configuration */
    f_OutputValue_u8 = UnusedPadConfig_ptr->OutputValue_u8;
    f_PcrValue_u32   = UnusedPadConfig_ptr->PinControlRegister_u32;
    f_Direction_en   = UnusedPadConfig_ptr->Direction_en;

    /* Initialize All UnUsed pins */
    for (f_PinIndex_u16 = 0U; f_PinIndex_u16 < NumUnusedPins_u16; f_PinIndex_u16++)
    {
        /* Get port index and pin index within the port */
        f_PortIndex_u32 = PORT_HW_GET_PORT_U32(UnusedPads_ptr[f_PinIndex_u16]);
        f_PinInPort_u32 = PORT_HW_GET_PIN_U32(UnusedPads_ptr[f_PinIndex_u16]);

        /* Check if the direction of the pin is OUTPUT */
        if (PORT_HW_PIN_OUT == f_Direction_en)
        {
            /* Set pin to High value */
            if ((uint8)1U == f_OutputValue_u8)
            {
                SchM_Enter_Port_PORT_EXCLUSIVE_AREA_03();
                PortHw_g_GpioBaseAddr_ptr[f_PortIndex_u32]->PSOR = ((uint32)1U << f_PinInPort_u32);
                SchM_Exit_Port_PORT_EXCLUSIVE_AREA_03();
            }
            else if ((uint8)0U == f_OutputValue_u8)
            {
                SchM_Enter_Port_PORT_EXCLUSIVE_AREA_04();
                PortHw_g_GpioBaseAddr_ptr[f_PortIndex_u32]->PCOR = ((uint32)1U << f_PinInPort_u32);
                SchM_Exit_Port_PORT_EXCLUSIVE_AREA_04();
            }
            else
            {
                /* No action to be done */
            }

            /* Set pin as output */
            SchM_Enter_Port_PORT_EXCLUSIVE_AREA_05();
            PortHw_g_GpioBaseAddr_ptr[f_PortIndex_u32]->PDDR |= ((uint32)1U << f_PinInPort_u32);
            SchM_Exit_Port_PORT_EXCLUSIVE_AREA_05();
        }
        /* The direction of pin is INPUT */
        else
        {
            /* Set pin as input */
            SchM_Enter_Port_PORT_EXCLUSIVE_AREA_06();
            PortHw_g_GpioBaseAddr_ptr[f_PortIndex_u32]->PDDR &= ~((uint32)1U << f_PinInPort_u32);
            SchM_Exit_Port_PORT_EXCLUSIVE_AREA_06();

            /* Enable input */
            SchM_Enter_Port_PORT_EXCLUSIVE_AREA_07();
            PortHw_g_GpioBaseAddr_ptr[f_PortIndex_u32]->PIDR &= ~((uint32)1U << f_PinInPort_u32);
            SchM_Exit_Port_PORT_EXCLUSIVE_AREA_07();
        }

        /* Write PCR configuration from Configuration tool */
        PortHw_g_PortBaseAddr_ptr[f_PortIndex_u32]->PCR[f_PinInPort_u32] = f_PcrValue_u32;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : PortHw_SetMuxModeSel
* Description   : Configures the pin multiplexing (alternate function)
*                 Based on Port_Ipw_SetPinMode
*
* @implements PortHw_SetMuxModeSel_Activity
******************************************************************************/
void PortHw_SetMuxModeSel(
    PORT_Type* const Base_ptr,
    uint32 Pin_u32,
    PortHw_MuxType Mux_en
)
{
    uint32 f_RegValue_u32;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);
    PORT_HW_DEV_ASSERT((Base_ptr->PCR[Pin_u32] & PORT_PCR_LK_MASK) == 0U);

    /* Enter critical section - Sets the port pin mode */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_08();

    /* Read current PCR value, modify MUX field, write back */
    f_RegValue_u32 = Base_ptr->PCR[Pin_u32];
    f_RegValue_u32 &= ~PORT_PCR_MUX_MASK;
    f_RegValue_u32 |= PORT_PCR_MUX(Mux_en);
    Base_ptr->PCR[Pin_u32] = f_RegValue_u32;

    /* Exit critical section */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_08();
}

/*FUNCTION**********************************************************************
*
* Function Name : PortHw_SetPinDirection
* Description   : Sets the direction of a GPIO pin
*                 Based on Port_Ipw_SetPinDirection
*
* @implements PortHw_SetPinDirection_Activity
******************************************************************************/
void PortHw_SetPinDirection(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32,
    PortHw_DirectionType Direction_en
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    /* Configures Port Pin as Output */
    if (PORT_HW_PIN_OUT == Direction_en)
    {
        SchM_Enter_Port_PORT_EXCLUSIVE_AREA_09();
        Base_ptr->PDDR |= ((uint32)1UL << Pin_u32);
        SchM_Exit_Port_PORT_EXCLUSIVE_AREA_09();
    }
    /* Configures Port Pin as Input or High-Z */
    else if (PORT_HW_PIN_IN == Direction_en)
    {
        /* Set pin as input - clear direction bit */
        SchM_Enter_Port_PORT_EXCLUSIVE_AREA_09();
        Base_ptr->PDDR &= ~((uint32)1UL << Pin_u32);
        SchM_Exit_Port_PORT_EXCLUSIVE_AREA_09();

        /* Enable/Disable input based on direction mode */
        SchM_Enter_Port_PORT_EXCLUSIVE_AREA_10();
        /* First enable input */
        Base_ptr->PIDR &= ~((uint32)1UL << Pin_u32);

        /* Check if the pin is HIGH-Z. In this case disable port input in PIDR register */
        SchM_Exit_Port_PORT_EXCLUSIVE_AREA_10();
    }
    else
    {
        /* Do nothing for PORT_HW_PIN_DISABLED or invalid direction */
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_SetGlobalPinControl
* Description   : Quickly configures multiple pins with the same configuration
*
* @implements Port_Hw_SetGlobalPinControl_Activity
******************************************************************************/
void PortHw_SetGlobalPinControl(
    PORT_Type* const Base_ptr,
    uint16 Pins_u16,
    uint16 Value_u16,
    PortHw_GlobalControlPinsType GlobalCtrlPins_en
)
{
    uint16 f_Mask_u16 = 0U;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);

    /* Build mask with valid PCR bits */
    f_Mask_u16 |= PORT_PCR_PS_MASK;
    f_Mask_u16 |= PORT_PCR_PE_MASK;
    f_Mask_u16 |= PORT_PCR_PFE_MASK;
    f_Mask_u16 |= PORT_PCR_DSE_MASK;
    f_Mask_u16 |= PORT_PCR_MUX_MASK;
    f_Mask_u16 |= PORT_PCR_LK_MASK;
    f_Mask_u16 &= Value_u16;

    /* Apply configuration to selected half of pins */
    switch (GlobalCtrlPins_en)
    {
        case PORT_HW_GLOBAL_LOWER_HALF:
            /* Configure lower 16 pins (0-15) */
            Base_ptr->GPCLR = (((uint32)Pins_u16) << PORT_GPCLR_GPWE_SHIFT) | (uint32)f_Mask_u16;
            break;

        case PORT_HW_GLOBAL_UPPER_HALF:
            /* Configure upper 16 pins (16-31) */
            Base_ptr->GPCHR = (((uint32)Pins_u16) << PORT_GPCHR_GPWE_SHIFT) | (uint32)f_Mask_u16;
            break;

        default:
            /* Invalid half port selection */
            PORT_HW_DEV_ASSERT(FALSE);
            break;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_WritePin
* Description   : Writes a value to GPIO output pin
*
* @implements Port_Hw_WritePin_Activity
******************************************************************************/
void PortHw_WritePin(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32,
    uint8 Value_u8
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    if (Value_u8 != 0U)
    {
        /* Set pin high using Port Set Output Register */
        Base_ptr->PSOR = (1UL << Pin_u32);
    }
    else
    {
        /* Set pin low using Port Clear Output Register */
        Base_ptr->PCOR = (1UL << Pin_u32);
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_ReadPin
* Description   : Reads the input value of a GPIO pin
*
* @implements Port_Hw_ReadPin_Activity
******************************************************************************/
uint8 PortHw_ReadPin(
    const GPIO_Type* const Base_ptr,
    uint32 Pin_u32
)
{
    uint8 f_RetVal_u8;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    /* Read pin value from Port Data Input Register */
    f_RetVal_u8 = (uint8)((Base_ptr->PDIR >> Pin_u32) & 1U);

    return f_RetVal_u8;
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_TogglePin
* Description   : Toggles the output value of a GPIO pin
*
* @implements Port_Hw_TogglePin_Activity
******************************************************************************/
void PortHw_TogglePin(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    /* Toggle pin using Port Toggle Output Register */
    Base_ptr->PTOR = (1UL << Pin_u32);
}

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
