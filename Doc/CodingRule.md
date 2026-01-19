## 1. Introduction
### 1.1 
## 2. Naming Convention
### 2.1 Variable/Constant Naming

#### 2.1.1 Avoid usage of '_' in between variable name
**Example:**
_Compliant:_ STATIC unit16 l_ResultBuffer_u16;

_Not compliant:_ STATIC unit16 l_Result_Buffer_u16;

#### 2.1.2 Using label for Variables according to the following scheme

**_Composition of name_** : <prefix >_<Variable name>_<suffix>

**_Spelling of name_** : Clearly convey/describe the functionality/purpose of the variable.

**_Prefix of name_** : prefixed by single keyword describing the scope of the var

**Keyword Scope**
g_ Global/Extern type
l_ Static / File local variables
f_ Function local variables
p_ For parameters of the function (there can be exception for AUTOSAR APIs) (No Prefix) For Structure/Union members

**_Suffix of name_** : Suffixed based on the data type of the var. (Also applies for
Structure/Union Members)

List of common data types used in AUTOSAR MCAL which should be used in variable
names:

| Order | Keyword | Data Type |
|---|---|---|
| 1  | pp  | pointer to pointer
| 2  | ptr | Pointer
| 3  | st  | Structure
| 4  | un  | Union
| 5  | aa  | Array
| 6  | en  | enumerated type
| 7  | u8  | Unsigned int 8
| 8  | u16 | Unsigned int 16
| 9  | u32 | Unsigned int 32
| 10 | c   | Char
| 11 | s   | String
| 12 | fl  | Float
| 13 | db  | Double
| 14 | boo | Boolean
| 15 | s8  | Signed int 8
| 16 | s16 | Signed int 16
| 17 | s32 | Signed int 32
| 18 | dd  | derived data type

**Example:**
Assume that ADC is the module name in below examples

```
- Function local variable of type uint
static uint32 f_Val_u32;
```
```
- static variable of type uint 8
static uint32 l_Var_u8 ;
```

```
- static pointer to type uint
static uint32 *l_PtrName_ptr;
```
```
- global/extern structure
extern AdcConfigType g_AdcConfig_st;
```

#### 2.1.3 All AUTOSAR MCAL Modules shall label global variables according to the following scheme:

**_Composition of name_** : <Module name>_<prefix >_<Variable name>_<suffix>

There should not be any underscore in the ‘ _Variable name_ ’.

_Spelling of name_ : First letter of each word upper case, consecutive letters lower case. The Prefix should be ‘g’ followed by a meaningful variable name. The list of common data types and the corresponding character string, which should be used in variable names mentioned in local variable section holds good for global variables also.

**Example:**
Global/exported variable of type unit
_Compliant:_ extern unit16 Adc_g_Result_u16;

_Not compliant:_ extern unit16 AdcResult_u16;

### 2.2 Function Naming

#### 2.2.1 Global function names follow Camel case convention 
_Composition of name:_ <Module name>_<Function name>

Only **One underscore '_'** between module name and function name. This shall be applicable to static functions which are not specified as part of AUTOSAR spec.

**Example:**
_Compliant:_
Com_NormalReset

_Not compliant:_
com_NormalReset
Com_normalReset
_com_NormalReset
Com_normal_Reset

**Rationale:**
The module to which the function belongs can be understood from its name.

### 2.3 Type Definition Naming

#### 2.3.1 All the Enumeration and Structure should be type casted using typedef keyword.

#### 2.3.2 Prefix not required for Structure/Union members

#### 2.3.3 Enumeration
- Enum shall be Uppercase
- The typedef name and the Enumeration name should be the same, except Enumeration element will have suffix '_t'
- MCAL Modules shall label self-defined i.e. specific data types according to the following 
**_Composition of type_** : <Module name>_<Type name>Type

    - Only one underscore between module name and type name.
    - Spelling of type: First letter of each word upper case, consecutive letters lower case.

**Example:**
_Compliant:_
typedef enum Spi_StatusType_t {
SPI_UNINIT,
SPI_IDLE,
SPI_BUSY
} Spi_StatusType;

Eep_LengthType
Dio_SignalType
Nm_StatusType

#### 2.3.4 Structure 

All structure member should follow this scheme
**_Composition of name_** : <Variable name>_<suffix>

**_Compliant:_**
typedef struct Spi_ConfigType_t {
    Spi_PortType* SpiPort_p;
} Spi_ConfigType;

### 2.4 Macro Naming

#### 2.4.1 CONSTANT DEFINED AS MACRO 
- Shall be written in UPPERCASE
- Digits and underscores are allowed but not at the start. With Exceptions for:


