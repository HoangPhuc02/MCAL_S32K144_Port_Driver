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
/**
* @brief Base address array for PORT instances
*/
PORT_Type* const Port_Hw_g_PortBaseAddr_ptr[PORT_HW_PORT_COUNT_U8] =
{
    PORTA,  /**< @brief Port A base address */
    PORTB,  /**< @brief Port B base address */
    PORTC,  /**< @brief Port C base address */
    PORTD,  /**< @brief Port D base address */
    PORTE   /**< @brief Port E base address */
};

/**
* @brief Base address array for GPIO instances
*/
GPIO_Type* const Port_Hw_g_GpioBaseAddr_ptr[PORT_HW_PORT_COUNT_U8] =
{
    PTA,    /**< @brief GPIO A base address */
    PTB,    /**< @brief GPIO B base address */
    PTC,    /**< @brief GPIO C base address */
    PTD,    /**< @brief GPIO D base address */
    PTE     /**< @brief GPIO E base address */
};

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
* @param[in]   Config_pst  Pointer to pin configuration structure
*
* @return      void
*/
static void Port_Hw_PinInit(const Port_Hw_PinSettingsConfigType* Config_pst);

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
* @param[in]   Config_pst  Pointer to pin configuration structure
*
* @return      void
*/
static void Port_Hw_PinInit(const Port_Hw_PinSettingsConfigType* Config_pst)
{
    uint32 f_PinsValues_u32 = 0U;
    uint32 f_DigitalFilters_u32;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Config_pst != NULL_PTR);
    PORT_HW_DEV_ASSERT(Config_pst->PinPortIdx_u32 < PORT_HW_PINS_PER_PORT_U8);
    /* Check if pin is not locked before configuring */
    PORT_HW_DEV_ASSERT((Config_pst->PortBase_ptr->PCR[Config_pst->PinPortIdx_u32] & PORT_PCR_LK_MASK) == 0U);

    /* Configure pull resistor */
    if (Config_pst->PullConfig_en != PORT_HW_PULL_NOT_ENABLED)
    {
        f_PinsValues_u32 |= PORT_PCR_PE(1U);
        f_PinsValues_u32 |= PORT_PCR_PS(Config_pst->PullConfig_en);
    }

    /* Configure drive strength */
    f_PinsValues_u32 |= PORT_PCR_DSE(Config_pst->DriveStrength_en);

    /* Configure lock register */
    f_PinsValues_u32 |= PORT_PCR_LK(Config_pst->LockRegister_en);

    /* Configure passive filter */
    f_PinsValues_u32 |= PORT_PCR_PFE(Config_pst->PassiveFilter_boo ? 1U : 0U);

    /* Configure pin mux */
    f_PinsValues_u32 |= PORT_PCR_MUX(Config_pst->Mux_en);

    /* Configure digital filter */
    f_DigitalFilters_u32 = Config_pst->PortBase_ptr->DFER;
    f_DigitalFilters_u32 &= ~(1UL << Config_pst->PinPortIdx_u32);
    f_DigitalFilters_u32 |= ((uint32)(Config_pst->DigitalFilter_boo ? 1U : 0U) << Config_pst->PinPortIdx_u32);
    Config_pst->PortBase_ptr->DFER = f_DigitalFilters_u32;

    /* Configure GPIO if mux is set to GPIO mode */
    if (PORT_HW_MUX_AS_GPIO == Config_pst->Mux_en)
    {
        /* Configure output direction */
        if (PORT_HW_PIN_OUT == Config_pst->Direction_en)
        {
            /* Set initial output value */
            if ((uint8)1U == Config_pst->InitValue_u8)
            {
                Config_pst->GpioBase_ptr->PSOR = (1UL << Config_pst->PinPortIdx_u32);
            }
            else
            {
                Config_pst->GpioBase_ptr->PCOR = (1UL << Config_pst->PinPortIdx_u32);
            }

            /* Set pin direction as output */
            Config_pst->GpioBase_ptr->PDDR |= (1UL << Config_pst->PinPortIdx_u32);
        }
        /* Configure input or high-z direction */
        else
        {
            /* Clear pin direction (set as input) */
            Config_pst->GpioBase_ptr->PDDR &= ~(1UL << Config_pst->PinPortIdx_u32);

            /* Enable input for normal input mode */
            Config_pst->GpioBase_ptr->PIDR &= ~(1UL << Config_pst->PinPortIdx_u32);

            /* Disable input for high-z mode */
            if (PORT_HW_PIN_HIGH_Z == Config_pst->Direction_en)
            {
                Config_pst->GpioBase_ptr->PIDR |= (1UL << Config_pst->PinPortIdx_u32);
            }
        }
    }

    /* Write configuration to PCR register */
    Config_pst->PortBase_ptr->PCR[Config_pst->PinPortIdx_u32] = f_PinsValues_u32;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_Init
