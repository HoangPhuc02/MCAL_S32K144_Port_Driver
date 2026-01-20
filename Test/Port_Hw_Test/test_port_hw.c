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
*   @file    test_port_hw.c
*
*   @brief   Test file for Port Hardware Abstraction Layer
*   @details This file contains test functions and examples for Port_Hw driver.
*            Demonstrates how to use the Port_Hw API for GPIO configuration and control.
*
*   @addtogroup Port_HW_Test
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
#define TEST_PORT_HW_VENDOR_ID_C                    43
#define TEST_PORT_HW_AR_RELEASE_MAJOR_VERSION_C     21
#define TEST_PORT_HW_AR_RELEASE_MINOR_VERSION_C     11
#define TEST_PORT_HW_AR_RELEASE_REVISION_VERSION_C  0
#define TEST_PORT_HW_SW_MAJOR_VERSION_C             1
#define TEST_PORT_HW_SW_MINOR_VERSION_C             0
#define TEST_PORT_HW_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief LED pin definitions for S32K144 EVB
* @details PTD15 - RED LED, PTD16 - GREEN LED, PTD0 - BLUE LED
*/
#define TEST_LED_RED_PORT           PORTD
#define TEST_LED_RED_GPIO           PTD
#define TEST_LED_RED_PIN            (15U)

#define TEST_LED_GREEN_PORT         PORTD
#define TEST_LED_GREEN_GPIO         PTD
#define TEST_LED_GREEN_PIN          (16U)

#define TEST_LED_BLUE_PORT          PORTD
#define TEST_LED_BLUE_GPIO          PTD
#define TEST_LED_BLUE_PIN           (0U)

/**
* @brief Button pin definitions for S32K144 EVB
* @details PTC12 - SW2, PTC13 - SW3
*/
#define TEST_BTN_SW2_PORT           PORTC
#define TEST_BTN_SW2_GPIO           PTC
#define TEST_BTN_SW2_PIN            (12U)

#define TEST_BTN_SW3_PORT           PORTC
#define TEST_BTN_SW3_GPIO           PTC
#define TEST_BTN_SW3_PIN            (13U)

/**
* @brief Number of pins in test configuration
*/
#define TEST_PIN_CONFIG_COUNT       (5U)

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
/**
* @brief Pin configuration array for test
*/
static const Port_Hw_PinSettingsConfigType l_TestPinConfig_ast[TEST_PIN_CONFIG_COUNT] =
{
    /* LED RED - PTD15 - Output, Active Low */
    {
        .PortBase_ptr       = TEST_LED_RED_PORT,
        .GpioBase_ptr       = TEST_LED_RED_GPIO,
        .PinPortIdx_u32     = TEST_LED_RED_PIN,
        .PullConfig_en      = PORT_HW_PULL_NOT_ENABLED,
        .Mux_en             = PORT_HW_MUX_AS_GPIO,
        .Direction_en       = PORT_HW_PIN_OUT,
        .DriveStrength_en   = PORT_HW_DRIVE_STRENGTH_HIGH,
        .PassiveFilter_boo  = FALSE,
        .LockRegister_en    = PORT_HW_LOCK_DISABLED,
        .DigitalFilter_boo  = FALSE,
        .InitValue_u8       = 1U    /* LED OFF (active low) */
    },
    /* LED GREEN - PTD16 - Output, Active Low */
    {
        .PortBase_ptr       = TEST_LED_GREEN_PORT,
        .GpioBase_ptr       = TEST_LED_GREEN_GPIO,
        .PinPortIdx_u32     = TEST_LED_GREEN_PIN,
        .PullConfig_en      = PORT_HW_PULL_NOT_ENABLED,
        .Mux_en             = PORT_HW_MUX_AS_GPIO,
        .Direction_en       = PORT_HW_PIN_OUT,
        .DriveStrength_en   = PORT_HW_DRIVE_STRENGTH_HIGH,
        .PassiveFilter_boo  = FALSE,
        .LockRegister_en    = PORT_HW_LOCK_DISABLED,
        .DigitalFilter_boo  = FALSE,
        .InitValue_u8       = 1U    /* LED OFF (active low) */
    },
    /* LED BLUE - PTD0 - Output, Active Low */
    {
        .PortBase_ptr       = TEST_LED_BLUE_PORT,
        .GpioBase_ptr       = TEST_LED_BLUE_GPIO,
        .PinPortIdx_u32     = TEST_LED_BLUE_PIN,
        .PullConfig_en      = PORT_HW_PULL_NOT_ENABLED,
        .Mux_en             = PORT_HW_MUX_AS_GPIO,
        .Direction_en       = PORT_HW_PIN_OUT,
        .DriveStrength_en   = PORT_HW_DRIVE_STRENGTH_HIGH,
        .PassiveFilter_boo  = FALSE,
        .LockRegister_en    = PORT_HW_LOCK_DISABLED,
        .DigitalFilter_boo  = FALSE,
        .InitValue_u8       = 1U    /* LED OFF (active low) */
    },
    /* Button SW2 - PTC12 - Input with Pull-up */
    {
        .PortBase_ptr       = TEST_BTN_SW2_PORT,
        .GpioBase_ptr       = TEST_BTN_SW2_GPIO,
        .PinPortIdx_u32     = TEST_BTN_SW2_PIN,
        .PullConfig_en      = PORT_HW_PULL_UP_ENABLED,
        .Mux_en             = PORT_HW_MUX_AS_GPIO,
        .Direction_en       = PORT_HW_PIN_IN,
        .DriveStrength_en   = PORT_HW_DRIVE_STRENGTH_LOW,
        .PassiveFilter_boo  = TRUE,     /* Enable passive filter for debounce */
        .LockRegister_en    = PORT_HW_LOCK_DISABLED,
        .DigitalFilter_boo  = TRUE,     /* Enable digital filter for debounce */
        .InitValue_u8       = 0U
    },
    /* Button SW3 - PTC13 - Input with Pull-up */
    {
        .PortBase_ptr       = TEST_BTN_SW3_PORT,
        .GpioBase_ptr       = TEST_BTN_SW3_GPIO,
        .PinPortIdx_u32     = TEST_BTN_SW3_PIN,
        .PullConfig_en      = PORT_HW_PULL_UP_ENABLED,
        .Mux_en             = PORT_HW_MUX_AS_GPIO,
        .Direction_en       = PORT_HW_PIN_IN,
        .DriveStrength_en   = PORT_HW_DRIVE_STRENGTH_LOW,
        .PassiveFilter_boo  = TRUE,
        .LockRegister_en    = PORT_HW_LOCK_DISABLED,
        .DigitalFilter_boo  = TRUE,
        .InitValue_u8       = 0U
    }
};