- Macros defined in Compiler.h for identifying the type of Compiler used
Ex: __ICCARM__
- Macros defined in Device header file.
Ex: _SAME_128_PIN_
- Device identification MACRO used as part of Project Pre-processor setting.
Ex: __SAMV71Q21__

**Example:**
_Compliant_ : #define NR_OF_ELEMENTS 10

_Not compliant_ : #define nr_of_elements 10

#### 2.4.2  MACROs and ENUM

MACROs and ENUM items should have **Module name as PREFIX** to avoid using the same name in other
BSW/MCAL Modules.

With Exceptions for:

- Macros defined in Compiler.h for identifying the type of Compiler used
Ex: __ICCARM__
- Macros defined in Device header file.
Ex: _SAME_128_PIN_


- Device identification MACRO used as part of Project Pre-processor setting.
Ex: __SAMV71Q21__

**Example:**
_Compliant_ :
```c
typedef enum Icu_DetectModeType_t
{
    ICU_SYNCHRONOUS = 0u,
    ICU_ASYNCHRONOUS,
}Icu_DetectModeType;

#define ICU_VERSION_INFO_API (STD_ON)
```
_Not compliant_ :
```c
typedef enum Icu_DetectModeType_t
{
SYNCHRONOUS = 0u,
ASYNCHRONOUS,
}Icu_DetectModeType;
#define VERSION_INFO_API (STD_ON)
```

## 3. Coding Style

### 3.1 File Structure
All MCAL Modules shall provide at least the following files:
- Module header file: `<Module name>.h`
- Module source file: `<Module name>.c`
- Module configuration file: `<Module name>_Cfg.h`
- Module configuration parameters: `<Module name>_Cfg.c`
- Module callback header file: `<Module name>_Cbk.h` (if callbacks are provided)
- Module ISR source file: `<Module name>_Irq.c`

**_Header files should not be included back to back (circular inclusion)._**

**Example:**
Gpt.h
Gpt.c
Gpt_Cfg.h
Gpt_Cfg.c
Gpt_Cbk.h
Gpt_Irq.c

### 3.2 Comments
- Comments shall comply with ANSI-C Standard. C++ comments (`//`) are not permitted.
- Use only `/* Comment */` format.
- The condition is repeated as a comment after `#endif`/`#else if`/`#else` for `#if` blocks longer than 10 lines.
**Example:**
#if (CONDITION == TRUE)
/*
more than 10 lines
*/
#else /* (CONDITION == TRUE) */
/*
more than 10 lines
*/
#endif /* (CONDITION == TRUE) */

- Comments generally precede a block of code.
- Use capitalized comment markers:
  - `WARNING:` - alerts a maintainer there is risk in changing code
  - `NOTE:` - provides descriptive comments about the "why"
  - `TODO:` - indicates area under construction
- No code shall be commented out. **Use `#if 0 #endif` to disable code segments temporarily**.

### 3.3 Indentation
- Each level of indentation should align at multiple of **2 spaces** (no Tabs).

