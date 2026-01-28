/*==================================================================================================
* Project : MCAL_PORT_S32K144
* Platform : CORTEXM
* Peripheral : PORT
* Dependencies : none
*
* Autosar Version : 21.11.0
* Autosar Revision : ASR_REL_4_4_REV_0000
* Autosar Conf.Variant :
* SW Version : 1.0.0
* Build Version : 
*
* Author: PhucPH32
==================================================================================================*/
/**
* @file Port.c
*
* @implements Port.c_Artifact
* @brief Autosar Port driver main source file
* @details Port driver file that contains the implementation of the interface functions
*
* @addtogroup Port_HLD
* @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Port.h"

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    #include "Det.h"
#endif

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
*/
#define PORT_VENDOR_ID_C                    43
#define PORT_AR_RELEASE_MAJOR_VERSION_C     21
#define PORT_AR_RELEASE_MINOR_VERSION_C     11
#define PORT_AR_RELEASE_REVISION_VERSION_C  0
#define PORT_SW_MAJOR_VERSION_C             1
#define PORT_SW_MINOR_VERSION_C             0
#define PORT_SW_PATCH_VERSION_C             0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if source file and Port header file are of the same vendor */
#if (PORT_VENDOR_ID_C != PORT_VENDOR_ID)
    #error "Port.c and Port.h have different vendor ids"
#endif

/* Check if source file and Port header file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port.c and Port.h are different"
#endif

/* Check if source file and Port header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port.c and Port.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the source file and Det.h file are of the same Autosar version */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
        #if ((PORT_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
             (PORT_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AutoSar Version Numbers of Port.c and Det.h are different"
        #endif
    #endif
#endif
/*=================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/

/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/

/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/

/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/

/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/
 #define PORT_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
 #include "Port_MemMap.h"

static const Port_ConfigType * Port_pConfigPtr = NULL_PTR;

 #define PORT_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
 #include "Port_MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
    extern const Port_ConfigType Port_Config;
#endif

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"
/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL FUNCTIONS
=================================================================================================*/
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*=================================================================================================
*                                      GLOBAL FUNCTIONS
=================================================================================================*/

/**
* @brief   Initializes the Port Driver module.
* @details The function @p Port_Init() will initialize ALL ports and port pins
*          with the configuration set pointed to by the parameter @p pConfigPtr.
* @post    Port_Init() must be called before all other Port Driver module's functions
*          otherwise no operation can occur on the MCU ports and port pins.
*
* @param[in] ConfigPtr     A pointer to the structure which contains
*                          initialization parameters.
*/
void Port_Init
(
    const Port_ConfigType * ConfigPtr
)
{
    const Port_ConfigType * pLocalConfigPtr = ConfigPtr;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
#if (STD_OFF == PORT_PRECOMPILE_SUPPORT)
    if (NULL_PTR == ConfigPtr)
#else /*(STD_OFF == PORT_PRECOMPILE_SUPPORT) */
    if (NULL_PTR != ConfigPtr)
#endif /* (STD_OFF == PORT_PRECOMPILE_SUPPORT) */
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, (uint8)PORT_INIT_ID, (uint8)PORT_E_INIT_FAILED);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
        pLocalConfigPtr = &Port_Config;
#endif /* (STD_ON == PORT_PRECOMPILE_SUPPORT) */

#if (STD_ON == PORT_DEV_ERROR_DETECT)
        /* Validate configuration pointer */
        if ((NULL_PTR == pLocalConfigPtr->IpConfig_ptr) || (0U == pLocalConfigPtr->NumPins_u16))
        {
            (void)Det_ReportError((uint16)PORT_MODULE_ID, PORT_INSTANCE_ID, (uint8)PORT_INIT_ID, (uint8)PORT_E_PARAM_CONFIG);
        }
        else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
        {
            /* Initialize Port using Hardware driver */
            (void)PortHw_Init(pLocalConfigPtr->NumPins_u16, pLocalConfigPtr->IpConfig_ptr, \
            				  pLocalConfigPtr->NumUnusedPins_u16, pLocalConfigPtr->UnusedPads_ptr,\
							  pLocalConfigPtr->UnusedPadConfig_ptr);

            /*  Save configuration pointer in global variable */
            Port_pConfigPtr = pLocalConfigPtr;
        }
    }
}

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
/**
* @brief   Sets the port pin direction.
* @details The function @p Port_SetPinDirection() will set the port pin direction
*          during runtime.
* @pre     @p Port_Init() must have been called first. In order to change the
*          pin direction the PortPinDirectionChangeable flag must have been set
*          to @p TRUE.
*
* @param[in] Pin            Pin ID number.
* @param[in] Direction     Port Pin direction.
*
*/
void Port_SetPinDirection
(
    Port_PinType Pin,
    Port_PinDirectionType Direction
)
{
    uint32 PinIndex_u32;
    PortHw_DirectionType HwDirection_en;
    GPIO_Type* GpioBase_ptr;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if Port module is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_UNINIT);
    }
    /* Check if pin is valid */
    else if (Pin >= Port_pConfigPtr->NumPins_u16)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_PARAM_PIN);
    }
    /* Check if direction is changeable */
    else if ((boolean)FALSE == Port_pConfigPtr->UsedPadConfig_ptr[Pin].DirectionChangeable_bool)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINDIRECTION_ID, (uint8)PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else
