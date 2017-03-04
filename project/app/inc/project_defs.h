#ifndef __PROJECT_DEFS_H__
#define __PROJECT_DEFS_H__

#include <stddef.h>
#include <stdio.h>

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

#endif // __PROJECT_DEFS_H__