**Example:**
_Compliant:_
If(contd1) {
__/*
__Statements #
__*/
} else {
__If(contd2) {
____/*
____Statements #
____*/
__} else {


##### ____/*

```
____Statements #
____*/
__}
}
```

_Non-Compliant:_
If(contd1) {
/*
Statements #
*/
} else {
If(contd2) {
/*
Statements #
*/
} else {
/*
Statements #
*/
}

- The tab character (ASCII 0x09) shall never appear within any source code file.
- Compound statements:
  - Opening left brace at the end of the line beginning the compound statement
  - Closing right brace alone on a line
  - Single statement in control structures shall also be surrounded by braces
- Use proper alignment for multiple arguments in functions and multiple members of Structure/Union.
**Example:**
{
uint32 Hello1; /* Variable #1 */
float HelloWorld2; /* Variable #2 */
Boolean HelloC3; /* Variable #3 */
}
- Within switch statement, case labels shall be aligned; contents of each case block indented once.

**Example:**
```
switch(hello) {
case 0x1:
/* Statements */
break;
case 0x1:
/* Statements */
break;
default:
/* Statements */
break;
}
```
- Whenever a line of code is too long to fit within the maximum line width, indent the second and any subsequent lines in the most readable manner possible
**Example:**
If ((ADC_READY == l_AdcCurrentStatus) && \
(ADC_BUSY == l_AdcCurrentStatus)) {
/*
Statements
*/
}

- The `#` in pre-processor directive shall always be at the start of a line.
**Example:**
If ((ADC_READY == l_AdcCurrentStatus) && \
(ADC_BUSY == l_AdcCurrentStatus)) {
#if (ADC_STATUS_API == STD_ON)
/*
Statements
*/
#else /* if (ADC_STATUS_API == STD_ON)*/
/*
Statements
*/
#endif /* if (ADC_STATUS_API == STD_ON) */
}

### 3.4 White Spaces
**One space shall be used:**
- After keywords: `if`, `while`, `for`, `switch`
- After each comma separating function parameters
- After each semicolon separating statement elements
- Before and after assignment operators: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `~=`, `!=`
- Before and after binary operators: `+`, `-`, `*`, `/`, `%`, `<`, `<=`, `>`, `>=`, `==`, `!=`, `<<`, `>>`, `^`, `&&`, `||`
- Before and after ternary operator characters `?` and `:`

**No spaces shall be used:**
- For unary operators on operand side: `+`, `-`, `++`, `--`, `!`, `~`
- Around structure operators: `->` and `.`
- Around array subscript operator: `[` and `]`
- Adjacent to left and right parenthesis characters
- After semicolon ending statement
- Between pointer operators `*` and `&` and their operands
- Around function call operator parentheses (except one space in function declaration between name and left parenthesis)

### 3.5 Blank Lines
There shall be a blank line before and after each natural block of code (loops, if...else, switch statements, and consecutive declarations).

### 3.6 Miscellaneous
- Maximum line width: **160 characters**
- Use parentheses to ensure proper execution order; each operand of `&&` and `||` operators shall be surrounded by parentheses
- Braces (curly brackets) styles:
  - **Function body:** Both open and close braces in new line
  - **Loops/Conditions:** Open brace on same line, close brace in new line
- When using conditional compilation for `DEV_ERROR_DETECT`, ensure opening and closing braces of last else block are placed **outside** the `#if DEV_ERROR_DETECT` block

## 4. Coding Rules

### 4.1 Conformance to External Rules
- Analyze MISRA warnings and avoid violations through code modifications or document violations with reasons
- All approved MISRA Exceptions should use MISRA Exception MACROs or LDRA exemption comments
- Analyze AUTOSAR C programming guideline violations

### 4.2 Environment
- Software modules must be compiler-independent and platform-independent
- Do not use compiler/platform specific keywords directly - use macros in Compiler.h
- Pre-compile time configuration data captured as #defines or constants
- Compiler specific header files, libraries and intrinsic functions shall not be used directly
- Avoid extensive usage of Assembly language; encapsulate and isolate if needed
- Document assumptions about atomic data access

### 4.3 File Inclusion
- Library header files: use `<>` (e.g., `#include <string.h>`)
- Project header files: use `""` (e.g., `#include "Eep_Read.h"`)
- Each header file shall protect against multiple inclusion
- Each module shall include its own header file and perform SW version check
- Perform Inter Module Checks through pre-processor checks

### 4.4 Comments/Documentation
- Comments in header files should describe externally visible behavior only
- SRS ID should be included as comments for functions, typedefs, macros, variables, loops, conditions

### 4.5 Types
- Use enumeration types instead of integer types/constants for limited choices
- Initialize enum elements by: not specifying any constants, specifying all constants, or specifying only first member
- Do not use integer values of enum elements in calculations
- Use AUTOSAR data types: `uint8`, `uint16`, `uint32`, `sint8`, `sint16`, `sint32`, `uint8_least`, etc.
- Use `Std_ReturnType` for standard API return (E_OK or E_NOT_OK)
- Use `boolean` type (FALSE = 0, TRUE = 1) for logical values
- Use `uint` for loop counter variables

### 4.6 Declarations and Definitions
- Do not use `register` or `auto` storage class specifiers
- Structure/enum type variables shall not be defined in type definition itself - use typedef
- Multiple variable declarations on same line not allowed
- Initialize all variables before use (including static and function local)
- Global/exported objects declared with `extern` only in module header file
- Variables and functions shall not be defined in .h files (exception: inline functions)
- Use `LOCAL_INLINE` macro for inline functions, not compiler-specific keywords
- Function declarations shall have detailed parameter list with identical names in .c and .h files
- Constant parameters should use `const` keyword
- Use `<MODULENAME>_DEV_ERROR_DETECT` naming convention
- Use `volatile` for hardware registers and dual-port memory
- Perform type casting correctly
- Bit-fields shall not be defined within signed integer types
- Place local variables at start of function; static variables at top of file

### 4.7 Control Statement Expressions
- Verify mask values and their impact
- Check for wrong usage of `&&`, `||` in mask operations
- Constants on left of equality operator (e.g., `if (0 == variable)`)
- Consider integer boundaries (overflow/underflow) in arithmetic operations
- Avoid dynamic objects (no `malloc()`)
- No implicit type conversions - use explicit casting
- Do not use bitwise operators with signed integers
- Do not combine signed and unsigned integers in comparisons/expressions

### 4.8 Control Flow
- All `if` statements shall end with `else` clause
- All `switch` statements shall have `default` case implemented
- Verify `break` between each `case` statement
- `for` loops: avoid comma operator in initialization or update clauses

### 4.9 Functions
- All services/APIs shall be multicore re-entrant
- Only one return statement per function (single exit point)
- Functions shall not be defined in .h files (exception: inline functions)
- Local functions shall have `static` storage class specifier

### 4.10 Interrupt Service Routine
- Upon entering ISR: store Interrupt Status Register value and clear all interrupt flags
- Each interrupt flag processing should be in separate `if` condition
- Do not assume only one instance for an interrupt flag set - handle multiple instances

### 4.11 Pointers and Arrays
- Limit extensive usage of pointers
- Check pointers before dereferencing (NULL check)
- Use typedef to simplify function pointer syntax
- Use `Ptr->Field` notation instead of `(*ptr).field`
- Functions shall not call themselves (no recursion)

### 4.12 Structures and Unions
- All structure members shall be named with suffix (no prefix)
- Prevent compiler from inserting padding bytes
- Prevent compiler from altering bit order within bit-fields

### 4.13 Pre-processing Directives
- Replace direct values with macros (#define) or constants (const)
- Use only: `#if`, `#elif`, `#else`, `#endif`, `#define`, `#include`, `#error`
- Exception for `#ifndef` to avoid multiple file inclusion
- Compare compiler switches with defined values (STD_ON/STD_OFF), not `#ifdef`
- Macros used as functions should have function notation
- Macros shall not use global names
- Multi-statement macros shall be encapsulated in curly brackets with `\` at line end
- Avoid explicit casting in macros for parameters
- Use functions instead of parameterized macros when possible
- Published information shall be in all header files
- Token pasting operator (##) can be used to improve readability

### 4.14 Optimization
- Avoid implementations weak against compiler optimization
- Minimize ISR execution time
- Optimize configuration structures (no NULL POINTER for unused items)
- Map pre-processor macros/config data to correct memory section
- Verify all data in RAM and code in FLASH
- Public inline functions should not be under START_SEC_CODE area
- Do not use memory mapping for variables within functions
- Interrupt locks must be < 10μs (target <5μs): no function calls, loops, or branches
- Initialize only configured resources
- Align variables in memory to avoid byte wastage (sort by size: pointers, 32-bit, 16-bit, 8-bit)

### 4.15 Miscellaneous
- No magic numbers - use symbolic values (exceptions: 0 for initialization, 1 for bit ops, constants in math)
- Do not use customer names in source files
- Initialize all STATIC variables during initialization
- Multiple assignments not allowed (e.g., `x = y = z`)
- Limit use of `++` and `--` to simple cases; prefix use forbidden
- No unreachable code, unused variables, unused type declarations, or unused parameters
- All variables shall have defined value before use
- Avoid negative statements in condition checking

## 5. Recommendations for MCAL module development

### 5.1 Tool Usage
- Use Notepad++ for creating/editing source files
- Configure IDE to use 2 spaces instead of Tab
- Enable color and highlighting for readability (grey for comments, blue for keywords)
- Enable "View Spaces/Tabs" to see white spaces and TABs
- Use Beyond Compare for file comparison

### 5.2 Template
- Use standard templates for all source files:
  - Module header file: `Mod.h`
  - Module source file: `Mod.c`
  - Module configuration file: `Mod_Cfg.h`
  - Module configuration parameters: `Mod_Cfg.c`
  - Module ISR source file: `Mod_Irq.c`
  - Module Memmap file: `Mod_MemMap.h`

### 5.3 Project Options
- Use relative path addressing for include paths (not absolute paths)
- Do not suppress compiler errors/warnings - address and fix all
- Group related .h and .c files in neat hierarchy/tree view
- Define symbols as part of project setting (not in source files):
  - Microcontroller variant (e.g., `__SAMV71Q21__`)
  - Code execution memory (e.g., `flash`)
  - Test related macros (e.g., `MCAL_TEST_ENVIRONMENT`)
  - Compiler related macros (e.g., `__ghs__`)
- Enable project options:
  - Require Prototype
  - Optimization: Medium
  - Output file: Executable (not Library)
  - Language: C
  - C dialect: C99
  - Generate Debug Information
- Include standard files, linker scripts, device description files, and flashloader files from project workspace (not from tool installation directory)