#endif /* PORT_DEV_ERROR_DETECT */
    {
        /* Get GPIO base address and pin index */
        GpioBase_ptr = Port_pConfigPtr->IpConfig_ptr[Pin].GpioBase_ptr;
        PinIndex_u32 = Port_pConfigPtr->IpConfig_ptr[Pin].PinPortIndex_u32;

        /* Convert AUTOSAR direction to HW direction */
        if (PORT_PIN_OUT == Direction)
        {
            HwDirection_en = PORT_HW_PIN_OUT;
        }
        else
        {
            HwDirection_en = PORT_HW_PIN_IN;
        }

        /* Set pin direction using Hardware driver */
        PortHw_SetPinDirection(GpioBase_ptr, PinIndex_u32, HwDirection_en);
    }
}
#endif /* (STD_ON == PORT_SET_PIN_DIRECTION_API) */



#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief   Sets the port pin mode.
* @details The function @p Port_SetPinMode() will set the port pin mode of the
*          referenced pin during runtime.
* @pre     @p Port_Init() must have been called first.
*
* @param[in] Pin       Pin ID number.
* @param[in] Mode      New Port Pin mode to be set on port pin.
*
*/
void Port_SetPinMode
(
    Port_PinType Pin,
    Port_PinModeType Mode
)
{
    uint32 PinIndex_u32;
    PORT_Type* PortBase_ptr;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_UNINIT);
    }
    /* Check if pin is valid */
    else if (Pin >= Port_pConfigPtr->NumPins_u16)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_PARAM_PIN);
    }
    /* Check if mode is changeable */
    else if ((boolean)FALSE == Port_pConfigPtr->UsedPadConfig_ptr[Pin].ModeChangeable_bool)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_MODE_UNCHANGEABLE);
    }
    /* Check if mode is valid (0-7) */
    else if (Mode > (Port_PinModeType)7U)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETPINMODE_ID, (uint8)PORT_E_PARAM_INVALID_MODE);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        /* Get PORT base address and pin index */
        PortBase_ptr = Port_pConfigPtr->IpConfig_ptr[Pin].PortBase_ptr;
        PinIndex_u32 = Port_pConfigPtr->IpConfig_ptr[Pin].PinPortIndex_u32;

        /* Set pin mode using Hardware driver */
        PortHw_SetMuxModeSel(PortBase_ptr, PinIndex_u32, (PortHw_MuxType)Mode);
    }
}
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */

/**
* @brief   Refreshes port direction.
* @details This function will refresh the direction of all configured ports to
*          the configured direction.
*          The PORT driver will exclude from refreshing those port pins that
*          are configured as "pin direction changeable during runtime".
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_RefreshPortDirection( void )
{
    uint16 PinIndex_u16;
    uint32 PinPortIndex_u32;
    GPIO_Type* GpioBase_ptr;
    PortHw_DirectionType HwDirection_en;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if Port module is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_REFRESHPINDIRECTION_ID, (uint8)PORT_E_UNINIT);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        /* Loop through all configured pins */
        for (PinIndex_u16 = 0U; PinIndex_u16 < Port_pConfigPtr->NumPins_u16; PinIndex_u16++)
        {
            /* Only refresh pins that are NOT direction changeable */
            if ((boolean)FALSE == Port_pConfigPtr->UsedPadConfig_ptr[PinIndex_u16].DirectionChangeable_bool)
            {
                /* Get GPIO base address and pin index */
                GpioBase_ptr = Port_pConfigPtr->IpConfig_ptr[PinIndex_u16].GpioBase_ptr;
                PinPortIndex_u32 = Port_pConfigPtr->IpConfig_ptr[PinIndex_u16].PinPortIndex_u32;

                /* Convert AUTOSAR direction to HW direction */
                if (PORT_PIN_OUT == Port_pConfigPtr->UsedPadConfig_ptr[PinIndex_u16].PinDirection_en)
                {
                    HwDirection_en = PORT_HW_PIN_OUT;
                }
                else
                {
                    HwDirection_en = PORT_HW_PIN_IN;
                }

                /* Refresh pin direction using Hardware driver */
                PortHw_SetPinDirection(GpioBase_ptr, PinPortIndex_u32, HwDirection_en);
            }
        }
    }
}


#if  (STD_ON == PORT_VERSION_INFO_API)
/**
* @brief   Returns the version information of this module.
* @details The function Port_GetVersionInfo() will return the version
*          information of this module. The version information includes:
*          - Module Id,
*          - Vendor Id,
*          - Vendor specific version numbers.
*
* @param[in,out] versioninfo      Pointer to where to store the version
*                                  information of this module.
*
*
*/
void Port_GetVersionInfo
(
    Std_VersionInfoType * versioninfo
)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_GETVERSIONINFO_ID, (uint8)PORT_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        (versioninfo)->vendorID         = (uint16)PORT_VENDOR_ID;
        (versioninfo)->moduleID         = (uint16)PORT_MODULE_ID;
        (versioninfo)->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        (versioninfo)->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        (versioninfo)->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON == PORT_VERSION_INFO_API) */