* Description   : Initializes multiple pins with the given configuration array
*
* @implements Port_Hw_Init_Activity
******************************************************************************/
Port_Hw_StatusType Port_Hw_Init(
    uint32 PinCount_u32,
    const Port_Hw_PinSettingsConfigType Config_pst[]
)
{
    uint32 f_Index_u32;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Config_pst != NULL_PTR);
    PORT_HW_DEV_ASSERT(PinCount_u32 > 0U);

    /* Initialize each pin with its configuration */
    for (f_Index_u32 = 0U; f_Index_u32 < PinCount_u32; f_Index_u32++)
    {
        Port_Hw_PinInit(&Config_pst[f_Index_u32]);
    }

    return PORT_HW_STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_SetMuxModeSel
* Description   : Configures the pin multiplexing (alternate function)
*
* @implements Port_Hw_SetMuxModeSel_Activity
******************************************************************************/
void Port_Hw_SetMuxModeSel(
    PORT_Type* const Base_ptr,
    uint32 Pin_u32,
    Port_Hw_MuxType Mux_en
)
{
    uint32 f_RegValue_u32;

    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);
    PORT_HW_DEV_ASSERT((Base_ptr->PCR[Pin_u32] & PORT_PCR_LK_MASK) == 0U);

    /* Read current PCR value, modify MUX field, write back */
    f_RegValue_u32 = Base_ptr->PCR[Pin_u32];
    f_RegValue_u32 &= ~PORT_PCR_MUX_MASK;
    f_RegValue_u32 |= PORT_PCR_MUX(Mux_en);
    Base_ptr->PCR[Pin_u32] = f_RegValue_u32;
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_SetPinDirection
* Description   : Sets the direction of a GPIO pin
*
* @implements Port_Hw_SetPinDirection_Activity
******************************************************************************/
void Port_Hw_SetPinDirection(
    GPIO_Type* const Base_ptr,
    uint32 Pin_u32,
    Port_Hw_DirectionType Direction_en
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    if (PORT_HW_PIN_OUT == Direction_en)
    {
        /* Set pin as output */
        Base_ptr->PDDR |= (1UL << Pin_u32);
    }
    else
    {
        /* Set pin as input */
        Base_ptr->PDDR &= ~(1UL << Pin_u32);

        /* Enable input */
        Base_ptr->PIDR &= ~(1UL << Pin_u32);

        /* Disable input for high-z mode */
        if (PORT_HW_PIN_HIGH_Z == Direction_en)
        {
            Base_ptr->PIDR |= (1UL << Pin_u32);
        }
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_EnableDigitalFilter
* Description   : Enables digital filter for a specific pin
*
* @implements Port_Hw_EnableDigitalFilter_Activity
******************************************************************************/
void Port_Hw_EnableDigitalFilter(
    PORT_Type* const Base_ptr,
    uint32 Pin_u32
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    /* Set digital filter enable bit for the pin */
    Base_ptr->DFER |= (1UL << Pin_u32);
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_DisableDigitalFilter
* Description   : Disables digital filter for a specific pin
*
* @implements Port_Hw_DisableDigitalFilter_Activity
******************************************************************************/
void Port_Hw_DisableDigitalFilter(
    PORT_Type* const Base_ptr,
    uint32 Pin_u32
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Pin_u32 < PORT_HW_PINS_PER_PORT_U8);

    /* Clear digital filter enable bit for the pin */
    Base_ptr->DFER &= ~(1UL << Pin_u32);
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_ConfigDigitalFilter
* Description   : Configures digital filter with given parameters
*
* @implements Port_Hw_ConfigDigitalFilter_Activity
******************************************************************************/
void Port_Hw_ConfigDigitalFilter(
    PORT_Type* const Base_ptr,
    const Port_Hw_DigitalFilterConfigType* Config_pst
)
{
    /* Validate input parameters */
    PORT_HW_DEV_ASSERT(Base_ptr != NULL_PTR);
    PORT_HW_DEV_ASSERT(Config_pst != NULL_PTR);
    PORT_HW_DEV_ASSERT(Config_pst->Width_u8 <= PORT_DFWR_FILT_MASK);

    /* Configure digital filter clock source */
    Base_ptr->DFCR = PORT_DFCR_CS(Config_pst->Clock_u8);

    /* Configure digital filter width */
    Base_ptr->DFWR = PORT_DFWR_FILT(Config_pst->Width_u8);
}

/*FUNCTION**********************************************************************
*
* Function Name : Port_Hw_SetGlobalPinControl
* Description   : Quickly configures multiple pins with the same configuration
*
* @implements Port_Hw_SetGlobalPinControl_Activity
******************************************************************************/
void Port_Hw_SetGlobalPinControl(
    PORT_Type* const Base_ptr,
    uint16 Pins_u16,
    uint16 Value_u16,
    Port_Hw_GlobalControlPinsType HalfPort_en
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
    switch (HalfPort_en)
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
void Port_Hw_WritePin(
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
uint8 Port_Hw_ReadPin(
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
void Port_Hw_TogglePin(
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

#ifdef __cplusplus
}
#endif

/** @} */
