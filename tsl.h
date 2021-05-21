#pragma once

/*
3.7.33.31
*/

/*
precomp.h:

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#include "precomp.h"

typedef uint64_t(*decrypt_func)(uint64_t);

struct tsl {
//	decrypt_func func;
};

int tsl_init(struct tsl *tsl);
void tsl_finit(struct tsl *tsl);