/**
* @brief Digital filter configuration for buttons
*/
static const Port_Hw_DigitalFilterConfigType l_BtnFilterConfig_st =
{
    .Port_u8     = 2U,          /* Port C index */
    .Clock_u8    = 0U,          /* Bus clock source */
    .Width_u8    = 31U,         /* Maximum filter width for debounce */
    .PinMask_u32 = (1UL << TEST_BTN_SW2_PIN) | (1UL << TEST_BTN_SW3_PIN)
};

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void Test_PortHw_SimpleDelay(uint32 Count_u32);
static Port_Hw_StatusType Test_PortHw_InitPins(void);
static void Test_PortHw_LedControl(void);
static void Test_PortHw_ButtonRead(void);
static void Test_PortHw_LedToggle(void);
static void Test_PortHw_RuntimeMuxChange(void);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief       Simple software delay
* @details     Blocking delay using a decrement loop
*
* @param[in]   Count_u32  Number of loop iterations
*
* @return      void
*/
static void Test_PortHw_SimpleDelay(uint32 Count_u32)
{
    volatile uint32 f_Counter_u32 = Count_u32;
    
    while (f_Counter_u32 > 0U)
    {
        f_Counter_u32--;
    }
}

/**
* @brief       Initialize all test pins
* @details     Uses Port_Hw_Init to configure LEDs and buttons
*
* @return      Port_Hw_StatusType
* @retval      PORT_HW_STATUS_SUCCESS  Initialization successful
* @retval      PORT_HW_STATUS_ERROR    Initialization failed
*/
static Port_Hw_StatusType Test_PortHw_InitPins(void)
{
    Port_Hw_StatusType f_Status_en;
    
    /* Initialize all pins using configuration array */
    f_Status_en = Port_Hw_Init(TEST_PIN_CONFIG_COUNT, l_TestPinConfig_ast);
    
    /* Configure digital filter for buttons */
    if (PORT_HW_STATUS_SUCCESS == f_Status_en)
    {
        Port_Hw_ConfigDigitalFilter(TEST_BTN_SW2_PORT, &l_BtnFilterConfig_st);
    }
    
    return f_Status_en;
}

