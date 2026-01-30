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
*   Description          : Header file for AUTOSAR Port Driver Test Implementation
==================================================================================================*/

#ifndef TEST_PORT_DRIVER_H
#define TEST_PORT_DRIVER_H

/**
*   @file    test_port_driver.h
*
*   @brief   Header for Port Driver Test implementation
*   @details Contains declarations for test functions and structures
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
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define TEST_PORT_DRIVER_VENDOR_ID_H                    43
#define TEST_PORT_DRIVER_AR_RELEASE_MAJOR_VERSION_H     21
#define TEST_PORT_DRIVER_AR_RELEASE_MINOR_VERSION_H     11
#define TEST_PORT_DRIVER_AR_RELEASE_REVISION_VERSION_H  0
#define TEST_PORT_DRIVER_SW_MAJOR_VERSION_H             1
#define TEST_PORT_DRIVER_SW_MINOR_VERSION_H             0
#define TEST_PORT_DRIVER_SW_PATCH_VERSION_H             0

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief Test result macros
*/
#define TEST_PASSED                     (0U)
#define TEST_FAILED                     (1U)

/**
* @brief Maximum number of test cases
*/
#define MAX_TEST_CASES                  (42U)

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/**
* @brief Test result structure
*/
typedef struct
{
    uint8   testId;             /**< @brief Test case ID (1-42) */
    char    testName[32];       /**< @brief Test case name */
    uint8   result;             /**< @brief TEST_PASSED or TEST_FAILED */
    uint8   detErrorExpected;   /**< @brief Expected DET error code */
    uint8   detErrorReceived;   /**< @brief Actual DET error received */
    uint8   serviceIdExpected;  /**< @brief Expected Service ID */
    uint8   serviceIdReceived;  /**< @brief Actual Service ID received */
} TestResult_Type;

/**
* @brief Test summary structure
*/
typedef struct
{
    uint32  totalTests;         /**< @brief Total number of tests executed */
    uint32  passedTests;        /**< @brief Number of passed tests */
    uint32  failedTests;        /**< @brief Number of failed tests */
    uint32  skippedTests;       /**< @brief Number of skipped tests */
} TestSummary_Type;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

/**
* @brief Run all Port Driver test cases
* @details Executes all 42 test cases from Port_Driver_Test_Specification.csv
*
* Test Categories:
* - PORT_IT_DRV_001 - 005: Port_Init API tests
* - PORT_IT_DRV_006 - 010: Port_SetPinDirection API tests
* - PORT_IT_DRV_011 - 015: Port_SetPinMode API tests
* - PORT_IT_DRV_016 - 018: Port_RefreshPortDirection API tests
* - PORT_IT_DRV_019 - 020: Port_GetVersionInfo API tests
* - PORT_IT_DRV_021 - 023: Port_SetAsUnusedPin API tests
* - PORT_IT_DRV_024 - 026: Port_SetAsUsedPin API tests
* - PORT_IT_DRV_027 - 030: Port_ResetPinMode API tests
* - PORT_IT_DRV_031 - 034: Boundary tests
* - PORT_IT_DRV_035:       Sequence test
* - PORT_IT_DRV_036 - 042: Functional tests
*/
void Test_Port_Driver_RunAllTests(void);

/**
* @brief Get test results array
* @return Pointer to test results array
*/
const TestResult_Type* Test_Port_Driver_GetResults(void);

/**
* @brief Get test summary
* @return Pointer to test summary structure
*/
const TestSummary_Type* Test_Port_Driver_GetSummary(void);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* TEST_PORT_DRIVER_H */

/*==================================================================================================
*                                      END OF FILE
==================================================================================================*/
