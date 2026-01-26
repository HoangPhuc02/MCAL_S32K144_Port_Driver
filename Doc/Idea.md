# MCAL PORT S32K144 - Development Ideas & Roadmap

## 1. Project Analysis

### 1.1 Current Status Overview

| Component | Status | Completion |
|-----------|--------|------------|
| **HLD (Port.c/h)** | Partial | ~60% |
| **IPW Layer** | Missing | 0% |
| **IPL Layer (Port_Hw)** | Done | ~90% |
| **Configuration (Port_Cfg)** | Empty | 0% |
| **Type Definitions** | Empty | 0% |
| **Standard Types** | Empty | 0% |
| **Det Stub** | Empty | 0% |
| **MemMap** | Missing | 0% |
| **Test Cases** | Partial | ~30% |

### 1.2 AUTOSAR Compliance Gap Analysis

According to **AUTOSAR_SWS_PortDriver R4.4**, the following items are missing or incomplete:

---

## 2. Architecture Options

### 2.1 Option A: With IPW Layer (Like NXP RTD)
```
┌─────────────────────────────────────────────────────────────┐
│                    APPLICATION LAYER                        │
├─────────────────────────────────────────────────────────────┤
│               HIGH LEVEL DRIVER (HLD)                       │
│                     Port.c / Port.h                         │
├─────────────────────────────────────────────────────────────┤
│            INTEGRATION WRAPPER (IPW)  <-- Extra Layer       │
│                Port_Ipw.c / Port_Ipw.h                      │
├─────────────────────────────────────────────────────────────┤
│              IP LEVEL DRIVER (IPL)                          │
│                Port_Hw.c / Port_Hw.h                        │
├─────────────────────────────────────────────────────────────┤
│                   HARDWARE (S32K144)                        │
└─────────────────────────────────────────────────────────────┘
```

**Pros:**
- Exact match with NXP RTD architecture
- Easy to integrate with other RTD modules
- Better abstraction for multi-platform support

**Cons:**
- More complexity
- More files to maintain
- Overkill for single-platform project

---

### 2.2 Option B: WITHOUT IPW Layer (Simplified - RECOMMENDED)
```
┌─────────────────────────────────────────────────────────────┐
│                    APPLICATION LAYER                        │
│                       (main.c)                              │
├─────────────────────────────────────────────────────────────┤
│               HIGH LEVEL DRIVER (HLD)                       │
│                     Port.c / Port.h                         │
│              (AUTOSAR API Implementation)                   │
│                          │                                  │
│                    Direct Call to IPL                       │
│                          ▼                                  │
├─────────────────────────────────────────────────────────────┤
│              IP LEVEL DRIVER (IPL)                          │
│                Port_Hw.c / Port_Hw.h                        │
│            (Direct HW Register Access)                      │
├─────────────────────────────────────────────────────────────┤
│                   HARDWARE (S32K144)                        │
│              PORT/GPIO Registers                            │
└─────────────────────────────────────────────────────────────┘
```

**Pros:**
- Simpler architecture
- Less code to maintain
- Faster development
- Easier to understand and debug
- Good enough for learning AUTOSAR

**Cons:**
- Not exact match with NXP RTD
- Less portable across platforms

---

## 3. Simplified Architecture (No IPW) - Implementation Guide

### 3.1 Required Files Structure
```
MCAL_PORT_S32K144/
├── BSW/
│   └── MCAL/
│       ├── Config/
│       │   ├── Common/
│       │   │   ├── Std_Types.h          [REQUIRED]
│       │   │   ├── Compiler.h           [REQUIRED]
│       │   │   └── Port_MemMap.h        [OPTIONAL - can be empty]
│       │   └── Port/
│       │       ├── Port_Cfg.h           [REQUIRED]
│       │       ├── Port_Cfg.c           [REQUIRED]
│       │       └── Port_PBcfg.c         [OPTIONAL - Post-build]
│       ├── Driver/
│       │   └── Port/
│       │       ├── Port.h               [REQUIRED]
│       │       └── Port.c               [REQUIRED - modify to call Port_Hw directly]
│       └── Stub/
│           ├── Det/
│           │   ├── Det.h                [REQUIRED - simple stub]
│           │   └── Det.c                [REQUIRED - simple stub]
│           └── SchM/
│               └── SchM_Port.h          [OPTIONAL - empty macros]
├── Board/
│   └── Driver/
│       └── HW_Port/
│           ├── Port_Hw_Types.h          [DONE]
│           ├── Port_Hw.h                [DONE]
│           └── Port_Hw.c                [DONE]
└── Test/
    └── test_port_hw.c                   [DONE]
```

