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
*   Description          : Main entry point for Port Driver Test
==================================================================================================*/

/**
*   @file    main_test.c
*
*   @brief   Main entry point for Port Driver Test
*   @details Initializes system and runs all Port driver test cases
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
#include "S32K144.h"
#include "test_port_driver.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief System clock configuration for S32K144
*/
#define FIRC_CLK_FREQ           (48000000U)     /**< @brief FIRC = 48MHz */
#define SIRC_CLK_FREQ           (8000000U)      /**< @brief SIRC = 8MHz */

/**
* @brief LED definitions for test status indication
*/
#define LED_RED_PORT            IP_PORTD
#define LED_RED_GPIO            IP_PTD
#define LED_RED_PIN             (15U)

#define LED_GREEN_PORT          IP_PORTD
#define LED_GREEN_GPIO          IP_PTD
#define LED_GREEN_PIN           (16U)

#define LED_BLUE_PORT           IP_PORTD
#define LED_BLUE_GPIO           IP_PTD
#define LED_BLUE_PIN            (0U)

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void SystemClock_Config(void);
static void LED_Init(void);
static void LED_SetStatus(uint32 passed, uint32 failed);
static void Delay(uint32 count);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/**
* @brief Configure system clock to use FIRC (48MHz)
*/
static void SystemClock_Config(void)
{
    /* FIRC is enabled by default at 48MHz */
    /* Configure FIRC as system clock source */
    
    /* Ensure FIRC is enabled and stable */
    while ((IP_SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) == 0U)
    {
        /* Wait for FIRC to be valid */
    }
    
    /* Configure RUN mode to use FIRC */
    IP_SCG->RCCR = SCG_RCCR_SCS(3U)     |   /* FIRC as system clock */
                   SCG_RCCR_DIVCORE(0U) |   /* CORE_CLK = SYS_CLK / 1 */
                   SCG_RCCR_DIVBUS(0U)  |   /* BUS_CLK = CORE_CLK / 1 */
                   SCG_RCCR_DIVSLOW(1U);    /* FLASH_CLK = CORE_CLK / 2 */
    
    /* Wait for clock switch */
    while ((IP_SCG->CSR & SCG_CSR_SCS_MASK) != SCG_CSR_SCS(3U))
    {
        /* Wait */
    }
}

/**
* @brief Initialize LEDs for test status indication
*/
static void LED_Init(void)
{
    /* Enable clock for PORTD */
    IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    
    /* Configure PTD0, PTD15, PTD16 as GPIO output */
    LED_RED_PORT->PCR[LED_RED_PIN] = PORT_PCR_MUX(1U);      /* GPIO */
    LED_GREEN_PORT->PCR[LED_GREEN_PIN] = PORT_PCR_MUX(1U);  /* GPIO */
    LED_BLUE_PORT->PCR[LED_BLUE_PIN] = PORT_PCR_MUX(1U);    /* GPIO */
    
    /* Set as output */
    LED_RED_GPIO->PDDR |= (1UL << LED_RED_PIN);
    LED_GREEN_GPIO->PDDR |= (1UL << LED_GREEN_PIN);
    LED_BLUE_GPIO->PDDR |= (1UL << LED_BLUE_PIN);
    
    /* Turn off all LEDs (active low) */
    LED_RED_GPIO->PSOR = (1UL << LED_RED_PIN);
    LED_GREEN_GPIO->PSOR = (1UL << LED_GREEN_PIN);
    LED_BLUE_GPIO->PSOR = (1UL << LED_BLUE_PIN);
}

/**
* @brief Set LED status based on test results
* @param passed Number of passed tests
* @param failed Number of failed tests
*/
static void LED_SetStatus(uint32 passed, uint32 failed)
{
    if (failed == 0U)
    {
        /* All tests passed - GREEN LED */
        LED_GREEN_GPIO->PCOR = (1UL << LED_GREEN_PIN);  /* ON */
        LED_RED_GPIO->PSOR = (1UL << LED_RED_PIN);      /* OFF */
    }
    else if (passed == 0U)
    {
        /* All tests failed - RED LED */
        LED_RED_GPIO->PCOR = (1UL << LED_RED_PIN);      /* ON */
        LED_GREEN_GPIO->PSOR = (1UL << LED_GREEN_PIN);  /* OFF */
    }
    else
    {
        /* Mixed results - Both LEDs (appears yellow/orange) */
        LED_RED_GPIO->PCOR = (1UL << LED_RED_PIN);      /* ON */
        LED_GREEN_GPIO->PCOR = (1UL << LED_GREEN_PIN);  /* ON */
    }
}

/**
* @brief Simple software delay
* @param count Delay loop count
*/
static void Delay(uint32 count)
{
    volatile uint32 i;
    for (i = 0U; i < count; i++)
    {
        /* Wait */
    }
}

/*==================================================================================================
*                                       MAIN FUNCTION
==================================================================================================*/

/**
* @brief Main entry point for Port Driver Test
* @details 
*   1. Initialize system clock
*   2. Initialize LEDs for status indication
*   3. Blink Blue LED to indicate test start
*   4. Run all Port driver test cases
*   5. Show test result status on LED:
*      - GREEN: All tests passed
*      - RED: All tests failed
*      - YELLOW (RED+GREEN): Mixed results
*   6. Enter infinite loop
*/
int main(void)
{
    const TestSummary_Type* pSummary;
    uint8 i;
    
    /* Initialize system */
    SystemClock_Config();
    LED_Init();
    
    /* Blink Blue LED to indicate test start */
    for (i = 0U; i < 3U; i++)
    {
        LED_BLUE_GPIO->PCOR = (1UL << LED_BLUE_PIN);    /* ON */
        Delay(500000U);
        LED_BLUE_GPIO->PSOR = (1UL << LED_BLUE_PIN);    /* OFF */
        Delay(500000U);
    }
    
    /* Run all Port driver tests */
    Test_Port_Driver_RunAllTests();
    
    /* Get test summary */
    pSummary = Test_Port_Driver_GetSummary();
    
    /* Set LED status based on results */
    LED_SetStatus(pSummary->passedTests, pSummary->failedTests);
    
    /* Infinite loop - blink status LED */
    while (1)
    {
        if (pSummary->failedTests == 0U)
        {
            /* All passed - slow blink green */
            LED_GREEN_GPIO->PTOR = (1UL << LED_GREEN_PIN);
            Delay(1000000U);
        }
        else
        {
            /* Some failed - fast blink red */
            LED_RED_GPIO->PTOR = (1UL << LED_RED_PIN);
            Delay(250000U);
        }
    }
    
    return 0;
}

#ifdef __cplusplus
}
#endif

/** @} */

/*==================================================================================================
*                                      END OF FILE
==================================================================================================*/
