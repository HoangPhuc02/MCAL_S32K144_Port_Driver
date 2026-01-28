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
* @file           Compiler_Cfg.h
* @implements     Compiler_Cfg.h_Artifact
* @brief          AUTOSAR Compiler configuration
* @details        Module specific memory and pointer classes
*
* @addtogroup     BASE_COMPONENT
* @{
*/

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define COMPILER_CFG_VENDOR_ID                      43U
#define COMPILER_CFG_AR_RELEASE_MAJOR_VERSION       21U
#define COMPILER_CFG_AR_RELEASE_MINOR_VERSION       11U
#define COMPILER_CFG_AR_RELEASE_REVISION_VERSION    0U
#define COMPILER_CFG_SW_MAJOR_VERSION               1U
#define COMPILER_CFG_SW_MINOR_VERSION               0U
#define COMPILER_CFG_SW_PATCH_VERSION               0U

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
*                               PORT Module Memory Classes
-------------------------------------------------------------------------------------------------*/
/**
* @brief PORT driver code memory class
*/
#define PORT_CODE

/**
* @brief PORT driver configuration data constant memory class
*/
#define PORT_CONFIG_DATA

/**
* @brief PORT driver constant memory class
*/
#define PORT_CONST

/**
* @brief PORT driver application data memory class
*/
#define PORT_APPL_DATA

/**
* @brief PORT driver application constant data memory class
*/
#define PORT_APPL_CONST

/**
* @brief PORT driver application code memory class
*/
#define PORT_APPL_CODE

/**
* @brief PORT driver variable cleared memory class
*/
#define PORT_VAR_CLEARED

/**
* @brief PORT driver variable initialized memory class
*/
#define PORT_VAR_INIT

/**
* @brief PORT driver variable no init memory class
*/
#define PORT_VAR_NOINIT

/**
* @brief PORT driver variable power on init memory class
*/
#define PORT_VAR_POWER_ON_INIT

/*-------------------------------------------------------------------------------------------------
*                               DET Module Memory Classes
-------------------------------------------------------------------------------------------------*/
#define DET_CODE
#define DET_CONST
#define DET_APPL_DATA
#define DET_APPL_CONST
#define DET_VAR_CLEARED
#define DET_VAR_INIT
#define DET_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------
*                               DIO Module Memory Classes
-------------------------------------------------------------------------------------------------*/
#define DIO_CODE
#define DIO_CONST
#define DIO_APPL_DATA
#define DIO_APPL_CONST
#define DIO_VAR_CLEARED
#define DIO_VAR_INIT
#define DIO_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------
*                               MCU Module Memory Classes
-------------------------------------------------------------------------------------------------*/
#define MCU_CODE
#define MCU_CONST
#define MCU_APPL_DATA
#define MCU_APPL_CONST
#define MCU_VAR_CLEARED
#define MCU_VAR_INIT
#define MCU_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------
*                               RTE Module Memory Classes
-------------------------------------------------------------------------------------------------*/
#define RTE_CODE
#define RTE_CONST
#define RTE_APPL_DATA
#define RTE_APPL_CONST
#define RTE_VAR_CLEARED
#define RTE_VAR_INIT
#define RTE_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------
*                               OSIF Module Memory Classes
-------------------------------------------------------------------------------------------------*/
#define OSIF_CODE
#define OSIF_CONST
#define OSIF_APPL_DATA
#define OSIF_APPL_CONST
#define OSIF_VAR_CLEARED
#define OSIF_VAR_INIT
#define OSIF_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------
*                               BASE Module Memory Classes
-------------------------------------------------------------------------------------------------*/
#define BASE_CODE
#define BASE_CONST
#define BASE_APPL_DATA
#define BASE_VAR_CLEARED
#define BASE_VAR_INIT
#define BASE_VAR_NOINIT

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

#endif /* COMPILER_CFG_H */