### 3.2 How Port.c Should Call Port_Hw Directly

**Current Port.c (with IPW calls - NOT working):**
```c
void Port_Init(const Port_ConfigType * ConfigPtr)
{
    ...
    Port_Ipw_Init(pLocalConfigPtr);  // <-- IPW doesn't exist!
    ...
}
```

**Modified Port.c (direct Port_Hw calls - WORKING):**
```c
#include "Port_Hw.h"  // Include IPL directly

void Port_Init(const Port_ConfigType * ConfigPtr)
{
    ...
    // Convert Port_ConfigType to Port_Hw format and call directly
    Port_Hw_Init(pLocalConfigPtr->u16NumPins, 
                 pLocalConfigPtr->IpConfigPtr);
    ...
}

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    ...
    // Map Pin to PORT/GPIO base and call directly
    PORT_Type* portBase = Port_Hw_g_PortBaseAddr_ptr[PORT_HW_GET_PORT_U32(Pin)];
    GPIO_Type* gpioBase = Port_Hw_g_GpioBaseAddr_ptr[PORT_HW_GET_PORT_U32(Pin)];
    uint32 pinIdx = PORT_HW_GET_PIN_U32(Pin);
    
    Port_Hw_SetPinDirection(gpioBase, pinIdx, (Port_Hw_DirectionType)Direction);
    ...
}
```

---

## 4. Stub Modules Development Strategy

### 4.1 Minimal Stub Approach (RECOMMENDED)
Since the project focuses on PORT only, stub modules should be **minimal but functional**.

### 4.2 Det (Default Error Tracer) Stub

**Det.h:**
```c
/*==================================================================================================
*   @file    Det.h
*   @brief   Default Error Tracer stub for MCAL_PORT_S32K144
==================================================================================================*/
#ifndef DET_H
#define DET_H

#include "Std_Types.h"

/*==================================================================================================
*                              VERSION INFORMATION
==================================================================================================*/
#define DET_VENDOR_ID                       43U
#define DET_AR_RELEASE_MAJOR_VERSION        21U
#define DET_AR_RELEASE_MINOR_VERSION        11U
#define DET_AR_RELEASE_REVISION_VERSION     0U
#define DET_SW_MAJOR_VERSION                1U
#define DET_SW_MINOR_VERSION                0U
#define DET_SW_PATCH_VERSION                0U

/*==================================================================================================
*                              FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief       Reports development error to DET
* @details     Stub implementation - logs error or does nothing
*
* @param[in]   ModuleId   Module ID of calling module
* @param[in]   InstanceId Instance ID
* @param[in]   ApiId      API Service ID
* @param[in]   ErrorId    Error ID
*
* @return      Std_ReturnType
*/
Std_ReturnType Det_ReportError(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
);

/**
* @brief       Reports runtime error to DET
*/
Std_ReturnType Det_ReportRuntimeError(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
);

#endif /* DET_H */
```

**Det.c (Simple Logging Stub):**
```c
/*==================================================================================================
*   @file    Det.c
*   @brief   Default Error Tracer stub implementation
==================================================================================================*/
#include "Det.h"

/*==================================================================================================
*                              LOCAL VARIABLES
==================================================================================================*/
#if defined(DET_ENABLE_LOGGING)
/* Error log buffer for debugging */
typedef struct {
    uint16 ModuleId_u16;
    uint8  InstanceId_u8;
    uint8  ApiId_u8;
    uint8  ErrorId_u8;
} Det_ErrorLogType;

#define DET_MAX_LOG_SIZE    (20U)
static Det_ErrorLogType Det_l_ErrorLog_ast[DET_MAX_LOG_SIZE];
static uint8 Det_l_LogIndex_u8 = 0U;
#endif

/*==================================================================================================
*                              FUNCTION IMPLEMENTATIONS
==================================================================================================*/
Std_ReturnType Det_ReportError(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
)
{
#if defined(DET_ENABLE_LOGGING)
    if (Det_l_LogIndex_u8 < DET_MAX_LOG_SIZE)
    {
        Det_l_ErrorLog_ast[Det_l_LogIndex_u8].ModuleId_u16 = ModuleId;
        Det_l_ErrorLog_ast[Det_l_LogIndex_u8].InstanceId_u8 = InstanceId;
        Det_l_ErrorLog_ast[Det_l_LogIndex_u8].ApiId_u8 = ApiId;
        Det_l_ErrorLog_ast[Det_l_LogIndex_u8].ErrorId_u8 = ErrorId;
        Det_l_LogIndex_u8++;
    }
#else
    /* Suppress unused parameter warnings */
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;
#endif
    
    /* Optional: Breakpoint for debugging */
    /* __BKPT(0); */
    
    return E_OK;
}

Std_ReturnType Det_ReportRuntimeError(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
)
{
    return Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId);
}
```

