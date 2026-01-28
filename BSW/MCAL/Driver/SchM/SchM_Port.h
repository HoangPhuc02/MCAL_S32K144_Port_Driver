/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K1_RTD_1_0_1_D2202_ASR_REL_4_4_REV_0000_20220224
*
*   (c) Copyright 2020-2022 NXP Semiconductors
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef SCHM_PORT_H
#define SCHM_PORT_H

/**
*   @file
*
*   @addtogroup RTE_MODULE
*   @{
*/

#ifdef __cplusplus
  "C" {
#endif
/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from  al units
* 3) internal and  al interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SCHM_PORT_AR_RELEASE_MAJOR_VERSION     4
#define SCHM_PORT_AR_RELEASE_MINOR_VERSION     4
#define SCHM_PORT_AR_RELEASE_REVISION_VERSION  0
#define SCHM_PORT_SW_MAJOR_VERSION             1
#define SCHM_PORT_SW_MINOR_VERSION             0
#define SCHM_PORT_SW_PATCH_VERSION             1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
#if 0
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"
#endif
#ifdef MCAL_TESTING_ENVIRONMENT
/** 
@brief   This function checks that all entered exclusive areas were also exited. 
@details This function checks that all entered exclusive areas were also exited. The check
         is done by verifying that all reentry_guard_* static variables are back to the
         zero value.
    
@param[in]     void       No input parameters
@return        void       This function does not return a value. Test asserts are used instead. 

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
void SchM_Check_port(void);
#endif /*MCAL_TESTING_ENVIRONMENT*/

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_01(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_01(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_02(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_02(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_03(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_03(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_04(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_04(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_05(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_05(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_06(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_06(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_07(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_07(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_08(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_08(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_09(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_09(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_10(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_10(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_11(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_11(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_12(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_12(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_13(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_13(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_14(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_14(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_15(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_15(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_16(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_16(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_17(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_17(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_18(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_18(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_19(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_19(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_20(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_20(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_21(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_21(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_22(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_22(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_23(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_23(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_24(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_24(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_25(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_25(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_26(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_26(void);

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_27(void);
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_27(void);

#if 0
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"
#endif

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SCHM_PORT_H */
