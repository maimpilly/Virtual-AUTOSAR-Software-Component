// File: Std_Types.h

#ifndef STD_TYPES_H
#define STD_TYPES_H

// Basic AUTOSAR types
#define FALSE   0
#define TRUE    1

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef uint8          boolean;

// Standard return type for RTE functions
typedef uint8 Std_ReturnType;
#define RTE_E_OK 0x00

#endif // STD_TYPES_H