### 4.3 SchM (Schedule Manager) Stub

**SchM_Port.h (Empty Macros):**
```c
/*==================================================================================================
*   @file    SchM_Port.h
*   @brief   Schedule Manager stub for PORT driver critical sections
==================================================================================================*/
#ifndef SCHM_PORT_H
#define SCHM_PORT_H

/*==================================================================================================
*                              CRITICAL SECTION MACROS
==================================================================================================*/
/* For bare-metal without OS, just disable/enable interrupts */
#define SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00()    __disable_irq()
#define SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00()     __enable_irq()

#define SchM_Enter_Port_PORT_EXCLUSIVE_AREA_01()    __disable_irq()
#define SchM_Exit_Port_PORT_EXCLUSIVE_AREA_01()     __enable_irq()

/* Add more areas as needed... */
#define SchM_Enter_Port_PORT_EXCLUSIVE_AREA_02()    __disable_irq()
#define SchM_Exit_Port_PORT_EXCLUSIVE_AREA_02()     __enable_irq()

#define SchM_Enter_Port_PORT_EXCLUSIVE_AREA_03()    __disable_irq()
#define SchM_Exit_Port_PORT_EXCLUSIVE_AREA_03()     __enable_irq()

/* Or use empty macros if critical sections not needed for testing */
/*
#define SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00()
#define SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00()
*/

#endif /* SCHM_PORT_H */
```

### 4.4 Mcal.h Stub (Optional)

**Mcal.h:**
```c
/*==================================================================================================
*   @file    Mcal.h
*   @brief   MCAL common definitions stub
==================================================================================================*/
#ifndef MCAL_H
#define MCAL_H

#include "Std_Types.h"

#define MCAL_AR_RELEASE_MAJOR_VERSION       21U
#define MCAL_AR_RELEASE_MINOR_VERSION       11U

/* Core ID for single-core MCU */
#define Port_GetCoreID()    ((uint8)0U)

/* Compiler abstraction */
#define FUNC(rettype, memclass)             rettype
#define P2VAR(ptrtype, memclass, ptrclass)  ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#endif /* MCAL_H */
```

---

## 5. Std_Types.h Implementation

```c
/*==================================================================================================
*   @file    Std_Types.h
*   @brief   AUTOSAR Standard Types definitions
==================================================================================================*/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/*==================================================================================================
*                              VERSION INFORMATION
==================================================================================================*/
#define STD_VENDOR_ID                       43U
#define STD_AR_RELEASE_MAJOR_VERSION        21U
#define STD_AR_RELEASE_MINOR_VERSION        11U
#define STD_AR_RELEASE_REVISION_VERSION     0U

/*==================================================================================================
*                              PLATFORM TYPES
==================================================================================================*/
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;

typedef signed char         sint8;
typedef signed short        sint16;
typedef signed long         sint32;
typedef signed long long    sint64;

typedef float               float32;
typedef double              float64;

typedef unsigned char       boolean;

/*==================================================================================================
*                              AUTOSAR STANDARD DEFINITIONS
==================================================================================================*/
#ifndef TRUE
    #define TRUE            (1U)
#endif

#ifndef FALSE
    #define FALSE           (0U)
#endif

#define STD_ON              (1U)
#define STD_OFF             (0U)

#define STD_HIGH            (1U)
#define STD_LOW             (0U)

#define STD_ACTIVE          (1U)
#define STD_IDLE            (0U)

#define E_OK                ((Std_ReturnType)0U)
#define E_NOT_OK            ((Std_ReturnType)1U)

#ifndef NULL_PTR
    #define NULL_PTR        ((void*)0)
#endif

/*==================================================================================================
*                              AUTOSAR TYPES
==================================================================================================*/
typedef uint8 Std_ReturnType;

typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;

/*==================================================================================================
*                              COMPILER ABSTRACTION
==================================================================================================*/
#define AUTOMATIC
#define TYPEDEF
#define STATIC          static
#define INLINE          inline
#define LOCAL_INLINE    static inline

/* Disable intermodule ASR check for simplicity */
#define DISABLE_MCAL_INTERMODULE_ASR_CHECK

#endif /* STD_TYPES_H */
```

---