/**
* @brief       Test LED control functions
* @details     Demonstrates Port_Hw_WritePin usage for LED on/off control
*
* @return      void
*/
static void Test_PortHw_LedControl(void)
{
    /* Turn ON RED LED (active low - write 0) */
    Port_Hw_WritePin(TEST_LED_RED_GPIO, TEST_LED_RED_PIN, 0U);
    Test_PortHw_SimpleDelay(500000U);
    
    /* Turn OFF RED LED */
    Port_Hw_WritePin(TEST_LED_RED_GPIO, TEST_LED_RED_PIN, 1U);
    Test_PortHw_SimpleDelay(500000U);
    
    /* Turn ON GREEN LED */
    Port_Hw_WritePin(TEST_LED_GREEN_GPIO, TEST_LED_GREEN_PIN, 0U);
    Test_PortHw_SimpleDelay(500000U);
    
    /* Turn OFF GREEN LED */
    Port_Hw_WritePin(TEST_LED_GREEN_GPIO, TEST_LED_GREEN_PIN, 1U);
    Test_PortHw_SimpleDelay(500000U);
    
    /* Turn ON BLUE LED */
    Port_Hw_WritePin(TEST_LED_BLUE_GPIO, TEST_LED_BLUE_PIN, 0U);
    Test_PortHw_SimpleDelay(500000U);
    
    /* Turn OFF BLUE LED */
    Port_Hw_WritePin(TEST_LED_BLUE_GPIO, TEST_LED_BLUE_PIN, 1U);
}

/**
* @brief       Test button read functions
* @details     Demonstrates Port_Hw_ReadPin usage for button state reading.
*              When button is pressed, turn on corresponding LED.
*
* @return      void
*/
static void Test_PortHw_ButtonRead(void)
{
    uint8 f_Sw2State_u8;
    uint8 f_Sw3State_u8;
    
    /* Read button states (active low - 0 when pressed) */
    f_Sw2State_u8 = Port_Hw_ReadPin(TEST_BTN_SW2_GPIO, TEST_BTN_SW2_PIN);
    f_Sw3State_u8 = Port_Hw_ReadPin(TEST_BTN_SW3_GPIO, TEST_BTN_SW3_PIN);
    
    /* SW2 controls RED LED */
    if (0U == f_Sw2State_u8)
    {
        /* Button pressed - turn ON LED */
        Port_Hw_WritePin(TEST_LED_RED_GPIO, TEST_LED_RED_PIN, 0U);
    }
    else
    {
        /* Button released - turn OFF LED */
        Port_Hw_WritePin(TEST_LED_RED_GPIO, TEST_LED_RED_PIN, 1U);
    }
    
    /* SW3 controls GREEN LED */
    if (0U == f_Sw3State_u8)
    {
        Port_Hw_WritePin(TEST_LED_GREEN_GPIO, TEST_LED_GREEN_PIN, 0U);
    }
    else
    {
        Port_Hw_WritePin(TEST_LED_GREEN_GPIO, TEST_LED_GREEN_PIN, 1U);
    }
}

/**
* @brief       Test LED toggle function
* @details     Demonstrates Port_Hw_TogglePin usage for blinking LED
*
* @return      void
*/
static void Test_PortHw_LedToggle(void)
{
    uint8 f_LoopCount_u8;
    
    /* Blink BLUE LED 10 times */
    for (f_LoopCount_u8 = 0U; f_LoopCount_u8 < 20U; f_LoopCount_u8++)
    {
        Port_Hw_TogglePin(TEST_LED_BLUE_GPIO, TEST_LED_BLUE_PIN);
        Test_PortHw_SimpleDelay(200000U);
    }
}

