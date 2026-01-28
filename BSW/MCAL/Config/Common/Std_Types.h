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
* @file           Std_Types.h
* @implements     Std_Types.h_Artifact
* @brief          AUTOSAR Standard Types definitions
* @details        This file contains all types that are used across several modules of the basic
*                 software and that are platform and compiler independent
*
* @addtogroup     BASE_COMPONENT
* @{
*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#include "Compiler.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the Std_Types header file
*/
#define STD_TYPES_VENDOR_ID                     43U
#define STD_TYPES_MODULE_ID                     197U
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION      21U
#define STD_TYPES_AR_RELEASE_MINOR_VERSION      11U
#define STD_TYPES_AR_RELEASE_REVISION_VERSION   0U
#define STD_TYPES_SW_MAJOR_VERSION              1U
#define STD_TYPES_SW_MINOR_VERSION              0U
#define STD_TYPES_SW_PATCH_VERSION              0U

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Physical state 5V or 3.3V
* @implements SymbolDefinitions_enumeration
*/
#define STD_HIGH    (0x01U)

/**
* @brief Physical state 0V
* @implements SymbolDefinitions_enumeration
*/
#define STD_LOW     (0x00U)

/**
* @brief Logical state active
* @implements SymbolDefinitions_enumeration
*/
#define STD_ACTIVE  (0x01U)

/**
* @brief Logical state idle
* @implements SymbolDefinitions_enumeration
*/
#define STD_IDLE    (0x00U)

/**
* @brief ON state
* @implements SymbolDefinitions_enumeration
*/
#define STD_ON      (0x01U)

/**
* @brief OFF state
* @implements SymbolDefinitions_enumeration
*/
#define STD_OFF     (0x00U)

/**
* @brief Return code for failure/error
* @implements SymbolDefinitions_enumeration
*/
#define E_NOT_OK    ((Std_ReturnType)0x01U)

/**
* @brief Return code for success
* @implements SymbolDefinitions_enumeration
*/
#define E_OK        ((Std_ReturnType)0x00U)

/**
* @brief NULL pointer definition
*/
#ifndef NULL_PTR
    #define NULL_PTR    ((void *)0)
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief Standard Return Type
* @details This type can be used as standard API return type which is shared between the RTE and
*          the BSW modules.
* @implements Std_ReturnType_type
*/
typedef uint8 Std_ReturnType;

/**
* @brief Standard Version Info Type
* @details This type shall be used to request the version of a BSW module using the
*          <Module name>_GetVersionInfo() function.
* @implements Std_VersionInfoType_structure
*/
typedef struct
{
    uint16 vendorID;           /**< @brief Vendor ID */
    uint16 moduleID;           /**< @brief Module ID */
    uint8 sw_major_version;    /**< @brief Software Major Version */
    uint8 sw_minor_version;    /**< @brief Software Minor Version */
    uint8 sw_patch_version;    /**< @brief Software Patch Version */
} Std_VersionInfoType;

/**
* @brief Standard Transformer Error Type
* @details Std_TransformerError represents a transformer error in the context of a certain
*          transformer chain.
*/
typedef uint8 Std_TransformerErrorCode;

/**
* @brief Standard Transformer Class Type
*/
typedef uint8 Std_TransformerClass;

/**
* @brief Standard Transformer Forward Code Type
*/
typedef uint8 Std_TransformerForwardCode;

/**
* @brief Std_TransformerError
*/
typedef struct
{
    Std_TransformerErrorCode errorCode;
    Std_TransformerClass transformerClass;
} Std_TransformerError;

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

#endif /* STD_TYPES_H */