## 6. Port_Cfg.h Essential Content

```c
/*==================================================================================================
*   @file    Port_Cfg.h
*   @brief   Port driver configuration header
==================================================================================================*/
#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Std_Types.h"
#include "Port_Hw_Types.h"  /* Include IPL types directly */

/*==================================================================================================
*                              VERSION INFORMATION
==================================================================================================*/
#define PORT_CFG_VENDOR_ID_H                    43U
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION_H     21U
#define PORT_CFG_AR_RELEASE_MINOR_VERSION_H     11U
#define PORT_CFG_AR_RELEASE_REVISION_VERSION_H  0U
#define PORT_CFG_SW_MAJOR_VERSION_H             1U
#define PORT_CFG_SW_MINOR_VERSION_H             0U
#define PORT_CFG_SW_PATCH_VERSION_H             0U

/*==================================================================================================
*                              CONFIGURATION SWITCHES
==================================================================================================*/
/** @brief Enable/disable development error detection */
#define PORT_DEV_ERROR_DETECT               (STD_ON)

/** @brief Enable/disable Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API          (STD_ON)

/** @brief Enable/disable Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API               (STD_ON)

/** @brief Enable/disable Port_GetVersionInfo API */
#define PORT_VERSION_INFO_API               (STD_ON)

/** @brief Enable/disable pre-compile configuration */
#define PORT_PRECOMPILE_SUPPORT             (STD_ON)

/** @brief Enable/disable Port_Set2PinsDirection API */
#define PORT_SET_2_PINS_DIRECTION_API       (STD_OFF)

/** @brief Enable/disable Port_SetAsUnusedPin API */
#define PORT_SET_AS_UNUSED_PIN_API          (STD_OFF)

/** @brief Enable/disable Port_ResetPinMode API */
#define PORT_RESET_PIN_MODE_API             (STD_OFF)

/** @brief Enable/disable multicore support */
#define PORT_MULTICORE_ENABLED              (STD_OFF)

/*==================================================================================================
*                              MODULE IDENTIFICATION
==================================================================================================*/
#define PORT_MODULE_ID                      (124U)
#define PORT_INSTANCE_ID                    (0U)
#define PORT_VENDOR_ID                      (43U)

/*==================================================================================================
*                              API SERVICE IDs
==================================================================================================*/
#define PORT_INIT_ID                        (0x00U)
#define PORT_SETPINDIRECTION_ID             (0x01U)
#define PORT_REFRESHPINDIRECTION_ID         (0x02U)
#define PORT_GETVERSIONINFO_ID              (0x03U)
#define PORT_SETPINMODE_ID                  (0x04U)
#define PORT_SETASUNUSEDPIN_ID              (0x05U)
#define PORT_SETASUSEDPIN_ID                (0x06U)
#define PORT_SET2PINSDIRECTION_ID           (0x07U)
#define PORT_RESETPINMODE_ID                (0x08U)

/*==================================================================================================
*                              DET ERROR CODES
==================================================================================================*/
#define PORT_E_PARAM_PIN                    (0x0AU)
#define PORT_E_DIRECTION_UNCHANGEABLE       (0x0BU)
#define PORT_E_INIT_FAILED                  (0x0CU)
#define PORT_E_PARAM_INVALID_MODE           (0x0DU)
#define PORT_E_MODE_UNCHANGEABLE            (0x0EU)
#define PORT_E_UNINIT                       (0x0FU)
#define PORT_E_PARAM_POINTER                (0x10U)
#define PORT_E_PARAM_CONFIG                 (0x12U)

/*==================================================================================================
*                              S32K144 SPECIFIC
==================================================================================================*/
/** @brief Maximum number of pins for S32K144 (5 ports x 32 pins) */
#define PORT_MAX_PIN_PACKAGE_U16            ((uint16)160U)

/** @brief Maximum configured pads */
#define PORT_MAX_CONFIGURED_PADS_U16        ((uint16)5U)  /* Adjust based on config */

/** @brief Number of port partitions (single core = 1) */
#define PORT_MAX_PARTITION                  (1U)

/*==================================================================================================
*                              TYPE DEFINITIONS
==================================================================================================*/
typedef uint16 Port_PinType;
typedef uint8 Port_PinModeType;

typedef enum {
    PORT_PIN_DISABLED = 0U,
    PORT_PIN_IN       = 1U,
    PORT_PIN_OUT      = 2U,
    PORT_PIN_HIGH_Z   = 3U
} Port_PinDirectionType;

/** @brief Pin mode definitions */
#define PORT_ALT0_FUNC_MODE                 ((Port_PinModeType)0U)
#define PORT_GPIO_MODE                      ((Port_PinModeType)1U)
#define PORT_ALT2_FUNC_MODE                 ((Port_PinModeType)2U)
#define PORT_ALT3_FUNC_MODE                 ((Port_PinModeType)3U)
#define PORT_ALT4_FUNC_MODE                 ((Port_PinModeType)4U)
#define PORT_ALT5_FUNC_MODE                 ((Port_PinModeType)5U)
#define PORT_ALT6_FUNC_MODE                 ((Port_PinModeType)6U)
#define PORT_ALT7_FUNC_MODE                 ((Port_PinModeType)7U)

/*==================================================================================================
*                              CONFIGURATION STRUCTURES
==================================================================================================*/
/** @brief Single pin configuration */
typedef struct {
    Port_PinType            Pin_u16;            /**< Pin ID (0-159) */
    uint32                  PcrValue_u32;       /**< PCR register value */
    uint8                   InitValue_u8;       /**< Initial GPIO value */
    Port_PinDirectionType   Direction_en;       /**< Pin direction */
    boolean                 IsGpio_boo;         /**< Is GPIO mode */
    boolean                 DirChangeable_boo;  /**< Direction changeable at runtime */
    boolean                 ModeChangeable_boo; /**< Mode changeable at runtime */
} Port_PinConfigType;

/** @brief Main configuration structure */
typedef struct {
    uint16                              NumPins_u16;        /**< Number of configured pins */
    const Port_PinConfigType*           PinConfig_ptr;      /**< Pointer to pin configs */
    const uint8*                        PartitionList_pu8;  /**< Partition mapping */
    const Port_Hw_PinSettingsConfigType* IpConfig_ptr;      /**< IPL configuration */
} Port_ConfigType;

/*==================================================================================================
*                              EXTERNAL DECLARATIONS
==================================================================================================*/
#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
extern const Port_ConfigType Port_Config;
#endif

#endif /* PORT_CFG_H */
```

