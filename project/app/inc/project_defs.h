#ifndef __PROJECT_DEFS_H__
#define __PROJECT_DEFS_H__

#include <stddef.h>

// Return values used throughout the project
#define INVALID_PARAM 2
#define NULL_POINTER 1
#define SUCCESS 0

#define CHECK_NULL(x) if(x == NULL) return NULL_POINTER

#endif
