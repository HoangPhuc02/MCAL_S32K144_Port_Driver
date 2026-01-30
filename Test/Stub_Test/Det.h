/*==================================================================================================
*   Project              : MCAL_PORT_S32K144
*   Platform             : CORTEXM
*   Peripheral           : PORT
*   Dependencies         : none
*
*   Autosar Version      : 21.11.0
*   SW Version           : 1.0.0
*
*   Author               : PhucPH32
*
*   Description          : DET stub header for Port Driver testing
==================================================================================================*/

#ifndef DET_H
#define DET_H

/**
*   @file    Det.h
*
*   @brief   DET (Default Error Tracer) stub header
*   @details Provides declarations for DET stub functions
*
*   @addtogroup Port_Driver_Test
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
* @brief DET error log entry structure
*/
typedef struct
{
    uint16  moduleId;       /**< @brief Module ID */
    uint8   instanceId;     /**< @brief Instance ID */
    uint8   apiId;          /**< @brief API service ID */
    uint8   errorId;        /**< @brief Error code */
} Det_ErrorLogEntry_Type;

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

/**
* @brief DET initialization
* @param ConfigPtr Configuration pointer (not used in stub)
*/
void Det_Init(const void* ConfigPtr);

/**
* @brief DET Start
*/
void Det_Start(void);

/**
* @brief Report development error
* @param ModuleId Module ID
* @param InstanceId Instance ID
* @param ApiId API service ID
* @param ErrorId Error code
* @return E_OK
*/
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**
* @brief Report runtime error
* @param ModuleId Module ID
* @param InstanceId Instance ID
* @param ApiId API service ID
* @param ErrorId Error code
* @return E_OK
*/
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**
* @brief Report transient fault
* @param ModuleId Module ID
* @param InstanceId Instance ID
* @param ApiId API service ID
* @param FaultId Fault code
* @return E_OK
*/
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);

/*==================================================================================================
*                              TEST HELPER FUNCTIONS
==================================================================================================*/

/**
* @brief Clear DET error tracking
*/
void Det_ClearError(void);

/**
* @brief Clear entire DET error log
*/
void Det_ClearLog(void);

/**
* @brief Check if a specific error was reported
* @param ModuleId Expected module ID
* @param ApiId Expected API service ID
* @param ErrorId Expected error code
* @return TRUE if expected error was reported
*/
boolean Det_CheckError(uint16 ModuleId, uint8 ApiId, uint8 ErrorId);

/**
* @brief Check if any error was reported
* @return TRUE if any error was reported
*/
boolean Det_IsErrorReported(void);

/**
* @brief Get last reported module ID
* @return Module ID of last reported error
*/
uint16 Det_GetLastModuleId(void);

/**
* @brief Get last reported instance ID
* @return Instance ID of last reported error
*/
uint8 Det_GetLastInstanceId(void);

/**
* @brief Get last reported API ID
* @return API service ID of last reported error
*/
uint8 Det_GetLastApiId(void);

/**
* @brief Get last reported error ID
* @return Error code of last reported error
*/
uint8 Det_GetLastErrorId(void);

/**
* @brief Get number of logged errors
* @return Number of errors in log
*/
uint32 Det_GetErrorCount(void);

/**
* @brief Get error log entry
* @param index Index in error log
* @param pEntry Pointer to store entry
* @return TRUE if entry exists
*/
boolean Det_GetLogEntry(uint32 index, Det_ErrorLogEntry_Type* pEntry);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* DET_H */

/*==================================================================================================
*                                      END OF FILE
==================================================================================================*/