---

## 7. Development Roadmap (Simplified - No IPW)

### Phase 1: Foundation (Week 1) - CRITICAL
- [x] Port_Hw (IPL) - DONE
- [ ] Std_Types.h - Create basic types
- [ ] Port_Cfg.h - Configuration macros and types
- [ ] Det.h/Det.c - Simple stub

### Phase 2: Core HLD (Week 2) - HIGH
- [ ] Port.h - Complete header with API declarations
- [ ] Port.c - Modify to call Port_Hw directly (remove IPW calls)
- [ ] Port_Cfg.c - Sample pin configuration

### Phase 3: Integration (Week 3) - MEDIUM
- [ ] SchM_Port.h - Empty macros for critical sections
- [ ] Update main.c - Demo using Port API
- [ ] Integration test

### Phase 4: Polish (Week 4) - LOW
- [ ] Complete Doxygen comments
- [ ] MISRA-C check (optional)
- [ ] Documentation

---

## 8. Quick Reference: Port.c Modification

**Key changes needed in Port.c to remove IPW dependency:**

```c
/* BEFORE (with IPW): */
#include "Port_Ipw.h"
void Port_Init(...) { Port_Ipw_Init(ConfigPtr); }

/* AFTER (direct to IPL): */
#include "Port_Hw.h"
void Port_Init(...) { 
    Port_Hw_Init(ConfigPtr->NumPins_u16, ConfigPtr->IpConfig_ptr); 
}
```

---

## 9. Summary: Files to Create/Modify

| File | Action | Priority |
|------|--------|----------|
| Std_Types.h | CREATE | HIGH |
| Port_Cfg.h | CREATE | HIGH |
| Port_Cfg.c | CREATE | HIGH |
| Det.h | CREATE | HIGH |
| Det.c | CREATE | HIGH |
| Port.h | CREATE | HIGH |
| Port.c | MODIFY | HIGH |
| SchM_Port.h | CREATE | MEDIUM |
| Mcal.h | CREATE | LOW |
| Port_MemMap.h | CREATE | LOW |

---

## 10. Notes

### Current Issues:
1. ✅ Port_Hw (IPL) - DONE
2. ❌ Port.c calls Port_Ipw_* but IPW doesn't exist
3. ❌ Port.h is empty
4. ❌ Port_Cfg.h is empty
5. ❌ Std_Types.h is empty
6. ❌ Det stub is empty

### Decision Made:
**Use Option B (No IPW Layer)** for simplicity. Port.c will call Port_Hw directly.

