#ifndef __PROJECT_DEFS_H__
#define __PROJECT_DEFS_H__

#include <stddef.h>
#include <stdio.h>
#include "log.h"

// Return values used throughout the project
#define FAILURE (4)
#define INVALID_PARAM (2)
#define NULL_POINTER (1)
#define SUCCESS (0)

// Null pointer check macro
#define CHECK_NULL(x) if(x == NULL) return NULL_POINTER

// Define a macro for logging depending on platform
#ifndef FRDM
#define PRINTF(...) printf(__VA_ARGS__);
#else
#define PRINTF(...)
#endif // FRDM

// Used to set pins to the correct settings
#define ALT_1 (1)
#define ALT_2 (2)
#define ALT_3 (3)
#define ALT_4 (4)
#define ALT_5 (5)

#endif // __PROJECT_DEFS_H__
