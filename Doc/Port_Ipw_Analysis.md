# Port_Ipw và Port_Ci_Port_Ip - Phân tích mối quan hệ

## 📌 Tổng quan

Tài liệu này mô tả mối quan hệ giữa lớp **Port_Ipw (Integration Port Wrapper)** và lớp **Port_Ci_Port_Ip (IP Driver)** trong kiến trúc AUTOSAR Port Driver của NXP RTD.

---

## 📌 Các điểm gọi từ `Port_Ipw.c` tới `Port_Ci_Port_Ip`

### 1. `Port_Ipw_Init()` - Cấu hình Digital Filter (Line ~413-414)

```c
/* Set digital filter clock and width for the current port */
Port_Ci_Port_Ip_ConfigDigitalFilter(Port_au32PortCiPortBaseAddr[u8Port], &(pConfigPtr->pDigitalFilterConfig[u16PinIndex]));
```

### 2. `Port_Ipw_Init()` - Khởi tạo Pins (Line ~420)

```c
(void)Port_Ci_Port_Ip_Init(NUM_OF_CONFIGURED_PINS, pConfigPtr->IpConfigPtr);
```

---

## 📌 Các biến toàn cục được sử dụng chung

Port_Ipw sử dụng **trực tiếp** các mảng base address được khai báo trong `Port_Ci_Port_Ip.c`:

```c
// Khai báo trong Port_Ci_Port_Ip.c
PORT_Type * Port_au32PortCiPortBaseAddr[PORT_INSTANCE_COUNT] = IP_PORT_BASE_PTRS;
GPIO_Type * Port_au32PortCiGpioBaseAddr[GPIO_INSTANCE_COUNT] = IP_GPIO_BASE_PTRS;

// Export trong Port_Ci_Port_Ip.h
extern PORT_Type * Port_au32PortCiPortBaseAddr[5];
extern GPIO_Type * Port_au32PortCiGpioBaseAddr[5];
```

### Các register được truy cập trực tiếp:

| Register | Mục đích |
|----------|----------|
| `PDDR` | Port Data Direction Register - Thiết lập hướng pin (Input/Output) |
| `PIDR` | Port Input Disable Register - Disable input cho HIGH-Z mode |
| `PSOR` | Port Set Output Register - Set pin HIGH |
| `PCOR` | Port Clear Output Register - Set pin LOW |
| `PCR[n]` | Pin Control Register - Cấu hình mux, pull, drive strength, lock |
| `DFER` | Digital Filter Enable Register - Enable digital filter |

---

## 📌 Các macro từ `Port_Ci_Port_Ip_Types.h`

```c
// Macro để lấy Port index từ channel number (mỗi port có 32 pins)
#define GPIO_PORT_U32(channel)      ((uint32)((uint32)(channel) >> 5))

// Macro để lấy Pin index trong port (0-31)
#define GPIO_CHANNEL_U32(channel)   ((uint32)((uint32)(channel) & (uint32)31))
```

---

## 📊 Bảng tổng kết: Port_Ipw gọi tới Port_Ci_Port_Ip

| Function trong Port_Ipw | Gọi tới Port_Ci_Port_Ip | Mục đích |
|------------------------|-------------------------|----------|
| `Port_Ipw_Init()` | `Port_Ci_Port_Ip_ConfigDigitalFilter()` | Cấu hình digital filter clock và width |
| `Port_Ipw_Init()` | `Port_Ci_Port_Ip_Init()` | Khởi tạo tất cả configured pins |

---

## ⚠️ Quan trọng - Những function Port_Ipw KHÔNG gọi Port_Ci_Port_Ip

Các function trong `Port_Ipw` thao tác **TRỰC TIẾP register** thông qua `Port_au32PortCiGpioBaseAddr[]` và `Port_au32PortCiPortBaseAddr[]` mà **KHÔNG** gọi qua function của `Port_Ci_Port_Ip`:

| Function | Thao tác trực tiếp |
|----------|-------------------|
| `Port_Ipw_Init_UnusedPins()` | PDDR, PIDR, PSOR, PCOR, PCR |
| `Port_Ipw_SetPinDirection()` | PDDR, PIDR |
| `Port_Ipw_Set2PinsSamePort()` | PDDR, PIDR |
| `Port_Ipw_Set2PinsDifferentPorts()` | PDDR, PIDR |
| `Port_Ipw_SetPinMode()` | PCR |
| `Port_Ipw_RefreshPortDirection()` | PDDR, PIDR |
| `Port_Ipw_SetAsUnusedPin()` | PDDR, PIDR, PSOR, PCOR, PCR |
| `Port_Ipw_SetAsUsedPin()` | PDDR, PIDR, PSOR, PCOR, PCR |
| `Port_Ipw_ResetPinMode()` | PDDR, PIDR, PCR |

---

## 📐 Kiến trúc NXP RTD Port Driver (3 layers)

```
+--------------------------------------------------+
|                    Port.c (HLD)                  |
|              AUTOSAR High Level Driver           |
+--------------------------------------------------+
                        |
                        v
+--------------------------------------------------+
|                  Port_Ipw.c (IPW)                |
|           Integration Port Wrapper               |
|    - Xử lý logic, validation, DET               |
|    - Gọi IP driver hoặc truy cập trực tiếp HW   |
+--------------------------------------------------+
                        |
                        v
+--------------------------------------------------+
|              Port_Ci_Port_Ip.c (IP)              |
|              IP Driver (Low Level)               |
|    - Khởi tạo pins với PinInit                  |
|    - Cấu hình digital filter                    |
|    - Set mux mode                               |
+--------------------------------------------------+
                        |
                        v
+--------------------------------------------------+
|               Hardware Registers                 |
|        PORT_Type, GPIO_Type (S32K144)           |
+--------------------------------------------------+
```

---

## 🎯 Kết luận cho việc thiết kế Port_Hw

Khi thiết kế `Port_Hw` để thay thế `Port_Ci_Port_Ip` + `Port_Ipw`, cần:

1. **Giữ lại các function cốt lõi:**
   - `PortHw_Init()` - thay thế `Port_Ci_Port_Ip_Init()`
   - `PortHw_SetMuxModeSel()` - thay thế `Port_Ci_Port_Ip_SetMuxModeSel()`
   - `PortHw_SetPinDirection()` - thay thế logic trong `Port_Ipw_SetPinDirection()`

2. **Loại bỏ Digital Filter** (theo yêu cầu):
   - Không cần `Port_Ci_Port_Ip_ConfigDigitalFilter()`
   - Không cần `Port_Ci_Port_Ip_EnableDigitalFilter()`
   - Không cần `Port_Ci_Port_Ip_DisableDigitalFilter()`

3. **Khai báo base address arrays riêng:**
   ```c
   PORT_Type* const PortHw_g_PortBaseAddr_ptr[5];
   GPIO_Type* const PortHw_g_GpioBaseAddr_ptr[5];
   ```

4. **Macro tương đương:**
   ```c
   #define PORT_HW_GET_PORT_U32(channel)   ((uint32)((uint32)(channel) >> 5U))
   #define PORT_HW_GET_PIN_U32(channel)    ((uint32)((uint32)(channel) & 31U))
   ```

---

## 📝 Lịch sử cập nhật

| Ngày | Mô tả |
|------|-------|
| 2026-01-27 | Tạo tài liệu phân tích ban đầu |