### Next Steps:
1. Create Std_Types.h
2. Create Port_Cfg.h with configuration
3. Create Det stub
4. Complete Port.h
5. Modify Port.c to use Port_Hw directly

---

## 11. Complete Stub Modules List (Reference: NXP RTD Port_Example_S32K144)

Dựa trên phân tích project mẫu **Port_Example_S32K144** từ NXP RTD 1.0.1, để xây dựng một ví dụ hoàn chỉnh cho Port driver, cần có các stub modules sau:

### 11.1 Stub Modules Overview

| # | Module | Files | Priority | Description |
|---|--------|-------|----------|-------------|
| 1 | **Det** | Det.h, Det.c | HIGH | Default Error Tracer - báo cáo lỗi development/runtime |
| 2 | **SchM_Port** | SchM_Port.h, SchM_Port.c | HIGH | Schedule Manager - quản lý critical sections |
| 3 | **OsIf** | OsIf.h, OsIf.c, OsIf_Cfg.h | MEDIUM | OS Interface - timer, delay, interrupt abstraction |
| 4 | **Mcal** | Mcal.h | HIGH | MCAL common definitions - Core ID, compiler abstraction |
| 5 | **Std_Types** | Std_Types.h | HIGH | AUTOSAR Standard Types |
| 6 | **Platform_Types** | Platform_Types.h | MEDIUM | Platform-specific types |
| 7 | **Compiler** | Compiler.h, Compiler_Cfg.h | MEDIUM | Compiler abstraction macros |
| 8 | **MemMap** | Port_MemMap.h, Rte_MemMap.h | LOW | Memory mapping sections |
| 9 | **Mcu** | Mcu.h (stub) | MEDIUM | MCU driver stub - clock initialization |
| 10 | **Dio** | Dio.h (stub) | LOW | DIO driver stub - optional for testing |

### 11.2 Dependency Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                           APPLICATION                                │
│                            (main.c)                                  │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   ┌─────────┐      ┌─────────────┐      ┌──────────────┐            │
│   │   Mcu   │      │    Port     │      │     Dio      │            │
│   │ (stub)  │      │  (target)   │      │   (stub)     │            │
│   └────┬────┘      └──────┬──────┘      └──────────────┘            │
│        │                  │                                          │
├────────┴──────────────────┼──────────────────────────────────────────┤
│                           │                                          │
│            COMMON STUB MODULES (Required by Port)                    │
│                           │                                          │
│   ┌───────────────────────┼───────────────────────────────────┐     │
│   │                       │                                    │     │
│   │  ┌─────────┐    ┌─────┴─────┐    ┌────────────┐           │     │
│   │  │   Det   │    │ SchM_Port │    │   OsIf     │           │     │
│   │  │ (stub)  │    │  (stub)   │    │  (stub)    │           │     │
│   │  └────┬────┘    └─────┬─────┘    └──────┬─────┘           │     │
│   │       │               │                 │                  │     │
│   └───────┴───────────────┴─────────────────┴──────────────────┘     │
│                           │                                          │
├───────────────────────────┼──────────────────────────────────────────┤
│                           │                                          │
│            BASE TYPES & PLATFORM ABSTRACTION                         │
│                           │                                          │
│   ┌───────────────────────┼───────────────────────────────────┐     │
│   │                       │                                    │     │
│   │  ┌─────────────┐  ┌───┴────┐  ┌──────────┐  ┌──────────┐ │     │
│   │  │ Std_Types.h │  │ Mcal.h │  │Compiler.h│  │ MemMap.h │ │     │
│   │  └─────────────┘  └────────┘  └──────────┘  └──────────┘ │     │
│   │                                                           │     │
│   └───────────────────────────────────────────────────────────┘     │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

### 11.3 Detailed Stub Specifications

#### 11.3.1 Det Stub (Default Error Tracer)
**Location:** `BSW/MCAL/Stub/Det/`

**Purpose:** Captures and reports development/runtime errors from MCAL modules.

**API Functions (Required):**
```c
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);
```

**Stub Implementation Strategy:**
- Simple: Return E_OK, do nothing
- Debug: Log errors to buffer/UART for debugging
- Breakpoint: Halt on error for debugging

---

#### 11.3.2 SchM_Port Stub (Schedule Manager)
**Location:** `BSW/MCAL/Stub/SchM/`

**Purpose:** Provides critical section protection (Enter/Exit exclusive areas).

**API Functions (Required for Port):**
```c
void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00(void);  // ... up to _27
void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00(void);   // ... up to _27
```

**Stub Implementation Strategy:**

