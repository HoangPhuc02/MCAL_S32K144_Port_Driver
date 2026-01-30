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
*   Description          : DET stub implementation for Port Driver testing
==================================================================================================*/

/**
*   @file    Det_Stub.c
*
*   @brief   DET (Default Error Tracer) stub for testing
*   @details Provides stub implementation of DET functions for capturing
*            and verifying error reports from Port driver during testing.
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
#include "Det.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief Maximum number of DET errors to store
*/
#define DET_MAX_ERROR_LOG       (100U)

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
* @brief DET error log entry structure
*/
typedef struct
{
    uint16  moduleId;
    uint8   instanceId;
    uint8   apiId;
    uint8   errorId;
} Det_ErrorLogEntry_Type;

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
/**
* @brief DET error log array
*/
static Det_ErrorLogEntry_Type Det_ErrorLog[DET_MAX_ERROR_LOG];

/**
* @brief Current index in error log
*/
static uint32 Det_ErrorLogIndex = 0U;

/**
* @brief Last reported error information
*/
static uint16 Det_LastModuleId = 0U;
static uint8  Det_LastInstanceId = 0U;
static uint8  Det_LastApiId = 0U;
static uint8  Det_LastErrorId = 0U;
static boolean Det_ErrorReported = FALSE;

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief DET initialization stub
* @details Clears all error tracking variables and log
*/
void Det_Init(const void* ConfigPtr)
{
    (void)ConfigPtr;
    
    Det_ErrorLogIndex = 0U;
    Det_LastModuleId = 0U;
    Det_LastInstanceId = 0U;
    Det_LastApiId = 0U;
    Det_LastErrorId = 0U;
    Det_ErrorReported = FALSE;
    
    /* Clear error log */
    uint32 i;
    for (i = 0U; i < DET_MAX_ERROR_LOG; i++)
    {
        Det_ErrorLog[i].moduleId = 0U;
        Det_ErrorLog[i].instanceId = 0U;
        Det_ErrorLog[i].apiId = 0U;
        Det_ErrorLog[i].errorId = 0U;
    }
}

/**
* @brief DET ReportError stub
* @details Captures error information for test verification
* @param ModuleId Module ID that reported the error
* @param InstanceId Instance ID
* @param ApiId API service ID that reported the error
* @param ErrorId Error code
* @return E_OK always
*/
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    /* Store last error information */
    Det_LastModuleId = ModuleId;
    Det_LastInstanceId = InstanceId;
    Det_LastApiId = ApiId;
    Det_LastErrorId = ErrorId;
    Det_ErrorReported = TRUE;
    
    /* Log error if space available */
    if (Det_ErrorLogIndex < DET_MAX_ERROR_LOG)
    {
        Det_ErrorLog[Det_ErrorLogIndex].moduleId = ModuleId;
        Det_ErrorLog[Det_ErrorLogIndex].instanceId = InstanceId;
        Det_ErrorLog[Det_ErrorLogIndex].apiId = ApiId;
        Det_ErrorLog[Det_ErrorLogIndex].errorId = ErrorId;
        Det_ErrorLogIndex++;
    }
    
    return E_OK;
}

/**
* @brief DET ReportRuntimeError stub
* @details Captures runtime error information
* @param ModuleId Module ID that reported the error
* @param InstanceId Instance ID
* @param ApiId API service ID that reported the error
* @param ErrorId Error code
* @return E_OK always
*/
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    /* Same handling as Det_ReportError */
    return Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId);
}

/**
* @brief DET ReportTransientFault stub
* @details Captures transient fault information
* @param ModuleId Module ID that reported the fault
* @param InstanceId Instance ID
* @param ApiId API service ID that reported the fault
* @param FaultId Fault code
* @return E_OK always
*/
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId)
{
    /* Same handling as Det_ReportError */
    return Det_ReportError(ModuleId, InstanceId, ApiId, FaultId);
}

/**
* @brief DET Start stub
*/
void Det_Start(void)
{
    /* Nothing to do in stub */
}

/*==================================================================================================
*                              TEST HELPER FUNCTIONS
==================================================================================================*/

/**
* @brief Clear DET error tracking
* @details Resets all error tracking variables (does not clear log)
*/
void Det_ClearError(void)
{
    Det_LastModuleId = 0U;
    Det_LastInstanceId = 0U;
    Det_LastApiId = 0U;
    Det_LastErrorId = 0U;
    Det_ErrorReported = FALSE;
}

/**
* @brief Clear entire DET error log
* @details Resets error log and all tracking variables
*/
void Det_ClearLog(void)
{
    Det_ErrorLogIndex = 0U;
    Det_ClearError();
}

/**
* @brief Check if a specific error was reported
* @param ModuleId Expected module ID
* @param ApiId Expected API service ID
* @param ErrorId Expected error code
* @return TRUE if expected error was reported, FALSE otherwise
*/
boolean Det_CheckError(uint16 ModuleId, uint8 ApiId, uint8 ErrorId)
{
    if ((Det_ErrorReported == TRUE) &&
        (Det_LastModuleId == ModuleId) &&
        (Det_LastApiId == ApiId) &&
        (Det_LastErrorId == ErrorId))
    {
        return TRUE;
    }
    return FALSE;
}

/**
* @brief Check if any error was reported
* @return TRUE if any error was reported, FALSE otherwise
*/
boolean Det_IsErrorReported(void)
{
    return Det_ErrorReported;
}

/**
* @brief Get last reported module ID
* @return Module ID of last reported error
*/
uint16 Det_GetLastModuleId(void)
{
    return Det_LastModuleId;
}

/**
* @brief Get last reported instance ID
* @return Instance ID of last reported error
*/
uint8 Det_GetLastInstanceId(void)
{
    return Det_LastInstanceId;
}

/**
* @brief Get last reported API ID
* @return API service ID of last reported error
*/
uint8 Det_GetLastApiId(void)
{
    return Det_LastApiId;
}

/**
* @brief Get last reported error ID
* @return Error code of last reported error
*/
uint8 Det_GetLastErrorId(void)
{
    return Det_LastErrorId;
}

/**
* @brief Get number of logged errors
* @return Number of errors in log
*/
uint32 Det_GetErrorCount(void)
{
    return Det_ErrorLogIndex;
}

/**
* @brief Get error log entry
* @param index Index in error log
* @param pEntry Pointer to store entry
* @return TRUE if entry exists, FALSE otherwise
*/
boolean Det_GetLogEntry(uint32 index, Det_ErrorLogEntry_Type* pEntry)
{
    if ((index < Det_ErrorLogIndex) && (pEntry != NULL_PTR))
    {
        pEntry->moduleId = Det_ErrorLog[index].moduleId;
        pEntry->instanceId = Det_ErrorLog[index].instanceId;
        pEntry->apiId = Det_ErrorLog[index].apiId;
        pEntry->errorId = Det_ErrorLog[index].errorId;
        return TRUE;
    }
    return FALSE;
}

#ifdef __cplusplus
}
#endif

/** @} */

/*==================================================================================================
*                                      END OF FILE
==================================================================================================*/
