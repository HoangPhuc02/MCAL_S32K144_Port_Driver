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
* @file           Compiler.h
* @implements     Compiler.h_Artifact
* @brief          AUTOSAR Compiler abstraction
* @details        Provides macros for the encapsulation of definitions and declarations
*
* @addtogroup     BASE_COMPONENT
* @{
*/

#ifndef COMPILER_H
#define COMPILER_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Compiler_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief Parameters that shall be published within the Compiler header file
*/
#define COMPILER_VENDOR_ID                      43U
#define COMPILER_MODULE_ID                      198U
#define COMPILER_AR_RELEASE_MAJOR_VERSION       21U
#define COMPILER_AR_RELEASE_MINOR_VERSION       11U
#define COMPILER_AR_RELEASE_REVISION_VERSION    0U
#define COMPILER_SW_MAJOR_VERSION               1U
#define COMPILER_SW_MINOR_VERSION               0U
#define COMPILER_SW_PATCH_VERSION               0U

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
*                               General Definitions
-------------------------------------------------------------------------------------------------*/
/**
* @brief AUTOMATIC keyword - Used for local non static variables
*/
#define AUTOMATIC

/**
* @brief TYPEDEF keyword - Used within type definitions
*/
#define TYPEDEF

/**
* @brief STATIC keyword - Used for file local variables
*/
#define STATIC          static

/**
* @brief NULL_PTR define with a void pointer
*/
#ifndef NULL_PTR
    #define NULL_PTR    ((void *)0)
#endif

/**
* @brief INLINE keyword abstraction
*/
#define INLINE          inline

/**
* @brief LOCAL_INLINE keyword - static inline abstraction
*/
#define LOCAL_INLINE    static inline

/*-------------------------------------------------------------------------------------------------
*                               Compiler Specific Keywords
-------------------------------------------------------------------------------------------------*/
#if defined(__GNUC__)
    /**
    * @brief GCC compiler detected
    */
    #define _GREENHILLS_C_S32K1XX_
    #define ASM_KEYWORD         __asm
    #define INTERRUPT_FUNC      __attribute__((interrupt))
    
#elif defined(__ICCARM__)
    /**
    * @brief IAR compiler detected
    */
    #define _IAR_C_S32K1XX_
    #define ASM_KEYWORD         __asm
    #define INTERRUPT_FUNC      __irq
    
#elif defined(__DCC__)
    /**
    * @brief Diab compiler detected
    */
    #define _DIABDATA_C_S32K1XX_
    #define ASM_KEYWORD         __asm
    #define INTERRUPT_FUNC      __interrupt__
    
#else
    /**
    * @brief Default/Unknown compiler
    */
    #define ASM_KEYWORD         __asm
    #define INTERRUPT_FUNC
#endif

/*-------------------------------------------------------------------------------------------------
*                               Function Definition Macros
-------------------------------------------------------------------------------------------------*/
/**
* @brief FUNC macro for declaring functions
* @details Syntax: FUNC(return_type, memory_class) function_name(parameters)
*
* @param[in] rettype     Return type of the function
* @param[in] memclass    Memory classification for the function
*/
#define FUNC(rettype, memclass)                 rettype

/**
* @brief FUNC_P2CONST macro for functions returning pointer to constant
*/
#define FUNC_P2CONST(rettype, ptrclass, memclass) \
        const rettype *

/**
* @brief FUNC_P2VAR macro for functions returning pointer to variable
*/
#define FUNC_P2VAR(rettype, ptrclass, memclass) \
        rettype *

/*-------------------------------------------------------------------------------------------------
*                               Pointer Definition Macros
-------------------------------------------------------------------------------------------------*/
/**
* @brief P2VAR macro for declaring pointer to variable
* @details Syntax: P2VAR(ptr_type, ptr_mem_class, ptr_def_mem_class) pointer_name
*
* @param[in] ptrtype     Type of the pointed data
* @param[in] memclass    Memory classification for the pointer
* @param[in] ptrclass    Memory classification for the pointer definition
*/
#define P2VAR(ptrtype, memclass, ptrclass)      ptrtype *

/**
* @brief P2CONST macro for declaring pointer to constant
* @details Syntax: P2CONST(ptr_type, ptr_mem_class, ptr_def_mem_class) pointer_name
*
* @param[in] ptrtype     Type of the pointed data
* @param[in] memclass    Memory classification for the pointer
* @param[in] ptrclass    Memory classification for the pointer definition
*/
#define P2CONST(ptrtype, memclass, ptrclass)    const ptrtype *

/**
* @brief CONSTP2VAR macro for declaring constant pointer to variable
*/
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/**
* @brief CONSTP2CONST macro for declaring constant pointer to constant
*/
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

/**
* @brief P2FUNC macro for declaring pointer to function
* @details Syntax: P2FUNC(return_type, ptr_mem_class, function_name)(parameters)
*/
#define P2FUNC(rettype, ptrclass, fctname)      rettype (*fctname)

/**
* @brief CONSTP2FUNC macro for declaring constant pointer to function
*/
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

/*-------------------------------------------------------------------------------------------------
*                               Variable Definition Macros
-------------------------------------------------------------------------------------------------*/
/**
* @brief VAR macro for declaring variables
* @details Syntax: VAR(var_type, mem_class) variable_name
*
* @param[in] vartype     Type of the variable
* @param[in] memclass    Memory classification for the variable
*/
#define VAR(vartype, memclass)                  vartype

/**
* @brief CONST macro for declaring constants
* @details Syntax: CONST(const_type, mem_class) constant_name
*/
#define CONST(consttype, memclass)              const consttype

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

#endif /* COMPILER_H */