**Option A - Simple (No OS, No Nesting):**
```c
#define SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00()    __disable_irq()
#define SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00()     __enable_irq()
```

**Option B - With Reentry Guard (Recommended):**
```c
static volatile uint32 reentry_guard_00 = 0;
static volatile uint32 msr_00 = 0;

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00(void) {
    uint32 msr = __get_PRIMASK();
    if (ISR_ON(msr)) {
        __disable_irq();
    }
    msr_00 = msr;
    reentry_guard_00++;
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00(void) {
    reentry_guard_00--;
    if (reentry_guard_00 == 0U && ISR_ON(msr_00)) {
        __enable_irq();
    }
}
```

**Note:** RTD uses 28 exclusive areas (00-27) for Port. For simplicity, implement only what Port.c uses.

---

#### 11.3.3 OsIf Stub (OS Interface)
**Location:** `BSW/MCAL/Stub/OsIf/`

**Purpose:** Provides OS abstraction for timers, delays, and counters.

**API Functions:**
```c
void OsIf_Init(const void* Config);
uint32 OsIf_GetCounter(OsIf_CounterType SelectedCounter);
uint32 OsIf_GetElapsed(uint32* const CurrentRef, OsIf_CounterType SelectedCounter);
void OsIf_SetTimerFrequency(uint32 Freq);
uint32 OsIf_MicrosToTicks(uint32 Micros, OsIf_CounterType SelectedCounter);
void OsIf_SuspendAllInterrupts(void);
void OsIf_ResumeAllInterrupts(void);
```

**Stub Implementation Strategy (Bare-metal SysTick):**
```c
void OsIf_Init(const void* Config) {
    (void)Config;
    /* SysTick already initialized by startup */
}

uint32 OsIf_GetCounter(OsIf_CounterType SelectedCounter) {
    (void)SelectedCounter;
    return SysTick->VAL;  /* Or use a simple counter */
}

void OsIf_SuspendAllInterrupts(void) {
    __disable_irq();
}

void OsIf_ResumeAllInterrupts(void) {
    __enable_irq();
}
```

---

#### 11.3.4 Mcal.h Stub
**Location:** `BSW/MCAL/Config/Common/`

**Purpose:** Common MCAL definitions, compiler abstraction, Core ID.

**Essential Content:**
```c
#ifndef MCAL_H
#define MCAL_H

#include "Std_Types.h"

/* Platform definition */
#define MCAL_PLATFORM_ARM
#define MCAL_ARM_MARCH   /* Cortex-M4 */

/* Version */
#define MCAL_AR_RELEASE_MAJOR_VERSION    4
#define MCAL_AR_RELEASE_MINOR_VERSION    4

/* Core ID for single-core S32K144 */
#define OsIf_GetCoreID()    ((uint32)0U)

/* Compiler abstraction */
#define FUNC(rettype, memclass)              rettype
#define P2VAR(ptrtype, memclass, ptrclass)   ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const
#define P2FUNC(rettype, ptrclass, fctname)   rettype (*fctname)
#define VAR(type, memclass)                  type

/* Cortex-M4 intrinsics */
#if defined(__GNUC__)
    #define ASM_KEYWORD  __asm
#elif defined(__ICCARM__)
    #define ASM_KEYWORD  __asm
#endif

/* Get PRIMASK for critical sections */
static inline uint32 Mcal_GetPrimask(void) {
    uint32 result;
    ASM_KEYWORD volatile ("MRS %0, primask" : "=r" (result));
    return result;
}

static inline void Mcal_SetPrimask(uint32 primask) {
    ASM_KEYWORD volatile ("MSR primask, %0" :: "r" (primask) : "memory");
}

#endif /* MCAL_H */
```

---

#### 11.3.5 Mcu Stub (Optional - for complete example)
**Location:** `BSW/MCAL/Stub/Mcu/`

**Purpose:** Minimal MCU stub for clock initialization.

**API Functions (Minimal):**
```c
void Mcu_Init(const Mcu_ConfigType* ConfigPtr);
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);
Mcu_PllStatusType Mcu_GetPllStatus(void);
Std_ReturnType Mcu_DistributePllClock(void);
void Mcu_SetMode(Mcu_ModeType McuMode);
```

**Stub Strategy:** 
- Return success without doing anything
- Or use direct register writes for basic clock setup

---

### 11.4 Recommended Stub File Structure

