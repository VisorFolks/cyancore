/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: ctype.h
 * Description		: This file contains prototypes of libc-ctypes
 *			  functions
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#include <stdbool.h>

bool isWhitespace(int);
bool isSpace(int);
bool isLowercase(int);
bool isUppercase(int);
bool isDigit(int);
bool isAlpha(int);
bool isAlphaNumeric(int);
bool isHexDigit(int);
bool isGraph(int);
bool isControl(int);
bool isPrintable(int);
bool isPunct(int);
bool isASCII(int);
int toLowercase(int);
int toUppercase(int);