#ifdef PORT_SET_AS_UNUSED_PIN_API
#if (STD_ON == PORT_SET_AS_UNUSED_PIN_API)
/**
* @brief   Set as unused pin.
* @details This function shall configure the referenced pin with all
*          the properties specified in the NotUsedPortPin container.
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_SetAsUnusedPin
(
    Port_PinType Pin
)
{
    uint32 PinPortIndex_u32;
    PORT_Type* PortBase_ptr;
    GPIO_Type* GpioBase_ptr;
    PortHw_DirectionType HwDirection_en;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETASUNUSEDPIN_ID, (uint8)PORT_E_UNINIT);
    }
    /* Check if pin is valid */
    else if (Pin >= Port_pConfigPtr->NumPins_u16)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETASUNUSEDPIN_ID, (uint8)PORT_E_PARAM_PIN);
    }
    else
#endif
    {
        /* Get base addresses and pin index */
        PortBase_ptr = Port_pConfigPtr->IpConfig_ptr[Pin].PortBase_ptr;
        GpioBase_ptr = Port_pConfigPtr->IpConfig_ptr[Pin].GpioBase_ptr;
        PinPortIndex_u32 = Port_pConfigPtr->IpConfig_ptr[Pin].PinPortIndex_u32;

        /* Configure pin with unused pin settings */
        if (Port_pConfigPtr->UnusedPadConfig_ptr != NULL_PTR)
        {
            /* Set mux mode from unused pin configuration */
            PortHw_SetMuxModeSel(PortBase_ptr, PinPortIndex_u32, PORT_HW_MUX_AS_GPIO);

            /* Convert and set direction */
            if (PORT_PIN_OUT == Port_pConfigPtr->UnusedPadConfig_ptr->PinDirection_en)
            {
                HwDirection_en = PORT_HW_PIN_OUT;
                /* Set output value */
                PortHw_WritePin(GpioBase_ptr, PinPortIndex_u32, Port_pConfigPtr->UnusedPadConfig_ptr->PinOutputValue_u8);
            }
            else
            {
                HwDirection_en = PORT_HW_PIN_IN;
            }
            PortHw_SetPinDirection(GpioBase_ptr, PinPortIndex_u32, HwDirection_en);
        }
    }
}


/**
* @brief   Set as used pin.
* @details This function shall configure the referenced pin with
*          all the properties that where set during the Port_Init operation.
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_SetAsUsedPin
(
    Port_PinType Pin
)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETASUSEDPIN_ID, (uint8)PORT_E_UNINIT);
    }
    /* Check if pin is valid */
    else if (Pin >= Port_pConfigPtr->NumPins_u16)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_SETASUSEDPIN_ID, (uint8)PORT_E_PARAM_PIN);
    }
    else
#endif
    {
        /* Re-initialize pin with original configuration */
        (void)PortHw_Init(1U, &Port_pConfigPtr->IpConfig_ptr[Pin]);
    }
}
#endif /* (STD_ON == PORT_SET_AS_UNUSED_PIN_API) */
#endif

#ifdef PORT_RESET_PIN_MODE_API
#if (STD_ON == PORT_RESET_PIN_MODE_API)
/**
* @brief   Reset Pin Mode.
* @details This function shall revert the port pin mode of the referenced pin
*          to the value that was set by Port_Init operation.
* @pre     @p Port_Init() must have been called first.
*
*/
void Port_ResetPinMode
(
    Port_PinType Pin
)
{
    uint32 PinPortIndex_u32;
    PORT_Type* PortBase_ptr;
    PortHw_MuxType OriginalMux_en;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if port is initialized */
    if (NULL_PTR == Port_pConfigPtr)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_RESETPINMODE_ID, (uint8)PORT_E_UNINIT);
    }
    /* Check if pin is valid */
    else if (Pin >= Port_pConfigPtr->NumPins_u16)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_RESETPINMODE_ID, (uint8)PORT_E_PARAM_PIN);
    }
    /* Check if mode is changeable */
    else if ((boolean)FALSE == Port_pConfigPtr->UsedPadConfig_ptr[Pin].ModeChangeable_bool)
    {
        (void)Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_RESETPINMODE_ID, (uint8)PORT_E_MODE_UNCHANGEABLE);
    }
    else
#endif
    {
        /* Get PORT base address and pin index */
        PortBase_ptr = Port_pConfigPtr->IpConfig_ptr[Pin].PortBase_ptr;
        PinPortIndex_u32 = Port_pConfigPtr->IpConfig_ptr[Pin].PinPortIndex_u32;

        /* Get original mux mode from configuration */
        OriginalMux_en = Port_pConfigPtr->IpConfig_ptr[Pin].Mux_en;

        /* Reset pin mode to original value using Hardware driver */
        PortHw_SetMuxModeSel(PortBase_ptr, PinPortIndex_u32, OriginalMux_en);
    }
}
#endif /* (STD_ON == PORT_RESET_PIN_MODE_API) */
#endif

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
