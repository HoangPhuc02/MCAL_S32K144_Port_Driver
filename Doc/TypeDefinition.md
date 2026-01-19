# Type Definitions

## AUTOSAR Standard Types

| Type | Base Type | Description |
|------|-----------|-------------|
| `uint8` | unsigned char | 8-bit unsigned integer |
| `uint16` | unsigned short | 16-bit unsigned integer |
| `uint32` | unsigned long | 32-bit unsigned integer |
| `boolean` | unsigned char | Boolean type (TRUE/FALSE) |

---

## Port Hardware Driver Types (Port_Hw)

### Enumerations

#### Port_Hw_StatusType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Return status for Port Hardware driver functions.

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_STATUS_SUCCESS` | 0U | Operation completed successfully |
| `PORT_HW_STATUS_ERROR` | 1U | Operation failed with error |

---

#### Port_Hw_PullConfigType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Configuration for internal pull-up/pull-down resistors.

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_PULL_DOWN_ENABLED` | 0U | Internal pull-down resistor enabled |
| `PORT_HW_PULL_UP_ENABLED` | 1U | Internal pull-up resistor enabled |
| `PORT_HW_PULL_NOT_ENABLED` | 2U | Internal pull resistor disabled |

---

#### Port_Hw_MuxType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Configuration for pin multiplexing (alternate function selection).

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_MUX_ALT0` | 0U | Pin disabled or ALT0 (Analog) mode |
| `PORT_HW_MUX_AS_GPIO` | 1U | Pin configured as GPIO |
| `PORT_HW_MUX_ALT2` | 2U | Alternate function 2 |
| `PORT_HW_MUX_ALT3` | 3U | Alternate function 3 |
| `PORT_HW_MUX_ALT4` | 4U | Alternate function 4 |
| `PORT_HW_MUX_ALT5` | 5U | Alternate function 5 |
| `PORT_HW_MUX_ALT6` | 6U | Alternate function 6 |
| `PORT_HW_MUX_ALT7` | 7U | Alternate function 7 |

---

#### Port_Hw_DirectionType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Configuration for GPIO pin direction.

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_PIN_DISABLED` | 0U | Pin disabled (ALT0 mode) |
| `PORT_HW_PIN_IN` | 1U | Pin configured as input |
| `PORT_HW_PIN_OUT` | 2U | Pin configured as output |
| `PORT_HW_PIN_HIGH_Z` | 3U | Pin configured as high impedance |

---

#### Port_Hw_DriveStrengthType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Configuration for output drive strength.

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_DRIVE_STRENGTH_LOW` | 0U | Low drive strength |
| `PORT_HW_DRIVE_STRENGTH_HIGH` | 1U | High drive strength |

---

#### Port_Hw_LockRegisterType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Configuration for pin configuration lock.

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_LOCK_DISABLED` | 0U | Pin configuration is not locked |
| `PORT_HW_LOCK_ENABLED` | 1U | Pin configuration is locked |

---

#### Port_Hw_GlobalControlPinsType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Selection for global pin control (lower or upper 16 pins).

| Enum Value | Value | Description |
|------------|-------|-------------|
| `PORT_HW_GLOBAL_LOWER_HALF` | 0U | Lower 16 pins (0-15) |
| `PORT_HW_GLOBAL_UPPER_HALF` | 1U | Upper 16 pins (16-31) |

---

### Typedef

#### Port_Hw_PinLevelType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

| Type | Base Type | Description |
|------|-----------|-------------|
| `Port_Hw_PinLevelType` | uint8 | Type for representing pin output level (HIGH/LOW) |

---

### Structures

#### Port_Hw_DigitalFilterConfigType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Structure for configuring digital filter on PORT pins.

| Member | Type | Description |
|--------|------|-------------|
| `Port_u8` | uint8 | Digital Filter Port index |
| `Clock_u8` | uint8 | Digital Filter Clock source (0=Bus, 1=LPO) |
| `Width_u8` | uint8 | Digital Filter Width (filter length) |
| `PinMask_u32` | uint32 | Bitmask of pins for which digital filter is enabled |

---

#### Port_Hw_PinSettingsConfigType
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

Main structure for configuring a single PORT pin.

| Member | Type | Description |
|--------|------|-------------|
| `PortBase_ptr` | PORT_Type* | Pointer to PORT peripheral base |
| `GpioBase_ptr` | GPIO_Type* | Pointer to GPIO peripheral base |
| `PinPortIdx_u32` | uint32 | Pin index within the port (0-31) |
| `PullConfig_en` | Port_Hw_PullConfigType | Pull resistor configuration |
| `Mux_en` | Port_Hw_MuxType | Pin mux (alternate function) |
| `Direction_en` | Port_Hw_DirectionType | Pin direction (in/out/high-z) |
| `DriveStrength_en` | Port_Hw_DriveStrengthType | Output drive strength |
| `PassiveFilter_boo` | boolean | Passive filter enable |
| `LockRegister_en` | Port_Hw_LockRegisterType | Configuration lock |
| `DigitalFilter_boo` | boolean | Digital filter enable |
| `InitValue_u8` | Port_Hw_PinLevelType | Initial output value for GPIO |

---

## Macros

### Port Hardware Macros
**File:** [Port_Hw_Types.h](../Board/Driver/HW_Port/Port_Hw_Types.h)

| Macro | Definition | Description |
|-------|------------|-------------|
| `PORT_HW_GET_PORT_U32(channel)` | `((uint32)((uint32)(channel) >> 5U))` | Extract port number from GPIO channel |
| `PORT_HW_GET_PIN_U32(channel)` | `((uint32)((uint32)(channel) & 31U))` | Extract pin number within a port |

---

## NON AUTOSAR Types

*Reserved for custom non-AUTOSAR type definitions*