/**
* @brief       Test runtime mux change
* @details     Demonstrates Port_Hw_SetMuxModeSel for runtime pin reconfiguration
*
* @return      void
*/
static void Test_PortHw_RuntimeMuxChange(void)
{
    /* Disable RED LED pin (set to analog/disabled mode) */
    Port_Hw_SetMuxModeSel(TEST_LED_RED_PORT, TEST_LED_RED_PIN, PORT_HW_MUX_ALT0);
    Test_PortHw_SimpleDelay(500000U);
    
    /* Re-enable RED LED pin as GPIO */
    Port_Hw_SetMuxModeSel(TEST_LED_RED_PORT, TEST_LED_RED_PIN, PORT_HW_MUX_AS_GPIO);
    
    /* Set direction back to output */
    Port_Hw_SetPinDirection(TEST_LED_RED_GPIO, TEST_LED_RED_PIN, PORT_HW_PIN_OUT);
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief       Main test function for Port_Hw driver
* @details     Executes all test cases for Port Hardware driver:
*              1. Pin initialization test
*              2. LED control test (WritePin)
*              3. Button read test (ReadPin)
*              4. LED toggle test (TogglePin)
*              5. Runtime mux change test (SetMuxModeSel)
*
* @return      Port_Hw_StatusType
* @retval      PORT_HW_STATUS_SUCCESS  All tests passed
* @retval      PORT_HW_STATUS_ERROR    Test failed
*/
Port_Hw_StatusType Test_PortHw_RunAllTests(void)
{
    Port_Hw_StatusType f_Status_en = PORT_HW_STATUS_SUCCESS;
    
    /*=========================================================================
     * Test 1: Initialize pins
     *=========================================================================*/
    f_Status_en = Test_PortHw_InitPins();
    
    if (PORT_HW_STATUS_SUCCESS != f_Status_en)
    {
        return PORT_HW_STATUS_ERROR;
    }
    
    /*=========================================================================
     * Test 2: LED control using WritePin
     *=========================================================================*/
    Test_PortHw_LedControl();
    
    /*=========================================================================
     * Test 3: LED toggle using TogglePin
     *=========================================================================*/
    Test_PortHw_LedToggle();
    
    /*=========================================================================
     * Test 4: Runtime mux change
     *=========================================================================*/
    Test_PortHw_RuntimeMuxChange();
    
    return f_Status_en;
}

/**
* @brief       Test function with button polling
* @details     Continuously polls buttons and controls LEDs accordingly.
*              This function runs in an infinite loop.
*
* @return      void (never returns)
*/
void Test_PortHw_ButtonPollingLoop(void)
{
    /* Initialize pins first */
    (void)Test_PortHw_InitPins();
    
    /* Infinite loop polling buttons */
    while (1U)
    {
        Test_PortHw_ButtonRead();
        Test_PortHw_SimpleDelay(10000U);    /* Small delay for debounce */
    }
}

/**
* @brief       Example: Configure single pin at runtime
* @details     Demonstrates how to configure a single pin without using Init function
*
* @param[in]   Port_ptr      Pointer to PORT peripheral
* @param[in]   Gpio_ptr      Pointer to GPIO peripheral
* @param[in]   Pin_u32       Pin number (0-31)
* @param[in]   IsOutput_boo  TRUE for output, FALSE for input
*
* @return      void
*/
void Test_PortHw_ConfigureSinglePin(
    PORT_Type* Port_ptr,
    GPIO_Type* Gpio_ptr,
    uint32 Pin_u32,
    boolean IsOutput_boo
)
{
    /* Step 1: Set pin mux to GPIO */
    Port_Hw_SetMuxModeSel(Port_ptr, Pin_u32, PORT_HW_MUX_AS_GPIO);
    
    /* Step 2: Set pin direction */
    if (TRUE == IsOutput_boo)
    {
        Port_Hw_SetPinDirection(Gpio_ptr, Pin_u32, PORT_HW_PIN_OUT);
        
        /* Step 3: Set initial output value (HIGH) */
        Port_Hw_WritePin(Gpio_ptr, Pin_u32, 1U);
    }
    else
    {
        Port_Hw_SetPinDirection(Gpio_ptr, Pin_u32, PORT_HW_PIN_IN);
        
        /* Enable digital filter for input pin */
        Port_Hw_EnableDigitalFilter(Port_ptr, Pin_u32);
    }
}

/**
* @brief       Example: Global pin control usage
* @details     Demonstrates how to configure multiple pins at once using global control
*
* @return      void
*/
void Test_PortHw_GlobalControlExample(void)
{
    uint16 f_PinMask_u16;
    uint16 f_ConfigValue_u16;
    
    /* Configure pins 0-3 of PORTD as GPIO outputs */
    f_PinMask_u16 = 0x000FU;    /* Pins 0, 1, 2, 3 */
    
    /* Build configuration value:
     * - MUX = 1 (GPIO)
     * - DSE = 1 (High drive strength)
     * - PE = 0, PS = 0 (No pull)
     */
    f_ConfigValue_u16 = PORT_PCR_MUX(1U) | PORT_PCR_DSE(1U);
    
    /* Apply configuration to lower half pins */
    Port_Hw_SetGlobalPinControl(PORTD, f_PinMask_u16, f_ConfigValue_u16, PORT_HW_GLOBAL_LOWER_HALF);
}

#ifdef __cplusplus
}
#endif

/** @} */