```
MCAL_PORT_S32K144/
├── BSW/
│   └── MCAL/
│       ├── Config/
│       │   └── Common/
│       │       ├── Std_Types.h           ✅ [Required]
│       │       ├── Platform_Types.h      ⚠️ [Optional - can merge into Std_Types]
│       │       ├── Compiler.h            ⚠️ [Optional - can merge into Mcal.h]
│       │       ├── Compiler_Cfg.h        ⚠️ [Optional]
│       │       ├── Mcal.h                ✅ [Required]
│       │       ├── Port_MemMap.h         ⚠️ [Optional - empty]
│       │       └── Rte_MemMap.h          ⚠️ [Optional - empty]
│       └── Stub/
│           ├── Det/
│           │   ├── Det.h                 ✅ [Required]
│           │   └── Det.c                 ✅ [Required]
│           ├── SchM/
│           │   ├── SchM_Port.h           ✅ [Required]
│           │   └── SchM_Port.c           ✅ [Required]
│           ├── OsIf/
│           │   ├── OsIf.h                ⚠️ [Medium - for timeout]
│           │   ├── OsIf.c                ⚠️ [Medium - for timeout]
│           │   └── OsIf_Cfg.h            ⚠️ [Medium]
│           └── Mcu/
│               ├── Mcu.h                 ⚡ [Low - for complete example]
│               └── Mcu.c                 ⚡ [Low - for complete example]
```

### 11.5 Minimum Viable Stubs (MVP)

Để Port driver có thể compile và chạy, **tối thiểu** cần:

| # | File | Reason |
|---|------|--------|
| 1 | **Std_Types.h** | Base types (uint8, uint16, Std_ReturnType, etc.) |
| 2 | **Mcal.h** | OsIf_GetCoreID() macro, compiler abstraction |
| 3 | **Det.h + Det.c** | Det_ReportError() cho PORT_DEV_ERROR_DETECT |
| 4 | **SchM_Port.h + SchM_Port.c** | Critical section functions (Enter/Exit) |

**Total: 5 files minimum**

---

### 11.6 Stub Implementation Priority

| Phase | Files | Goal |
|-------|-------|------|
| **Phase 1** | Std_Types.h, Mcal.h, Det.h/c, SchM_Port.h/c | Port.c compiles |
| **Phase 2** | OsIf.h/c, OsIf_Cfg.h | Timeout support |
| **Phase 3** | Mcu.h/c (stub), MemMap files | Complete example |
| **Phase 4** | Dio.h/c (stub) | LED toggle demo |

---

### 11.7 Reference Files from RTD

Các file tham khảo từ **Port_Example_S32K144/RTD/**:

| RTD File | Our Stub | Notes |
|----------|----------|-------|
| `RTD/include/Det.h` | `Stub/Det/Det.h` | Simplify, remove unused features |
| `RTD/src/Det.c` | `Stub/Det/Det.c` | Simplify to logging only |
| `RTD/include/SchM_Port.h` | `Stub/SchM/SchM_Port.h` | Keep function declarations |
| `RTD/src/SchM_Port.c` | `Stub/SchM/SchM_Port.c` | Simplify, keep critical section logic |
| `RTD/include/OsIf.h` | `Stub/OsIf/OsIf.h` | Simplify for bare-metal |
| `RTD/src/OsIf_Timer.c` | `Stub/OsIf/OsIf.c` | Basic SysTick-based timer |
| `generate/include/OsIf_Cfg.h` | `Stub/OsIf/OsIf_Cfg.h` | Configuration defines |

---

### 11.8 Quick Reference: RTD Exclusive Areas Used by Port

From `SchM_Port.h`, Port driver uses these exclusive areas:
- `PORT_EXCLUSIVE_AREA_00` to `PORT_EXCLUSIVE_AREA_27` (28 areas total)

For simplified stub, implement only what Port.c actually uses (check Port.c for actual usage).

---

## 12. Action Plan for Stub Development

### Step 1: Analyze Port.c Dependencies
```bash
grep -E "SchM_Enter|SchM_Exit|Det_Report|OsIf_" Port.c
```

### Step 2: Create Minimum Stubs
1. `Std_Types.h` - Copy from template
2. `Mcal.h` - Core ID + compiler macros
3. `Det.h/c` - Simple logging stub
4. `SchM_Port.h/c` - Interrupt disable/enable

### Step 3: Verify Compilation
```bash
# Try to compile Port.c with stubs
gcc -c Port.c -I../Config/Common -I../Stub/Det -I../Stub/SchM
```

### Step 4: Add Optional Stubs
- OsIf (if timeout needed)
- Mcu (for complete main.c example)
- Dio (for LED demo)

---

*Last Updated: January 20, 2026*

