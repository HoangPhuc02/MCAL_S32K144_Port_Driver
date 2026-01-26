/*==================================================================================================
*   Project              : MCAL_PORT_S32K144
*   Platform             : CORTEXM
*   Peripheral           : PORT
*   Dependencies         : none
*
*   SW Version           : 1.0.0
*   Author               : PhucPH32
*
*   Description          : Main application to test AUTOSAR Port driver on S32K144 EVB
==================================================================================================*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "S32K144.h"
#include "Port.h"
#include "Port_Hw.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief S32K144 EVB LED Pin Definitions (Active LOW - LED ON when pin LOW)
*        Note: Pin Index in Port configuration (based on Port_VS_0_PBcfg.c)
*/
#define LED_BLUE_PIN_INDEX      (0U)    /**< @brief PTD0 - Blue LED (First configured pin) */

/**
* @brief Physical pin definitions for GPIO access
*/
#define LED_BLUE_PIN            (0U)    /**< @brief PTD0 - Blue LED */
#define LED_RED_PIN             (15U)   /**< @brief PTD15 - Red LED */
#define LED_GREEN_PIN           (16U)   /**< @brief PTD16 - Green LED */

/**
* @brief Delay loop count
*/
#define DELAY_COUNT             (500000UL)

/*==================================================================================================
*                                    EXTERNAL DECLARATIONS
==================================================================================================*/
extern const Port_ConfigType Port_Config_VS_0;

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void Delay(uint32 count);
static void Test_Port_Init(void);
static void Test_Port_SetPinDirection(void);
static void Test_Port_SetPinMode(void);
static void Test_Port_RefreshPortDirection(void);
static void Test_Port_GetVersionInfo(void);
static void Led_Toggle(void);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief Simple software delay
* @param count - delay loop count
*/
static void Delay(uint32 count)
{
    volatile uint32 i;
    for (i = 0U; i < count; i++)
    {
        /* Wait */
    }
}

/**
* @brief Toggle LED using direct GPIO register access
*/
static void Led_Toggle(void)
{
    PTD->PTOR = (1UL << LED_BLUE_PIN);
}

/**
* @brief Test Port_Init function
* @details Initialize Port driver with configuration from Port_Config_VS_0
*/
static void Test_Port_Init(void)
{
    /* Call AUTOSAR Port_Init with post-build configuration */
    Port_Init(&Port_Config_VS_0);

    /* After initialization, toggle LED to indicate success */
    for (uint8 i = 0U; i < 3U; i++)
    {
        Led_Toggle();
        Delay(DELAY_COUNT);
    }
}

/**
* @brief Test Port_SetPinDirection function
* @details Change pin direction at runtime (if direction changeable is enabled)
*/
static void Test_Port_SetPinDirection(void)
{
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    /* Change LED pin direction to INPUT */
    Port_SetPinDirection(LED_BLUE_PIN_INDEX, PORT_PIN_IN);
    Delay(DELAY_COUNT);

    /* Change LED pin direction back to OUTPUT */
    Port_SetPinDirection(LED_BLUE_PIN_INDEX, PORT_PIN_OUT);

    /* Toggle LED to confirm direction change worked */
    for (uint8 i = 0U; i < 4U; i++)
    {
        Led_Toggle();
        Delay(DELAY_COUNT / 2U);
    }
#endif /* PORT_SET_PIN_DIRECTION_API */
}

/**
* @brief Test Port_SetPinMode function
* @details Change pin mode (mux) at runtime (if mode changeable is enabled)
*/
static void Test_Port_SetPinMode(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    /* Change LED pin to ALT0 (disable GPIO) */
    Port_SetPinMode(LED_BLUE_PIN_INDEX, PORT_ALT0_FUNC_MODE);
    Delay(DELAY_COUNT);

    /* Restore LED pin to GPIO mode */
    Port_SetPinMode(LED_BLUE_PIN_INDEX, PORT_GPIO_MODE);

    /* Toggle LED to confirm mode change worked */
    for (uint8 i = 0U; i < 5U; i++)
    {
        Led_Toggle();
        Delay(DELAY_COUNT / 3U);
    }
#endif /* PORT_SET_PIN_MODE_API */
}

/**
* @brief Test Port_RefreshPortDirection function
* @details Refresh all pins direction to configured values
*          (excludes pins with direction changeable enabled)
*/
static void Test_Port_RefreshPortDirection(void)
{
    /* First, manually change direction (if allowed) */
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(LED_BLUE_PIN_INDEX, PORT_PIN_IN);
    Delay(DELAY_COUNT / 2U);
#endif

    /* Now refresh port direction - should restore original direction
       Note: Only pins with DirectionChangeable = FALSE will be refreshed */
    Port_RefreshPortDirection();

    /* Toggle LED to confirm refresh worked */
    for (uint8 i = 0U; i < 2U; i++)
    {
        Led_Toggle();
        Delay(DELAY_COUNT);
    }
}

/**
* @brief Test Port_GetVersionInfo function
* @details Get Port driver version information
*/
static void Test_Port_GetVersionInfo(void)
{
#if (STD_ON == PORT_VERSION_INFO_API)
    Std_VersionInfoType versionInfo;

    /* Get version information */
    Port_GetVersionInfo(&versionInfo);

    /* Check version info - blink LED based on major version */
    for (uint8 i = 0U; i < versionInfo.sw_major_version; i++)
    {
        Led_Toggle();
        Delay(DELAY_COUNT / 4U);
        Led_Toggle();
        Delay(DELAY_COUNT / 4U);
    }

    Delay(DELAY_COUNT);
#endif /* PORT_VERSION_INFO_API */
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief Main function - AUTOSAR Port driver test application
*/
int main(void)
{
    /*==========================================================================
    * Test 1: Port_Init
    * - Initialize Port driver with post-build configuration
    * - Configuration defined in Port_VS_0_PBcfg.c
    * - PTD0 (Blue LED) configured as GPIO Output
    *==========================================================================*/
    Test_Port_Init();
    Delay(DELAY_COUNT);

    /*==========================================================================
    * Main test loop
    *==========================================================================*/
    while(1)
    {
        /*======================================================================
        * Test 2: Port_SetPinDirection
        * - Change pin direction at runtime
        * - Requires PORT_SET_PIN_DIRECTION_API = STD_ON
        * - Requires pin's DirectionChangeable = TRUE
        *======================================================================*/
        Test_Port_SetPinDirection();
        Delay(DELAY_COUNT);

        /*======================================================================
        * Test 3: Port_SetPinMode
        * - Change pin mux mode at runtime
        * - Requires PORT_SET_PIN_MODE_API = STD_ON
        * - Requires pin's ModeChangeable = TRUE
        *======================================================================*/
        Test_Port_SetPinMode();
        Delay(DELAY_COUNT);

        /*======================================================================
        * Test 4: Port_RefreshPortDirection
        * - Refresh all pins to configured direction
        * - Excludes pins with DirectionChangeable = TRUE
        *======================================================================*/
        Test_Port_RefreshPortDirection();
        Delay(DELAY_COUNT);

        /*======================================================================
        * Test 5: Port_GetVersionInfo
        * - Get Port driver version information
        * - Requires PORT_VERSION_INFO_API = STD_ON
        *======================================================================*/
        Test_Port_GetVersionInfo();
        Delay(DELAY_COUNT * 2U);
    }

    return 0;
}
