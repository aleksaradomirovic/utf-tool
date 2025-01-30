/*
 * SPDX-License-Identifier: 0BSD
 * Copyright (C) 2025 Aleksa Radomirovic
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

typedef int_least32_t utf32_t;

unsigned int mcharw(const char * mchar);
utf32_t mchar(const char * str, const char ** next);
